/**
 * @file SvgRenderer.cpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#include <mi/SvgRenderer.hpp>
#include <mi/xml.hpp>
namespace mi
{
        class SvgRenderer::Impl : public NonCopyable
        {
        public:
                class Vector2d
                {
                public:
                        double x;
                        double y;
                private:
                        Vector2d ( const Vector2d& that );
                        void operator = ( const Vector2d& that );
                public:
                        explicit Vector2d ( const double x0 = 0, const double y0 = 0 ) : x ( x0 ), y ( y0 )
                        {
                                return;
                        }
                };
                void convert ( double& x, double& y )
                {
                        const double s = ( x - this->_bmin.x ) / ( this->_bmax.x - this->_bmin.x ) ;
                        const double t = ( y - this->_bmin.y ) / ( this->_bmax.y - this->_bmin.y ) ;
                        x = s * this->_size.x;
                        y = ( 1.0 - t ) * this->_size.y;
                        return;
                }

                Impl ( const int width, const int height, const std::string& filename )
                {
                        this->_size.x = width;
                        this->_size.y = height;
                        this->_filename = filename;
                        this->_xml = std::make_shared<XmlDocument>();
                        this->init();

                        return;
                }

                ~Impl ( void )
                {
                        return;
                }

                void init ( void )
                {
                        this->_stroke_dashed = 0;
                        this->setStrokeWidth ( 1.0 );
                        this->setStrokeColor ( std::string ( "#000000" ) );
                        this->setFillColor ( std::string ( "#000000" ) );
                        this->setFontSize ( 20 );
                        this->setFontFamily ( "serif" );
                        return;
                }

                const std::string& getFileName ( void )const
                {
                        return this->_filename;
                }

                void setViewBox ( const double mnx, const double mny, const double mxx, const double mxy )
                {
                        if ( std::fabs ( mxx - mnx ) < 1.0e-10 || std::fabs ( mxy - mny ) < 1.0e-10 ) {
                                std::cerr << "warning : invalid viewport size" << "(" << mnx << "," << mny << ")" << "-" << "(" << mxx << "," << mxy << ")" << std::endl;
                        }

                        this->_bmin.x = mnx;
                        this->_bmin.y = mny;

                        this->_bmax.x = mxx;
                        this->_bmax.y = mxy;

                        return;
                }

                void setStrokeWidth ( const double width )
                {
                        this->_stroke_width = width;
                }

                void setStrokeColor ( const std::string& col )
                {
                        this->_stroke_color = col;
                }

                void setFillColor ( const std::string& col )
                {
                        this->_fill_color = col;
                }

                void setStrokeDash ( const int dash_pitch )
                {
                        this->_stroke_dashed = dash_pitch;
                }

                void setFontSize ( const int size )
                {
                        this->_font_size = size;
                }

                void setFontFamily ( const std::string& family )
                {
                        this->_font_family = family;
                }

                double getStrokeWidth ( void ) const
                {
                        return this->_stroke_width;
                }

                std::string  getStrokeColor ( void ) const
                {
                        return this->_stroke_color;
                }

                std::string getFillColor ( void ) const
                {
                        return this->_fill_color;
                }

                int getStrokeDash ( void ) const
                {
                        return this->_stroke_dashed;
                }
                int getFontSize ( void ) const
                {
                        return this->_font_size;
                }
                std::string getFontFamily ( void ) const
                {
                        return this->_font_family;
                }

                std::shared_ptr<XmlDocument> getXml ( void )
                {
                        return this->_xml;
                }
        private:
                std::shared_ptr<XmlDocument> _xml;
                std::string _filename;

                int _stroke_dashed;
                double _stroke_width;
                std::string _stroke_color;
                std::string _fill_color;
                int _font_size;
                std::string _font_family;

                SvgRenderer::Impl::Vector2d _bmin;
                SvgRenderer::Impl::Vector2d _bmax;
                SvgRenderer::Impl::Vector2d _size;

        };

        // Definition of SvgRenderer

        SvgRenderer::SvgRenderer ( const int width, const int height, const std::string& filename )
                : NonCopyable(), _impl ( new SvgRenderer::Impl ( width, height, filename ) )
        {
                std::shared_ptr<mi::XmlElement> elem ( new mi::XmlElement ( "svg" ) ) ;
                elem->addAttribute ( "xmlns", "http://www.w3.org/2000/svg" );
                elem->addAttribute ( "xmlns:xlink", "http://www.w3.org/1999/xlink" );
                elem->addAttribute ( "width", std::to_string ( width ) );
                elem->addAttribute ( "height", std::to_string ( height ) );
                this->_impl->getXml()->addRoot ( elem );
                return;
        }

        SvgRenderer::~SvgRenderer ( void )
        {
                if ( !mi::XmlDocumentExporter ( this->_impl->getXml() ).write ( this->_impl->getFileName() ) ) {
                        std::cerr << "Saving failed." << std::endl;
                };
                return;
        }

        void
        SvgRenderer::setViewBox ( const double mnx, const double mny, const double mxx, const double mxy )
        {
                SvgRenderer::Impl& impl = * ( this->_impl );

                if ( std::fabs ( mxx - mnx ) < 1.0e-10 || std::fabs ( mxy - mny ) < 1.0e-10 ) {
                        std::cerr << "warning : invalid viewport size" << "(" << mnx << "," << mny << ")" << "-" << "(" << mxx << "," << mxy << ")" << std::endl;
                }

                impl.setViewBox ( mnx, mny, mxx, mxy );
                return;
        }

        void
        SvgRenderer::setStrokeWidth ( const double width )
        {
                SvgRenderer::Impl& impl = * ( this->_impl );
                impl.setStrokeWidth ( width );
                return;
        }

        void
        SvgRenderer::setStrokeColor ( const std::string& col )
        {
                SvgRenderer::Impl& impl = * ( this->_impl );
                impl.setStrokeColor ( col );
                return;
        }

        void
        SvgRenderer::setFillColor ( const std::string& col )
        {
                SvgRenderer::Impl& impl = * ( this->_impl );
                impl.setFillColor ( col );
                return;
        }

        void
        SvgRenderer::setStrokeDash ( const int dash_pitch )
        {
                SvgRenderer::Impl& impl = * ( this->_impl );
                impl.setStrokeDash ( dash_pitch );
                return;
        }

        void
        SvgRenderer::setFontSize ( const int size )
        {
                SvgRenderer::Impl& impl = * ( this->_impl );
                impl.setFontSize ( size );
                return;
        }

        void
        SvgRenderer::setFontFamily ( const std::string& family )
        {
                SvgRenderer::Impl& impl = * ( this->_impl );
                impl.setFontFamily ( family );
                return;
        }

        void
        SvgRenderer::drawLine ( const double x0 , const double y0, const double x1, const double y1 )
        {
                SvgRenderer::Impl& impl = * ( this->_impl );
                double v0x = x0;
                double v0y = y0;
                double v1x = x1;
                double v1y = y1;
                impl.convert ( v0x, v0y );
                impl.convert ( v1x, v1y );
                const int stroke_dashed = impl.getStrokeDash();
                const double stroke_width = impl.getStrokeWidth();
                const std::string stroke_color = impl.getStrokeColor();

                std::shared_ptr<XmlElement> elem ( new XmlElement ( "line" ) );
                elem->addAttribute ( "x1", std::to_string ( v0x ) );
                elem->addAttribute ( "y1", std::to_string ( v0y ) );
                elem->addAttribute ( "x2", std::to_string ( v1x ) );
                elem->addAttribute ( "y2", std::to_string ( v1y ) );

                if ( stroke_dashed > 0 ) {
                        elem->addAttribute ( "stroke-dasharray", std::to_string ( stroke_dashed ) );
                }

                elem->addAttribute ( "stroke-width", std::to_string ( stroke_width ) );
                elem->addAttribute ( "stroke", stroke_color );
                this->_impl->getXml()->getRoot()->addChild ( elem );
                return;
        }

        void
        SvgRenderer::drawCircle ( const double cx, const double cy, const double r )
        {
                SvgRenderer::Impl& impl = * ( this->_impl );
                double c0x = cx;
                double c0y = cy;
                impl.convert ( c0x, c0y );

                const int stroke_dashed = impl.getStrokeDash();
                const double stroke_width = impl.getStrokeWidth();
                const std::string stroke_color = impl.getStrokeColor();
                const std::string fill_color =  impl.getFillColor();;


                std::shared_ptr<XmlElement> elem ( new XmlElement ( "circle" ) );
                elem->addAttribute ( "cx", std::to_string ( c0x ) );
                elem->addAttribute ( "cy", std::to_string ( c0y ) );
                elem->addAttribute ( "r", std::to_string ( r ) );
                elem->addAttribute ( "stroke-width", std::to_string ( stroke_width ) );
                elem->addAttribute ( "stroke", stroke_color );

                if ( stroke_dashed > 0 ) {
                        elem->addAttribute ( "stroke-dasharray", std::to_string ( stroke_dashed ) );
                }

                elem->addAttribute ( "fill", fill_color );
                this->_impl->getXml()->getRoot()->addChild ( elem );
                return;
        }

        void
        SvgRenderer::drawRect ( const double x0, const double y0, const double w, const double h )
        {
                SvgRenderer::Impl& impl = * ( this->_impl );

                const int stroke_dashed = impl.getStrokeDash();
                const double stroke_width = impl.getStrokeWidth();
                const std::string stroke_color = impl.getStrokeColor();
                const std::string fill_color =  impl.getFillColor();;

                double v0x = x0;
                double v0y = y0;
                double v1x = x0 + w;
                double v1y = y0 + h;

                impl.convert ( v0x, v0y );
                impl.convert ( v1x, v1y );

                const double minx = v0x < v1x ? v0x : v1x;
                const double miny = v0y < v1y ? v0y : v1y;
                const double maxx = v0x < v1x ? v1x : v0x;
                const double maxy = v0y < v1y ? v1y : v0y;

                const double sizex = maxx - minx;
                const double sizey = maxy - miny;

                std::shared_ptr<XmlElement> elem ( new XmlElement ( "rect" ) );
                elem->addAttribute ( "x", std::to_string ( v0x ) );
                elem->addAttribute ( "y", std::to_string ( v0y ) );
                elem->addAttribute ( "width", std::to_string ( sizex ) );
                elem->addAttribute ( "height", std::to_string ( sizey ) );

                if ( stroke_dashed > 0 ) {
                        elem->addAttribute ( "stroke-dasharray", std::to_string ( stroke_dashed ) );
                }

                elem->addAttribute ( "stroke-width", std::to_string ( stroke_width ) );
                elem->addAttribute ( "stroke", stroke_color );
                elem->addAttribute ( "fill", fill_color );
                this->_impl->getXml()->getRoot()->addChild ( elem );
                return;
        }

        void
        SvgRenderer::drawText ( const double bx, const double by, const std::string& text, const std::string& align )
        {
                SvgRenderer::Impl& impl = * ( this->_impl );

                const std::string& fill_color =  impl.getFillColor();
                const int font_size = impl.getFontSize();
                const std::string&  font_family = impl.getFontFamily();
                double b0x = bx;
                double b0y = by;
                impl.convert ( b0x, b0y );

                std::shared_ptr<XmlElement> elem ( new XmlElement ( "text" ) );
                elem->addAttribute ( "x", std::to_string ( b0x ) );
                elem->addAttribute ( "y", std::to_string ( b0y ) );
                elem->addAttribute ( "font-family", font_family );
                elem->addAttribute ( "fill", fill_color );
                elem->addAttribute ( "font-size", std::to_string ( font_size ) );
                elem->addAttribute ( "align", align );

                std::shared_ptr<XmlText> tnode ( new XmlText ) ;
                tnode->setText ( text );
                elem->addChild ( tnode );
                this->_impl->getXml()->getRoot()->addChild ( elem );
                return;
        }
}

