/**
* 
* @file     function
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/01/15
*/
#ifndef LEMON_CXX_FUNCTION_HPP
#define LEMON_CXX_FUNCTION_HPP

#include <functional>
#include <lemonxx/configure.h>
#include <lemonxx/function/handle.hpp>
#include <lemonxx/function/mem_handle.hpp>
#include <lemonxx/function/basic_function.hpp>
#include <lemonxx/mpl/inttypes.hpp>
#include <lemonxx/type_traits/type_traits.hpp>


namespace lemon{

	template<class Signature>
	class function : public basic_function<Signature>
	{
	public:

		typedef basic_function<Signature> base_type;

		typedef typename base_type::wrapper_type wrapper_type;

		function(){}
		
		function(const function& rhs):basic_function<Signature>(rhs){}

		function(wrapper_type data):basic_function<Signature>(data){}

		template<class Func>
		function(Func fn)
			:basic_function<Signature>(create_handle(fn,typename is_same<Func,function<Signature> >::type()))
		{

		}

		template<class Class,class Func>
		function(Func fn,Class * object)
			:basic_function<Signature>(new functions::mem_handle<Signature,Class,Func>(object,fn))
		{

		}

	private:
		template<class Func>
		static wrapper_type create_handle(Func fun,mpl::true_type)
		{
			return fun.release();
		}

		template<class Func>
		static functions::handle<Signature,Func>* create_handle(Func fun,mpl::false_type)
		{
			return new functions::handle<Signature,Func>(fun);
		}
	};

}

#endif //LEMON_CXX_FUNCTION_HPP
