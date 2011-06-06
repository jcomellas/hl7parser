/**
* \file message.c
*
* HL7 message data types and functions.
*
* \internal
* Copyright (c) 2003-2011 \b Erlar (http://erlar.com)
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/alloc.h>
#include <hl7parser/element.h>
#include <hl7parser/export.h>
#include <hl7parser/message.h>
#include <hl7parser/node.h>
#include <hl7parser/segment.h>
#include <stdarg.h>
#include <string.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_message_init( HL7_Message *message, HL7_Settings *settings,
                                  HL7_Allocator *allocator )
{
    HL7_ASSERT( message != 0 );
    HL7_ASSERT( allocator != 0 );

    message->head       = 0;
    message->settings   = settings;
    message->allocator  = allocator;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_message_reset( HL7_Message *message, HL7_Settings *settings,
                                   HL7_Allocator *allocator )
{
    HL7_ASSERT( message != 0 );
    HL7_ASSERT( allocator != 0 );

    if ( message->head != 0 )
    {
        hl7_message_destroy_branch( message, message->head, true );
    }

    message->head       = 0;
    message->settings   = settings;
    message->allocator  = allocator;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_message_fini( HL7_Message *message )
{
    HL7_ASSERT( message != 0 );

    if ( message->head != 0 )
    {
        hl7_message_destroy_branch( message, message->head, true );
    }

    message->head       = 0;
    message->settings   = 0;
    message->allocator  = 0;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Node *hl7_message_head( HL7_Message *message )
{
    HL7_ASSERT( message != 0 );

    return message->head;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_message_set_head( HL7_Message *message, HL7_Node *head )
{
    HL7_ASSERT( message != 0 );

    if ( message->head != 0 )
    {
        hl7_message_destroy_branch( message, message->head, true );
    }
    message->head = head;
}

/* ------------------------------------------------------------------------ */
HL7_Node *hl7_message_create_node( HL7_Message *message )
{
    HL7_ASSERT( message != 0 );

    return hl7_node_create( message->allocator );
}

/* ------------------------------------------------------------------------ */
void hl7_message_destroy_node( HL7_Message *message, HL7_Node *node )
{
    HL7_ASSERT( message != 0 );

    return hl7_node_destroy( node, message->allocator );
}

/* ------------------------------------------------------------------------ */
void hl7_message_destroy_branch( HL7_Message *message, HL7_Node *node, const bool destroy_siblings )
{
    HL7_ASSERT( message != 0 );

    return hl7_node_destroy_branch( node, message->allocator, destroy_siblings );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Node *hl7_message_node( HL7_Message *message, HL7_Element_Type element_type, ... )
{
    HL7_Node    *node;
    va_list     ap;

    HL7_ASSERT( message != 0 );

    va_start( ap, element_type );

    node = hl7_message_node_va( message, element_type, ap );

    va_end( ap );

    return node;
}

/* ------------------------------------------------------------------------ */
HL7_Node *hl7_message_node_va( HL7_Message *message, HL7_Element_Type element_type, va_list ap )
{
    HL7_Node    *node = message->head;
    size_t      position;
    int         i;

    HL7_ASSERT( element_type >= HL7_ELEMENT_SUBCOMPONENT && element_type <= HL7_ELEMENT_SEGMENT );

    /*
    * The structure of the HL7 element tree is the following. Vertical
    * arrows indicate a sibling relationship (i.e. elements of the same type).
    * Horizontal arrows indicate a parent-child relationship (i.e. subelements).
    *
    * 0/Segment 0 -> 0/Segment ID
    *    |                |
    *    |           1/Field 0 -> Repetition 0 -> Component 0 -> Subcomponent 0
    *    |                |            |              |                |
    *    |                |            |              |          Subcomponent n
    *    |                |            |              |
    *    |                |            |          Component n -> Subcomponent 0
    *    |                |            |                               |
    *    |                |            |                         Subcomponent n
    *    |                |            |
    *    |                |       Repetition n -> Component 0 -> Subcomponent 0
    *    |                |                           |                |
    *    |                |                           |          Subcomponent n
    *    |                |                           |
    *    |                |                       Component n -> Subcomponent 0
    *    |                |                                            |
    *    |                |                                      Subcomponent n
    *    |                |
    *    |         n+1/Field n -> Repetition 0 -> Component 0 -> Subcomponent 0
    *    |                             |              |                |
    *    |                             |              |          Subcomponent n
    *    |                             |              |
    *    |                             |          Component n -> Subcomponent 0
    *    |                             |                                |
    *    |                             |                         Subcomponent n
    *    |                             |
    *    |                        Repetition n -> Component 0 -> Subcomponent 0
    *    |                                            |                |
    *    |                                            |          Subcomponent n
    *    |                                            |
    *    |                                        Component n -> Subcomponent 0
    *    |                                                             |
    *    |                                                       Subcomponent n
    *    |
    * n/Segment n ...
    *
    * As we see, when dealing with fields, we have to adjust the index passed by
    * the caller in order to keep it 0-based as the rest of the element types.
    * We achieve this by adding 1 to the field index.
    **/
    for ( i = HL7_ELEMENT_SEGMENT; i >= element_type; --i )
    {
        position = va_arg( ap, size_t );

        if ( i == HL7_ELEMENT_FIELD )
        {
            ++position;
        }

        node = hl7_node_sibling( node, position );

        if ( i != element_type && node != 0 )
        {
            node = hl7_node_child( node, 0 );
        }
        else
        {
            break;
        }
    }
    return node;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_message_segment( HL7_Message *message, HL7_Segment *segment,
                                    const char *segment_id, size_t sequence )
{
    int         rc      = -1;
    HL7_Node    *node   = message->head;

    segment->head = 0;

    while ( node != 0 )
    {
        if ( node->children != 0 )
        {
            if ( hl7_element_strcmp( &node->children->element, segment_id ) == 0 )
            {
                if ( sequence == 0 )
                {
                    segment->message_node   = node;
                    segment->head           = node->children;
                    segment->allocator      = message->allocator;
                    rc                      = 0;
                    break;
                }
                --sequence;
            }
        }
        node = node->sibling;
    }
    return rc;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_message_segment_sibling( HL7_Message *message, HL7_Segment *sibling,
                                            HL7_Segment *segment, const char *segment_id )
{
    int rc = -1;

    if ( message != 0 && sibling != 0 )
    {
        if ( segment != 0 && segment->message_node != 0 )
        {
            HL7_Node *node  = segment->message_node->sibling;

            while ( node != 0 )
            {
                if ( node->children != 0 )
                {
                    if ( hl7_element_strcmp( &node->children->element, segment_id ) == 0 )
                    {
                        sibling->message_node   = node;
                        sibling->head           = node->children;
                        sibling->allocator      = message->allocator;
                        rc                      = 0;
                        break;
                    }
                }
                node = node->sibling;
            }
        }
    }
    return rc;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_message_append_segment( HL7_Message *message, HL7_Segment *segment )
{
    int rc = -1;

    if ( message != 0 && segment != 0 && segment->head != 0 )
    {
        HL7_Node *node;

        node = hl7_node_create( message->allocator );
        if ( node != 0 )
        {
            node->element.attr  = HL7_TOKEN_ATTR_SEPARATOR;
            node->children      = segment->head;

            if ( message->head == 0 )
            {
                message->head = node;
            }
            else
            {
                hl7_node_append_sibling( message->head, node );
            }

            segment->message_node = node;

            rc = 0;
        }
    }
    return rc;
}

END_C_DECL()
