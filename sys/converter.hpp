/**
* 
* @file     converter
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/08/20
*/
#ifndef LEMONXX_SYS_CONVERTER_HPP
#define LEMONXX_SYS_CONVERTER_HPP
#include <lemonxx/sys/text.hpp>

namespace lemon{

	inline std::string to_locale(const String & source)
	{
		error_info errorCode;

		if(source.empty()) return "";

		std::vector<char> buffer(source.length() * 6 + 1);

		LemonToLocale(source.c_str(),source.length() + 1,(lemon::byte_t*)&buffer[0],buffer.size(),&errorCode);

		errorCode.check_throw();

		return &buffer[0];
	}

	inline String from_locale(const std::string & source)
	{
		error_info errorCode;

		if(source.empty()) return LEMON_TEXT("");

		std::vector<lemon_char_t> buffer(source.length() * 6 + 1);

		LemonFromLocale((const lemon::byte_t*)source.c_str(),source.length() + 1,&buffer[0],buffer.size(),&errorCode);

		errorCode.check_throw();

		return &buffer[0];
	}


	inline std::string to_utf8(const String & source)
	{
		error_info errorCode;

		if(source.empty()) return "";

		std::vector<char> buffer(source.length() * 6 + 1);

		LemonToUTF8(source.c_str(),source.length() + 1,(lemon::byte_t*)&buffer[0],buffer.size(),&errorCode);

		errorCode.check_throw();

		return &buffer[0];
	}

	inline String from_utf8(const std::string & source)
	{
		error_info errorCode;

		if(source.empty()) return LEMON_TEXT("");

		std::vector<lemon_char_t> buffer(source.length() * 6 + 1);

		LemonFromUTF8((const lemon::byte_t*)source.c_str(),source.length() + 1,&buffer[0],buffer.size(),&errorCode);

		errorCode.check_throw();

		return &buffer[0];
	}

}

#endif //LEMONXX_SYS_CONVERTER_HPP