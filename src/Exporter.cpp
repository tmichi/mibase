#include <mi/Exporter.hpp>
#include <string>
#include <iostream>
#include <fstream>
namespace mi
{
        Exporter::Exporter ( const bool isBinary ) : _isBinary ( isBinary )
        {
                return;
        }

        Exporter::~Exporter ( void )
        {
                return;
        }

        bool
        Exporter::writeHeader ( std::ofstream& fout )
        {
                return fout.good();
        }

        bool
        Exporter::isBinary ( void ) const
        {
                return  this->_isBinary;
        }

        bool
        Exporter::write ( const std::string& filename )
        {
                std::ios_base::openmode mode = std::ios_base::out;

                if ( this->_isBinary ) {
                        mode |= std::ios::binary;
                }

                std::ofstream fout ( filename.c_str(), mode );

                if ( !fout ) {
                        std::cerr << filename << "is not found." << std::endl;
                        return false;
                }

                std::cerr << "writing data to " << filename << " as " << this->toString() << " format ... ";

                if ( !this->writeHeader ( fout ) ) {
                        std::cerr << "failed." << std::endl
                                  << "file header was not written." << std::endl;
                        return false;
                }

                if ( !this->writeBody ( fout ) ) {
                        std::cerr << "failed." << std::endl
                                  << "file body was not written." << std::endl;
                        return false;
                }

                std::cerr << "done." << std::endl;
                return true;
        }
}
