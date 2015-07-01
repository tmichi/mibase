/**
 * @file Importer.cpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#include <mi/Importer.hpp>

namespace mi
{
        Importer::Importer ( const bool isBinary ) : _isBinary ( isBinary )
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
        Importer::isBinary ( void )
        {
                return this->_isBinary;
        }

        bool
        Importer::read ( const std::string& filename  )
        {
                std::ios_base::openmode mode = std::ios_base::in;

                if ( this->_isBinary ) {
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
                } else if ( !this->readBody ( fin ) ) {
                        std::cerr << "failed." << std::endl;
                        return false;
                }

                std::cerr << "done." << std::endl;
                return true;
        }
};
