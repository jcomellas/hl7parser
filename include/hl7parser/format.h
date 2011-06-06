#ifndef HL7PARSER_FORMAT_H
#define HL7PARSER_FORMAT_H

/**
* \file format.h
*
* Functions to encode/decode text elements using the HL7 formatting rules.
*
* \internal
* Copyright (c) 2003-2011 \b Erlar (http://erlar.com)
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/export.h>
#include <hl7parser/settings.h>
#include <stddef.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------
   Function prototypes
   ------------------------------------------------------------------------ */
/**
* Encodes a string using the HL7 formatting rules.
* \see hl7_format_decode()
*/
HL7_EXPORT int hl7_format_encode( HL7_Settings *settings, char *dest_begin, size_t *dest_length, char *src_begin, size_t src_length );
/**
* Decodes a string using the HL7 formatting rules.
* \todo Support for hexadecimal escaped characters.
* \see hl7_format_encode()
*/
HL7_EXPORT int hl7_format_decode( HL7_Settings *settings, char *dest_begin, size_t *dest_length, char *src_begin, size_t src_length );


END_C_DECL()

#endif /* HL7PARSER_FORMAT_H */
