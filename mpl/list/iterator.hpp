/**
 * 
 * @file     iterator
 * @brief    Copyright (C) 2010  yayanyang All Rights Reserved 
 * @author   yayanyang
 * @version  1.0.0.0  
 * @date     2010/12/06
 */
#ifndef GHCA_STDEXT_MPL_CONTAINER_LIST_ITERATOR_HPP
#define GHCA_STDEXT_MPL_CONTAINER_LIST_ITERATOR_HPP

#include <lemonxx/mpl/algorithm.hpp>

#include <lemonxx/mpl/list.hpp>


namespace lemon{namespace mpl{

	template<typename Head,typename Tail>
	struct iterator< list<Head,Tail> >
	{
		typedef Head type;

		typedef iterator<Tail> next;
	};

	template<typename Head,typename Tail>
	struct next< iterator< list<Head,Tail> > >
	{
		typedef iterator<Tail> type;
	};


	template<>
	struct iterator< list<null,null> >
	{
		typedef null type;

		//typedef iterator<Tail> next;
	};


	template<typename Head,typename Tail>
	struct deref< iterator< list<Head,Tail> > >
	{
		typedef Head type;
	};

	template<typename Head,typename Tail ,size_t N>
	struct advance< iterator< list<Head,Tail> > , N>
	{
		typedef typename advance< iterator<Tail> , N - 1 >::type type;
	};

	template<typename Head,typename Tail>
	struct advance< iterator< list<Head,Tail> > , 0>
	{
		typedef iterator< list<Head,Tail> > type;
	};

}}

#endif	//GHCA_STDEXT_MPL_CONTAINER_LIST_ITERATOR_HPP
