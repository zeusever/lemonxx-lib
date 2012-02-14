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


LEMONXX_API void* 
	LemonXXGlobalSmallObjAlloc(
	__lemon_in size_t size,
	__lemon_inout LemonErrorInfo *errorCode);

LEMONXX_API void 
	LemonXXGlobalSmallObjFree(
	__lemon_free void * block __lemon_buffer(size),
	__lemon_in size_t size,
	__lemon_inout LemonErrorInfo *errorCode);

namespace lemon{

	class smallobj
	{
	public:

		static void* operator new(std::size_t size)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			void * block = LemonXXGlobalSmallObjAlloc(size,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception("call LemonXXGlobalSmallObjAlloc exception",errorCode);

			return block;
		}

		static void operator delete(void * block,std::size_t size)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonXXGlobalSmallObjFree(block,size,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception("call LemonXXGlobalSmallObjFree exception",errorCode);
		}

		virtual ~ smallobj(){}
	};
}
#endif  //LEMONXX_MEMORY_SMALLOBJ_HPP
