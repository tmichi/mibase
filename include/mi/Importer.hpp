/**
 * @file Importer.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#pragma once
#ifndef MI_IMPORTER_HPP
#define MI_IMPORTER_HPP 1

#include <string>
#include <iostream>
#include <fstream>
#include <memory>

#include "NonCopyable.hpp"
namespace mi
{
        /**
         * @class Importer
         * @brief Base class for Impoters.
         */
        class Importer : public NonCopyable
        {
        protected:
                /**
                 * @brief Constructor.
                 * @param [in] isBinary Open binary mode for reading.
                 */
                explicit Importer ( const bool isBinary = true );

                /**
                 * @brief Destructor.
                 */
                virtual ~Importer ( void );

                /**
                 * @brief Read header part of the file.
                 * @retval true Success.
                 * @retval false Failure.
                 */
                virtual bool readHeader ( std::ifstream& fin );

                /**
                 * @brief Read body part of the file.
                 * @retval true Success.
                 * @retval false Failure.
                 */
                virtual bool readBody ( std::ifstream& fin ) = 0;

                /**
                 * @brief Return importer types.
                 * @return Importer type.
                 */
                virtual std::string toString ( void ) const = 0;


                bool isBinary ( void ) const;

        public:
                /**
                 * @brief Read data from a file.
                 * @return true Success.
                 * @return false Failure.
                 */
                bool read ( const std::string& filename  );
        private:
                class Impl;
                std::unique_ptr<Impl> _impl;
        };
};
#endif//MI_IMPORTER_HPP
