#ifndef HL7PARSER_ERROR_H
#define HL7PARSER_ERROR_H

/**
* \file error.h
*
* Error codes returned by the \c HL7_Parser and \c HL7_Lexer.
*
* \internal
* Copyright (c) 2003-2013 Juan Jose Comellas <juanjo@comellas.org>
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------
   Macros
   ------------------------------------------------------------------------ */

#define HL7_OK                              0

#define HL7_ERROR_BUFFER_TOO_SMALL          -51
#define HL7_ERROR_INVALID_ESCAPED_CHAR      -52



END_C_DECL()

#endif /* HL7PARSER_ERROR_H */

