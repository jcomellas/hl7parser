#ifndef HL7PARSER_ELEMENT_H
#define HL7PARSER_ELEMENT_H

/**
* \file element.h
*
* Data types and functions used to handle an HL7 element.
*
* \internal
* Copyright (c) 2003-2011 \b Erlar (http://erlar.com)
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/alloc.h>
#include <hl7parser/defs.h>
#include <hl7parser/export.h>
#include <hl7parser/token.h>
#include <stddef.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------
   Typedefs
   ------------------------------------------------------------------------ */

/**
* \struct HL7_Element
* Holds all the data related to an HL7 element.
*/
typedef struct HL7_Element_Struct
{
    /**
    * Pointer to the beginning to the string with the element's value.
    */
    char                *value;
    /**
    * Length of the \a value string.
    */
    size_t              length;
    /**
    * Indicates whether this element is NULL, empty, formatted or if it's a
    * separator (empty parent).
    */
    HL7_Token_Attribute attr;
    /**
    * Indicates whether the memory where the \a value field is stored was
    * dynamically allocated.
    */
    bool                auto_delete;
} HL7_Element;


/* ------------------------------------------------------------------------
   Function prototypes
   ------------------------------------------------------------------------ */

HL7_EXPORT void hl7_element_init( HL7_Element *element );
HL7_EXPORT void hl7_element_fini( HL7_Element *element, HL7_Allocator *allocator );

HL7_EXPORT int  hl7_element_create( HL7_Element *element, HL7_Token *token,
                                    HL7_Allocator *allocator );
HL7_EXPORT int  hl7_element_create_copy( HL7_Element *dest, const HL7_Element *src,
                                         HL7_Allocator *allocator );
HL7_EXPORT void hl7_element_destroy( HL7_Element *element, HL7_Allocator *allocator );
/**
* Returns a pointer to a null HL7 element. Useful when returning an
* invalid element instead of the null pointer.
*/
HL7_EXPORT HL7_Element *hl7_element_null( void );

HL7_EXPORT void hl7_element_set( HL7_Element *element, const HL7_Token *token,
                                 const bool auto_delete );
HL7_EXPORT int  hl7_element_set_str( HL7_Element *element, char *str,
                                     const bool auto_delete );
HL7_EXPORT int  hl7_element_set_ptr( HL7_Element *element, char *value, const size_t length,
                                     const bool auto_delete );
HL7_EXPORT int  hl7_element_copy( HL7_Element *dest, HL7_Element *src,
                                  HL7_Allocator *allocator, const bool assume_ownership );
HL7_EXPORT int hl7_element_copy_str( HL7_Element *element, const char *str,
                                     HL7_Allocator *allocator );
HL7_EXPORT int hl7_element_copy_ptr( HL7_Element *element, const char *ptr, const size_t length,
                                     HL7_Allocator *allocator );

/**
* Converts an \a element to an integer.
* \return The integer corresponding to the value in the \a element.
* \return 0 if the value was not a valid integer.
*/
HL7_EXPORT int  hl7_element_int( HL7_Element *element );
HL7_EXPORT int  hl7_element_set_int( HL7_Element *element, const int value,
                                     HL7_Allocator *allocator );
/**
* Converts an \a element containing a string with the syntax: YYYYMMDD[hhmm[ss]]
* to a time_t value.
* \return The time corresponding to the value in the \a element.
* \return -1 if the value was not valid time.
*/
HL7_EXPORT time_t hl7_element_date( HL7_Element *element );
HL7_EXPORT int  hl7_element_set_date( HL7_Element *element, const time_t value,
                                      const bool include_time, const bool include_secs,
                                      HL7_Allocator *allocator );

HL7_EXPORT bool hl7_element_is_empty( const HL7_Element *element );
HL7_EXPORT int  hl7_element_strcmp( const HL7_Element *element, const char *str );


END_C_DECL()

#endif /* HL7PARSER_ELEMENT_H */
