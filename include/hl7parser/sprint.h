#ifndef HL7PARSER_SPRINT_H
#define HL7PARSER_SPRINT_H

/**
* \file dump.h
*
* Functions used to format and print HL7 messages into strings.
*
* \internal
* Copyright (c) 2003-2013 Juan Jose Comellas <juanjo@comellas.org>
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/export.h>
#include <stdlib.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------
   Function prototypes
   ------------------------------------------------------------------------ */
/**
* Converts a buffer containing an HL7 message into a printable format using
* the C escaping rules.
*/
HL7_EXPORT size_t hl7_sprint( char *output_buffer, const size_t output_len,
                              const char *input_buffer, const size_t input_len );


END_C_DECL()

#endif /* HL7PARSER_SPRINT_H */
