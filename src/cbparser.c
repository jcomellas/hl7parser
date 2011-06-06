/**
* \file cbparser.c
*
* HL7 callback parser.
*
* \internal
* Copyright (c) 2003-2011 \b Erlar (http://erlar.com)
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/cbparser.h>
#include <hl7parser/defs.h>
#include <hl7parser/element.h>
#include <hl7parser/export.h>
#include <hl7parser/format.h>
#include <hl7parser/handler.h>
#include <hl7parser/parser.h>
#include <hl7parser/settings.h>
#include <hl7parser/token.h>
#include <hl7parser/lexer.h>
#include <stdlib.h>
#include <string.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_parser_cb_init( HL7_Parser *parser, HL7_Parser_Callback *callback, HL7_Settings *settings )
{
    HL7_ASSERT( parser != 0 );
    HL7_ASSERT( settings != 0 );

    parser->settings        = settings;
    parser->user_data       = 0;

    /* HL7 parser handlers. */
    callback->start_document    = hl7_handler_start_document;   /* int (*start_document)( void *user_data ) */
    callback->end_document      = hl7_handler_end_document;     /* int (*end_document)( void *user_data ) */
    callback->start_element     = hl7_handler_start_element;    /* int (*start_element)( void *user_data, HL7_Element_Type element_type ); */
    callback->end_element       = hl7_handler_end_element;      /* int (*end_element)( void *user_data, HL7_Element_Type element_type ); */
    callback->characters        = hl7_handler_characters;       /* int (*characters)( void *user_data, HL7_Element *element ); */
    callback->error             = hl7_handler_parse_error;      /* int (*error)( void *user_data, int error_code, char *error_msg ) */

    callback->format_encode     = hl7_format_encode;            /* int (*format_encode)( HL7_Settings *settings, char *dest_begin, size_t *dest_length, char *src_begin, size_t src_length ); */
    callback->format_decode     = hl7_format_decode;            /* int (*format_decode)( HL7_Settings *settings, char *dest_begin, size_t *dest_length, char *src_begin, size_t src_length ); */
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_parser_cb_fini( HL7_Parser *parser )
{
    hl7_parser_fini( parser );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_parser_cb_read( HL7_Parser *parser, HL7_Parser_Callback *callback, HL7_Buffer *buffer )
{
    int                 rc = 0;
    HL7_Element_Type    current_type;
    HL7_Element_Type    element_type;
    HL7_Token           token;
    HL7_Element         element;

    HL7_ASSERT( parser != 0 );
    HL7_ASSERT( callback != 0 );
    HL7_ASSERT( buffer != 0 );

    /*
    if ( first_chunk )
    {
    */
    hl7_lexer_init( &parser->lexer, parser->settings, buffer );

    parser->prev_type = HL7_ELEMENT_SEGMENT;

    callback->start_document( parser );
    /* } */

    /* FIXME: check lexer error codes. */
    while ( hl7_lexer_read( &parser->lexer, &token ) == 0 && parser->lexer.state != HL7_LEXER_STATE_END )
    {
        if ( token.attr & HL7_TOKEN_ATTR_SEPARATOR )
        {
            current_type = hl7_element_type( parser->settings, *token.value );

            if ( hl7_is_descendant_type( current_type, parser->prev_type ) ||
                 current_type == parser->prev_type )
            {
                for ( element_type = parser->prev_type;
                      element_type != HL7_ELEMENT_INVALID && element_type != current_type;
                      element_type = hl7_child_type( element_type ) )
                {
                    callback->start_element( parser, element_type );
                }

                /* Invoke the start_element() callback for the current element. */
                callback->start_element( parser, current_type );

                /* Invoke the characters() callback for the current element. */
                hl7_element_set( &element, &parser->characters_token, false );
                callback->characters( parser, current_type, &element );

                /* Invoke the end_element() callback for the current element. */
                callback->end_element( parser, current_type );

                parser->prev_type = current_type;
            }
            else
            {
                /* Invoke the start_element() callback for the current element. */
                callback->start_element( parser, parser->prev_type );

                /* Invoke the characters() callback for the current element. */
                hl7_element_set( &element, &parser->characters_token, false );
                callback->characters( parser, parser->prev_type, &element );

                /* Invoke the end_element() callback for the current element. */
                callback->end_element( parser, parser->prev_type );

                for ( element_type = hl7_parent_type( parser->prev_type );
                      element_type != HL7_ELEMENT_INVALID && element_type != hl7_parent_type( current_type );
                      element_type = hl7_parent_type( element_type ) )
                {
                    callback->end_element( parser, element_type );
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
    callback->end_document( parser );

    hl7_lexer_fini( &parser->lexer );

    parser->prev_type = HL7_ELEMENT_SEGMENT;
    /* } */

    return rc;
}


END_C_DECL()
