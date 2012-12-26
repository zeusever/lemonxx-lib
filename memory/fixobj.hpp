/**
* 
* @file     fixobj
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/02/14
*/
#ifndef LEMONXX_MEMORY_FIXOBJ_HPP
#define LEMONXX_MEMORY_FIXOBJ_HPP
#include <lemonxx/sys/sys.hpp>
#include <lemon/memory/fixobj.h>
#include <lemonxx/utility/utility.hpp>

namespace lemon{namespace memory{namespace fixed{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	template<size_t N> class fixobject_allocator : private nocopyable
	///
	/// @brief	  
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<size_t N>
	class allocator : private nocopyable
	{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	fixobject_allocator()
		///
		/// @brief	Default constructor. 
		///
		/// @author	Yuki
		/// @date	2012/2/14
		///
		/// @exception	Exception	Thrown when . 
		////////////////////////////////////////////////////////////////////////////////////////////////////

		allocator()
		{
			error_info errorCode;

			_allocator = LemonCreateFixObjectAllocator(N,&errorCode);

			errorCode.check_throw();
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	~fixobject_allocator()
		///
		/// @brief	Finaliser. 
		///
		/// @author	Yuki
		/// @date	2012/2/14
		////////////////////////////////////////////////////////////////////////////////////////////////////

		~allocator()
		{
			LemonReleaseFixObjectAllocator(_allocator);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	void* alloc()
		///
		/// @brief	Allocs this object. 
		///
		/// @return	null if it fails, else. 
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void* alloc()
		{
			return LemonFixObjectAlloc(_allocator);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	void free(void * block)
		///
		/// @brief	Frees. 
		///
		/// @author	Yuki
		/// @date	2012/2/14
		///
		/// @param [in,out]	block	If non-null, the block. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef free
#define free_crt free
#undef free
#endif //free	
		void free(void * block)
		{
			LemonFixObjectFree(_allocator,block);
		}
#ifdef free_crt
#define free free_crt
#endif //	
	private:
		LemonFixObjectAllocator _allocator;
	};

}}}

#endif //LEMONXX_MEMORY_FIXOBJ_HPP