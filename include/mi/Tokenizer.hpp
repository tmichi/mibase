/**
 * @file Tokenizer.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#ifndef MI_TOKENIZER_HPP
#define MI_TOKENIZER_HPP 1
#include <string>
#include <iostream>
#include <memory>
#include "NonCopyable.hpp"

namespace mi
{
        /**
         * @class Tokenizer Tokenizer.hpp "mi/Tokenizer.hpp"
         * @brief Tokenize the string.
         */
        class Tokenizer : public NonCopyable
        {
        public:
                /**
                 * @brief Constructor.
                 * @param [in] str String.
                 * @param [in] delimiter Delimiter of the string.
                 */
                explicit Tokenizer ( const std::string& str, const std::string delimiter = std::string ( " " ) );
                /**
                 * @brief Destructor.
                 */
                ~Tokenizer ( void );
                /**
                 * @brief Get the number of tokens.
                 * @return The number of tokens.
                 */
                int size ( void ) const;
                /**
                 * @brief Get a token.
                 * @param [in] i Index.
                 * @return Token.
                 */
                std::string get ( const int i ) const;

                /**
                 * @brief Print all tokens.
                 */
                void printAll ( std::ostream& out = std::cerr );
        private:
                class Impl;
		std::unique_ptr<Tokenizer::Impl> _impl;
        };
};
#endif//MI_TOKENIZER_HPP
