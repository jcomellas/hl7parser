#ifndef HL7PARSER_SEGMENT_H
#define HL7PARSER_SEGMENT_H

/**
* \file segment.h
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
#include <stdarg.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------
   Typedefs
   ------------------------------------------------------------------------ */

/**
* \struct HL7_Segment
* The structure of the HL7 segment tree is the following. Vertical
* arrows indicate a sibling relationship (i.e. elements of the same type).
* Horizontal arrows indicate a parent-child relationship (i.e. subelements).
*
* \code
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
* \endcode
*
* As we see, when dealing with fields, we have to start the search in the
* second field (position 1) so that the indexes passed by the caller
* correspond to the actual positions of the elements.
*/
typedef struct HL7_Segment_Struct
{
    /**
    * Node of the segment in the message.
    */
    HL7_Node        *message_node;

    /**
    * First node of the segment tree. This node contains the segment ID.
    */
    HL7_Node        *head;
    /**
    * Memory allocator for the nodes of the segment tree.
    */
    HL7_Allocator   *allocator;

} HL7_Segment;


/* ------------------------------------------------------------------------
   Function prototypes
   ------------------------------------------------------------------------ */

HL7_EXPORT int          hl7_segment_create( HL7_Segment *segment, const char *segment_id,
                                            HL7_Allocator *allocator );
HL7_EXPORT int          hl7_segment_create_copy( HL7_Segment *dest, HL7_Segment *src,
                                                 const bool copy_elements );
HL7_EXPORT void         hl7_segment_destroy( HL7_Segment *segment );

HL7_EXPORT void         hl7_segment_id( HL7_Segment *segment, char *buffer, size_t length );

HL7_EXPORT HL7_Element  *hl7_segment_field( HL7_Segment *segment,
                                            const size_t field_pos );
HL7_EXPORT int          hl7_segment_set_field( HL7_Segment *segment,
                                               const size_t field_pos,
                                               HL7_Element *element );

HL7_EXPORT HL7_Element  *hl7_segment_repetition( HL7_Segment *segment,
                                                 const size_t field_pos,
                                                 const size_t repetition_pos );
HL7_EXPORT int          hl7_segment_set_repetition( HL7_Segment *segment,
                                                    const size_t field_pos,
                                                    const size_t repetition_pos,
                                                    HL7_Element *element );

HL7_EXPORT HL7_Element  *hl7_segment_component( HL7_Segment *segment,
                                                const size_t field_pos,
                                                const size_t component_pos );
HL7_EXPORT int          hl7_segment_set_component( HL7_Segment *segment,
                                                   const size_t field_pos,
                                                   const size_t component_pos,
                                                   HL7_Element *element );

HL7_EXPORT HL7_Element  *hl7_segment_component_rep( HL7_Segment *segment,
                                                    const size_t field_pos,
                                                    const size_t repetition_pos,
                                                    const size_t component_pos );
HL7_EXPORT int          hl7_segment_set_component_rep( HL7_Segment *segment,
                                                       const size_t field_pos,
                                                       const size_t repetition_pos,
                                                       const size_t component_pos,
                                                       HL7_Element *element );

HL7_EXPORT HL7_Element  *hl7_segment_subcomponent( HL7_Segment *segment,
                                                   const size_t field_pos,
                                                   const size_t component_pos,
                                                   const size_t subcomponent_pos );
HL7_EXPORT int          hl7_segment_set_subcomponent( HL7_Segment *segment,
                                                      const size_t field_pos,
                                                      const size_t component_pos,
                                                      const size_t subcomponent_pos,
                                                      HL7_Element *element );

HL7_EXPORT HL7_Element  *hl7_segment_subcomponent_rep( HL7_Segment *segment,
                                                       const size_t field_pos,
                                                       const size_t repetition_pos,
                                                       const size_t component_pos,
                                                       const size_t subcomponent_pos );
HL7_EXPORT int          hl7_segment_set_subcomponent_rep( HL7_Segment *segment,
                                                          const size_t field_pos,
                                                          const size_t repetition_pos,
                                                          const size_t component_pos,
                                                          const size_t subcomponent_pos,
                                                          HL7_Element *element );

/**
* Returns the HL7 element of \a element_type from the \a segment in the position
* indicated by the variable arguments.
* \bug Should we return a null pointer or hl7_element_null()?
*/
HL7_EXPORT HL7_Element *hl7_segment_element( HL7_Segment *segment,
                                             const HL7_Element_Type element_type, ... );
/**
* Returns the HL7 element of \a element_type from the \a segment in the position
* indicated by the variable argument list \a ap.
* \bug Should we return a null pointer or hl7_element_null()?
*/
HL7_EXPORT HL7_Element *hl7_segment_element_va( HL7_Segment *segment,
                                                const HL7_Element_Type element_type,
                                                va_list ap );
HL7_EXPORT int hl7_segment_set_element( HL7_Segment *segment, HL7_Element *source,
                                        const HL7_Element_Type element_type, ... );
HL7_EXPORT int hl7_segment_set_element_int( HL7_Segment *segment, int value,
                                            const HL7_Element_Type element_type, ... );
HL7_EXPORT int hl7_segment_set_element_date( HL7_Segment *segment, time_t value,
                                             const bool include_time, const bool include_secs,
                                             const HL7_Element_Type element_type, ... );
HL7_EXPORT int hl7_segment_set_element_va( HL7_Segment *segment, HL7_Element *source,
                                           const HL7_Element_Type element_type,
                                           va_list ap );
/**
* Returns the \c HL7_Node containing an element of \a element_type from the
* \a segment in the position indicated by the variable arguments.
* \return The \c HL7_Node in the indicate position if it exists; 0 if not.
*/
HL7_EXPORT HL7_Node *hl7_segment_node( HL7_Segment *segment,
                                       const HL7_Element_Type element_type, ... );
/**
* Returns the \c HL7_Node containing an element of \a element_type from the
* \a segment in the position indicated by the variable argument list \a ap.
* \return The \c HL7_Node in the indicate position if it exists; 0 if not.
*
* \warning
*
* HL7 allows trailing optional items that have no value to be omitted.
* This causes an ambiguity because one same item can be interpreted in
* several ways when it is the first and only item present.
*
* e.g.: For HL7 the item in the third field (504599) is the same for
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
* \bug Resolve the ambiguity in the HL7 syntax. Ensure that we get the correct value
*      in all the cases. This means that for the second example we should always get
*      the "504599" value both by requesting the AUT.2 and the AUT.2.1 elements.
*/
HL7_EXPORT HL7_Node *hl7_segment_node_va( HL7_Segment *segment,
                                          const HL7_Element_Type element_type, va_list ap );


END_C_DECL()

#endif /* HL7PARSER_SEGMENT_H */
