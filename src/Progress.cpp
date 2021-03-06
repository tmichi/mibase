/**
 * @file Progress.cpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#include <mi/Progress.hpp>

#include <cmath>
#include <sstream>
#include <iostream>
#include <iomanip>

namespace mi
{
        class Progress::Impl : public NonCopyable
        {
        public:
                Impl ( const int maxStep, const int width ) : NonCopyable(), _maxStep ( maxStep ), _width ( width ), _current ( 0 ), _isReturned ( false )
                {
                        return;
                }
                bool  add ( void )
                {
                        if ( this->end() ) {
                                return false;
                        }

                        this->_current += 1;
                        return true;
                }

                bool end ( void )
                {
                        return this->getMaxSteps() <= this->getCurrentSteps();
                }
                int getMaxSteps ( void ) const
                {
                        return this->_maxStep;
                }

                int getCurrentSteps ( void ) const
                {
                        return this->_current;
                }

                int getWidth ( void ) const
                {
                        return this->_width;
                }

                bool isReturned ( void ) const
                {
                        return this->_isReturned;
                }

                void setReturned ( void )
                {
                        this->_isReturned = true;
                }
        private:
                int _maxStep; ///< Max value.
                int _width;    ///< Display width
                int _current;  ///< Current value.
                bool _isReturned; ///< Flag for adding end line.
        };



        Progress::Progress ( const int maxSteps, const int width ) : _impl ( new Impl ( maxSteps, width ) )
        {
                std::cerr << std::endl;
                std::cerr << "Progress : " << this->to_string();
                return;
        }

        Progress::~Progress ( void )
        {
                return ;
        }

        void
        Progress::print ( void )
        {
                if ( this->_impl->isReturned() ) {
                        return;
                }

                const int keta = this->_impl->getWidth() * 2 + 1;

                for ( int i = 0 ; i < keta; ++i ) {
                        std::cerr << "\b";
                }

                std::cerr << this->to_string();

                if ( this->_impl->end() ) {
                        std::cerr << std::endl;
                        this->_impl->setReturned();
                }

                return;
        }

        bool
        Progress::addCounter ( void )
        {
                if ( this->_impl->end() ) {
                        return false;
                }

                this->_impl->add();
                return true;
        }

        std::string
        Progress::to_string ( void ) const
        {
                std::stringstream ss;

                if ( this->_impl->getCurrentSteps() <= this->_impl->getMaxSteps() ) {
                        ss << std::setw ( this->_impl->getWidth() ) << std::setfill ( ' ' ) << this->_impl->getCurrentSteps() << "/"
                           << std::setw ( this->_impl->getWidth() ) << std::setfill ( ' ' ) << this->_impl->getMaxSteps();
                }

                return ss.str();
        }
}

