/**
 * 
 * @file     push_front
 * @brief    Copyright (C) 2010  yayanyang All Rights Reserved 
 * @author   yayanyang
 * @version  1.0.0.0  
 * @date     2010/12/07
 */
#ifndef GHCA_STDEXT_MPL_CONTAINER_LIST_HPP
#define GHCA_STDEXT_MPL_CONTAINER_LIST_HPP

#include <lemonxx/mpl/algorithm.hpp>

#include <lemonxx/mpl/list.hpp>

namespace lemon{namespace mpl{
	
	template<typename Head,typename Tail,typename T>
	struct push_front< list<Head,Tail>,T>
	{
		typedef list<T,list<Head,Tail> > type;
	};
}}

#endif	//GHCA_STDEXT_MPL_CONTAINER_LIST_HPP
