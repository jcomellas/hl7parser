#ifndef HL7PARSER_MESSAGE_H
#define HL7PARSER_MESSAGE_H

/**
* \file message.h
*
* HL7 message data types and functions.
*
* \internal
* Copyright (c) 2003-2011 \b Erlar (http://erlar.com)
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/alloc.h>
#include <hl7parser/element.h>
#include <hl7parser/export.h>
#include <hl7parser/node.h>
#include <hl7parser/segment.h>
#include <hl7parser/settings.h>
#include <stdarg.h>


BEGIN_C_DECL()

/* ------------------------------------------------------------------------
   Typedefs
   ------------------------------------------------------------------------ */

/**
* Tree of \c HL7_Node's holding an HL7 message.
* The structure of the HL7 node tree is the following. Vertical
* arrows indicate a sibling relationship (i.e. elements of the same type).
* Horizontal arrows indicate a parent-child relationship (i.e. subelements).
*
*\code
* 0/Segment 0 -> 0/Segment ID
*    |                |
*    |           1/Field 0 -> Repetition 0 -> Component 0 -> Subcomponent 0
*    |                |            |              |                |
*    |                |            |              |          Subcomponent n
*    |                |            |              |
*    |                |            |          Component n -> Subcomponent 0
*    |                |            |                               |
*    |                |            |                         Subcomponent n
*    |                |            |
*    |                |       Repetition n -> Component 0 -> Subcomponent 0
*    |                |                           |                |
*    |                |                           |          Subcomponent n
*    |                |                           |
*    |                |                       Component n -> Subcomponent 0
*    |                |                                            |
*    |                |                                      Subcomponent n
*    |                |
*    |         n+1/Field n -> Repetition 0 -> Component 0 -> Subcomponent 0
*    |                             |              |                |
*    |                             |              |          Subcomponent n
*    |                             |              |
*    |                             |          Component n -> Subcomponent 0
*    |                             |                                |
*    |                             |                         Subcomponent n
*    |                             |
*    |                        Repetition n -> Component 0 -> Subcomponent 0
*    |                                            |                |
*    |                                            |          Subcomponent n
*    |                                            |
*    |                                        Component n -> Subcomponent 0
*    |                                                             |
*    |                                                       Subcomponent n
*    |
* n/Segment n ...
* \endcode
*
* As we see, when dealing with fields, we have to adjust the index passed by
* the caller in order to keep it 0-based as the rest of the element types.
* We achieve this by adding 1 to the field index.
*/
typedef struct HL7_Message_Struct
{
    /**
    * First node of the message tree.
    */
    HL7_Node        *head;
    /**
    * Parser settings.
    */
    HL7_Settings    *settings;
    /**
    * Memory allocator for the nodes of the message tree.
    */
    HL7_Allocator   *allocator;

} HL7_Message;


/* ------------------------------------------------------------------------
   Function prototypes
   ------------------------------------------------------------------------ */

/**
* Initialize an HL7_Message.
* \param message The \c HL7_Message to be initialized.
* \param allocator Memory allocator used to reserve memory for the \c HL7_Node's
*                  in the \a message.
*/
HL7_EXPORT void hl7_message_init( HL7_Message *message, HL7_Settings *settings, HL7_Allocator *allocator );
/**
* Reset the contents of an HL7_Message.
* \warning The \a message must be an initialized message.
* \param message The \c HL7_Message to be initialized.
* \param allocator Memory allocator used to reserve memory for the \c HL7_Node's
*                  in the \a message.
* \see hl7_message_init()
*/
HL7_EXPORT void hl7_message_reset( HL7_Message *message, HL7_Settings *settings, HL7_Allocator *allocator );
/**
* Clear the \a message.
*/
HL7_EXPORT void hl7_message_fini( HL7_Message *message );

/**
* Returns the first node of the \a message.
*/
HL7_EXPORT HL7_Node *hl7_message_head( HL7_Message *message );

/**
* Sets the first node of the \a message. If there was a previous valid node
* as head of the message, it is destroyed together with all its children
* and siblings.
* \see hl7_message_head()
*/
HL7_EXPORT void hl7_message_set_head( HL7_Message *message, HL7_Node *head );

/**
* Allocate and initialize an \c HL7_Node that will be inserted in the \a message.
* \see hl7_message_destroy_node()
*/
HL7_EXPORT HL7_Node *hl7_message_create_node( HL7_Message *message );

/**
* Destroy and deallocate an \c HL7_Node that was created to be used with
* the \a message.
*
* \see hl7_message_create_node()
*/
HL7_EXPORT void hl7_message_destroy_node( HL7_Message *message, HL7_Node *node );

/**
* Destroy and deallocate an \c HL7_Node, all its children and optionally all
* its siblings.
*
* \see hl7_message_destroy_node()
*/
HL7_EXPORT void hl7_message_destroy_branch( HL7_Message *message, HL7_Node *node, const bool destroy_siblings );

/**
* Returns the node of type \a element_type that is located in the position
* indicated by the variable arguments.
* \warning All the positions are 0-based.
*
* e.g. to get the fourth field element of the second segment you would write:
*
* \code
* HL7_Message message;
* HL7_Node    *node;
*
* node = hl7_message_node( &message, HL7_ELEMENT_FIELD, 1, 3 );
* \endcode
*/
HL7_EXPORT HL7_Node *hl7_message_node( HL7_Message *message, HL7_Element_Type element_type, ... );

/**
* Returns the node of type \a element_type that is located in the position
* indicated by the variable argument list \a ap.
*
* \warning All the positions are 0-based.\n
* \n
* e.g. to get the fourth field element of the second segment you would write:
*
* \code
* HL7_Message message;
* HL7_Node    *node;
*
* node = hl7_message_node( &message, HL7_ELEMENT_FIELD, 1, 3 );
* \endcode
*/
HL7_EXPORT HL7_Node *hl7_message_node_va( HL7_Message *message, HL7_Element_Type element_type, va_list ap );

/**
* Returns the \a repetition of the segment with the ID \a segment_id.
*
* \warning All the positions are 0-based.
* \n
* e.g. to get the second instance of the NTE segment you would write:
*
* \code
* HL7_Message message;
* HL7_Segment nte;
*
* rc = hl7_message_segment( &message, &nte, "NTE", 1 );
* \endcode
* \return 0 if the segment was found.
* \return -1 if not.
*/
HL7_EXPORT int hl7_message_segment( HL7_Message *message, HL7_Segment *segment, const char *segment_id, size_t sequence );

HL7_EXPORT int hl7_message_segment_sibling( HL7_Message *message, HL7_Segment *sibling,
                                            HL7_Segment *segment, const char *segment_id );

HL7_EXPORT int hl7_message_append_segment( HL7_Message *message, HL7_Segment *segment );

END_C_DECL()

#endif /* HL7PARSER_MESSAGE_H */
