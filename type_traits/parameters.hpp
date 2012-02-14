/**
* 
* @file     addref
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/01/17
*/
#ifndef LEMON_CXX_STDEXT_ADDREF_HPP
#define LEMON_CXX_STDEXT_ADDREF_HPP

#include <lemonxx/type_traits/type_traits.hpp>


namespace lemon{

	template<typename T>
	struct parameter
	{
		typedef typename remove_reference<T>::type no_ref;

		typedef typename conditional<
		        is_pod<T>::value || is_reference<T>::value,
			T,
			typename add_lvalue_reference<typename add_const<T>::type>::type
		>::type type;
	};
}
#endif //LEMON_CXX_STDEXT_ADDREF_HPP
