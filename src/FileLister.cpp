#include <mi/FileLister.hpp>
#include <mi/Tokenizer.hpp>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)// Win32 API
#ifndef	OS_WINDOWS
#define	OS_WINDOWS 1
#endif	//OS_WINDOWS
#else
#ifndef OS_UNIX
#define OS_UNIX 1
#endif//OS_UNIX
#if defined (__APPLE__)
#ifndef OS_MAC
#define OS_MAC 1
#endif//OS_MAC
#elif defined(__linux__)
#ifndef OS_LINUX
#define OS_LINUX 1
#endif//OS_LINUX
#else
#ifndef OS_UNKNOWN
#define OS_UNKNOWN 1
#endif//OS_UNKNOWN
#endif//if defined __APPLE__ __linux
#endif//if defined 

#if defined (OS_WINDOWS)
#include <windows.h>
#else //MAC
#include <dirent.h>
#endif
namespace mi
{
        std::string
        FileLister::modify_path ( const std::string& path )
        {
#if defined (OS_WINDOWS)
                const static char SEPARATER = '\\';
#else
                const static char SEPARATER = '/';
#endif
                std::string path0 = path;
                const char lastChar = path0.at ( path0.length() - 1 );

                if ( lastChar != SEPARATER ) {
                        path0 += SEPARATER;
                }

                return path0;
        };

        int
        FileLister::list_all ( const std::string& path, std::vector<std::string>& result )
        {
                std::string path0 = FileLister::modify_path ( path );
                result.clear();
#if defined (OS_WINDOWS)
                HANDLE hSearch;
                WIN32_FIND_DATA fd;
                path0 += "*";
                hSearch = FindFirstFile ( path0.c_str(), &fd );

                if ( hSearch == INVALID_HANDLE_VALUE ) {
                        return 0;
                }

                while ( TRUE ) {
                        result.push_back ( std::string ( fd.cFileName ) );

                        if ( !FindNextFile ( hSearch, &fd ) ) {
                                break;
                        }
                }

                FindClose ( hSearch );
#else
                DIR* dir = opendir ( path0.c_str() );

                if ( dir == NULL ) {
                        return 0;        // dir is somewhat wrong ( wrong path, permission, etc)
                }

                for ( struct dirent* dp = readdir ( dir ) ; dp != NULL ; dp = readdir ( dir ) ) {
                        const std::string file = std::string ( dp->d_name );
                        result.push_back ( file );
                }

                closedir ( dir );
#endif
                return static_cast<int> ( result.size() );
        }

        int
        FileLister::list ( const std::string& path, const std::string& filter, std::vector<std::string>& result )
        {
                // step 1: decomposes extensions of filters
                std::vector< std::string > filters;
                mi::Tokenizer tokenizer ( filter, " ," );

                for ( int i = 0 ; i < tokenizer.size() ; ++i ) {
                        filters.push_back ( tokenizer.get ( i ) );
                }

                // step 2: lists all files
                typedef std::vector<std::string>::iterator string_iterator;
                std::vector< std::string > files;
                FileLister::list_all ( path, files );

                // step 3: removes the file without any filters.
                if ( filters.size() == 0 ) {
                        result.insert ( result.end(), files.begin(), files.end() );
                } else {
                        for ( string_iterator iter0 = files.begin() ; iter0 != files.end() ; ++iter0 ) {
                                for ( string_iterator iter1 = filters.begin() ; iter1 != filters.end() ; ++iter1 ) {
                                        const int n = static_cast<int> ( iter0->rfind ( *iter1 ) );

                                        if ( n > 0 && n == static_cast<int> ( iter0->length() - iter1->length() ) ) {
                                                std::string path0 = FileLister::modify_path ( path );
                                                path0 += *iter0;
                                                result.push_back ( path0 );
                                                break;
                                        }
                                }
                        }
                }

                return static_cast<int> ( result.size() );
        }
}


