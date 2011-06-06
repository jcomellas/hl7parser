/**
* \file seg_qak.c
*
* Query acknowledgment segment (QAK) accessors for the HL7 parser.
*
* \internal
* Copyright (c) 2011 \b Erlar (http://erlar.com)
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
#include <hl7parser/seg_qak.h>

BEGIN_C_DECL()

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element *hl7_qak_query_tag( HL7_Segment *segment )
{
    return hl7_segment_field( segment, 0 );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_qak_set_query_tag( HL7_Segment *segment, HL7_Element *element )
{
    return hl7_segment_set_field( segment, 0, element );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_qak_set_query_tag_str( HL7_Segment *segment, const char *value )
{
    int         rc;
    HL7_Element element;

    rc = hl7_element_copy_str( &element, value, segment->allocator );

    return ( rc == 0 ? hl7_segment_set_field( segment, 0, &element ) : rc );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element *hl7_qak_query_response_status( HL7_Segment *segment )
{
    return hl7_segment_field( segment, 1 );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_qak_set_query_response_status( HL7_Segment *segment, HL7_Element *element )
{
    return hl7_segment_set_field( segment, 1, element );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_qak_set_query_response_status_str( HL7_Segment *segment, const char *value )
{
    int         rc;
    HL7_Element element;

    rc = hl7_element_copy_str( &element, value, segment->allocator );

    return ( rc == 0 ? hl7_segment_set_field( segment, 1, &element ) : rc );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element *hl7_qak_query_id( HL7_Segment *segment )
{
    return hl7_segment_component( segment, 2, 0 );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_qak_set_query_id( HL7_Segment *segment, HL7_Element *element )
{
    return hl7_segment_set_component( segment, 2, 0, element );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_qak_set_query_id_str( HL7_Segment *segment, const char *value )
{
    int         rc;
    HL7_Element element;

    rc = hl7_element_copy_str( &element, value, segment->allocator );

    return ( rc == 0 ? hl7_segment_set_component( segment, 2, 0, &element ) : rc );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element *hl7_qak_query_name( HL7_Segment *segment )
{
    return hl7_segment_component( segment, 2, 1 );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_qak_set_query_name( HL7_Segment *segment, HL7_Element *element )
{
    return hl7_segment_set_component( segment, 2, 1, element );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_qak_set_query_name_str( HL7_Segment *segment, const char *value )
{
    int         rc;
    HL7_Element element;

    rc = hl7_element_copy_str( &element, value, segment->allocator );

    return ( rc == 0 ? hl7_segment_set_component( segment, 2, 1, &element ) : rc );
}

END_C_DECL()