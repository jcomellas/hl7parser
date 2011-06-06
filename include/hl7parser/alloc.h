#ifndef HL7PARSER_ALLOC_H
#define HL7PARSER_ALLOC_H

/**
* \file alloc.h
*
* Memory allocator used by the HL7 parser to reserve and free memory
* for \c HL7_Node's and \c HL7_Element's.
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

/**
* \struct HL7_Allocator
* Memory allocator used by the HL7 parser to reserve and free memory
* for \c HL7_Node's and \c HL7_Element's.
*/
typedef struct HL7_Allocator_Struct
{
    /**
    * Function used to allocate memory.
    */
    void *(*malloc)( size_t size );
    /**
    * Function used to deallocate memory.
    */
    void (*mfree)( void *ptr );

} HL7_Allocator;


/* ------------------------------------------------------------------------
   Function prototypes
   ------------------------------------------------------------------------ */

/**
* Initialize the \a allocator.
* \param allocator The \c HL7_Allocator to be initialized.
* \param malloc The function used to allocate memory.
*               The \c malloc() function from the Standard C Library can be used.
* \param mfree  The function used to deallocate memory.
*               The \c free() function from the Standard C Library can be used.
*/
HL7_EXPORT void hl7_allocator_init( HL7_Allocator *allocator,
                                    void *(*malloc)( size_t size ),
                                    void (*mfree)( void *ptr ) );
/**
* Clear the \a allocator.
*/
HL7_EXPORT void hl7_allocator_fini( HL7_Allocator *allocator );


END_C_DECL()

#endif /* HL7PARSER_ALLOC_H */
