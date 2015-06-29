/**
 * @file AttributeSet.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#pragma once
#ifndef MI_ATTRIBUTE_SET_HPP
#define MI_ATTRIBUTE_SET_HPP 1

#include <list>
#include <string>

#include "Attribute.hpp"
#include "BooleanAttribute.hpp"
#include "NumericAttribute.hpp"
#include "StringAttribute.hpp"
#include "DoubleNumericAttribute.hpp"
#include "TripleNumericAttribute.hpp"

namespace mi
{
        /**
         * @class AttributeSet "AttributeSet.hpp"  <mi/AttributeSet.hpp>
         * @brief Attribute set.
         *
         * This class represents a set of attributes.
         */
        class AttributeSet : public Attribute
        {
        protected:
                typedef std::list<Attribute*>::iterator Iterator;
        public:
                /**
                 * @brief Constructor.
                 */
                AttributeSet ( void );
                /**
                 * @brief Destructor.
                 */
                virtual ~AttributeSet ( void );

                /**
                 * @brief Set this class is "OR".
                 *
                 * When this method is called, return ATTRIBUTE_ERROR_OK if one of attributes is analyzed.
                 * @return Object itself.
                 */
                AttributeSet& setOr ( void );

                /**
                 * @brief Return instance of AttributeSet.
                 * @return The isntance.
                 * @note Created instance is released at AttributeSet::~AttributeSet(), or you do not have to take care it.
                 */
                AttributeSet& createAttributeSet ( void );

                /**
                 * @brief Return instance of BooleanAttribute.
                 * @return The isntance.
                 * @note Created instance is released at AttributeSet::~AttributeSet(), or you do not have to take care it.
                 */
                BooleanAttribute& createBooleanAttribute ( const std::string& key, bool& value , const std::string& message = std::string() );

                /**
                 * @brief Return instance of StringAttribute.
                 * @return he isntance.
                 * @note Created instance is released at AttributeSet::~AttributeSet(), or you do not have to take care it.
                 */
                StringAttribute& createStringAttribute ( const std::string& key, std::string& value , const std::string& message = std::string() );

                /**
                 * @brief Return instance of NumericAttribute.
                 * @return The isntance.
                 */
                template<typename T>
                NumericAttribute<T>& createNumericAttribute ( const std::string& key, T& value,  const std::string& message = std::string() ) ;

                template<typename T>
                DoubleNumericAttribute<T>& createDoubleNumericAttribute ( const std::string& key, T& value0, T& value1, const std::string& message = std::string() );

                template<typename T>
                TripleNumericAttribute<T>& createTripleNumericAttribute ( const std::string& key, T& value0, T& value1, T& value2, const std::string& message = std::string() );


                /**
                 * @brief Analyze all of childattributes.
                 * @retval true Success.
                 * @retval false Failure. Call AttributeSet::printError() to check which attribute is failed.
                 */
                bool parse ( const Argument& arg );

                /**
                 * @brief Print error messages on console.
                 */
                void printError ( void );

                /**
                 * @brief Print analysis result on console.
                 */
                void print ( std::ostream& out = std::cout );


                /**
                 * @brief print string.
                 * @return "Attribute set".
                 */
                std::string toString ( void ) const ;

                void printUsage ( const std::string cmdStr ) ;

                virtual void print_usage ( void ) ;
        private:
                bool _isAnd; ///< Flag whether this attribute set is "AND".
        protected:
                std::list<Attribute*> _attr; ///< List of attributes.
        };
};
#endif //MI_ATTRIBUTE_SET_HPP
