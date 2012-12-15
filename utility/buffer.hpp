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
#include <string>
#include <lemonxx/configure.h>
#include <lemonxx/sys/inttypes.hpp>
#include <lemonxx/type_traits/type_traits.hpp>
#include <lemonxx/sys/text.hpp>

namespace lemon{

	struct const_buffer : public LemonCBuff
	{
		const_buffer()
		{
			LemonCBuff::Data = NULL;

			LemonCBuff::Length = 0;
		}

		const_buffer(LemonCBuff rhs)
		{
			LemonCBuff::Data = rhs.Data;

			LemonCBuff::Length = rhs.Length;
		}

		const_buffer(LemonBuff rhs)
		{
			LemonCBuff::Data = rhs.Data;

			LemonCBuff::Length = rhs.Length;
		}

		const_buffer(const byte_t * source,size_t length)	
		{
			LemonCBuff::Data = source;

			LemonCBuff::Length = length;
		}

		bool empty() const
		{
			return !LEMON_CHECK_BUFF(*this);
		}
	};

	struct mutable_buffer : public LemonBuff
	{
		mutable_buffer()
		{
			LemonBuff::Data = NULL;

			LemonBuff::Length = 0;
		}

		mutable_buffer(LemonBuff rhs)
		{
			LemonBuff::Data = rhs.Data;

			LemonBuff::Length = rhs.Length;
		}

		mutable_buffer(byte_t * source,size_t length)
		{
			LemonBuff::Data = source;

			LemonBuff::Length = length;
		}

		bool empty() const
		{
			return !LEMON_CHECK_BUFF(*this);
		}
	};

	inline mutable_buffer buf(byte_t * source,size_t length)
	{
		return mutable_buffer(source,length);
	}

	template<typename T>
	inline mutable_buffer buf(T & t)
	{
		return mutable_buffer((lemon_byte_t*)&t,sizeof(T));
	}

	template<typename T>
	inline const_buffer cbuf(const T & t)
	{
		return const_buffer((const lemon_byte_t*)&t,sizeof(T));
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

	inline const_buffer cbuf(void * source,size_t length)
	{
		return const_buffer((byte_t*)source,length);
	}

	template<size_t N>
	inline const_buffer cbuf(const byte_t (&source) [N])
	{
		return const_buffer(source,N);
	}

	template<typename T,size_t N>
	inline const_buffer cbuf(const T (&source) [N])
	{
		return const_buffer((const lemon::byte_t *)source,N * sizeof(T));
	}

#ifdef WIN32
	inline const_buffer cbuf(const lemon::char_t * message)
	{
		return const_buffer((const byte_t*)message,lemon_strlen(message) * sizeof(lemon::char_t));
	}
#endif //WIN32

	template<size_t N>
	inline mutable_buffer buf(char (&source) [N])
	{
		return mutable_buffer((byte_t*)source,N);
	}

	inline const_buffer cbuf(const char * message)
	{
		return const_buffer((const byte_t*)message,strlen(message));
	}

	inline const_buffer cbuf(const char * message,size_t length)
	{
		return const_buffer((const byte_t*)message,length);
	}

	inline const_buffer cbuf(const std::string &message)
	{
		return const_buffer((const byte_t*)message.c_str(),message.length());
	}

	template<typename R,typename Buffer>
	inline R& buffer_cast(Buffer buffer)
	{
		assert(!buffer.empty() && sizeof(R) <= buffer.Length);

		return *(R*)buffer.Data;
	}

	template<typename Buffer>
	inline mutable_buffer mutable_buffer_cast(Buffer buffer)
	{
		return mutable_buffer((byte_t*)buffer.Data,buffer.Length);
	}
}
#endif //LEMONXX_UTILITY_BUFFER_HPP