/**
* \file stack.c
*
* Generic stack used by the HL7 message parser to keep track of the parent
* HL7_Node's that have been already parsed.
*
* \internal
* Copyright (c) 2003-2013 Juan Jose Comellas <juanjo@comellas.org>
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/export.h>
#include <hl7parser/stack.h>
#include <stdlib.h>
#include <string.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_stack_init( HL7_Stack *stack, const int max_length, const size_t element_size )
{
    int rc;

    HL7_ASSERT( stack != 0 );
    HL7_ASSERT( max_length > 0 );
    HL7_ASSERT( element_size > 0 );

    stack->data = (char *) malloc( (size_t) max_length * element_size );
    if ( stack->data != 0 )
    {
        stack->max_length   = max_length;
        stack->element_size = element_size;
        stack->top          = -1;
        rc                  = 0;
    }
    else
    {
        rc                  = -1;
    }
    return rc;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_stack_fini( HL7_Stack *stack )
{
    if ( stack->data != 0 )
    {
        free( stack->data );
        memset( stack, 0, sizeof ( HL7_Stack ) );
    }
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT bool hl7_stack_empty( const HL7_Stack *stack )
{
    HL7_ASSERT( stack != 0 );

    return ( stack->top == -1 );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_stack_max_length( const HL7_Stack *stack )
{
    HL7_ASSERT( stack != 0 );

    return ( stack->max_length );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_stack_length( const HL7_Stack *stack )
{
    HL7_ASSERT( stack != 0 );

    return ( stack->top + 1 );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void *hl7_stack_top( HL7_Stack *stack )
{
    HL7_ASSERT( stack != 0 );

    return ( stack->top >= 0 ? ( stack->data + stack->top * stack->element_size ) : 0 );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_stack_push( HL7_Stack *stack, void *element )
{
    int rc;

    HL7_ASSERT( stack != 0 );
    HL7_ASSERT( element != 0 );

    if ( stack->top + 1 < stack->max_length )
    {
        ++stack->top;
        memcpy( ( (char *) stack->data + stack->top * stack->element_size ), element, stack->element_size );
        rc = 0;
    }
    else
    {
        rc = -1;
    }
    return rc;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_stack_pop( HL7_Stack *stack, void *element )
{
    int rc;

    HL7_ASSERT( stack != 0 );

    if ( stack->top >= 0 )
    {
        if ( element != 0 )
        {
            memcpy( element, ( stack->data + stack->top * stack->element_size ), stack->element_size );
        }
        --stack->top;
        rc = 0;
    }
    else
    {
        rc = -1;
    }
    return rc;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_stack_clear( HL7_Stack *stack )
{
    stack->top = -1;
}


END_C_DECL()
