/**
* \file lexer.c
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
#include <hl7parser/lexer.h>
#include <hl7parser/settings.h>
#include <ctype.h>
#include <string.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------
   Function prototypes
   ------------------------------------------------------------------------ */

/**
* \internal
* Reads a segment ID from the \a lexer's buffer.
* \return 0 if a \a token was found; -1 if not.
**/
static int lexer_read_segment_id( HL7_Lexer *lexer, HL7_Token *token );
/**
* \internal
* Generates a "virtual" field separator before the element after  the MSH segment ID.
*
* \return 0 if a \a token was found; -1 if not.
**/
static int lexer_read_virtual_msh_field_separator( HL7_Lexer *lexer, HL7_Token *token, bool is_first );
/**
* \internal
* Reads the first character following the segment ID. This character defines
* the field separator for the rest of the message.
*
* \return 0 if a \a token was found; -1 if not.
**/
static int lexer_read_msh_field_separator( HL7_Lexer *lexer, HL7_Token *token );
/**
* \internal
* Reads the characters use by HL7 as: component separator, repetition separator,
* escape character, subcomponent separator.
*
* \return 0 if a \a token was found; -1 if not.
**/
static int lexer_read_msh_encoding_characters( HL7_Lexer *lexer, HL7_Token *token );
/**
* \internal
* Reads a character \a token from the \a lexer's buffer.
* \return 0 if a \a token was found; -1 if not.
**/
static int lexer_read_characters( HL7_Lexer *lexer, HL7_Token *token );
/**
* \internal
* Reads a character \a token from the \a lexer's buffer.
* \return 0 if a \a token was found; -1 if not.
**/
static int lexer_read_separator( HL7_Lexer *lexer, HL7_Token *token );


/* ------------------------------------------------------------------------
   Functions
   ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_lexer_init( HL7_Lexer *lexer, HL7_Settings *settings, HL7_Buffer *buffer )
{
    HL7_ASSERT( lexer != 0 );

    lexer->buffer   = buffer;
    lexer->settings = settings;
    lexer->state    = HL7_LEXER_STATE_SEGMENT_ID;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_lexer_fini( HL7_Lexer *lexer )
{
    HL7_ASSERT( lexer != 0 );

    memset( lexer, 0, sizeof ( HL7_Lexer ) );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_lexer_read( HL7_Lexer *lexer, HL7_Token *token )
{
    int rc;

    switch ( lexer->state )
    {
        case HL7_LEXER_STATE_CHARACTERS:
            rc = lexer_read_characters( lexer, token );
            break;

        case HL7_LEXER_STATE_SEPARATOR:
            rc = lexer_read_separator( lexer, token );
            break;

        case HL7_LEXER_STATE_SEGMENT_ID:
            rc = lexer_read_segment_id( lexer, token );
            break;

        case HL7_LEXER_STATE_BEFORE_MSH_FIELD_SEPARATOR:
        case HL7_LEXER_STATE_AFTER_MSH_FIELD_SEPARATOR:
            rc = lexer_read_virtual_msh_field_separator( lexer, token,
                                                         ( lexer->state == HL7_LEXER_STATE_BEFORE_MSH_FIELD_SEPARATOR ) );
            break;

        case HL7_LEXER_STATE_MSH_FIELD_SEPARATOR:
            rc = lexer_read_msh_field_separator( lexer, token );
            break;

        case HL7_LEXER_STATE_MSH_ENCODING_CHARACTERS:
            rc = lexer_read_msh_encoding_characters( lexer, token );
            break;

        /* case HL7_LEXER_STATE_END: */
        /* case HL7_LEXER_STATE_ERROR: */
        default:
            rc = -1;
            break;

    }
    return rc;
}

/* ------------------------------------------------------------------------ */
static int lexer_read_segment_id( HL7_Lexer *lexer, HL7_Token *token )
{
    static const char MSH_SEGMENT_ID[] = "MSH";

    int     rc;
    char    *current    = hl7_buffer_rd_ptr( lexer->buffer );
    char    *end        = hl7_buffer_wr_ptr( lexer->buffer );

    if ( ( current + HL7_SEGMENT_ID_LENGTH < end ) &&
         ( isalnum( current[0] ) && isalnum( current[1] ) && isalnum( current[2] ) ) )
    {
        token->value    = current;
        token->length   = HL7_SEGMENT_ID_LENGTH;
        token->attr     = 0;

        hl7_buffer_move_rd_ptr( lexer->buffer, token->length );

        lexer->state    = ( ( memcmp( current, MSH_SEGMENT_ID, sizeof ( MSH_SEGMENT_ID ) - 1 ) == 0 ) ?
                            HL7_LEXER_STATE_BEFORE_MSH_FIELD_SEPARATOR : HL7_LEXER_STATE_SEPARATOR );
        rc              = 0;
    }
    else
    {
        token->value    = 0;
        token->length   = 0;
        token->attr     = HL7_TOKEN_ATTR_EMPTY;
        lexer->state    = ( ( current + sizeof ( MSH_SEGMENT_ID ) - 1 < end ) ?
                            HL7_LEXER_STATE_END : HL7_LEXER_STATE_ERROR );
        rc              = -1;
    }
    return rc;
}

/* ------------------------------------------------------------------------ */
static int lexer_read_virtual_msh_field_separator( HL7_Lexer *lexer, HL7_Token *token, bool is_first )
{
    static char *prev_separator;

    int     rc;
    char    *current    = hl7_buffer_rd_ptr( lexer->buffer );
    char    *end        = hl7_buffer_wr_ptr( lexer->buffer );

    if ( current < end )
    {
        if ( is_first )
        {
            token->value    = current;
            lexer->state    = HL7_LEXER_STATE_MSH_FIELD_SEPARATOR;
            prev_separator  = current;
        }
        else
        {
            token->value    = prev_separator;
            lexer->state    = HL7_LEXER_STATE_MSH_ENCODING_CHARACTERS;
        }

        token->length       = 1;
        token->attr         = HL7_TOKEN_ATTR_SEPARATOR;

        /* We don't increment the buffer position. */
        rc                  = 0;
    }
    else
    {
        token->value        = 0;
        token->length       = 0;
        token->attr         = HL7_TOKEN_ATTR_SEPARATOR | HL7_TOKEN_ATTR_EMPTY;
        lexer->state        = HL7_LEXER_STATE_END;
        rc                  = -1;
    }
    return rc;
}

/* ------------------------------------------------------------------------ */
static int lexer_read_msh_field_separator( HL7_Lexer *lexer, HL7_Token *token )
{
    int     rc;
    char    *current    = hl7_buffer_rd_ptr( lexer->buffer );
    char    *end        = hl7_buffer_wr_ptr( lexer->buffer );

    if ( current < end )
    {
        token->value        = current;
        token->length       = 1;
        token->attr         = 0;

        hl7_set_separator( lexer->settings, HL7_ELEMENT_FIELD, *current );

        hl7_buffer_move_rd_ptr( lexer->buffer, token->length );

        lexer->state        = HL7_LEXER_STATE_AFTER_MSH_FIELD_SEPARATOR;
        rc                  = 0;
    }
    else
    {
        token->value        = 0;
        token->length       = 0;
        token->attr         = HL7_TOKEN_ATTR_EMPTY;
        lexer->state        = HL7_LEXER_STATE_END;
        rc                  = -1;
    }
    return rc;
}

/* ------------------------------------------------------------------------ */
static int lexer_read_msh_encoding_characters( HL7_Lexer *lexer, HL7_Token *token )
{
    int     rc;
    char    *current    = hl7_buffer_rd_ptr( lexer->buffer );
    char    *end        = hl7_buffer_wr_ptr( lexer->buffer );

    if ( ( current + 4 < end ) &&
         ( current[4] == hl7_separator( lexer->settings, HL7_ELEMENT_FIELD ) ) )
    {
        token->value        = current;
        token->length       = 4;
        token->attr         = 0;

        hl7_set_separator( lexer->settings, HL7_ELEMENT_COMPONENT, *( current++ ) );
        hl7_set_separator( lexer->settings, HL7_ELEMENT_REPETITION, *( current++ ) );
        hl7_set_escape_char( lexer->settings, *( current++ ) );
        hl7_set_separator( lexer->settings, HL7_ELEMENT_SUBCOMPONENT, *( current++ ) );

        hl7_buffer_move_rd_ptr( lexer->buffer, token->length );

        lexer->state        = HL7_LEXER_STATE_SEPARATOR;
        rc                  = 0;
    }
    else
    {
        token->value        = 0;
        token->length       = 0;
        token->attr         = HL7_TOKEN_ATTR_EMPTY;
        lexer->state        = ( current + 4 >= end ? HL7_LEXER_STATE_END : HL7_LEXER_STATE_ERROR );
        rc                  = -1;
    }
    return rc;
}

/* ------------------------------------------------------------------------ */
static int lexer_read_characters( HL7_Lexer *lexer, HL7_Token *token )
{
    int             rc                  = 0;
    char            *current            = hl7_buffer_rd_ptr( lexer->buffer );
    char            *end                = hl7_buffer_wr_ptr( lexer->buffer );

    token->value    = 0;
    token->attr     = 0;

    while ( true )
    {
        if ( current < end )
        {
            if ( !hl7_is_separator( lexer->settings, *current ) )
            {
                /* Check if the token is a formatted/escaped character. */
                if ( *current == hl7_escape_char( lexer->settings ) )
                {
                    token->attr |= HL7_TOKEN_ATTR_FORMATTED;
                }

                /* If this is the first character of the token, we must set it. */
                if ( token->value == 0 )
                {
                    token->value = current;
                }
                ++current;
            }
            else
            {
                /* Separator found: we break the loop. */
                lexer->state    = HL7_LEXER_STATE_SEPARATOR;
                break;
            }
        }
        else
        {
            /* End of buffer reached. */
            lexer->state    = HL7_LEXER_STATE_END;
            rc                  = -1;
            break;
        }
    }

    /* Set the buffer's read pointer to the position of the next token. */
    hl7_buffer_set_rd_ptr( lexer->buffer, current );

    if ( token->value != 0 )
    {
        token->length = current - token->value;

        /* In HL7 a NULL value is represented by the string "". */
        if ( token->length == 2 && token->value[0] == '\"' && token->value[1] == '\"' )
        {
            token->attr    |= HL7_TOKEN_ATTR_NULL;
        }
        else if ( lexer->settings->strip_whitespace )
        {
            hl7_token_strip( token );
        }
    }
    else
    {
        token->length   = 0;
        token->attr    |= HL7_TOKEN_ATTR_EMPTY;
    }

    return rc;
}

/* ------------------------------------------------------------------------ */
static int lexer_read_separator( HL7_Lexer *lexer, HL7_Token *token )
{
    int     rc          = 0;
    char    *current    = hl7_buffer_rd_ptr( lexer->buffer );
    char    *end        = hl7_buffer_wr_ptr( lexer->buffer );

    token->value    = 0;
    token->attr     = HL7_TOKEN_ATTR_SEPARATOR;

    /* HL7 separators are always 1 byte long, so there is no need to loop. */
    if ( current < end )
    {
        if ( hl7_is_separator( lexer->settings, *current ) )
        {
            token->value        = current;

            /* Set the buffer's read pointer to the position of the next token. */
            hl7_buffer_move_rd_ptr( lexer->buffer, 1 );

            /* Separator found: if it's a segment separator we check the segment id;
                                if not now we start looking for data/characters. */
            lexer->state    = ( *current == HL7_SEPARATOR_SEGMENT ) ?
                                HL7_LEXER_STATE_SEGMENT_ID :
                                HL7_LEXER_STATE_CHARACTERS;
            ++current;
        }
        else
        {
            /* End of buffer reached. */
            lexer->state    = HL7_LEXER_STATE_ERROR;
            rc                  = -1;
        }
    }
    else
    {
        /* End of buffer reached. */
        lexer->state    = HL7_LEXER_STATE_END;
        rc                  = -1;
    }

    if ( token->value != 0 )
    {
        token->length = current - token->value;
    }
    else
    {
        token->length   = 0;
        token->attr    |= HL7_TOKEN_ATTR_EMPTY;
    }
    return rc;
}


END_C_DECL()
