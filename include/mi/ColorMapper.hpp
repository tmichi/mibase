#ifndef MI_COLOR_MAPPER_HPP
#define MI_COLOR_MAPPER_HPP 1
#include <memory>
namespace mi
{
        /**
         * @class ColorMapper
         * @brief Mapping scalar value to color map
         */
        class ColorMapper
        {
        public:
                explicit ColorMapper ( const double lower = 0.0, const double upper = 1.0 );
                ~ColorMapper ( void ) ;
                void convert ( const double value, double& r,  double& g, double& b );
                void convert ( const double value, int& r,  int& g, int& b );
                void convert ( const double value, unsigned char& r,  unsigned char& g, unsigned char& b );
        private:
                class Impl;
                std::unique_ptr<Impl> _impl;
        };
}
#endif
