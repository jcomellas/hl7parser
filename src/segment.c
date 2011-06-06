/**
* \file segment.c
*
* HL7 segment data types and functions.
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
#include <hl7parser/node.h>
#include <hl7parser/segment.h>
#include <string.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_segment_create( HL7_Segment *segment, const char *segment_id,
                                   HL7_Allocator *allocator )
{
    int         rc = -1;
    HL7_Node    *node;

    HL7_ASSERT( segment != 0 );
    HL7_ASSERT( allocator != 0 );
    HL7_ASSERT( segment_id != 0 );

    node = hl7_node_create( allocator );
    if ( node != 0 )
    {
        if ( hl7_element_copy_str( &node->element, segment_id, allocator ) == 0 )
        {
            segment->message_node   = 0;
            segment->head           = node;
            segment->allocator      = allocator;

            rc = 0;
        }
        else
        {
            hl7_node_destroy( node, allocator );
        }
    }
    return rc;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_segment_create_copy( HL7_Segment *dest, HL7_Segment *src,
                                        const bool copy_elements )
{
    int rc = -1;

    if ( dest != 0 && src != 0 )
    {
        dest->message_node  = 0;
        dest->head          = hl7_node_copy_branch( src->head, src->allocator, true, copy_elements );
        if ( dest->head != 0 )
        {
            dest->allocator = src->allocator;
            rc = 0;
        }
    }
    return rc;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_segment_destroy( HL7_Segment *segment )
{
    if ( segment != 0 )
    {
        if ( segment->head != 0 )
        {
            hl7_node_destroy_branch( segment->head, segment->allocator, true );
        }

        segment->message_node   = 0;
        segment->head           = 0;
        segment->allocator      = 0;
    }
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_segment_id( HL7_Segment *segment, char *buffer, size_t length )
{
    if ( buffer != 0 && length > HL7_SEGMENT_ID_LENGTH )
    {
        if ( segment != 0 && segment->head != 0 && segment->head->children != 0 )
        {
            HL7_Element *element = &segment->head->children->element;

            if ( element->length < length )
            {
                memcpy( buffer, element->value, element->length );
                buffer[element->length] = '\0';
            }
            else
            {
                *buffer = '\0';
            }
        }
        else
        {
            *buffer = '\0';
        }
    }
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element *hl7_segment_field( HL7_Segment *segment,
                                           const size_t field_pos )
{
    return hl7_segment_element( segment, HL7_ELEMENT_FIELD, field_pos );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_segment_set_field( HL7_Segment *segment, const size_t field_pos,
                                      HL7_Element *element )
{
    return hl7_segment_set_element( segment, element, HL7_ELEMENT_FIELD, field_pos );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element *hl7_segment_repetition( HL7_Segment *segment,
                                                const size_t field_pos,
                                                const size_t repetition_pos )
{
    return hl7_segment_element( segment, HL7_ELEMENT_REPETITION, field_pos, repetition_pos );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_segment_set_repetition( HL7_Segment *segment,
                                           const size_t field_pos, const size_t repetition_pos,
                                           HL7_Element *element )
{
    return hl7_segment_set_element( segment, element, HL7_ELEMENT_REPETITION,
                                    field_pos, repetition_pos );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element *hl7_segment_component( HL7_Segment *segment,
                                               const size_t field_pos,
                                               const size_t component_pos )
{
    return hl7_segment_element( segment, HL7_ELEMENT_COMPONENT,
                                field_pos, 0, component_pos );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_segment_set_component( HL7_Segment *segment,
                                          const size_t field_pos, const size_t component_pos,
                                          HL7_Element *element )
{
    return hl7_segment_set_element( segment, element, HL7_ELEMENT_COMPONENT,
                                    field_pos, 0, component_pos );
}


/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element *hl7_segment_component_rep( HL7_Segment *segment,
                                                   const size_t field_pos,
                                                   const size_t repetition_pos,
                                                   const size_t component_pos )
{
    return hl7_segment_element( segment, HL7_ELEMENT_COMPONENT,
                                field_pos, repetition_pos, component_pos );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_segment_set_component_rep( HL7_Segment *segment, const size_t field_pos,
                                              const size_t repetition_pos, const size_t component_pos,
                                              HL7_Element *element )
{
    return hl7_segment_set_element( segment, element, HL7_ELEMENT_COMPONENT,
                                    field_pos, repetition_pos, component_pos );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element *hl7_segment_subcomponent( HL7_Segment *segment,
                                                  const size_t field_pos,
                                                  const size_t component_pos,
                                                  const size_t subcomponent_pos )
{
    return hl7_segment_element( segment, HL7_ELEMENT_SUBCOMPONENT,
                                field_pos, 0, component_pos, subcomponent_pos );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_segment_set_subcomponent( HL7_Segment *segment, const size_t field_pos,
                                             const size_t component_pos, const size_t subcomponent_pos,
                                             HL7_Element *element )
{
    return hl7_segment_set_element( segment, element, HL7_ELEMENT_SUBCOMPONENT,
                                    field_pos, 0, component_pos, subcomponent_pos );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element *hl7_segment_subcomponent_rep( HL7_Segment *segment,
                                                      const size_t field_pos,
                                                      const size_t repetition_pos,
                                                      const size_t component_pos,
                                                      const size_t subcomponent_pos )
{
    return hl7_segment_element( segment, HL7_ELEMENT_SUBCOMPONENT,
                                field_pos, repetition_pos, component_pos, subcomponent_pos );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_segment_set_subcomponent_rep( HL7_Segment *segment, const size_t field_pos,
                                                 const size_t repetition_pos, const size_t component_pos,
                                                 const size_t subcomponent_pos, HL7_Element *element )
{
    return hl7_segment_set_element( segment, element, HL7_ELEMENT_SUBCOMPONENT,
                                    field_pos, repetition_pos, component_pos, subcomponent_pos );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element *hl7_segment_element( HL7_Segment *segment,
                                             const HL7_Element_Type element_type, ... )
{
    HL7_Element *element;
    va_list     ap;

    va_start( ap, element_type );
    element = hl7_segment_element_va( segment, element_type, ap );
    va_end( ap );

    return ( element );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element *hl7_segment_element_va( HL7_Segment *segment,
                                                const HL7_Element_Type element_type,
                                                va_list ap )
{
    HL7_Node *node;

    node = hl7_segment_node_va( segment, element_type, ap );

    /* FIXME: should we return a null pointer or hl7_element_null()? */
    return ( node != 0 ? &node->element : hl7_element_null() );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_segment_set_element( HL7_Segment *segment, HL7_Element *src,
                                        const HL7_Element_Type element_type, ... )
{
    int     rc;
    va_list ap;

    va_start( ap, element_type );
    rc = hl7_segment_set_element_va( segment, src, element_type, ap );
    va_end( ap );

    return ( rc );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_segment_set_element_str( HL7_Segment *segment, const char *str,
                                            const HL7_Element_Type element_type, ... )
{
    int         rc;
    va_list     ap;
    HL7_Element element;

    hl7_element_copy_str( &element, str, segment->allocator );

    va_start( ap, element_type );
    rc = hl7_segment_set_element_va( segment, &element, element_type, ap );
    va_end( ap );

    return ( rc );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_segment_set_element_int( HL7_Segment *segment, int value,
                                            const HL7_Element_Type element_type, ... )
{
    int         rc;
    HL7_Element element;

    hl7_element_init( &element );

    rc = hl7_element_set_int( &element, value, segment->allocator );
    if ( rc == 0 )
    {
        va_list ap;

        va_start( ap, element_type );
        rc = hl7_segment_set_element_va( segment, &element, element_type, ap );
        va_end( ap );
    }
    return ( rc );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_segment_set_element_date( HL7_Segment *segment, time_t value,
                                             const bool include_time, const bool include_secs,
                                             const HL7_Element_Type element_type, ... )
{
    int         rc;
    HL7_Element element;

    hl7_element_init( &element );

    rc = hl7_element_set_date( &element, value, include_time, include_secs,
                               segment->allocator );
    if ( rc == 0 )
    {
        va_list ap;

        va_start( ap, element_type );
        rc = hl7_segment_set_element_va( segment, &element, element_type, ap );
        va_end( ap );
    }
    return ( rc );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_segment_set_element_va( HL7_Segment *segment, HL7_Element *src,
                                           const HL7_Element_Type element_type, va_list ap )
{
    int         rc = -1;
    HL7_Node    *node;

    node = hl7_node_create_branch_va( segment->head, HL7_ELEMENT_FIELD,
                                      segment->allocator, element_type, ap );
    if ( node != 0 )
    {
        /* The destination element assumes ownership of the memory allocated
           in src->value.
        */
        rc = hl7_element_copy( &node->element, src, segment->allocator, true );
    }
    return ( rc );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Node *hl7_segment_node( HL7_Segment *segment,
                                       const HL7_Element_Type element_type, ... )
{
    HL7_Node    *node;
    va_list     ap;

    va_start( ap, element_type );

    node = hl7_segment_node_va( segment, element_type, ap );

    va_end( ap );

    return node;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Node *hl7_segment_node_va( HL7_Segment *segment,
                                          const HL7_Element_Type element_type, va_list ap )
{
    HL7_Node    *node;
    size_t      position;
    int         i;

    HL7_ASSERT( element_type >= HL7_ELEMENT_SUBCOMPONENT && element_type <= HL7_ELEMENT_SEGMENT );

    /*
    * The structure of the HL7 segment tree is the following. Vertical
    * arrows indicate a sibling relationship (i.e. elements of the same type).
    * Horizontal arrows indicate a parent-child relationship (i.e. subelements).
    *
    *   0/Segment ID
    *        |
    *   1/Field 0 -> Repetition 0 -> Component 0 -> Subcomponent 0
    *        |            |              |                |
    *        |            |              |          Subcomponent n
    *        |            |              |
    *        |            |          Component n -> Subcomponent 0
    *        |            |                               |
    *        |            |                         Subcomponent n
    *        |            |
    *        |       Repetition n -> Component 0 -> Subcomponent 0
    *        |                           |                |
    *        |                           |          Subcomponent n
    *        |                           |
    *        |                       Component n -> Subcomponent 0
    *        |                                            |
    *        |                                      Subcomponent n
    *        |
    * n+1/Field n -> Repetition 0 -> Component 0 -> Subcomponent 0
    *                     |              |                |
    *                     |              |          Subcomponent n
    *                     |              |
    *                     |          Component n -> Subcomponent 0
    *                     |                                |
    *                     |                         Subcomponent n
    *                     |
    *                Repetition n -> Component 0 -> Subcomponent 0
    *                                    |                |
    *                                    |          Subcomponent n
    *                                    |
    *                                Component n -> Subcomponent 0
    *                                                     |
    *                                               Subcomponent n
    *
    * As we see, when dealing with fields, we have to start the search in the
    * second field (position 1) so that the indexes passed by the caller
    * correspond to the actual positions of the elements.
    **/
    if ( segment != 0 && segment->head != 0 )
    {
        node = segment->head;

        if ( node != 0 )
        {
            bool resolve_ambiguity = false;

            node = node->sibling;

            for ( i = HL7_ELEMENT_FIELD; i >= element_type; --i )
            {
                position = va_arg( ap, size_t );

                /*
                * HL7 allows trailing optional elements that have no value to be omitted.
                * This causes an ambiguity because one same element can be interpreted in
                * several ways when it is the first and only element present.
                *
                * e.g.: For HL7 the element in the third field (504599) is the same for
                *       these two examples:
                *
                *       1) AUT||504599^^||||0000190447|^||
                *       2) AUT||504599||||0000190447|^||
                *
                *       But for this parser it has two different representations:
                *
                *       1) First component of the third field
                *       2) Third field
                *
                * To resolve the ambiguity in the HL7 syntax, whenever we find that node->children
                * is NULL we must check that the indexes we're looking for are not the first ones
                * for each element type. If they are, we must return the node before the first
                * NULL child.
                */
                if ( !resolve_ambiguity )
                {
                    node = hl7_node_sibling( node, position );

                    if ( i != element_type && node != 0 )
                    {
                        if ( node->children != 0 )
                        {
                            node = node->children;
                        }
                        else
                        {
                            resolve_ambiguity = true;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    if ( position != 0 )
                    {
                        node = 0;
                        break;
                    }
                }
            }
        }
    }
    else
    {
        node = 0;
    }
    return node;
}


END_C_DECL()
