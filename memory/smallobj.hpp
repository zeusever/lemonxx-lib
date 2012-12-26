/**
* 
* @file     smallobj
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/02/02
*/
#ifndef LEMONXX_MEMORY_SMALLOBJ_HPP
#define LEMONXX_MEMORY_SMALLOBJ_HPP
#include <lemonxx/configure.h>
#include <lemonxx/sys/sys.hpp>
#include <lemon/memory/smallobj.h>

namespace lemon{namespace memory{namespace smallobject{
	template<size_t MaxBlockSize,size_t AlignSize = sizeof(int)>
	class allocator : private nocopyable
	{
	public:
		allocator()
		{
			error_info errorCode;

			_allocator = LemonCreateSmallObjAllocator(MaxBlockSize,AlignSize,&errorCode);

			errorCode.check_throw();
		}
		~allocator()
		{
			LemonReleaseSmallObjAllocator(_allocator);
		}

		void* alloc(size_t N)
		{
			return LemonSmallObjAlloc(_allocator,N);
		}
#ifdef free
#define free_crt free
#undef free
#endif //free
		void free(void * block,size_t N)
		{
			LemonSmallObjFree(_allocator,block,N);
		}
#ifdef free_crt
#define free free_crt
#endif //

	private:
		LemonSmallObjAllocator _allocator;
	};

}}}


#endif  //LEMONXX_MEMORY_SMALLOBJ_HPP
