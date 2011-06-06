#ifndef HL7PARSER_NODE_H
#define HL7PARSER_NODE_H

/**
* \file node.h
*
* Node used to hold elements in an HL7 message tree.
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
#include <stdarg.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------
   Typedefs
   ------------------------------------------------------------------------ */

/**
* \struct HL7_Node
* An HL7 message is represented by a tree of HL7_Node's.
**/
typedef struct HL7_Node_Struct
{
    /**
    * The value contained in the \a HL7_Node.
    */
    HL7_Element element;
    /**
    * The elements at the same level are stored as a linked list of sibling nodes.
    */
    struct HL7_Node_Struct *sibling;
    /**
    * The child elements are stored as a linked list of child nodes.
    **/
    struct HL7_Node_Struct *children;

} HL7_Node;


/* ------------------------------------------------------------------------
   Function prototypes
   ------------------------------------------------------------------------ */

/** Initialize an HL7_Node. **/
HL7_EXPORT void hl7_node_init( HL7_Node *node );
/** Clear an HL7_Node. **/
HL7_EXPORT void hl7_node_fini( HL7_Node *node, HL7_Allocator *allocator );

/**
* Return the sibling node following the one passed as argument.
**/
HL7_EXPORT HL7_Node *hl7_node_next_sibling( HL7_Node *node );
/**
* Return the sibling node in the indicated position. The positions are 0 based
* and the node passed as first argument is in position 0.
**/
HL7_EXPORT HL7_Node *hl7_node_sibling( HL7_Node *node, const size_t position );
/**
* Add a sibling node after the node passed as first argument.
* \return A pointer to the node that was added as a sibling.
* \return NULL if it couldn't be added.
**/
HL7_EXPORT HL7_Node *hl7_node_add_sibling( HL7_Node *node, HL7_Node *sibling );
/**
* Add a node as the last sibling of the node passed as first argument.
* \return A pointer to the node that was added as a sibling.
* \return NULL if it couldn't be added.
**/
HL7_EXPORT HL7_Node *hl7_node_append_sibling( HL7_Node *node, HL7_Node *sibling );
/**
* Add a sibling node in the position indicated by the last argument.
* \param node The HL7_Node where the \a sibling will be inserted.
* \param sibling The HL7_Node that will be inserted.
* \param position The position where the sibling will be added; must be 1 or bigger.
* \return A pointer to the node that was added as a sibling.
* \return NULL if it couldn't be added.
**/
HL7_EXPORT HL7_Node *hl7_node_insert_sibling( HL7_Node *node, HL7_Node *sibling, const size_t position );

/**
* Return the child node in the indicated position. The positions are 0 based.
**/
HL7_EXPORT HL7_Node *hl7_node_child( HL7_Node *node, const size_t position );
/**
* Add a node as the first child of the node passed as first argument.
* \return A pointer to the node that was added as a child.
* \return NULL if it couldn't be added.
**/
HL7_EXPORT HL7_Node *hl7_node_add_child( HL7_Node *parent, HL7_Node *child );
/**
* Add a node as the last child of the node passed as first argument.
* \return A pointer to the node that was added as a child.
* \return NULL if it couldn't be added.
**/
HL7_EXPORT HL7_Node *hl7_node_append_child( HL7_Node *parent, HL7_Node *child );
/**
* Add a child node in the position indicated by the last argument.
* \param parent The HL7_Node where the \a child will be inserted.
* \param child The HL7_Node that will be inserted.
* \param position The position where the sibling will be added.
* \return A pointer to the node that was added as a sibling.
* \return NULL if it couldn't be added.
**/
HL7_EXPORT HL7_Node *hl7_node_insert_child( HL7_Node *parent, HL7_Node *child, const size_t position );
/**
* Allocate and initialize an \c HL7_Node using the provided \a allocator.
* \see hl7_node_init(), hl7_node_destroy()
*/
HL7_EXPORT HL7_Node *hl7_node_create( HL7_Allocator *allocator );
/**
* Destroy and deallocate an \c HL7_Node that was created with the provided
* \a allocator.
*
* \see hl7_node_fini(), hl7_node_create()
*/
HL7_EXPORT void hl7_node_destroy( HL7_Node *node, HL7_Allocator *allocator );
/**
* Create a node of type \a element_type in the position indicated by the
* variable arguments using the \a allocator. If the intermediate nodes
* don't exist they are created. Both the initial \a node and its contents
* (\c node-\\>element) must be valid.
* \return The node that was created in the indicated position.
*/
HL7_EXPORT HL7_Node *hl7_node_create_branch( HL7_Node *node_begin, HL7_Element_Type start_type,
                                             HL7_Allocator *allocator, HL7_Element_Type element_type, ... );
/**
* Create a node of type \a element_type in the position indicated by the
* variable argument list \a ap using the \a allocator. If the intermediate nodes
* don't exist they are created. Both the initial \a node and its contents
* (\c node-\\>element) must be valid.
* \return The node that was created in the indicated position.
*/
HL7_EXPORT HL7_Node *hl7_node_create_branch_va( HL7_Node *node, HL7_Element_Type start_type,
                                                HL7_Allocator *allocator, HL7_Element_Type element_type,
                                                va_list ap );
/**
* Destroy and deallocate an \c HL7_Node, all its children and optionally all
* its siblings.
*
* \see hl7_node_destroy(), hl7_node_create_branch()
**/
HL7_EXPORT void hl7_node_destroy_branch( HL7_Node *node, HL7_Allocator *allocator,
                                         const bool destroy_siblings );

HL7_EXPORT HL7_Node *hl7_node_copy_branch( HL7_Node *src, HL7_Allocator *allocator,
                                           const bool copy_siblings,
                                           const bool copy_elements );

END_C_DECL()

#endif /* HL7PARSER_NODE_H */
