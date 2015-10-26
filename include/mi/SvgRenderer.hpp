/**
 * @file SvgRenderer.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#ifndef MI_SVG_DRAWER_HPP
#define MI_SVG_DRAWER_HPP 1
#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
namespace mi
{
        /**
	 * @class SvgRenderer "SvgRenderer.hpp" <mi/SvgRenderer.hpp>
	 * @brief Light-weight drawing tools of vector graphics as SVG files.
	 * @note Current implementation supports drawing lines, circles and rectangles.
	 */
        class SvgRenderer
        {
	public:
		class Impl;
        private:
		Impl* _impl;
        public:
                SvgRenderer( const int width, const int height, const std::string& filename = std::string( "draw.svg" ) );
                ~SvgRenderer ( void );
                void setViewBox ( const double mnx, const double mny, const double mxx, const double mxy );

		// Attributes (width, font, colors.
                void init ( void );

                void setStrokeWidth ( const double width );
                void setStrokeColor( const std::string &col );
                void setFillColor( const std::string &col );
                void setStrokeDash( const int dash_pitch );
		void setFontSize ( const int size );
		void setFontFamily ( const std::string& family) ;
		
		// Drawing functions
                void drawLine ( const double x0 , const double y0, const double x1, const double y1 );
                void drawCircle ( const double cx, const double cy, const double r );
                void drawRect ( const double x0, const double y0, const double w, const double h );               
		void drawText ( const double bx, const double by, const std::string& text, const std::string& algin = std::string("start")); // start, end, middle
        };
}
#endif// MI_SVG_DRAWER_HPP
