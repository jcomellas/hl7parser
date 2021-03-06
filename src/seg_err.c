/**
* \file seg_err.c
*
* Error information segment (ERR) accessors for the HL7 parser.
*
* \internal
* Copyright (c) 2011 Juan Jose Comellas <juanjo@comellas.org>
*
* \warning DO NOT MODIFY THIS FILE.
*
* Autogenerated by the ./hl7segdef.py script on Mon Jun  6 12:54:47 2011
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/element.h>
#include <hl7parser/export.h>
#include <hl7parser/segment.h>
#include <hl7parser/seg_err.h>

BEGIN_C_DECL()

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element *hl7_err_segment_id( HL7_Segment *segment )
{
    return hl7_segment_component( segment, 0, 0 );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_err_set_segment_id( HL7_Segment *segment, HL7_Element *element )
{
    return hl7_segment_set_component( segment, 0, 0, element );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_err_set_segment_id_str( HL7_Segment *segment, const char *value )
{
    int         rc;
    HL7_Element element;

    rc = hl7_element_copy_str( &element, value, segment->allocator );

    return ( rc == 0 ? hl7_segment_set_component( segment, 0, 0, &element ) : rc );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_err_sequence( HL7_Segment *segment )
{
    return hl7_element_int( hl7_segment_component( segment, 0, 1 ) );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_err_set_sequence( HL7_Segment *segment, HL7_Element *element )
{
    return hl7_segment_set_component( segment, 0, 1, element );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_err_set_sequence_int( HL7_Segment *segment, const int value )
{
    int         rc;
    HL7_Element element;

    rc = hl7_element_set_int( &element, value, segment->allocator );

    return ( rc == 0 ? hl7_segment_set_component( segment, 0, 1, &element ) : rc );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_err_field_pos( HL7_Segment *segment )
{
    return hl7_element_int( hl7_segment_component( segment, 0, 2 ) );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_err_set_field_pos( HL7_Segment *segment, HL7_Element *element )
{
    return hl7_segment_set_component( segment, 0, 2, element );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_err_set_field_pos_int( HL7_Segment *segment, const int value )
{
    int         rc;
    HL7_Element element;

    rc = hl7_element_set_int( &element, value, segment->allocator );

    return ( rc == 0 ? hl7_segment_set_component( segment, 0, 2, &element ) : rc );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element *hl7_err_error_code( HL7_Segment *segment )
{
    return hl7_segment_subcomponent( segment, 0, 3, 0 );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_err_set_error_code( HL7_Segment *segment, HL7_Element *element )
{
    return hl7_segment_set_subcomponent( segment, 0, 3, 0, element );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_err_set_error_code_str( HL7_Segment *segment, const char *value )
{
    int         rc;
    HL7_Element element;

    rc = hl7_element_copy_str( &element, value, segment->allocator );

    return ( rc == 0 ? hl7_segment_set_subcomponent( segment, 0, 3, 0, &element ) : rc );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element *hl7_err_error_text( HL7_Segment *segment )
{
    return hl7_segment_subcomponent( segment, 0, 3, 1 );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_err_set_error_text( HL7_Segment *segment, HL7_Element *element )
{
    return hl7_segment_set_subcomponent( segment, 0, 3, 1, element );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_err_set_error_text_str( HL7_Segment *segment, const char *value )
{
    int         rc;
    HL7_Element element;

    rc = hl7_element_copy_str( &element, value, segment->allocator );

    return ( rc == 0 ? hl7_segment_set_subcomponent( segment, 0, 3, 1, &element ) : rc );
}

END_C_DECL()
