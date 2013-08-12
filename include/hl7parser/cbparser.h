#ifndef HL7PARSER_CBPARSER_H
#define HL7PARSER_CBPARSER_H

/**
* \file cbparser.h
*
* HL7 callback parser.
*
* \internal
* Copyright (c) 2003-2013 Juan Jose Comellas <juanjo@comellas.org>
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/defs.h>
#include <hl7parser/element.h>
#include <hl7parser/export.h>
#include <hl7parser/settings.h>
#include <hl7parser/parser.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------
   Typedefs
   ------------------------------------------------------------------------ */
/**
* \struct HL7_Parser_Callback
* Callback functions that are invoked by the hl7_parser_cb_read() function.
*/
typedef struct HL7_Parser_Callback_Struct
{
    int (*start_document)( HL7_Parser *parser );
    int (*end_document)( HL7_Parser *parser );
    int (*start_element)( HL7_Parser *parser, HL7_Element_Type element_type );
    int (*end_element)( HL7_Parser *parser, HL7_Element_Type element_type );
    int (*characters)( HL7_Parser *parser, HL7_Element_Type element_type, HL7_Element *element );
    int (*error)( HL7_Parser *parser, int error_code, char *error_msg );
    int (*format_encode)( HL7_Settings *settings, char *dest_begin, size_t *dest_length, char *src_begin, size_t src_length );
    int (*format_decode)( HL7_Settings *settings, char *dest_begin, size_t *dest_length, char *src_begin, size_t src_length );

} HL7_Parser_Callback;


/* ------------------------------------------------------------------------
   Function prototypes
   ------------------------------------------------------------------------ */

/**
* Initialize the \a parser and \a callback's with default values.
*/
HL7_EXPORT void hl7_parser_cb_init( HL7_Parser *parser, HL7_Parser_Callback *callback, HL7_Settings *settings );

/**
* Release any data that may have been allocated during initialization
* of the \a callback \a parser.
*/
HL7_EXPORT void hl7_parser_cb_fini( HL7_Parser *parser );

/**
* Parses the contents of the \a buffer and invokes the callbacks to the event handlers
* in the \c HL7_Parser_Callback.
* \todo Check lexer error codes.
* \todo Add support for incremental parsing.
*/
HL7_EXPORT int hl7_parser_cb_read( HL7_Parser *parser, HL7_Parser_Callback *callback, HL7_Buffer *buffer );


END_C_DECL()

#endif /* HL7PARSER_CBPARSER_H */
