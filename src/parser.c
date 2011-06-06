/**
* \file parser.c
*
* HL7 message parser.
*
* \internal
* Copyright (c) 2003-2011 \b Erlar (http://erlar.com)
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/buffer.h>
#include <hl7parser/defs.h>
#include <hl7parser/element.h>
#include <hl7parser/export.h>
#include <hl7parser/format.h>
#include <hl7parser/parser.h>
#include <hl7parser/settings.h>
#include <hl7parser/stack.h>
#include <hl7parser/token.h>
#include <hl7parser/lexer.h>
#include <stdlib.h>
#include <string.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_parser_init( HL7_Parser *parser, HL7_Settings *settings )
{
    HL7_ASSERT( parser != 0 );
    HL7_ASSERT( settings != 0 );

    parser->settings        = settings;
    parser->user_data       = 0;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_parser_fini( HL7_Parser *parser )
{
    HL7_ASSERT( parser != 0 );

    memset( parser, 0, sizeof ( HL7_Parser ) );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void *hl7_parser_user_data( HL7_Parser *parser )
{
    HL7_ASSERT( parser != 0 );

    return parser->user_data;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_parser_set_user_data( HL7_Parser *parser, void *user_data )
{
    HL7_ASSERT( parser != 0 );

    parser->user_data = user_data;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_parser_read( HL7_Parser *parser, HL7_Message *message, HL7_Buffer *buffer )
{
    int                 rc = 0;
    HL7_Element_Type    current_type;
    HL7_Element_Type    element_type;
    HL7_Token           token;
    HL7_Node            fake_head;
    HL7_Node            *node;
    HL7_Node            *tmp;
    HL7_Stack           node_stack;

    HL7_ASSERT( parser != 0 );
    HL7_ASSERT( message != 0 );
    HL7_ASSERT( buffer != 0 );

#define APPEND_SIBLING( node_stack, node )                                                              \
        hl7_node_append_sibling( (HL7_Node *) *( (void **) hl7_stack_top( &(node_stack) ) ), (node) );  \

#define APPEND_CHILD( node_stack, node )                                                                \
        hl7_node_append_child( (HL7_Node *) *( (void **) hl7_stack_top( &(node_stack) ) ), (node) );    \

    /*
    if ( first_chunk )
    {
    */
    hl7_lexer_init( &parser->lexer, parser->settings, buffer );

    parser->prev_type = HL7_ELEMENT_SEGMENT;

    hl7_stack_init( &node_stack, HL7_ELEMENT_TYPE_COUNT + 1, sizeof ( HL7_Node * ) );

    /* We create a fake head node for the message to simplify the message creation routine. */
    hl7_node_init( &fake_head );
    hl7_token_set( &token, hl7_buffer_rd_ptr( buffer ), hl7_buffer_length( buffer ), HL7_TOKEN_ATTR_SEPARATOR );
    hl7_element_set( &fake_head.element, &token, false );
    hl7_message_set_head( message, &fake_head );

    node = &fake_head;
    hl7_stack_push( &node_stack, &node );
    /* } */

    /* FIXME: check lexer error codes. */
    while ( hl7_lexer_read( &parser->lexer, &token ) == 0 && parser->lexer.state != HL7_LEXER_STATE_END )
    {
        if ( token.attr & HL7_TOKEN_ATTR_SEPARATOR )
        {
            current_type = hl7_element_type( parser->settings, *token.value );

            /* We found a separator that is a direct child of the previous one. */
            if ( current_type == parser->prev_type )
            {
                node = hl7_message_create_node( message );
                hl7_element_set( &node->element, &parser->characters_token, false );

                APPEND_SIBLING( node_stack, node );

                /* hl7_stack_pop( &node_stack, 0 ); */
                hl7_stack_pop( &node_stack, &tmp );
                hl7_stack_push( &node_stack, &node );
            }
            /* We found a separator that is an indirect descendant of the previous one. */
            else if ( hl7_is_descendant_type( current_type, parser->prev_type ) )
            {
                token.value     = 0;
                token.length    = 0;

                for ( element_type = parser->prev_type;
                      element_type != HL7_ELEMENT_INVALID && element_type != current_type;
                      element_type = hl7_child_type( element_type ) )
                {
                    node = hl7_message_create_node( message );
                    hl7_element_set( &node->element, &token, false );

                    if ( element_type == parser->prev_type )
                    {
                        APPEND_SIBLING( node_stack, node );

                        /* hl7_stack_pop( &node_stack, 0 ); */
                        hl7_stack_pop( &node_stack, &tmp );
                    }
                    else
                    {
                        APPEND_CHILD( node_stack, node );
                    }

                    hl7_stack_push( &node_stack, &node );
                }

                node = hl7_message_create_node( message );
                hl7_element_set( &node->element, &parser->characters_token, false );

                APPEND_CHILD( node_stack, node );

                hl7_stack_push( &node_stack, &node );

                parser->prev_type = current_type;
            }
            /* We found a separator that is a parent of the previous one. */
            else
            {
                node = hl7_message_create_node( message );
                hl7_element_set( &node->element, &parser->characters_token, false );

                APPEND_SIBLING( node_stack, node );

                for ( element_type = hl7_parent_type( parser->prev_type );
                      element_type != HL7_ELEMENT_INVALID && element_type != hl7_parent_type( current_type );
                      element_type = hl7_parent_type( element_type ) )
                {
                    /* hl7_stack_pop( &node_stack, 0 ); */
                    hl7_stack_pop( &node_stack, &tmp );
                }
                parser->prev_type = current_type;
            }
        }
        else
        {
            hl7_token_copy( &parser->characters_token, &token );
        }
    }

    /*
    if ( last_chunk )
    {
    */
    /* We remove the fake head node from the message. */
    message->head = message->head->sibling;

    hl7_stack_fini( &node_stack );

    hl7_lexer_fini( &parser->lexer );

    parser->prev_type = HL7_ELEMENT_SEGMENT;
    /* } */

#undef APPEND_CHILD
#undef APPEND_SIBLING

    return rc;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_parser_write( HL7_Parser *parser, HL7_Buffer *buffer, HL7_Message *message )
{
    int         rc      = 0;
    HL7_Node    *node   = message->head;

    while ( node != 0 && rc == 0 )
    {
        rc      = hl7_parser_write_segment_node( parser, buffer, node->children );
        node    = node->sibling;
    }
    return rc;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_parser_write_segment( HL7_Parser *parser, HL7_Buffer *buffer, HL7_Segment *segment )
{
    return hl7_parser_write_segment_node( parser, buffer, segment->head );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_parser_write_segment_node( HL7_Parser *parser, HL7_Buffer *buffer, HL7_Node *node )
{
    int rc = 0;

    if ( node != 0 )
    {
        /* Copy the segment ID. */
        rc = hl7_buffer_copy( buffer, node->element.value, node->element.length );
        if ( rc == 0 )
        {
            /* If we are writing the MSH segment, we skip the second sibling (field separator). */
            if ( hl7_element_strcmp( &node->element, "MSH" ) == 0 )
            {
                node = node->sibling;
            }

            if ( node != 0 && node->sibling != 0 )
            {
                rc = hl7_buffer_copy_char( buffer, hl7_separator( parser->settings, HL7_ELEMENT_FIELD ) );
                if ( rc == 0 )
                {
                    rc = hl7_parser_write_node( parser, buffer, node->sibling, HL7_ELEMENT_FIELD );
                }
            }
            if ( rc == 0 )
            {
                /* Write segment terminator. */
                rc = hl7_buffer_copy_char( buffer, hl7_separator( parser->settings, HL7_ELEMENT_SEGMENT ) );
            }
        }
    }
    return rc;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_parser_write_node( HL7_Parser *parser, HL7_Buffer *buffer,
                                      HL7_Node *node, HL7_Element_Type element_type )
{
    int rc = 0;

    while ( node != 0 && rc == 0 )
    {
        /* The only nodes that contain character elements are the ones in which node->children is 0. */
        if ( node->children == 0 )
        {
            if ( node->element.value != 0 && node->element.length > 0 )
            {
                rc = hl7_buffer_copy( buffer, node->element.value, node->element.length );
            }
        }
        else
        {
            rc = hl7_parser_write_node( parser, buffer, node->children, hl7_child_type( element_type ) );
        }

        if ( rc != 0 )
        {
            break;
        }

        /*
        * We only write an ending separator when there is no sibling or when
        * we're dealing with a segment. We treat the segments differently because
        * they are the topmost elements and are always terminated.
        */
        if ( node->sibling != 0 || element_type == HL7_ELEMENT_SEGMENT )
        {
            rc = hl7_buffer_copy_char( buffer, hl7_separator( parser->settings, element_type ) );
        }

        node = node->sibling;
    }
    return rc;
}

END_C_DECL()
