#ifndef HL7PARSER_HANDLER_H
#define HL7PARSER_HANDLER_H

/**
* \file handler.h
*
* Default handlers for the HL7_Parser callbacks.
*
* \internal
* Copyright (c) 2003-2013 Juan Jose Comellas <juanjo@comellas.org>
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/defs.h>
#include <hl7parser/export.h>
#include <hl7parser/parser.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------
   Function prototypes
   ------------------------------------------------------------------------ */

int hl7_handler_start_document( HL7_Parser *parser );
int hl7_handler_end_document( HL7_Parser *parser );
int hl7_handler_start_element( HL7_Parser *parser, HL7_Element_Type element_type );
int hl7_handler_end_element( HL7_Parser *parser, HL7_Element_Type element_type );
int hl7_handler_characters( HL7_Parser *parser, HL7_Element_Type element_type, HL7_Element *element );
int hl7_handler_parse_error( HL7_Parser *parser, int error_code, char *error_msg );


END_C_DECL()

#endif /* HL7PARSER_HANDLER_H */
