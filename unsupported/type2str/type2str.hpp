#ifndef MI_TYPE_2_STR_HPP
#define MI_TYPE_2_STR_HPP 1
#include <string>
namespace mi {
	template <typename T> 
	std::string type2str( void );	
	
	template <> 
	std::string type2str<char>( void ) {
		return std::string ("char");
	}
	
	template <> 
	std::string type2str<unsigned char>( void ) {
		return std::string ("uchar");
	}
	
	
	template <> 
	std::string type2str<short>( void ) {
		return std::string ("short");
	}
	
	template <> 
	std::string type2str<unsigned short>( void ) {
		return std::string ("ushort");
	}
	
	template <> 
	std::string type2str<int>( void ) {
		return std::string ("int");
	}
	
	template <> 
	std::string type2str<unsigned int>( void ) {
		return std::string ("uint");
	}
	
	template <> 
	std::string type2str<float>( void ) {
		return std::string ("float");
	}
	
	template <> 
	std::string type2str<double>( void ) {
		return std::string ("double");
	}
}

#endif// MI_TYPE_2_STR_HPP
