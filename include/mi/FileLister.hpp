/**
 * @file FileLister.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#ifndef MI_FILE_LISTER_HPP
#define MI_FILE_LISTER_HPP 1
#include <vector>
#include <string>
namespace mi
{
        /**
         * @class FileLiter FileLister.hpp <mi/FileLister.hpp>
         * @brief List files 
         *
         */
        class FileLister
        {
	private:
                static std::string modify_path ( const std::string& path );
                static int list_all ( const std::string& path, std::vector<std::string>& result );
        public:
                /**
                 * @brief List file paths. 
                 * @param [in] path A path where you want to search
                 * @param [in] filter Filters. it is tokenized by a space and ",". e.g. "cpp,hpp txt"
                 * @param [out] result result paths. 
                 * @retval The number of listed paths
                 */
                static int list ( const std::string& path, const std::string& filter, std::vector<std::string>& result );
        };
}
#endif //MI_FILE_LISTER_HPP

