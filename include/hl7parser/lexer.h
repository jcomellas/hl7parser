#ifndef HL7PARSER_LEXER_H
#define HL7PARSER_LEXER_H

/**
* \file lexer.h
*
* HL7 lexer used by the \c HL7_Parser to retrieve tokens from an \c HL7_Buffer.
*
* \internal
* Copyright (c) 2003-2013 Juan Jose Comellas <juanjo@comellas.org>
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/buffer.h>
#include <hl7parser/element.h>
#include <hl7parser/export.h>
#include <hl7parser/settings.h>
#include <hl7parser/token.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------
   Typedefs
   ------------------------------------------------------------------------ */

/**
* \internal
* \enum HL7_Lexer_State
* States that the \c HL7_Lexer state machine can take.
*/
typedef enum HL7_Lexer_State
{
    HL7_LEXER_STATE_SEGMENT_ID,
    HL7_LEXER_STATE_BEFORE_MSH_FIELD_SEPARATOR,
    HL7_LEXER_STATE_MSH_FIELD_SEPARATOR,
    HL7_LEXER_STATE_AFTER_MSH_FIELD_SEPARATOR,
    HL7_LEXER_STATE_MSH_ENCODING_CHARACTERS,
    HL7_LEXER_STATE_SEPARATOR,
    HL7_LEXER_STATE_CHARACTERS,
    HL7_LEXER_STATE_END,
    HL7_LEXER_STATE_ERROR
} HL7_Lexer_State;


/* ------------------------------------------------------------------------
   Typedefs
   ------------------------------------------------------------------------ */

/**
* \struct HL7_Lexer
* HL7 lexer used to retrieve tokens from a \a buffer.
*/
typedef struct HL7_Lexer_Struct
{
    /**
    * Global settings used to decide if the \c HL7_Lexer should strip whitespaces.
    */
    HL7_Settings    *settings;
    /**
    * Buffer from which the HL7 tokens are read.
    */
    HL7_Buffer      *buffer;
    /**
    * Internal state of the \c HL7_Lexer.
    */
    HL7_Lexer_State state;

} HL7_Lexer;


/* ------------------------------------------------------------------------
   Function prototypes
   ------------------------------------------------------------------------ */

/**
* Initialize the \a lexer.
*/
HL7_EXPORT void hl7_lexer_init( HL7_Lexer *lexer, HL7_Settings *settings, HL7_Buffer *buffer );
/**
* Clear the \a lexer.
*/
HL7_EXPORT void hl7_lexer_fini( HL7_Lexer *lexer );
/**
* Read a \a token from the \a lexer's buffer.
* \return 0 if a token could be read successfully; -1 otherwise.
*/
HL7_EXPORT int  hl7_lexer_read( HL7_Lexer *lexer, HL7_Token *token );


END_C_DECL()

#endif /* HL7PARSER_LEXER_H */
