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
#include <fstream>
#include <lemon/sys/text.h>
#include <lemonxx/sys/exception.hpp>

#include <vector>

#include <string>

#include <locale>

#include <algorithm>

namespace lemon{

	typedef lemon_char_t char_t;

	typedef std::basic_string<lemon_char_t> String;

	typedef std::basic_stringstream<lemon_char_t> StringStream;

	typedef std::basic_fstream<lemon_char_t> FileStream;

	inline std::string to_locale(const String & source)
	{
		LEMON_DECLARE_ERRORINFO(errorCode);

		if(source.empty()) return "";

		std::vector<char> buffer(source.length() * 6 + 1);

		LemonToLocale(source.c_str(),source.length() + 1,(lemon::byte_t*)&buffer[0],buffer.size(),&errorCode);

		if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

		return &buffer[0];
	}

	inline String from_locale(const std::string & source)
	{
		LEMON_DECLARE_ERRORINFO(errorCode);

		if(source.empty()) return LEMON_TEXT("");

		std::vector<lemon_char_t> buffer(source.length() * 6 + 1);

		LemonFromLocale((const lemon::byte_t*)source.c_str(),source.length() + 1,&buffer[0],buffer.size(),&errorCode);

		if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

		return &buffer[0];
	}


	inline std::string to_utf8(const String & source)
	{
		LEMON_DECLARE_ERRORINFO(errorCode);

		if(source.empty()) return "";

		std::vector<char> buffer(source.length() * 6 + 1);

		LemonToUTF8(source.c_str(),source.length() + 1,(lemon::byte_t*)&buffer[0],buffer.size(),&errorCode);

		if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

		return &buffer[0];
	}

	inline String from_utf8(const std::string & source)
	{
		LEMON_DECLARE_ERRORINFO(errorCode);

		if(source.empty()) return LEMON_TEXT("");

		std::vector<lemon_char_t> buffer(source.length() * 6 + 1);

		LemonFromUTF8((const lemon::byte_t*)source.c_str(),source.length() + 1,&buffer[0],buffer.size(),&errorCode);

		if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

		return &buffer[0];
	}

	namespace string_algorithm{

		template<typename CharType>
		struct to_lowerF
		{
			to_lowerF(const std::locale& Loc ) : _locale(&Loc) {}

			CharType operator ()( CharType Ch ) const
			{
				return std::tolower<CharType>(Ch, *_locale);
			}
		private:
			const std::locale *_locale;
		};

		template<typename CharType>
		struct to_upperF
		{
			to_upperF(const std::locale& Loc ) : _locale(&Loc) {}

			CharType operator ()( CharType Ch ) const
			{
				return std::toupper<CharType>(Ch, *_locale);
			}
		private:
			const std::locale *_locale;
		};
	}


	template<typename CharType>
	inline std::basic_string<CharType> string_toupper(const CharType* rhs)
	{
		std::locale loc;

		std::basic_string<CharType> result = rhs;

		std::transform(result.begin(),result.end(),result.begin(),string_algorithm::to_upperF<CharType>(loc));

		return result;
	}

	template<typename CharType>
	inline std::basic_string<CharType> string_toupper(const std::basic_string<CharType> & rhs)
	{
		std::locale loc;

		std::basic_string<CharType> result(rhs.begin(),rhs.end());

		std::transform(result.begin(),result.end(),result.begin(),string_algorithm::to_upperF<CharType>(loc));

		return result;
	}

	template<typename CharType>
	inline std::basic_string<CharType> string_tolower(const std::basic_string<CharType> & rhs)
	{
		std::locale loc;

		std::basic_string<CharType> result(rhs.begin(),rhs.end());

		std::transform(result.begin(),result.end(),result.begin(),string_algorithm::to_lowerF<CharType>(loc));

		return result;
	}


	template<typename CharType>
	inline std::basic_string<CharType> string_replaceall
		(
		const std::basic_string<CharType> & source,
		const std::basic_string<CharType> & match,
		const std::basic_string<CharType> & replace
		)
	{
		typename std::basic_string<CharType>::size_type pos;

		std::basic_string<CharType> result = source;

		while(std::basic_string<CharType>::npos != (pos = result.find(match)))
		{
			result.replace(pos,match.size(),replace);
		}

		return result;
	}
}

#endif  //LEMON_CXX_SYS_TEXT_HPP

