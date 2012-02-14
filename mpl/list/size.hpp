/**
 * 
 * @file     size
 * @brief    Copyright (C) 2010  yayanyang All Rights Reserved 
 * @author   yayanyang
 * @version  1.0.0.0  
 * @date     2010/12/07
 */
#ifndef GHCA_STDEXT_MPL_CONTAINER_LIST_SIZE_HPP
#define GHCA_STDEXT_MPL_CONTAINER_LIST_SIZE_HPP

#include <lemonxx/mpl/algorithm.hpp>

namespace lemon{namespace mpl{
	

	template<class T,class U> 
	struct size< list<T,U> >
		:size_t_< 1 + size<U>::value>
	{
		//typedef size_t_< 1 + size<U>::value> type;
	};

	template<> 
	struct size< list<null,null> >
		:size_t_<0>
	{
		//typedef size_t_<0> type;
	};

}}

#endif	//GHCA_STDEXT_MPL_CONTAINER_LIST_SIZE_HPP
