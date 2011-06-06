#ifndef HL7PARSER_SETTINGS_H
#define HL7PARSER_SETTINGS_H

/**
* \file settings.h
*
* HL7 parser settings.
*
* \internal
* Copyright (c) 2003-2011 \b Erlar (http://erlar.com)
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/defs.h>
#include <hl7parser/element.h>
#include <hl7parser/export.h>
#include <hl7parser/element.h>
#include <hl7parser/token.h>
#include <stddef.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------
   Typedefs
   ------------------------------------------------------------------------ */

/**
* \struct HL7_Settings
* HL7 Parser settings.
**/
typedef struct HL7_Settings_Struct
{
    /**
    * Array with the HL7 element separators.
    **/
    char separator[HL7_ELEMENT_TYPE_COUNT + 1];
    /**
    * Escape character used to format HL7 elements.
    * \see hl7_format_encode(), hl7_format_decode()
    **/
    char escape_char;
    /**
    * Should the parser strip the whitespace at the beginning and end of each \a HL7_Element?
    **/
    bool strip_whitespace;
    /**
    * Should the parser escape the characters in each \a HL7_Element automatically?
    **/
    bool auto_escape;

} HL7_Settings;


/* ------------------------------------------------------------------------
   Function prototypes
   ------------------------------------------------------------------------ */

/**
* Initialize the parser configuration with default values.
*/
HL7_EXPORT void hl7_settings_init( HL7_Settings *settings );
/**
* Releases any data that may have been allocated during initialization
* of the parser configuration.
*/
HL7_EXPORT void hl7_settings_fini( HL7_Settings *settings );
/**
* Returns the separator character for the \a element_type passed as argument.
*/
HL7_EXPORT char hl7_separator( const HL7_Settings *settings, const HL7_Element_Type element_type );
/**
* Sets the \a separator character for the \a element_type passed as argument.
*/
HL7_EXPORT void hl7_set_separator( HL7_Settings *settings, const HL7_Element_Type element_type, const char separator );
/**
* Returns true if the character is a valid separator.
*/
HL7_EXPORT bool hl7_is_separator( HL7_Settings *settings, const char separator );
/**
* Returns the separator character for the element type passed as argument.
*/
HL7_EXPORT char hl7_escape_char( const HL7_Settings *settings );
/**
* Sets the escape character.
*/
HL7_EXPORT void hl7_set_escape_char( HL7_Settings *settings, const char escape_char );
/**
* Returns the element type of the \a separator character.
* @return The element type if the character is a valid separator; HL7_ELEMENT_INVALID if it's invalid.
**/
HL7_EXPORT HL7_Element_Type hl7_element_type( HL7_Settings *settings, const char separator );

HL7_EXPORT HL7_Element_Type hl7_child_type( const HL7_Element_Type element_type );
HL7_EXPORT bool hl7_is_child_type( const HL7_Element_Type child_type, const HL7_Element_Type parent_type );
HL7_EXPORT bool hl7_is_descendant_type( const HL7_Element_Type ancestor_type, const HL7_Element_Type descendant_type );

HL7_EXPORT HL7_Element_Type hl7_parent_type( const HL7_Element_Type element_type );
HL7_EXPORT bool hl7_is_parent_type( const HL7_Element_Type parent_type, const HL7_Element_Type child_type );
HL7_EXPORT bool hl7_is_ancestor_type( const HL7_Element_Type ancestor_type, const HL7_Element_Type descendant_type );

HL7_EXPORT void hl7_child_separators( HL7_Settings *settings, const HL7_Element_Type element_type,
                                      const char *separator_begin, const char *separator_end );

HL7_EXPORT char hl7_terminator( HL7_Settings *settings, const HL7_Element_Type element_type );
HL7_EXPORT void hl7_parent_terminators( HL7_Settings *settings, HL7_Element_Type const element_type,
                                        const char *separator_begin, const char *separator_end );


END_C_DECL()

#endif /* HL7PARSER_SETTINGS_H */
