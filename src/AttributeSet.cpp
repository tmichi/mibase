/**
 * @file AttributeSet.cpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#include <list>
#include <string>

#include <mi/AttributeSet.hpp>

namespace mi
{
        class AttributeSet::Impl
        {
        public:
                Impl ( void ) : _isAnd ( true )
                {
                        return;
                };

                ~Impl ( void )
                {
                        for ( Iterator iter = this->_attr.begin() ; iter != this->_attr.end() ; ++iter ) {
                                delete ( *iter );
                        }
                }

                void setOr ( void )
                {
                        this->_isAnd = false;
                        return;
                }

                Attribute& add ( Attribute* attribute )
                {
                        this->_attr.push_back ( attribute );
                        return *attribute;
                }

                bool isAnd ( void )
                {
                        return this->_isAnd;
                }

                Iterator begin ( void )
                {
                        return this->_attr.begin();
                }
                Iterator end ( void )
                {
                        return this->_attr.end();
                }
        private:
                bool _isAnd; ///< Flag whether this attribute set is "AND".
                std::list<Attribute*> _attr; ///< List of attributes.
        };

        AttributeSet::AttributeSet ( void ) : Attribute ( "" ) , _impls ( new Impl() )
        {
                return;
        }

        AttributeSet::~AttributeSet ( void )
        {
                if ( this->_impls != NULL ) {
                        delete this->_impls;
                        this->_impls = NULL;
                }

                return ;
        }

        AttributeSet&
        AttributeSet::setOr ( void )
        {
                this->_impls->setOr();
                return *this;
        }

        AttributeSet&
        AttributeSet::createAttributeSet ( void )
        {
                Attribute& attr = this->_impls->add ( new AttributeSet() );
                return dynamic_cast<AttributeSet&> ( attr );
        }

        BooleanAttribute&
        AttributeSet::createBooleanAttribute ( const std::string& key, bool& value , const std::string& message )
        {
                Attribute& attr =  this->_impls->add ( new BooleanAttribute ( key, value ) );
                attr.setMessage ( message );
                return dynamic_cast<BooleanAttribute& > ( attr );
        }

        StringAttribute&
        AttributeSet::createStringAttribute ( const std::string& key, std::string& value , const std::string& message )
        {
                Attribute& attr =  this->_impls->add ( new StringAttribute ( key, value ) );
                attr.setMessage ( message );
                return dynamic_cast<StringAttribute&> ( attr );
        }


        template<typename T>
        NumericAttribute<T>&
        AttributeSet::createNumericAttribute ( const std::string& key, T& value,  const std::string& message )
        {
                Attribute& attr =  this->_impls->add ( new NumericAttribute<T> ( key, value , 1 ) );
                attr.setMessage ( message );
                return dynamic_cast<NumericAttribute<T>& > ( attr );
        }

        template<typename T>
        DoubleNumericAttribute<T>&
        AttributeSet::createDoubleNumericAttribute ( const std::string& key, T& value0, T& value1, const std::string& message )
        {
                /// @todo should allocate memory in Double Numeric Attribute.
                NumericAttribute<T>* nAttr0 = new NumericAttribute<T> ( key, value0 , 1 );
                NumericAttribute<T>* nAttr1 = new NumericAttribute<T> ( key, value1 , 2 );
                Attribute& attr =  this->_impls->add ( new DoubleNumericAttribute<T> ( key, nAttr0, nAttr1 ) );
                attr.setMessage ( message );
                return dynamic_cast<DoubleNumericAttribute<T>& > ( attr );
        }

        template<typename T>
        TripleNumericAttribute<T>&
        AttributeSet::createTripleNumericAttribute ( const std::string& key, T& value0, T& value1, T& value2, const std::string& message )
        {
                NumericAttribute<T>* nAttr0 = new NumericAttribute<T> ( key, value0 , 1 );
                NumericAttribute<T>* nAttr1 = new NumericAttribute<T> ( key, value1 , 2 );
                NumericAttribute<T>* nAttr2 = new NumericAttribute<T> ( key, value2 , 3 );
                Attribute& attr = this->_impls->add ( new TripleNumericAttribute<T> ( key, nAttr0, nAttr1, nAttr2 ) );
                attr.setMessage ( message );
                return dynamic_cast<TripleNumericAttribute<T>& > ( attr );
        }

        bool
        AttributeSet::parse ( const Argument& arg )
        {
                Iterator begin = this->_impls->begin();
                Iterator end   = this->_impls->end();
                bool result;

                if ( this->_impls->isAnd() ) {
                        result = true;

                        for ( Iterator iter = begin ; iter != end ; ++iter ) {
                                result &= ( *iter )->parse ( arg );
                        }
                } else {
                        result  = false;

                        for ( Iterator iter = begin ; iter != end ; ++iter ) {
                                result |=  ( *iter )->parse ( arg );
                        }
                }

                if ( !result ) {
                        std::cerr << "error" << std::endl;
                        this->printError();
                }

                return result;
        }

        void
        AttributeSet::printError ( void )
        {
                for ( Iterator iter = this->_impls->begin() ; iter != this->_impls->end() ; iter++ ) {
                        ( *iter )->printError();
                }

                return;
        }

        void
        AttributeSet::print ( std::ostream& out )
        {
                out << "Arguments: " << std::endl;

                for ( Iterator iter = this->_impls->begin() ; iter != this->_impls->end() ; iter++ ) {
                        ( *iter )->print ( out );
                }

                return;
        }

        std::string
        AttributeSet::toString ( void ) const
        {
                return std::string ( "Attribute set" );
        }


        void
        AttributeSet::printUsage ( const std::string cmdStr )
        {
                std::cerr << "Usage : " << cmdStr << " [OPTIONS]" << std::endl
                          << std::endl
                          << "OPTIONS:" << std::endl;
                this->print_usage();
        }


        void
        AttributeSet::print_usage ( void )
        {
                for ( Iterator iter = this->_impls->begin() ; iter != this->_impls->end() ; iter++ ) {
                        ( *iter )->print_usage();
                }
        }

#ifndef ATTRIBUTE_SET__CREATE_NUMERIC_ATTRIBUTE
#define ATTRIBUTE_SET__CREATE_NUMERIC_ATTRIBUTE( TYPE ) template NumericAttribute<TYPE>&  AttributeSet::createNumericAttribute<TYPE>( const std::string& key, TYPE& value,  const std::string &message = std::string() )
        ATTRIBUTE_SET__CREATE_NUMERIC_ATTRIBUTE ( unsigned char ) ;
        ATTRIBUTE_SET__CREATE_NUMERIC_ATTRIBUTE ( char ) ;
        ATTRIBUTE_SET__CREATE_NUMERIC_ATTRIBUTE ( unsigned short ) ;
        ATTRIBUTE_SET__CREATE_NUMERIC_ATTRIBUTE ( short ) ;
        ATTRIBUTE_SET__CREATE_NUMERIC_ATTRIBUTE ( unsigned int ) ;
        ATTRIBUTE_SET__CREATE_NUMERIC_ATTRIBUTE ( int ) ;
        ATTRIBUTE_SET__CREATE_NUMERIC_ATTRIBUTE ( float ) ;
        ATTRIBUTE_SET__CREATE_NUMERIC_ATTRIBUTE ( double ) ;
#endif
#ifndef ATTRIBUTE_SET__CREATE_DOUBLE_NUMERIC_ATTRIBUTE
#define ATTRIBUTE_SET__CREATE_DOUBLE_NUMERIC_ATTRIBUTE( TYPE ) template DoubleNumericAttribute<TYPE>& AttributeSet::createDoubleNumericAttribute<TYPE>( const std::string& key, TYPE& value0, TYPE& value1, const std::string &message = std::string() )
        ATTRIBUTE_SET__CREATE_DOUBLE_NUMERIC_ATTRIBUTE ( unsigned char ) ;
        ATTRIBUTE_SET__CREATE_DOUBLE_NUMERIC_ATTRIBUTE ( char ) ;
        ATTRIBUTE_SET__CREATE_DOUBLE_NUMERIC_ATTRIBUTE ( unsigned short ) ;
        ATTRIBUTE_SET__CREATE_DOUBLE_NUMERIC_ATTRIBUTE ( short ) ;
        ATTRIBUTE_SET__CREATE_DOUBLE_NUMERIC_ATTRIBUTE ( unsigned int ) ;
        ATTRIBUTE_SET__CREATE_DOUBLE_NUMERIC_ATTRIBUTE ( int ) ;
        ATTRIBUTE_SET__CREATE_DOUBLE_NUMERIC_ATTRIBUTE ( float ) ;
        ATTRIBUTE_SET__CREATE_DOUBLE_NUMERIC_ATTRIBUTE ( double ) ;
#endif
#ifndef ATTRIBUTE_SET__CREATE_TRIPLE_NUMERIC_ATTRIBUTE
#define ATTRIBUTE_SET__CREATE_TRIPLE_NUMERIC_ATTRIBUTE( TYPE ) template  TripleNumericAttribute<TYPE>& AttributeSet::createTripleNumericAttribute<TYPE>( const std::string& key, TYPE& value0, TYPE& value1, TYPE& value2, const std::string &message = std::string() )
        ATTRIBUTE_SET__CREATE_TRIPLE_NUMERIC_ATTRIBUTE ( unsigned char ) ;
        ATTRIBUTE_SET__CREATE_TRIPLE_NUMERIC_ATTRIBUTE ( char ) ;
        ATTRIBUTE_SET__CREATE_TRIPLE_NUMERIC_ATTRIBUTE ( unsigned short ) ;
        ATTRIBUTE_SET__CREATE_TRIPLE_NUMERIC_ATTRIBUTE ( short ) ;
        ATTRIBUTE_SET__CREATE_TRIPLE_NUMERIC_ATTRIBUTE ( unsigned int ) ;
        ATTRIBUTE_SET__CREATE_TRIPLE_NUMERIC_ATTRIBUTE ( int ) ;
        ATTRIBUTE_SET__CREATE_TRIPLE_NUMERIC_ATTRIBUTE ( float ) ;
        ATTRIBUTE_SET__CREATE_TRIPLE_NUMERIC_ATTRIBUTE ( double ) ;
#endif

};
