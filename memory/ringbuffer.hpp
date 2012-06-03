/**
* 
* @file     ringbuffer
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012
*/
#ifndef LEMONXX_MEMORY_RINGBUFFER_HPP
#define LEMONXX_MEMORY_RINGBUFFER_HPP
#include <lemonxx/sys/sys.hpp>
#include <lemon/memory/ringbuffer.h>
#include <lemonxx/utility/utility.hpp>

namespace lemon{namespace memory{namespace ringbuffer{

	template<size_t BlockSize,size_t Blocks = 1024>
	class allocator : private nocopyable
	{
	public:
		allocator()
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			_allocator = LemonCreateRingBuffer(Blocks,BlockSize,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
		}

		~allocator()
		{
			LemonReleaseRingBuffer(_allocator);
		}

	private:

		LemonRingBuffer		_allocator;
	};

}}}
#endif // LEMONXX_MEMORY_RINGBUFFER_HPP
