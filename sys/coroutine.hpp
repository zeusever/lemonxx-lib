/**
* 
* @file     coroutine
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/01/21
*/
#ifndef LEMON_CXX_SYS_COROUTINE_HPP
#define LEMON_CXX_SYS_COROUTINE_HPP
#include <lemon/sys/coroutine.h>
#include <lemonxx/sys/errorcode.hpp>
#include <lemonxx/utility/utility.hpp>
#include <lemonxx/function/function.hpp>

namespace lemon{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	coroutine
	///
	/// @brief	Coroutine. 
	///
	/// @author	Yayanyang
	/// @date	2012/1/21
	////////////////////////////////////////////////////////////////////////////////////////////////////

	class coroutine : private nocopyable
	{
	public:
		typedef lemon::function<void(coroutine * coro)> Proc;
	private:

		

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	static void __call(LemonCoroutine self,void* data)
		///
		/// @brief	Calls. 
		///
		/// @author	Yayanyang
		/// @date	2012/1/21
		///
		/// @param	self			The self. 
		/// @param [in,out]	data	If non-null, the data. 
		////////////////////////////////////////////////////////////////////////////////////////////////////

		static void __call(LemonCoroutine,void* data)
		{
			coroutine * coro = (coroutine*)data;

			coro->_proc(coro);
		}

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	coroutine()
		///
		/// @brief	Create thread root coroutine
		///
		/// @author	Yayanyang
		/// @date	2012/1/21
		////////////////////////////////////////////////////////////////////////////////////////////////////

		coroutine()
		{
			error_info errorCode;

			_coroutine = LemonThreadToCoroutine(errorCode);

			errorCode.check_throw();
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	coroutine(coroutine * parent)
		///
		/// @brief	Create child coroutine.
		///
		/// @author	Yayanyang
		/// @date	2012/1/21
		///
		/// @param [in,out]	parent	If non-null, the parent. 
		////////////////////////////////////////////////////////////////////////////////////////////////////

		coroutine(coroutine & parent,const Proc & proc,size_t stackSize)
			:_proc(proc)
		{
			error_info errorCode;

			_coroutine = LemonCreateCoroutine(parent._coroutine,&coroutine::__call,this,stackSize,errorCode);

			errorCode.check_throw();
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	~coroutine()
		///
		/// @brief	Finaliser. 
		///
		/// @author	Yayanyang
		/// @date	2012/1/21
		////////////////////////////////////////////////////////////////////////////////////////////////////

		~coroutine()
		{
			LemonReleaseCoroutine(_coroutine);
		}

		void yield()
		{
			error_info errorCode;

			LemonCoroutineYield(_coroutine,errorCode);

			errorCode.check_throw();
		}

		void resume()
		{
			error_info errorCode;

			LemonCoroutineResume(_coroutine,errorCode);

			errorCode.check_throw();
		}

	private:

		Proc			_proc;

		LemonCoroutine  _coroutine;
	};
}
#endif  //LEMON_CXX_SYS_COROUTINE_HPP
