/**
* 
* @file     buffer
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/02/13
*/
#ifndef LEMONXX_UTILITY_BUFFER_HPP
#define LEMONXX_UTILITY_BUFFER_HPP
#include <vector>
#include <lemonxx/configure.h>
#include <lemonxx/sys/inttypes.hpp>

namespace lemon{

	template<typename T>
	struct buffer_wrapper
	{
		T			*Data;

		size_t		Length;

		buffer_wrapper(T * data,size_t length)
			:Data(data),Length(length)
		{

		}
	};
	template<size_t N>
	inline buffer_wrapper<byte_t> buf(byte_t data[N])
	{
		return buffer_wrapper<byte_t>(data,N);
	}

	template<size_t N>
	inline buffer_wrapper<byte_t const> cbuf(byte_t data[N])
	{
		return buffer_wrapper<byte_t const >(data,N);
	}

	template<size_t N>
	inline buffer_wrapper<byte_t const> cbuf(const byte_t data[N])
	{
		return buffer_wrapper<byte_t const>(data,N);
	}

	inline buffer_wrapper<byte_t> buf(byte_t * data,size_t length)
	{
		return buffer_wrapper<byte_t>(data,length);
	}

	inline buffer_wrapper<byte_t const> cbuf(byte_t * data,size_t length)
	{
		return buffer_wrapper<byte_t const>(data,length);
	}

	inline buffer_wrapper<byte_t const> cbuf(const byte_t * data,size_t length)
	{
		return buffer_wrapper<byte_t const>(data,length);
	}

	inline buffer_wrapper<byte_t const> cbuf(const char * message)
	{
		return buffer_wrapper<byte_t const>((byte_t const*)message,strlen(message));
	}

	inline buffer_wrapper<byte_t> buf(std::vector<byte_t> & source)
	{
		if(source.empty()) return buffer_wrapper<byte_t>(0,0);

		return buffer_wrapper<byte_t>(&source[0],source.size());
	}

	inline buffer_wrapper<byte_t const> cbuf(std::vector<byte_t> & source)
	{
		if(source.empty()) return buffer_wrapper<byte_t const>(0,0);

		return buffer_wrapper<byte_t const>(&source[0],source.size());
	}

	inline buffer_wrapper<byte_t const> cbuf(const std::vector<byte_t> & source)
	{
		if(source.empty()) return buffer_wrapper<byte_t const>(0,0);

		return buffer_wrapper<byte_t const>(&source[0],source.size());
	}
}
#endif //LEMONXX_UTILITY_BUFFER_HPP