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
#include <lemonxx/type_traits/type_traits.hpp>

namespace lemon{

	struct const_buffer
	{
		const_buffer(const byte_t * source,size_t length)
			:Data(source),Length(length)
		{}

		byte_t const	*Data;

		size_t			Length;
	};

	struct mutable_buffer
	{
		mutable_buffer(byte_t * source,size_t length)
			:Data(source),Length(length)
		{}
		
		byte_t		*Data;

		size_t		Length;
	};

	inline mutable_buffer buf(byte_t * source,size_t length)
	{
		return mutable_buffer(source,length);
	}

	template<size_t N>
	inline mutable_buffer buf(byte_t (&source) [N])
	{
		return mutable_buffer(source,N);
	}

	inline const_buffer cbuf(const byte_t * source,size_t length)
	{
		return const_buffer(source,length);
	}

	template<size_t N>
	inline const_buffer cbuf(const byte_t (&source) [N])
	{
		return const_buffer(source,N);
	}

	template<size_t N>
	inline mutable_buffer buf(char (&source) [N])
	{
		return mutable_buffer((byte_t*)source,N);
	}

	inline const_buffer cbuf(const char * message)
	{
		return const_buffer((const byte_t*)message,strlen(message));
	}
}
#endif //LEMONXX_UTILITY_BUFFER_HPP