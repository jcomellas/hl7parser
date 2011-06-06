#ifndef HL7PARSER_TOKEN_H
#define HL7PARSER_TOKEN_H

/**
* \file token.h
*
* HL7 tokens returned by the \c HL7_Lexer.
*
* \internal
* Copyright (c) 2003-2011 \b Erlar (http://erlar.com)
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/export.h>
#include <stddef.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------
   Macros
   ------------------------------------------------------------------------ */

/* Attributes of a token returned by the HL7 lexer. */
#define HL7_TOKEN_ATTR_SEPARATOR        0x01
#define HL7_TOKEN_ATTR_EMPTY            0x02
#define HL7_TOKEN_ATTR_NULL             0x04
#define HL7_TOKEN_ATTR_FORMATTED        0x08

#define HL7_TOKEN_ATTR_COUNT            4


/* ------------------------------------------------------------------------
   Typedefs
   ------------------------------------------------------------------------ */

/**
* \typedef HL7_Token_Attribute
* Attributes the the tokens indicating whether the token is: empty, null,
* formatted or a separator.
*/
typedef unsigned char HL7_Token_Attribute;

/**
* \struct HL7_Token
* Tokens returned by the \c HL7_Lexer.
*/
typedef struct HL7_Token_Struct
{
    char                *value;
    size_t              length;
    HL7_Token_Attribute attr;
} HL7_Token;


/* ------------------------------------------------------------------------
   Function prototypes
   ------------------------------------------------------------------------ */

HL7_EXPORT void hl7_token_set( HL7_Token *token, char *value, const size_t length, const HL7_Token_Attribute attr );
HL7_EXPORT void hl7_token_copy( HL7_Token *dest, const HL7_Token *src );

/**
* Removes the whitespace at the left (beginning) of the token.
* \todo What characters do we consider spaces in a HL7 token?
*/
HL7_EXPORT void hl7_token_left_strip( HL7_Token *token );
/**
* Removes the whitespace at the right (end) of the token.
* \todo What characters do we consider spaces in a HL7 token?
*/
HL7_EXPORT void hl7_token_right_strip( HL7_Token *token );
/**
* Removes the whitespace both at the left (beginning) and right (end) of the token.
* \todo What characters do we consider spaces in a HL7 token?
*/
HL7_EXPORT void hl7_token_strip( HL7_Token *token );


END_C_DECL()

#endif /* HL7PARSER_TOKEN_H */
