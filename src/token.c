/**
* \file token.c
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
#include <hl7parser/defs.h>
#include <hl7parser/export.h>
#include <hl7parser/token.h>
#include <string.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_token_set( HL7_Token *token, char *value, const size_t length, const HL7_Token_Attribute attr )
{
    HL7_ASSERT( token != 0 );

    token->value    = value;
    token->length   = length;
    token->attr     = attr;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_token_copy( HL7_Token *dest, const HL7_Token *src )
{
    HL7_ASSERT( src != 0 );
    HL7_ASSERT( dest != 0 );

    memcpy( dest, src, sizeof ( HL7_Token ) );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_token_left_strip( HL7_Token *token )
{
    if ( token != 0 && token->value != 0 )
    {
        char *end       = token->value + token->length;
        char *current;

        for ( current = token->value;
              current < end && HL7_IS_SPACE( *current );
              ++current )
        {
        }

        token->length  -= ( current - token->value );
        token->value    = current;
    }
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_token_right_strip( HL7_Token *token )
{
    if ( token != 0 && token->value != 0 )
    {
        char *base      = token->value;
        char *current   = token->value + token->length;

        for ( current = token->value + token->length - 1;
              current >= base && HL7_IS_SPACE( *current );
              --current )
        {
        }

        token->length = current + 1 - token->value;
    }
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_token_strip( HL7_Token *token )
{
    hl7_token_right_strip( token );
    hl7_token_left_strip( token );
}


END_C_DECL()
