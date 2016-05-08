#include <mi/Argument.hpp>
#include <mi/Parse.hpp>
#include <deque>

namespace mi
{
        class Argument::Impl
        {
        private:
                Impl ( const Argument::Impl& that );
                void operator = ( const Argument::Impl& that );
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

                std::string get ( const size_t i ) const
                {
                        if ( i < this->size() ) {
                                return this->_argv.at ( i );
                        } else {
                                return std::string();
                        }
                }

                size_t size ( void ) const
                {
                        return this->_argv.size();
                }

        private:
                std::deque<std::string>  _argv; ///< Arguments.
        };


        Argument::Argument ( int argc, char** argv ) : NonCopyable(), _impl ( new Argument::Impl() )
        {
                for ( int i = 0 ; i < argc ; ++i ) {
                        this->add ( std::string ( argv[i] ) );
                }

                return;
        }

        Argument::~Argument ( void )
        {
                return;
        }

        int
        Argument::size ( void ) const
        {
                return static_cast<int> ( this->_impl->size() );
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
                return mi::parse<T> ( this->_impl->get ( static_cast<size_t> ( idx ) ) ) ;
        }

        int
        Argument::find ( const std::string& key, const int offset ) const
        {
                if ( offset < 0 ) {
                        return -1;        // Offset number is negative
                }

                const size_t end = static_cast<size_t> ( static_cast<int> ( this->size() ) - offset );

                for ( size_t i = 0 ; i < end ; ++i ) {
                        if ( this->_impl->get ( i ).compare ( key ) == 0 ) {
                                return static_cast<int> ( i ) + offset;
                        }
                }

                return -1; // any arguments are not matched.
        };

        void
        Argument::print ( std::ostream& out )
        {
                const size_t end = this->_impl->size();

                for ( size_t i = 0  ; i < end ; ++i ) {
                        const std::string str = this->_impl->get ( i );

                        if ( str.find ( "-", 0 ) == 0 ) {
                                out << std::endl;        //
                        }

                        out << str << " ";
                }

                out << std::endl;
                return;
        }


#define MI_ARGUMENT__GET2(TYPE) template TYPE Argument::get<TYPE> ( const std::string& key, const int offset ) const
        MI_ARGUMENT__GET2 ( unsigned char );
        MI_ARGUMENT__GET2 ( char );
        MI_ARGUMENT__GET2 ( unsigned short );
        MI_ARGUMENT__GET2 ( short );
        MI_ARGUMENT__GET2 ( unsigned int );
        MI_ARGUMENT__GET2 ( int );
        MI_ARGUMENT__GET2 ( float );
        MI_ARGUMENT__GET2 ( double );
        MI_ARGUMENT__GET2 ( std::string );
#define MI_ARGUMENT__GET(TYPE) template TYPE Argument::get<TYPE> ( const int idx ) const
        MI_ARGUMENT__GET ( unsigned char );
        MI_ARGUMENT__GET ( char );
        MI_ARGUMENT__GET ( unsigned short );
        MI_ARGUMENT__GET ( short );
        MI_ARGUMENT__GET ( unsigned int );
        MI_ARGUMENT__GET ( int );
        MI_ARGUMENT__GET ( float );
        MI_ARGUMENT__GET ( double );
        MI_ARGUMENT__GET ( std::string );
}
