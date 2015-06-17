#include <mi/Argument.hpp>
#include <mi/Parse.hpp>
#include <deque>

namespace mi
{
        class Argument::Impl
        {
        private:
                Impl ( const Impl& that );
                void operator = ( const Impl& that );
        public:
                Impl ( void )
                {
                        return;
                }

                ~Impl ( void )
                {
                        this->_argv.clear();
                        return;
                }

                void add ( const std::string& str )
                {
                        this->_argv.push_back ( str );
                        return;
                }

                std::string get ( const int i ) const
                {
                        if ( this->is_valid ( i ) ) return this->_argv.at ( i );
                        else return std::string();
                }

                int size ( void ) const
                {
                        return static_cast<int> ( this->_argv.size() );
                }
        private:
                bool is_valid ( const int i ) const
                {
                        return ( 0 <= i && i < this->size() );
                }
        private:
                std::deque<std::string>  _argv; ///< Arguments.
        };


        Argument::Argument ( int argc, char** argv ) : _impl ( new Argument::Impl() )
        {
                for ( int i = 0 ; i < argc ; ++i ) {
                        this->_impl->add ( std::string ( argv[i] ) );
                }
                return;
        }

        Argument::~Argument ( void )
        {
                if ( this->_impl != NULL ) {
                        delete this->_impl;
                        this->_impl = NULL;
                }
                return;
        }

        int
        Argument::size ( void ) const
        {
                return this->_impl->size();
        }

        Argument&
        Argument::add ( const std::string& str )
        {
                this->_impl->add ( str );
                return *this;
        }

        bool
        Argument::exist ( const std::string& key, const int offset ) const
        {
                return ( this->find ( key, offset ) > -1 );
        }

	template <typename T>
	T
	Argument::get ( const std::string& key, const int offset ) const
	{
		const int index = this->find ( key , offset );
		return this->get<T> ( index ) ;
	};
	
	
        template <typename T>
        T
        Argument::get ( const int idx ) const
        {
                return mi::parse<T> ( this->_impl->get ( idx ) ) ;
        }

        int
        Argument::find ( const std::string& key, const int offset ) const
        {
                if ( offset < 0 ) return -1;
                for ( int i = 0 ; i < this->size() - offset ; ++i ) {
                        if ( this->_impl->get ( i ).compare ( key ) == 0 ) return i + offset;
                }
                return -1; // any arguments are not matched.
        };

        void
        Argument::print ( std::ostream& out )
        {
                for ( int i = 0  ; i < this->size() ; ++i ) {
                        std::string str = this->_impl->get ( i );
                        if ( str.find ( "-", 0 ) == 0 ) out << std::endl; //
                        out << str << " ";
                }
                out << std::endl;
                return;
        }

#define ARGUMENT__GET2(TYPE) template TYPE Argument::get<TYPE> ( const std::string& key, const int offset ) const
        ARGUMENT__GET2 ( unsigned char );
        ARGUMENT__GET2 ( char );
        ARGUMENT__GET2 ( unsigned short );
        ARGUMENT__GET2 ( short );
        ARGUMENT__GET2 ( unsigned int );
        ARGUMENT__GET2 ( int );
        ARGUMENT__GET2 ( float );
        ARGUMENT__GET2 ( double );
        ARGUMENT__GET2 ( std::string );
#define ARGUMENT__GET(TYPE) template TYPE Argument::get<TYPE> ( const int idx ) const
        ARGUMENT__GET ( unsigned char );
        ARGUMENT__GET ( char );
        ARGUMENT__GET ( unsigned short );
        ARGUMENT__GET ( short );
        ARGUMENT__GET ( unsigned int );
        ARGUMENT__GET ( int );
        ARGUMENT__GET ( float );
        ARGUMENT__GET ( double );
        ARGUMENT__GET ( std::string );
}
