/**
* 
* @file     STM-ringbuffer
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/08/16
*/
#ifndef LEMONXX_MEMORY_STM_RINGBUFFER_HPP
#define LEMONXX_MEMORY_STM_RINGBUFFER_HPP

#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>
#include <lemon/memory/STM-ringbuffer.h>

namespace lemon{namespace memeory{namespace STM{

	template<size_t blockSize>
	class ringbuffer : public basic_handle_object<LemonSTMRingBuffer,&LemonReleaseSTMRingBuffer>
	{
	public:

		typedef basic_handle_object<LemonSTMRingBuffer,&LemonReleaseSTMRingBuffer> base_type;

		ringbuffer(size_t blocks,size_t blocksOfPage) :base_type(Create(blocks,blockSize,blocksOfPage))
		{}

		ringbuffer(size_t blocks) :base_type(Create(blocks,blockSize,1024))
		{}

		size_t size() const
		{
			return LemonSTMRingBufferSize(*this);
		}

		size_t capacity() const
		{
			return LemonSTMRingBufferCapacity(*this);
		}

		bool empty() const { return size() == 0; }

	private:

		LemonSTMRingBuffer Create(size_t blocks,size_t blocksize,size_t blocksOfPage)
		{
			error_info errorCode;

			LemonSTMRingBuffer rb = LemonCreateSTMRingBuffer(blocks,blocksize,blocksOfPage,errorCode);

			errorCode.check_throw();

			return rb;
		}
	};

	
}}}

#endif //LEMONXX_MEMORY_STM_RINGBUFFER_HPP