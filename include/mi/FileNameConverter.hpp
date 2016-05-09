/**
 * @file FileNameConverter.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#ifndef MI_FILE_NAME_CONVERTER_HPP
#define MI_FILE_NAME_CONVERTER_HPP 1

#include <cctype>
#include <sstream>
#include <iomanip>
#include <memory>
#include "NonCopyable.hpp"
namespace mi
{
        /**
         * @class FileNameConverter FileNameConverter.hpp <mi/FileNameConverter.hpp>
         * @brief Converter for changing filename.
         */
        class FileNameConverter : public NonCopyable
        {
        public:
                /**
                 * @brief Contrucor.
                 * @param [in] filename File name.
                 */
                explicit FileNameConverter ( const std::string& filename = std::string() );
                /**
                 * @brief Destructor.
                 */
                ~FileNameConverter ( void );
                /**
                 * @brief Remove extension (".raw", ".stl" and so on ) from the filename.
                 * @return File name without extension.
                 */
                std::string removeExtension ( void ) const;
                /**
                 * @brief Add new extenstion to the filename.
                 * @param [in] ext new extension.
                 * @return File name with new extension.
                 */
                std::string getNewFileName ( const std::string& ext );

                /**
                 * @brief Add index and new extenstion to the filename.
                 * @param [in] ext new extension.
                 * @param [in] index new index.
                 * @param [in] fillN minimum order of index. If order of index is less than fillN, "0" is filled.
                 * @return File name with index and new extension.
                 */
                std::string getNewFileName ( const std::string& ext, const int index , const int fillN = 0 );

                /**
                 * @brief Get extension of the file.
                 * @retval Extension of the file.
                 */
                std::string getExtension ( void ) const;

                /**
                 * @brief Check the filename has the extension.
                 * @param [in] ext Extension.
                 * @retval true The file name has the extension.
                 * @retval true The file name does not hav the extension.
                 */
                bool checkExtension ( const std::string ext );

                /**
                 * @brief Get the original file name.
                 * @return File name.
                 */
                std::string getOriginal ( void ) const;
        private:
                /**
                 * @brief Capitalize the string.
                 * @param [in] str String.
                 @ return Capitalized string.
                 */
                std::string to_upper ( const  std::string str ) const;
        private:
                class Impl;
                std::unique_ptr<Impl> _impl;
        };
};
#endif// MI_FILE_NAME_CONVERTER_HPP
