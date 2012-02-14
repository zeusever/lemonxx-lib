/**
 * 
 * @file     erase
 * @brief    Copyright (C) 2010  yayanyang All Rights Reserved 
 * @author   yayanyang
 * @version  1.0.0.0  
 * @date     2010/12/07
 */
#ifndef GHCA_STDEXT_MPL_CONTAINER_LIST_ERASE_HPP
#define GHCA_STDEXT_MPL_CONTAINER_LIST_ERASE_HPP

#include <lemonxx/mpl/algorithm.hpp>

#include <lemonxx/mpl/list.hpp>

namespace lemon{namespace mpl{

	template<typename Seq,typename Iterator>
	struct erase
	{
		typedef list<typename Seq::head,typename erase<typename Seq::tail,Iterator>::type> type;
	};

	template<typename H1,typename T1,typename H2,typename T2>
	struct erase< list<H1,T1>, iterator< list<H2,T2> > >
	{
		typedef list<H1,typename erase<T1,iterator< list<H2,T2> > >::type> type;
	};

	template<typename H,typename T>
	struct erase<list<H,T>, iterator< list<H,T> > >
	{
		typedef T type;
	};
}}

#endif	//GHCA_STDEXT_MPL_CONTAINER_LIST_ERASE_HPP
