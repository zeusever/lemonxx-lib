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

	template<size_t BlockSize,size_t BlocksPerPage = 1024 * 1024 / BlockSize>
	class allocator : private nocopyable
	{
	public:
		allocator(size_t blocks)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			_allocator = LemonCreateRingBuffer(blocks,BlockSize,BlocksPerPage,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
		}

		~allocator()
		{
			LemonReleaseRingBuffer(_allocator);
		}

		size_t capacity() const 
		{
			return LemonRingBufferCapacity(_allocator);
		}

		size_t length() const
		{
			return LemonRingBufferLength(_allocator);
		}

		bool empty() const {return 0 == capacity();}

		void * push_front(void * data,size_t dataLength)
		{
			return LemonRingBufferWriteFront(_allocator,data,dataLength);
		}

		void * push_back(void * data,size_t dataLength)
		{
			return LemonRingBufferWriteBack(_allocator,data,dataLength);
		}

		void direct_write(void * block,void * data,size_t dataLength)
		{
			LemonRingBufferDirectWrite(block,data,dataLength);
		}

		void * pop_front()
		{
			return LemonRingBufferReadFront(_allocator);
		}

		void * pop_back()
		{
			return LemonRingBufferReadBack(_allocator);
		}

	private:

		LemonRingBuffer		_allocator;
	};

}}}
#endif // LEMONXX_MEMORY_RINGBUFFER_HPP
