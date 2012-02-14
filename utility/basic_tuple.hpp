/**
* 
* @file     basic_tuple
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/01/16
*/
#ifndef LEMON_CXX_UTILITY_BASIC_TUPLE_HPP
#define LEMON_CXX_UTILITY_BASIC_TUPLE_HPP
#include <iostream>
#include <algorithm>
#include <lemonxx/mpl/list.hpp>
#include <lemonxx/mpl/list/end.hpp>
#include <lemonxx/mpl/list/size.hpp>
#include <lemonxx/mpl/algorithm.hpp>
#include <lemonxx/mpl/list/begin.hpp>
#include <lemonxx/mpl/list/iterator.hpp>
#include <lemonxx/type_traits/parameters.hpp>
#include <lemonxx/utility/ref.hpp>

namespace lemon{

	template<typename B,typename E> struct basic_tuple;

	template<typename I,typename E>
	struct basic_tuple
		:  basic_tuple<typename mpl::next<I>::type,E>
	{
		typedef basic_tuple<I,E> self_type;

		typedef typename mpl::deref<I>::type origin_type;

		typedef typename remove_reference<origin_type>::type type;

		typedef typename conditional<
			is_reference<origin_type>::value,
			lemon::refrence_wrapper<type>,
			typename remove_cv<origin_type>::type
		>::type value_type;

		typedef basic_tuple<typename mpl::next<I>::type,E> base_type;

		typedef typename lemon::parameter<value_type>::type param_type;

		typedef typename mpl::distance<I,E>::size size_type;

		value_type Value;

		void swap(self_type & rhs)
		{
			std::swap(Value,rhs.Value);

			base_type::swap(rhs);
		}

		bool operator == (const self_type& rhs) const
		{
			return Value == rhs.Value && ((base_type&)*this == rhs);
		}
	};

	template<typename E>
	struct basic_tuple<E,E>
	{
		void swap(basic_tuple<E,E> &){}

		bool operator == (const basic_tuple<E,E>&) const {return true;}
	};

	template<typename Seq,size_t N>
	struct basic_tuple_cast
	{
		typedef typename mpl::advance<typename mpl::begin<Seq>::type,N>::type I;

		typedef typename mpl::end<Seq>::type E;

		typedef typename lemon::basic_tuple<I,E> type;

		typedef typename type::value_type value_type;
	};
}

#endif //LEMON_CXX_UTILITY_BASIC_TUPLE_HPP