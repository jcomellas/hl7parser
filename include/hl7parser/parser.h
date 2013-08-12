#ifndef HL7PARSER_PARSER_H
#define HL7PARSER_PARSER_H

/**
* \file parser.h
*
* HL7 message parser.
*
* \internal
* Copyright (c) 2003-2013 Juan Jose Comellas <juanjo@comellas.org>
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/element.h>
#include <hl7parser/export.h>
#include <hl7parser/message.h>
#include <hl7parser/settings.h>
#include <hl7parser/lexer.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------
   Typedefs
   ------------------------------------------------------------------------ */

/**
* \struct HL7_Parser
* HL7 parser.
*/
typedef struct HL7_Parser_Struct
{
    /**
    * HL7 parser settings.
    */
    HL7_Settings        *settings;
    /**
    * Lexer used to retrieve tokens from an HL7 message stream.
    */
    HL7_Lexer           lexer;
    /**
    * Element type of the last separator (non-character) token read by the \a lexer.
    */
    HL7_Element_Type    prev_type;
    /**
    * Last character token read from the lexer.
    */
    HL7_Token           characters_token;
    /**
    * User-defined data.
    */
    void                *user_data;
} HL7_Parser;


/* ------------------------------------------------------------------------
   Function prototypes
   ------------------------------------------------------------------------ */

/**
* Initialize the parser with default values.
*/
HL7_EXPORT void hl7_parser_init( HL7_Parser *parser, HL7_Settings *settings );
/**
* Release any data that may have been allocated during initialization
* of the parser.
**/
HL7_EXPORT void hl7_parser_fini( HL7_Parser *parser );
/**
* Returns the user-defined data that is passed as argument to each callback
* function of the parser when they are called.
**/
HL7_EXPORT void *hl7_parser_user_data( HL7_Parser *parser );
/**
* Sets the user-defined data that is passed as argument to each callback
* function of the parser when they are called.
**/
HL7_EXPORT void hl7_parser_set_user_data( HL7_Parser *parser, void *user_data );
/**
* Parses the contents of the \a buffer into the \a message.
* \todo Check lexer error codes.
* \todo Add support for incremental parsing.
**/
HL7_EXPORT int hl7_parser_read( HL7_Parser *parser, HL7_Message *message, HL7_Buffer *buffer );
/**
* Writes the \a message into the \a buffer.
* \todo Add specific error codes.
* \todo Add support for incremental writing.
**/
HL7_EXPORT int hl7_parser_write( HL7_Parser *parser, HL7_Buffer *buffer, HL7_Message *message );
/**
* Writes the \a segment into the \a buffer.
* \todo Add specific error codes.
* \todo Add support for incremental writing.
**/
HL7_EXPORT int hl7_parser_write_segment( HL7_Parser *parser, HL7_Buffer *buffer, HL7_Segment *segment );
/**
* Writes the node corresponding to the beginning of a \a segment (\c segment->head) into the \a buffer.
* \todo Add specific error codes.
* \todo Add support for incremental writing.
**/
HL7_EXPORT int hl7_parser_write_segment_node( HL7_Parser *parser, HL7_Buffer *buffer, HL7_Node *node );
/**
* Writes the contents of a \a node into the \a buffer. This function calls itself recursively
* to write the entire contents of the node and its children to the buffer. It will call itself
* a maximum of \c HL7_ELEMENT_COUNT times.
* \todo Add specific error codes.
* \todo Add support for incremental writing.
**/
HL7_EXPORT int hl7_parser_write_node( HL7_Parser *parser, HL7_Buffer *buffer,
                                      HL7_Node *node, HL7_Element_Type element_type );


END_C_DECL()

#endif /* HL7PARSER_PARSER_H */
