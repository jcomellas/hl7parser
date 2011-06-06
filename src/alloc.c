/**
* \file alloc.c
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
#include <hl7parser/alloc.h>
#include <hl7parser/export.h>
#include <string.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_allocator_init( HL7_Allocator *allocator,
                                    void *(*malloc)( size_t size ),
                                    void (*mfree)( void *ptr ) )
{
    HL7_ASSERT( allocator != 0 );
    HL7_ASSERT( malloc != 0 );
    HL7_ASSERT( mfree != 0 );

    allocator->malloc   = malloc;
    allocator->mfree    = mfree;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_allocator_fini( HL7_Allocator *allocator )
{
    HL7_ASSERT( allocator != 0 );

    memset( allocator, 0, sizeof ( HL7_Allocator ) );
}


END_C_DECL()
