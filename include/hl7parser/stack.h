#ifndef HL7PARSER_STACK_H
#define HL7PARSER_STACK_H

/**
* \file stack.h
*
* Generic stack used by the HL7 message parser to keep track of the parent
* \c HL7_Node's that have been already parsed.
*
* \internal
* Copyright (c) 2003-2011 \b Erlar (http://erlar.com)
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/export.h>
#include <stdlib.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------
   Typedefs
   ------------------------------------------------------------------------ */

/**
* \struct HL7_Stack
* Generic stack used by the HL7 message parser to keep track of the parent
* \c HL7_Node's that have been already parsed.
*/
typedef struct HL7_Stack_Struct
{
    /**
    * Buffer where the data that is pushed into the stack will be kept.
    */
    char    *data;
    /**
    * Size of each element that will be kept in the stack.
    */
    size_t  element_size;
    /**
    * Maximum amount of elements that can be kept in the stack.
    */
    int     max_length;
    /**
    * Position of the last element that was pushed into the stack;
    * -1 if the stack is empty.
    */
    int     top;

} HL7_Stack;


/* ------------------------------------------------------------------------
   Function prototypes
   ------------------------------------------------------------------------ */

/**
* Initialize the stack.
* \param stack The \c HL7_Stack to be initialized.
* \param max_length Maximum amount of elements that can be kept in the stack.
* \param element_size Size of each element that will be kept in the stack.
* \return 0 if the stack was initialized correctly; -1 in case of error.
*/
HL7_EXPORT int  hl7_stack_init( HL7_Stack *stack, const int max_length, const size_t element_size );
/**
* Releases any data that may have been allocated during initialization
* of the stack.
*/
HL7_EXPORT void hl7_stack_fini( HL7_Stack *stack );
/**
* Checks whether the stack is empty or not.
*/
HL7_EXPORT bool hl7_stack_empty( const HL7_Stack *stack );
/**
* Returns the maximum amount of elements that can be kept in the stack.
*/
HL7_EXPORT int  hl7_stack_max_length( const HL7_Stack *stack );
/**
* Returns the amount of elements that are currently in the stack.
*/
HL7_EXPORT int  hl7_stack_length( const HL7_Stack *stack );
/**
* Returns a pointer to the element that was last inserted into the stack.
*/
HL7_EXPORT void *hl7_stack_top( HL7_Stack *stack );
/**
* Inserts an element into the stack. The element is copied to the stack using memcpy().
*/
HL7_EXPORT int  hl7_stack_push( HL7_Stack *stack, void *element );
/**
* Removes the last element that was inserted into the stack. If \a element is not null,
* the element in the stack is copied to the memory associated with \a element using
* memcpy().
*/
HL7_EXPORT int  hl7_stack_pop( HL7_Stack *stack, void *element );
/**
* Removes all the elements in the stack.
*/
HL7_EXPORT void hl7_stack_clear( HL7_Stack *stack );


END_C_DECL()

#endif /* HL7PARSER_STACK_H */
