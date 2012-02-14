/**
 * 
 * @file     iterator
 * @brief    Copyright (C) 2010  yayanyang All Rights Reserved 
 * @author   yayanyang
 * @version  1.0.0.0  
 * @date     2010/12/08
 */
#ifndef GHCA_STDEXT_MPL_CONTAINER_ITERATOR_HPP
#define GHCA_STDEXT_MPL_CONTAINER_ITERATOR_HPP

#include <lemonxx/mpl/inttypes.hpp>

#include <lemonxx/mpl/nulltype.hpp>

#include <lemonxx/type_traits/type_traits.hpp>


namespace lemon{namespace mpl{

	template<typename Node>
	struct iterator;

	template<typename Iterator>
	struct next;

	template<typename Sequeue>
	struct begin;

	template<typename Sequeue>
	struct end;

	template<typename Iterator>
	struct deref;

	template<typename Iterator,size_t N>
	struct advance;

	template<typename Sequeue>
	struct size;

	template<typename Sequeue>
	struct front;

	template<typename Sequeue,typename Iterator,typename T>
	struct insert;

	template<typename Sequeue,typename T>
	struct push_front;

	template<typename Sequeue>
	struct pop_front;

	template<typename Sequeue,typename Iterator>
	struct erase;

	template<typename First,typename Last>
	struct distance;

	template<typename First,typename Last>
	struct distance
	{
		typedef size_t_< 1 + distance<typename next<First>::type,Last>::size::value> size;
	};

	template<typename Iterator>
	struct distance <Iterator,Iterator> 
	{
		typedef size_t_<0> size; 
	};

	template<
		typename Sequeue,
		size_t N
	>
	struct at
	{
		typedef typename deref<typename advance<typename begin<Sequeue>::type,N>::type>::type type;
	};

	template<typename Begin,typename End,typename T>
	struct find;


	template<typename Begin,typename End,typename T>
	struct find
	{
		typedef typename mpl::deref<Begin>::type current_type;

		typedef find<typename next<Begin>::type,End,T> next_type;

		typedef typename lemon::conditional<lemon::is_same<current_type,T>::value,Begin,typename next_type::result_type>::type result_type;
	};

	template<typename Iterator,typename T>
	struct find<Iterator,Iterator,T>
	{
		typedef typename mpl::deref<Iterator>::type current_type;

		typedef Iterator result_type;

	};
}}


namespace lemon{namespace mpl{

	template<typename Seq>
	struct empty
		:public bool_<size<Seq>::value == 0>
	{};

	template<>
	struct begin<null>
	{
		typedef iterator<null> type;
	};

	template<>
	struct deref< iterator<null> >
	{
		typedef null type;
	};

	template<size_t N>
	struct advance<iterator<null>,N>
	{
		typedef iterator<null> type;
	};
}}



#endif	//GHCA_STDEXT_MPL_CONTAINER_ITERATOR_HPP
