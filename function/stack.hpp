/**
* 
* @file     stack
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/01/16
*/
#ifndef LEMON_CXX_FUNCTION_STACK_HPP
#define LEMON_CXX_FUNCTION_STACK_HPP

#include <lemonxx/utility/tuple.hpp>
#include <lemonxx/mpl/list/size.hpp>
#include <lemonxx/mpl/algorithm.hpp>
#include <lemonxx/type_traits/parameters.hpp>
#include <lemonxx/utility/placeholder.hpp>

namespace lemon{namespace binds{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @property	template<typename S,typename Seq> struct call_parameters
	///
	/// @brief	 options for controlling the call. 
	///
	/// @return	Options that control the call. 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<
		typename L,//the bind_t stack parameters list
		typename R,//the bound function input parameters list
		size_t N
	>
	struct call_parameters
	{
		typedef typename mpl::begin<L>::type	begin;

		typedef typename mpl::end<L>::type		end;

		typedef typename mpl::find<begin,end,placeholder<N> >::result_type I; 

		typedef typename mpl::at<R,mpl::distance<begin,I>::size::value>::type type;
	};

	template<
		typename Seq,
		size_t N,
		typename L,
		typename R
	>
	struct unwind_type
	{
		typedef typename parameter<typename mpl::at<Seq,N>::type>::type type;

		typedef typename mpl::at<typename L::Seq,N>::type ltype;

		typedef is_placeholder<ltype> selector;

		typedef typename conditional<selector::value,placeholder_value<ltype>,mpl::size_t_<N> >::type index;
	};

	template<
		typename unwind_t,
		typename L,
		typename R
	>
	inline typename unwind_t::type unwind_s (const L & ,const R & r,mpl::true_type)
	{
	  const static size_t index = unwind_t::index::value;

	  return lemon::get<R,index>(r);
	}

	template<
		typename unwind_t,
		typename L,
		typename R
	>
	inline typename unwind_t::type unwind_s (const L & l,const R & ,mpl::false_type)
	{
	  const static size_t index = unwind_t::index::value;

	  return lemon::get<L,index>(l);
	}

	template<
		typename Seq,
		size_t N,
		typename L,
		typename R
	>
	inline typename unwind_type<Seq,N,L,R>::type 
	unwind(const L & l,const R & r)
	{
		typedef unwind_type<Seq,N,L,R> unwind_t;

		return unwind_s<unwind_t>(l,r,mpl::bool_<unwind_t::selector::value>());
	}
	
}}

#endif //LEMON_CXX_FUNCTION_STACK_HPP
