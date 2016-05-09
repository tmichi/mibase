/**
 * @file Exporter.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#pragma once
#ifndef MI_EXPORTER_HPP
#define MI_EXPORTER_HPP 1

#include <string>
#include <fstream>
#include <memory>

#include "NonCopyable.hpp"
namespace mi
{
        /**
         * @class Exporter Exporter.hpp "Exporter.hpp"
         * @brief Base class for Exporters.
         */
        class Exporter : public NonCopyable
        {

        protected:
                /**
                 * @brief Constructor.
                 * @param [in] isBinary binary mode flag.
                 */
                explicit Exporter ( const bool isBinary = true );
                /**
                 * @brief Destructor.
                 */
                virtual ~Exporter ( void );
                /**
                 * @brief Write header part of the file.
                 * @retval true Success.
                 * @retval false Failure.
                 */
                virtual bool writeHeader ( std::ofstream& fout );
                /**
                 * @brief Write body part of the file.
                 * @retval true Success.
                 * @retval false Failure.
                 */
                virtual bool writeBody ( std::ofstream& fout ) = 0;

                /**
                 * @brief Check data mode.
                 * @retval true Binary mode.
                 * @retval false Ascii mode.
                 */
                bool isBinary ( void ) const;

        public:
                /**
                 * @brief Return exporter types.
                 * @return Exporter type.
                 */
                virtual std::string toString ( void ) const = 0;

                /**
                 * @brief Write data to a file.
                 * @return true Success.
                 * @return false Failure.
                 */
                bool write ( const std::string& filename );
        private:
                class Impl;
                std::unique_ptr<Impl> _impl;
//                const bool _isBinary; ///< Binary mode.
        };
}
#endif //MI_EXPORTER_HPP
