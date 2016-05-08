#ifndef MI_INTERNAL_SYSTEM_INFO_INTERNAL
#define MI_INTERNAL_SYSTEM_INFO_INTERNAL 1

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <sstream>

//Windows
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)// Win32 API
#ifndef	OS_WINDOWS
#define	OS_WINDOWS 1
#include "SystemInfoInternalWindows.hpp"
#endif	//OS_WINDOWS
//Cygwin
#elif defined (__CYGWIN__)
#ifndef OS_CYGWIN
#define OS_CYGWIN 1
#include "SystemInfoInternalCygwin.hpp"
#endif//OS_CYGWIN 

#else //UNIX
#ifndef OS_UNIX
#define OS_UNIX 1
#include "SystemInfoInternalUnix.hpp"
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
#include "SystemInfoInternalUnknown.hpp"
#endif//OS_UNKNOWN
#endif//if defined __APPLE__ __linux

#endif//if defined win, cyg, unix

#endif //MI_INTERNAL_SYSTEM_INFO_INTERNAL_HPP
