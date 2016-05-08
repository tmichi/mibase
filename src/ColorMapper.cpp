#include <mi/ColorMapper.hpp>
#include <mi/Clamp.hpp>
#include <cmath>
#include <iostream>
namespace mi
{
        /**
         * @class ColorMapper
         * @brief Mapping scalar value to color map
         */
        class ColorMapper::Impl
        {
        public:
                const double _lower;
                const double _upper;
        public:
                explicit Impl ( const double lower = 0.0, const double upper = 1.0 ) : _lower ( lower ), _upper ( upper )
                {
                        if ( lower >= upper ) {
                                std::cerr << "warning. lower value is larger than upper value. " << std::endl;
                        }

                        return;
                }

                ~Impl ( void )
                {
                        return;
                }

                double lower ( void ) const
                {
                        return this->_lower;
                }

                double upper ( void ) const
                {
                        return this->_upper;
                }

        };

        ColorMapper::ColorMapper ( const double lower, const double upper ) : _impl ( new Impl ( lower , upper ) )
        {
                return;
        }

        ColorMapper::~ColorMapper ( void )
        {
                if ( this->_impl != NULL ) {
                        delete this->_impl;
                        this->_impl = NULL;
                }

                return;
        }


        void
        ColorMapper::convert ( const double value, double& r,  double& g, double& b )
        {
                const double upper = this->_impl->upper();
                const double lower = this->_impl->lower();
                const double v = ( value - lower ) * 1.0 / ( upper - lower ) * 4;
                r = mi::clamp ( v   - 2.0                , 0.0, 1.0 );
                g = mi::clamp ( 2.0 - std::fabs ( 2.0 - v ), 0.0, 1.0 );
                b = mi::clamp ( 2.0 - v                  , 0.0, 1.0 );
                return;
        }

        void
        ColorMapper::convert ( const double value, int& r,  int& g, int& b )
        {
                double r0, g0, b0;
                this->convert ( value, r0, g0, b0 );
                r = static_cast<int> ( r0 * 255 ) ;
                g = static_cast<int> ( g0 * 255 ) ;
                b = static_cast<int> ( b0 * 255 ) ;
                return;
        }

        void
        ColorMapper::convert ( const double value, unsigned char& r,  unsigned char& g, unsigned char& b )
        {
                int r0, g0, b0;
                this->convert ( value, r0, g0, b0 );
                r = static_cast<unsigned char> ( r0 ) ;
                g = static_cast<unsigned char> ( g0 ) ;
                b = static_cast<unsigned char> ( b0 ) ;
                return;
        }
}

