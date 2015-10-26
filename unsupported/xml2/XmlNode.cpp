#include "XmlNode.hpp"

#include <map>
#include <iostream>
namespace mi
{
        class XmlNode::Impl
        {
        private:
                Impl ( const Impl& that ) ;
                void operator = ( const Impl& that );
        public:
                Impl ( const std::string& node_name ) : _node_name( node_name ), _child_node( NULL ), _sibling_node( NULL ), _parent_node( NULL )
                {
                        return;
                }

                ~Impl ( void )
                {
                        return;
                }

                XmlNode* child( void )
                {
                        return this->_child_node;
                }

                XmlNode* sibling ( void )
                {
                        return this->_sibling_node;
                }

                XmlNode* parent ( void )
                {
                        return this->_parent_node;
                }

                void set_child( XmlNode* node )
                {
                        this->_child_node = node;
                }
                void set_sibling( XmlNode* node )
                {
                        this->_sibling_node = node;
                }
                void set_parent( XmlNode* node )
                {
                        this->_parent_node = node;
                }
                std::string name ( void ) const
                {
                        return this->_node_name;
                }
        private:
                std::string _node_name;
                XmlNode* _child_node; // Child node
                XmlNode* _sibling_node; // sibling node
                XmlNode* _parent_node;
        };

        XmlNode::XmlNode( const std::string& name ) : _impl ( new Impl ( name )  )
        {
                return;
        }

        XmlNode::~XmlNode ( void )
        {
                if ( this->_impl != NULL ) {
                        delete this->_impl;
                        this->_impl = NULL;
                }
                return;
        }

        XmlNode*
        XmlNode::getFirstChildNode( void )
        {
                return this->_impl->child();
        }

        XmlNode*
        XmlNode::getNextSiblingNode( void )
        {
                return this->_impl->sibling();
        }

        XmlNode*
        XmlNode::getParentNode( void )
        {
                return this->_impl->parent();
        }

        XmlDocument*
        XmlNode::getOwnerDocument ( void )
        {
                XmlNode* node = this;
                while ( node->getNodeType() != mi::XmlNodeElement ) {
                        node = node->getParentNode();
                }
                return ( XmlDocument* )node;
        }

        XmlNodeType
        XmlNode::getNodeType ( void ) const
        {
                return mi::XmlNodeInvalid;
        }

        std::string
        XmlNode::getNodeName ( void ) const
        {
                return this->_impl->name();
        }

        std::string
        XmlNode::getNodeValue( void )const
        {
                return std::string();
        }

        XmlNode*
        XmlNode::appendChild( XmlNode* newChild )
        {
                XmlNode* node = this->getFirstChildNode();
                if ( node == NULL ) {
                        this->_impl->set_child( newChild );
                } else {
                        while ( node->getNextSiblingNode() != NULL ) {
                                node = node->getNextSiblingNode();
                        }
                        node->_impl->set_sibling( newChild );
                }
                newChild->_impl->set_parent( this );
                return newChild;
        }
};

