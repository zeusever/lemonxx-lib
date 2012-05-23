/**
* 
* @file     text
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/01/22
*/
#ifndef LEMON_CXX_SYS_TEXT_HPP
#define LEMON_CXX_SYS_TEXT_HPP
#include <vector>
#include <sstream>
#include <lemon/sys/text.h>
#include <lemonxx/sys/exception.hpp>
#include <lemonxx/utility/utility.hpp>

namespace lemon{

	typedef std::basic_string<lemon_char_t> String;

	typedef std::basic_stringstream<lemon_char_t> StringStream;

	inline std::string to_ascii(const String & source)
	{
		LEMON_DECLARE_ERRORINFO(errorCode);

		if(source.empty()) return "";

		std::vector<char> buffer(source.length() * 6 + 1);

		LemonToASCII(source.c_str(),source.length() + 1,(lemon::byte_t*)&buffer[0],buffer.size(),&errorCode);

		if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

		return &buffer[0];
	}

	inline String from_ascii(const std::string & source)
	{
		LEMON_DECLARE_ERRORINFO(errorCode);

		if(source.empty()) return LEMON_TEXT("");

		std::vector<lemon_char_t> buffer(source.length() * 6 + 1);

		LemonFromASCII((const lemon::byte_t*)source.c_str(),source.length() + 1,&buffer[0],buffer.size(),&errorCode);

		if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

		return &buffer[0];
	}
}

#endif  //LEMON_CXX_SYS_TEXT_HPP

