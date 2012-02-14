/**
 * 
 * @file     insert
 * @brief    Copyright (C) 2010  yayanyang All Rights Reserved 
 * @author   yayanyang
 * @version  1.0.0.0  
 * @date     2010/12/07
 */
#ifndef GHCA_STDEXT_MPL_CONTAINER_LIST_INSERT_HPP
#define GHCA_STDEXT_MPL_CONTAINER_LIST_INSERT_HPP

#include <lemonxx/mpl/algorithm.hpp>

#include <lemonxx/mpl/list.hpp>

namespace lemon{namespace mpl{

	/*template<typename Head,typename Tail, typename Head1,typename Tail1, typename Iterator,typename T>
	struct insert< list<Head,Tail>, iterator< list<Head1,Tail1> > , T>
	{
		typedef list<Head,typename insert<Tail,iterator< list<Head1,Tail1> >,T>::type> type;
	};

	template<typename Head,typename Tail,typename T>
	struct insert<list<Head,Tail>,iterator< list<Head,Tail> >,T>
	{
		typedef list<Head,list<T,Tail> > type;
	};

	template<typename T>
	struct insert<list<null,null>,iterator< list<null,null> >,T>
	{
		typedef list<T,null> type;
	};*/

	template<typename Head1,typename Tail1,typename Head2,typename Tail2,typename T>
	struct insert< list<Head1,Tail1>,iterator< list<Head2,Tail2> >, T>
	{
		typedef list<Head1,typename insert<Tail1,iterator< list<Head2,Tail2> >,T>::type> type;
	};

	template<typename Head,typename Tail,typename T>
	struct insert<list<Head,Tail>,iterator< list<Head,Tail> >,T>
	{
		typedef list<Head,list<T,Tail> > type;
	};


	template<typename T>
	struct insert<list<null,null>,iterator< list<null,null> >,T>
	{
		typedef list<T,list<null,null> > type;
	};

}}

#endif	//GHCA_STDEXT_MPL_CONTAINER_LIST_INSERT_HPP
