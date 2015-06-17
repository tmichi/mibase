/**
 * @file FileNameConverter.cpp
 * @author Takashi Michikawa
 */
#include <mi/FileNameConverter.hpp>
#include <cctype>
#include <sstream>
#include <iomanip>

namespace mi
{

        FileNameConverter::FileNameConverter ( const std::string& filename ) : _filename ( filename )
        {
                return;
        }

        /**
         * @brief Destructor.
         */
        FileNameConverter::~FileNameConverter ( void )
        {
                return;
        }

        /**
         * @brief Remove extension (".raw", ".stl" and so on ) from the filename.
         * @return File name without extension.
         */
        std::string
        FileNameConverter::removeExtension ( void ) const
        {
                std::stringstream ss;
                ss << this->getOriginal().substr ( 0, this->getOriginal().find_last_of ( "." ) );
                return ss.str();
        }

        /**
         * @brief Add new extenstion to the filename.
         * @param [in] ext new extension.
         * @return File name with new extension.
         */
        std::string
        FileNameConverter::getNewFileName ( const std::string& ext )
        {
                std::stringstream ss;
                ss << this->removeExtension() << "." << ext;
                return ss.str();
        }

        std::string
        FileNameConverter::getNewFileName ( const std::string& ext, const int index , const int fillN )
        {
                std::stringstream ss;
                ss << this->removeExtension() << "-" << std::setw ( fillN ) << std::setfill ( '0' ) << index << "." << ext;
                return ss.str();
        }

        std::string
        FileNameConverter::getExtension ( void ) const
        {
                return this->_filename.substr ( this->_filename.find_last_of ( "." ) + 1 );
        }


        bool
        FileNameConverter::checkExtension ( const std::string ext )
        {
                const std::string src = this->getExtension();
                const std::string src_upper = this->to_upper ( src );
                const std::string ext_upper = this->to_upper ( ext );
                return src_upper.compare ( ext_upper ) == 0;
        }

        std::string
        FileNameConverter::getOriginal ( void ) const
        {
                return this->_filename;
        }
        std::string
        FileNameConverter::to_upper ( const  std::string str ) const
        {
                std::string result = str;
                for ( std::string::iterator iter = result.begin() ; iter != result.end() ; iter++ ) {
                        *iter = static_cast<char> ( std::toupper ( *iter ) );
                }
                return result;
        }
};

