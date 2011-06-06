/**
* \file node.c
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
#include <hl7parser/node.h>
#include <hl7parser/settings.h>
#include <stdarg.h>
#include <stddef.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_node_init( HL7_Node *node )
{
    hl7_element_init( &node->element );

    node->sibling   = 0;
    node->children  = 0;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_node_fini( HL7_Node *node, HL7_Allocator *allocator )
{
    node->children  = 0;
    node->sibling   = 0;

    hl7_element_fini( &node->element, allocator );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Node *hl7_node_next_sibling( HL7_Node *node )
{
    return ( node != 0 ? node->sibling : 0 );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Node *hl7_node_sibling( HL7_Node *node, size_t position )
{
    size_t i;

    for ( i = 0; i < position && node != 0; ++i )
    {
        node = node->sibling;
    }
    return node;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Node *hl7_node_add_sibling( HL7_Node *node, HL7_Node *sibling )
{
    if ( node != 0 )
    {
        /* FIXME: what happens if sibling is NULL and node->sibling is not NULL? */
        if ( sibling != 0 )
        {
            sibling->sibling = node->sibling;
        }
        node->sibling   = sibling;
        node            = sibling;
    }
    return node;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Node *hl7_node_append_sibling( HL7_Node *node, HL7_Node *sibling )
{
    if ( node != 0 )
    {
        while ( node->sibling != 0 )
        {
            node = node->sibling;
        }
        node = hl7_node_add_sibling( node, sibling );
    }
    return node;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Node *hl7_node_insert_sibling( HL7_Node *node, HL7_Node *sibling, const size_t position )
{
    if ( position != 0 )
    {
        size_t i = 0;

        while ( node != 0 )
        {
            if ( ++i < position )
            {
                node = node->sibling;
            }
            else
            {
                node = hl7_node_add_sibling( node, sibling );
                break;
            }
        }
    }
    else
    {
        node = 0;
    }
    return node;
}


/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Node *hl7_node_child( HL7_Node *node, const size_t position )
{
    if ( node != 0 )
    {
        size_t i;

        node = node->children;

        for ( i = 0; i < position && node != 0; ++i )
        {
            node = node->sibling;
        }
    }
    return node;
}


/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Node *hl7_node_add_child( HL7_Node *node, HL7_Node *child )
{
    if ( node != 0 )
    {
        /* FIXME: what happens if child is NULL and node->children is not NULL? */
        if ( child != 0 )
        {
            child->sibling = node->children;
        }
        node->children  = child;
        node            = child;
    }
    return node;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Node *hl7_node_append_child( HL7_Node *node, HL7_Node *child )
{
    if ( node != 0 )
    {
        if ( node->children != 0 )
        {
            node = hl7_node_append_sibling( node->children, child );
        }
        else
        {
            node = hl7_node_add_child( node, child );
        }
    }
    return node;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Node *hl7_node_insert_child( HL7_Node *node, HL7_Node *child, const size_t position )
{
    if ( node != 0 )
    {
        if ( position >= 1 )
        {
            node = hl7_node_insert_sibling( node->children, child, position );
        }
        else
        {
            node = hl7_node_add_child( node, child );
        }
    }
    return node;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Node *hl7_node_create( HL7_Allocator *allocator )
{
    HL7_Node *node;

    HL7_ASSERT( allocator != 0 );
    HL7_ASSERT( allocator->malloc != 0 );

    node = (HL7_Node *) allocator->malloc( sizeof ( HL7_Node ) );
    if ( node != 0 )
    {
        hl7_node_init( node );
    }
    return node;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_node_destroy( HL7_Node *node, HL7_Allocator *allocator )
{
    HL7_ASSERT( allocator != 0 );
    HL7_ASSERT( allocator->free != 0 );

    if ( node != 0 )
    {
        hl7_node_fini( node, allocator );

        allocator->mfree( node );
    }
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Node *hl7_node_create_branch( HL7_Node *node_begin, HL7_Element_Type start_type,
                                             HL7_Allocator *allocator, HL7_Element_Type element_type, ... )
{
    HL7_Node    *node;
    va_list     ap;

    va_start( ap, element_type );

    node = hl7_node_create_branch_va( node_begin, start_type, allocator, element_type, ap );

    va_end( ap );

    return node;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Node *hl7_node_create_branch_va( HL7_Node *node, HL7_Element_Type start_type,
                                                HL7_Allocator *allocator, HL7_Element_Type element_type, va_list ap )
{
    HL7_ASSERT( element_type >= HL7_ELEMENT_SUBCOMPONENT && element_type <= HL7_ELEMENT_SEGMENT );

    if ( node != 0 )
    {
        size_t              position;
        HL7_Element_Type    current_type;
        HL7_Node            *aux;
        HL7_Token           token;

        hl7_token_set( &token, 0, 0, HL7_TOKEN_ATTR_SEPARATOR );

        for ( current_type = start_type;
              current_type != HL7_ELEMENT_INVALID && current_type >= element_type;
              current_type = hl7_child_type( current_type ) )
        {
            position = va_arg( ap, size_t );
            /**
            * The first field in a segment is the segment ID, but it is not
            * taken into account when expressing an offset.
            */
            if ( current_type == HL7_ELEMENT_FIELD )
            {
                ++position;
            }

            while ( position > 0 )
            {
                if ( node->sibling == 0 )
                {
                    aux = hl7_node_create( allocator );
                    if ( aux != 0 )
                    {
                        hl7_element_set( &aux->element, &token, false );
                        node->sibling = aux;
                    }
                    else
                    {
                        node = 0;
                        break;
                    }
                }
                node = node->sibling;

                --position;
            }

            /**
            * We don't have to examine the children if we've already found the
            * node (element_type) we are looking for.
            */
            if ( current_type != element_type )
            {
                if ( node->children == 0 )
                {
                    aux = hl7_node_create( allocator );
                    if ( aux != 0 )
                    {
                        hl7_element_set( &aux->element, &token, false );
                        node->children = aux;
                    }
                    else
                    {
                        node = 0;
                        break;
                    }
                }
                node = node->children;
            }
        }
    }
    return node;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_node_destroy_branch( HL7_Node *node, HL7_Allocator *allocator, const bool destroy_siblings )
{
    HL7_ASSERT( message != 0 );

    while ( node != 0 )
    {
        if ( node->children != 0 )
        {
            hl7_node_destroy_branch( node->children, allocator, true );
        }

        if ( destroy_siblings )
        {
            HL7_Node *sibling = node->sibling;

            hl7_node_destroy( node, allocator );

            node = sibling;
        }
        else
        {
            break;
        }
    }
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Node *hl7_node_copy_branch( HL7_Node *src, HL7_Allocator *allocator,
                                           const bool copy_siblings,
                                           const bool copy_elements )
{
    HL7_Node    head;
    HL7_Node    *node   = &head;
    int         rc      = 0;

    head.sibling = 0;

    while ( src != 0 )
    {
        node->sibling = hl7_node_create( allocator );
        if ( node->sibling != 0 )
        {
            node = node->sibling;

            /* Copy the contents of the source element. */
            rc = ( copy_elements ?
                   hl7_element_create_copy( &node->element, &src->element, allocator ) :
                   hl7_element_copy( &node->element, &src->element, allocator, false ) );

            if ( rc == 0 )
            {
                /* Copy the children nodes. */
                node->children = hl7_node_copy_branch( src->children, allocator, true, copy_elements );

                if ( copy_siblings )
                {
                    src = src->sibling;
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
        else
        {
            rc = -1;
            break;
        }
    }

    if ( rc != 0 )
    {
        hl7_node_destroy_branch( head.sibling, allocator, true );
        head.sibling = 0;
    }
    return head.sibling;
}


END_C_DECL()
