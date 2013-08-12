#ifndef HL7PARSER_BUFFER_H
#define HL7PARSER_BUFFER_H

/**
* \file buffer.h
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
#include <hl7parser/export.h>
#include <stddef.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------
   Typedefs
   ------------------------------------------------------------------------ */

/**
* \struct HL7_Buffer
* Buffer abstraction used by the HL7 parser. Its purpose is to enable
* efficient manipulation of arbitrarily-large messages without incurring
* much memory copying overhead.
* Used by the \c HL7_Lexer to read the HL7 message stream.
*
* \see HL7_Lexer
**/
typedef struct HL7_Buffer_Struct
{
    char    *base;
    size_t  size;
    size_t  rd_offset;
    size_t  wr_offset;
} HL7_Buffer;


/* ------------------------------------------------------------------------
   Function prototypes
   ------------------------------------------------------------------------ */

/**
* Initialize a \a buffer that assumes it has ownership of \a base, but in
* reality it doesnt (i.e., cannot delete it since it didn't malloc it!).
* Note that the \c size of the \a buffer will be \a size, but the \c length
* will be 0 until \c wr_ptr is set.
*/
HL7_EXPORT void hl7_buffer_init( HL7_Buffer *buffer, char *base, const size_t size );
/**
* Clear the \a buffer. Note that the memory allocated to the \a buffer will
* not be deleted since it wasn't malloc'd by the \a buffer.
*/
HL7_EXPORT void hl7_buffer_fini( HL7_Buffer *buffer );
/**
* Return the a pointer to the beginning of the \a buffer.
*/
HL7_EXPORT char *hl7_buffer_base( HL7_Buffer *buffer );
/**
* Get the read pointer.
*/
HL7_EXPORT char *hl7_buffer_rd_ptr( HL7_Buffer *buffer );
/**
* Get the offset of the read pointer (from the base).
*/
HL7_EXPORT size_t hl7_buffer_rd_offset( HL7_Buffer *buffer );
/**
* Get the write pointer.
*/
HL7_EXPORT char *hl7_buffer_wr_ptr( HL7_Buffer *buffer );
/**
* Get the offset of the write pointer (from the base).
*/
HL7_EXPORT size_t hl7_buffer_wr_offset( HL7_Buffer *buffer );
/**
* Return a pointer to 1 past the end of the allocated data in a \a buffer.
*/
HL7_EXPORT char *hl7_buffer_end( HL7_Buffer *buffer );
/**
* Set the read pointer.
*/
HL7_EXPORT void hl7_buffer_set_rd_ptr( HL7_Buffer *buffer, char *ptr );
/**
* Move the read pointer ahead \a offset bytes.
*/
HL7_EXPORT void hl7_buffer_move_rd_ptr( HL7_Buffer *buffer, size_t offset );
/**
* Set the write pointer.
*/
HL7_EXPORT void hl7_buffer_set_wr_ptr( HL7_Buffer *buffer, char *ptr );
/**
* Move the write pointer ahead \a offset bytes.
*/
HL7_EXPORT void hl7_buffer_move_wr_ptr( HL7_Buffer *buffer, size_t offset );
/**
* Returns the maximum length of the \a buffer.
*/
HL7_EXPORT size_t hl7_buffer_size( HL7_Buffer *buffer );
/**
* Returns the length of the used part of the \a buffer (\c wr_ptr - \c rd_ptr).
*/
HL7_EXPORT size_t hl7_buffer_length( HL7_Buffer *buffer );
/**
* Returns the number of bytes available in the \a buffer after the \c wr_ptr.
*/
HL7_EXPORT size_t hl7_buffer_space( HL7_Buffer *buffer );
/**
* Resets the \a buffer to contain nothing, i.e., sets the read and write
* pointers to align with the base.
*/
HL7_EXPORT void hl7_buffer_reset( HL7_Buffer *buffer );
/**
* Copies data into this \a buffer. Data is copied starting at the current write
* pointer.
* \warning The data is copied using using memcpy(), so it cannot overlap with
*          the buffer contents.
* \param buffer The buffer in which the data will be copied.
* \param ptr Pointer to the buffer to copy from.
* \param length The number of bytes to copy.
* \return 0 on success; the write pointer is advanced by \a length bytes.
* \return -1 if the amount of free space following the write pointer in
*            the block is less than \a length. Free space can be checked
*            by calling space().
*/
HL7_EXPORT int  hl7_buffer_copy( HL7_Buffer *buffer, const char *ptr, const size_t length );
/**
* Copies a NULL terminated character string into this \a buffer. The string is
* copied into the \a buffer starting at the current write pointer.
* \warning The 0-terminator is NOT included in the copied data.
* \warning The data is copied using using memcpy(), so it cannot overlap with
*          the buffer contents.
* \param buffer The buffer in which the data will be copied.
* \param str Pointer to the character string to copy from.
* \return 0 on success; the write pointer is advanced by the string's length,
*           (NOT including the 0 terminator).
* \return -1 if the amount of free space following the write pointer in the \a buffer
*            is less than required to hold the entire string. Free space can be
*            checked by calling space().
*/
HL7_EXPORT int  hl7_buffer_copy_str( HL7_Buffer *buffer, const char *str );
/**
* Copies a character into this \a buffer. The character is
* copied into the \a buffer starting at the current write pointer.
* \param buffer The buffer in which the data will be copied.
* \param c Character to copy from.
* \return 0 on success; the write pointer is advanced by 1,
* \return -1 if the amount of free space following the write pointer in the \a buffer
*            is less than required to hold the character. Free space can be
*            checked by calling space().
*/
HL7_EXPORT int  hl7_buffer_copy_char( HL7_Buffer *buffer, const char c );
/**
* Normalizes data in the \a buffer to align with the base, i.e., it "shifts"
* the data pointed to by \c rd_ptr down to the \c base and then readjusts
* \c rd_ptr to point to \c base and \c wr_ptr to point to \c base + the length
* of the moved data.
*/
HL7_EXPORT void hl7_buffer_crunch( HL7_Buffer *buffer );


END_C_DECL()

#endif /* HL7PARSER_BUFFER_H */
