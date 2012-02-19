/**
* 
* @file     handle
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/02/16
*/
#ifndef LEMONXX_SYS_HANDLE_HPP
#define LEMONXX_SYS_HANDLE_HPP
#include <algorithm>
#include <lemon/sys/abi.h>
#include <lemonxx/utility/nocopyable.hpp>

namespace lemon{

	template<class T,void(*Release)(T)>
	class handle
	{
	public:
		typedef T									handle_type;

		typedef T const								const_handle_type;

		handle():_handle(LEMON_HANDLE_NULL_VALUE){}

		handle(handle_type h):_handle(h){}

		handle(const handle & rhs):_handle(rhs.move()) {}

		~handle()
		{
			if(LEMON_CHECK_HANDLE(_handle)) Release(_handle);
		}

		operator handle_type ()
		{
			return _handle;
		}

		operator const_handle_type () const
		{
			return _handle;
		}

		handle_type move() const
		{
			handle_type result  = LEMON_HANDLE_NULL_VALUE;

			std::swap(result,_handle);

			return result;
		}

		void swap(handle & rhs)
		{
			std::swap(_handle,rhs._handle);
		}

		handle& operator = ( const handle & rhs)
		{
			handle(rhs).swap(_handle);

			return *this;
		}

	private:

		mutable handle_type _handle;
	};

	template<class T,void(*Release)(T)>
	class basic_handle_object : private nocopyable
	{
	public:
		typedef T									handle_type;

		typedef T const								const_handle_type;

		basic_handle_object():_handle(LEMON_HANDLE_NULL_VALUE){}

		basic_handle_object(handle_type h):_handle(h){}

		~basic_handle_object()
		{
			if(LEMON_CHECK_HANDLE(_handle)) Release(_handle);
		}

		operator handle_type ()
		{
			return _handle;
		}

		operator const_handle_type () const
		{
			return _handle;
		}

		handle_type release() 
		{
			handle_type result  = LEMON_HANDLE_NULL_VALUE;

			std::swap(result,_handle);

			return result;
		}

		handle_type reset(handle_type val)
		{
			std::swap(val,_handle);

			return val;
		}

	private:

		handle_type _handle;
	};
}

#endif //LEMONXX_SYS_HANDLE_HPP