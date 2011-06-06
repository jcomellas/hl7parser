/**
* \file handler.c
*
* Default handlers for the HL7_Parser callbacks.
*
* \internal
* Copyright (c) 2003-2011 \b Erlar (http://erlar.com)
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/export.h>
#include <hl7parser/element.h>
#include <hl7parser/handler.h>
#include <hl7parser/message.h>
#include <hl7parser/parser.h>
#include <stdio.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------ */
int hl7_handler_start_document( HL7_Parser *parser )
{
    return 0;
}

/* ------------------------------------------------------------------------ */
int hl7_handler_end_document( HL7_Parser *parser )
{
    return 0;
}

/* ------------------------------------------------------------------------ */
int hl7_handler_start_element( HL7_Parser *parser, HL7_Element_Type element_type )
{
    return ( 0 );
}

/* ------------------------------------------------------------------------ */
int hl7_handler_end_element( HL7_Parser *parser, HL7_Element_Type element_type )
{
    return ( 0 );
}

/* ------------------------------------------------------------------------ */
int hl7_handler_characters( HL7_Parser *parser, HL7_Element_Type element_type, HL7_Element *element )
{
    return ( 0 );
}

/* ------------------------------------------------------------------------ */
int hl7_handler_parse_error( HL7_Parser *parser, int error_code, char *error_msg )
{
    return ( 0 );
}


END_C_DECL()
