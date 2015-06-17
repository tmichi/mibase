#ifndef MI_FILE_LISTER_HPP
#define MI_FILE_LISTER_HPP 1
#include <vector>
#include <string>
namespace mi
{
        class FileLister
        {
	private:
                static std::string modify_path ( const std::string& path );
                static int list_all ( const std::string& path, std::vector<std::string>& result );
        public:
                static int list ( const std::string& path, const std::string& filter, std::vector<std::string>& result );
        };

}
#endif

