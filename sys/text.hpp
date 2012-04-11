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

	typedef std::string utf8string;

	typedef std::basic_string<utf16_t> utf16string;

	typedef std::basic_string<lemon_syschar_t> systring;

	typedef std::basic_ostringstream<lemon_syschar_t> sysostringstream;

	typedef std::basic_stringstream<lemon_syschar_t> systringstream;

	typedef std::basic_istringstream<lemon_syschar_t> sysistringstream;

	inline std::string to_utf8(const std::string & source)
	{
		if(source.empty()) return source;

		LEMON_DECLARE_ERRORINFO(errorinfo);

		std::vector<char> buffer(source.size() * 6 + 1,0);

		LemonLocaleToUTF8(source.c_str(),source.size(),&buffer[0],buffer.size(),&errorinfo);

		if(LEMON_FAILED(errorinfo)) throw Exception("call LemonLocaleToUTF8 exception",errorinfo);

		return &buffer[0];
	}

	inline std::string from_utf8(const std::string & source)
	{
		if(source.empty()) return source;

		LEMON_DECLARE_ERRORINFO(errorinfo);

		std::vector<char> buffer(source.size() + 1,0);

		LemonUTF8ToLocale(source.c_str(),source.size(),&buffer[0],buffer.size(),&errorinfo);

		if(LEMON_FAILED(errorinfo)) throw Exception("call LemonLocaleToUTF8 exception",errorinfo);

		return &buffer[0];
	}

}

#endif  //LEMON_CXX_SYS_TEXT_HPP

