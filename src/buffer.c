/**
* \file buffer.c
*
* Buffer abstraction used in the HL7 parser. Its purpose is to enable
* efficient manipulation of arbitrarily-large messages without incurring
* much memory copying overhead.
*
* \internal
* Copyright (c) 2003-2013 Juan Jose Comellas <juanjo@comellas.org>
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/buffer.h>
#include <hl7parser/export.h>
#include <string.h>

BEGIN_C_DECL()

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_buffer_init( HL7_Buffer *buffer, char *base, const size_t size )
{
    if ( buffer != 0 )
    {
        buffer->base    = base;
        buffer->size    = size;
        buffer->rd_offset  = 0;
        buffer->wr_offset  = 0;
    }
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_buffer_fini( HL7_Buffer *buffer )
{
    if ( buffer != 0 )
    {
        memset( buffer, 0, sizeof ( HL7_Buffer ) );
    }
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT char *hl7_buffer_base( HL7_Buffer *buffer )
{
    return buffer->base;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT char *hl7_buffer_rd_ptr( HL7_Buffer *buffer )
{
    return buffer->base + buffer->rd_offset;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT size_t hl7_buffer_rd_offset( HL7_Buffer *buffer )
{
    return buffer->rd_offset;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT char *hl7_buffer_wr_ptr( HL7_Buffer *buffer )
{
    return buffer->base + buffer->wr_offset;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT size_t hl7_buffer_wr_offset( HL7_Buffer *buffer )
{
    return buffer->wr_offset;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT char *hl7_buffer_end( HL7_Buffer *buffer )
{
    return buffer->base + buffer->size;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_buffer_set_rd_ptr( HL7_Buffer *buffer, char *ptr )
{
    HL7_ASSERT( ptr > buffer->base );

    buffer->rd_offset = ptr - buffer->base;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_buffer_move_rd_ptr( HL7_Buffer *buffer, const size_t offset )
{
    buffer->rd_offset += offset;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_buffer_set_wr_ptr( HL7_Buffer *buffer, char *ptr )
{
    HL7_ASSERT( ptr > buffer->base );

    buffer->wr_offset = ptr - buffer->base;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_buffer_move_wr_ptr( HL7_Buffer *buffer, size_t offset )
{
    buffer->wr_offset += offset;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT size_t hl7_buffer_size( HL7_Buffer *buffer )
{
    return buffer->size;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT size_t hl7_buffer_length( HL7_Buffer *buffer )
{
    return buffer->wr_offset - buffer->rd_offset;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT size_t hl7_buffer_space( HL7_Buffer *buffer )
{
    return buffer->size - buffer->wr_offset;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_buffer_reset( HL7_Buffer *buffer )
{
    buffer->rd_offset = 0;
    buffer->wr_offset = 0;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_buffer_copy( HL7_Buffer *buffer, const char *ptr, const size_t length )
{
    int rc;

    HL7_ASSERT( buffer != 0 && buffer->base != 0 );

    if ( buffer->size - buffer->wr_offset >= length )
    {
        memcpy( buffer->base + buffer->wr_offset, ptr, length );
        buffer->wr_offset += length;
        rc = 0;
    }
    else
    {
        rc = -1;
    }
    return rc;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_buffer_copy_str( HL7_Buffer *buffer, const char *str )
{
    HL7_ASSERT( str != 0 );

    return hl7_buffer_copy( buffer, str, strlen( str ) );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int  hl7_buffer_copy_char( HL7_Buffer *buffer, const char c )
{
    int     rc;

    HL7_ASSERT( buffer != 0 && buffer->base != 0 );

    if ( buffer->size - buffer->wr_offset >= 1 )
    {
        buffer->base[buffer->wr_offset++] = c;
        rc = 0;
    }
    else
    {
        rc = -1;
    }
    return rc;
}
/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_buffer_crunch( HL7_Buffer *buffer )
{
    char *rd_ptr = buffer->base + buffer->rd_offset;

    if ( rd_ptr > buffer->base )
    {
        size_t length = buffer->wr_offset - buffer->rd_offset;

        memmove( buffer->base, rd_ptr, length );

        /* Shift rd_offset and wr_offset so that rd_offset is aligned with base. */
        buffer->rd_offset = 0;
        buffer->wr_offset = length;
    }
}

END_C_DECL()

