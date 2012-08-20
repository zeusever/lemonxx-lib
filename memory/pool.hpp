/**
* 
* @file     pool
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/02/15
*/
#ifndef LEMONXX_MEMORY_POOL_HPP
#define LEMONXX_MEMORY_POOL_HPP
#include <lemon/memory/pool.h>
#include <lemonxx/utility/utility.hpp>

namespace lemon{namespace memory{namespace pool{

	template<size_t PageSize,size_t AlignSize = sizeof(int)>
	class allocator : private nocopyable
	{
	public:

		allocator()
		{
			error_info errorCode;

			_allocator = LemonCreateMemoryPool(PageSize,AlignSize,&errorCode);

			errorCode.check_throw();
		}

		~allocator()
		{
			LemonReleaseMemoryPool(_allocator);
		}

		void* alloc(size_t blockSize)
		{
			return LemonMemoryPoolAlloc(_allocator,blockSize);
		}

		void garbagecollect()
		{
			LemonMemoryPoolGarbageCollect(_allocator);
		}

	private:
		LemonMemoryPool _allocator;
	};

}}}


#endif  //LEMONXX_MEMORY_POOL_HPP
