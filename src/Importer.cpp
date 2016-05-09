/**
 * @file Importer.cpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#include <mi/Importer.hpp>

namespace mi
{
        class Importer::Impl
        {
        public:
                Impl ( const bool isBinary ) : _isBinary ( isBinary )
                {
                        return ;
                }
                ~Impl ( void )
                {
                        return ;
                }
                bool& isBinary ( void )
                {
                        return this->_isBinary;
                }
        private:
                bool _isBinary;
        };

        Importer::Importer ( const bool isBinary ) : NonCopyable(), _impl ( new Impl ( isBinary ) )
        {
                return;
        }

        Importer::~Importer ( void )
        {
                return;
        }

        bool
        Importer::readHeader ( std::ifstream& fin )
        {
                return fin.good();
        }

        bool
        Importer::isBinary ( void ) const
        {
                return this->_impl->isBinary();
        }

        bool
        Importer::read ( const std::string& filename  )
        {
                std::ios_base::openmode mode = std::ios_base::in;

                if ( this->isBinary() ) {
                        mode |= std::ios::binary;
                }

                std::ifstream fin ( filename.c_str(), mode );

                if ( !fin ) {
                        std::cerr << filename << " cannot be open." << std::endl;
                        return false;
                }

                std::cerr << "reading data from " << filename << " as " << this->toString() << " format ... ";

                if ( !this->readHeader ( fin ) ) {
                        std::cerr << "failed. invalid header." << std::endl;
                        return false;
                }

                if ( !this->readBody ( fin ) ) {
                        std::cerr << "failed." << std::endl;
                        return false;
                }

                std::cerr << "done." << std::endl;
                return true;
        }
};
