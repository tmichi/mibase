/**
 * @file Tokenizer.cpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#include <mi/Tokenizer.hpp>
#include <vector>
namespace mi {
        class Tokenizer::Impl {
        private:
                Impl ( const Impl& that );
                void operator = ( const Impl& that );
        public:
                Impl ( void ) {
                        return;
                };
                ~Impl ( void ) {
                        return;
                }
                void add ( const std::string&  str ) {
                        this->_token.push_back ( str );
                }

                int size ( void ) const {
                        return static_cast<int> ( this->_token.size() );
                }

                std::string get ( const int i ) const {
                        if ( 0 <= i && i < this->size() ) return this->_token.at ( i );
                        else return std::string();
                }
        private:
                std::vector<std::string> _token; ///<Tokens
        };

        Tokenizer::Tokenizer ( const std::string& str, const std::string delimiter ) : _impl ( new Tokenizer::Impl() ) {
                std::string::size_type end;
                std::string line = str;
                for ( ; ; ) {
                        end = line.find_first_of ( delimiter );
                        if ( line.substr ( 0, end ).length() > 0 ) {
                                this->_impl->add ( line.substr ( 0, end ) );
                        }
                        if ( std::string::npos == end ) break;
                        line = line.substr ( end + 1 );
                }
                return;
        };
        Tokenizer::~Tokenizer ( void ) {
                if ( this->_impl != NULL ) {
                        delete this->_impl;
                        this->_impl = NULL;
                }
                return;
        }

        int
        Tokenizer::size ( void ) const {
                return this->_impl->size();
        }

        std::string
        Tokenizer::get ( const int i ) const {
                return this->_impl->get ( i );
        }

        void
        Tokenizer::printAll ( std::ostream& out ) {
                out << "Num. of tokens : " << this->size() << std::endl;
                for ( int i = 0 ; i < this->size() ; ++i ) {
                        out << "token[" << i << "] : " << this->_impl->get ( i ) << std::endl;
                }
                return;
        }
};

