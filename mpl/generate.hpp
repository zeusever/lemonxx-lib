/**
 * 
 * @file     generate
 * @brief    Copyright (C) 2010  yayanyang All Rights Reserved 
 * @author   yayanyang
 * @version  1.0.0.0  
 * @date     2010/12/08
 */
#ifndef GHCA_STDEXT_MPL_GENERATE_HPP
#define GHCA_STDEXT_MPL_GENERATE_HPP

#include <lemonxx/mpl/algorithm.hpp>

namespace lemon{namespace mpl{

	template<template<typename,class> class Base,typename IteratorBegin,typename IteratorEnd>
	struct linear_generator_helper 
		: public Base<typename deref<IteratorBegin>::type,linear_generator_helper<Base,typename IteratorBegin::next,IteratorEnd> >
	{
		typedef Base<typename deref<IteratorBegin>::type,linear_generator_helper<Base,typename IteratorBegin::next,IteratorEnd> >

			base_type;
	};
	
	template<template<typename,class> class Base,typename Iterator>
	struct linear_generator_helper<Base,Iterator,Iterator>
	{
	};


	template<template<typename,class> class Base,typename Sequeue>
	struct linear_generator
		: public linear_generator_helper<Base,typename begin<Sequeue>::type,typename end<Sequeue>::type>
	{
		
	};


	template<template<typename,class> class Base,typename Sequeue,size_t N>
	struct linear_generator_cast
	{
		typedef typename advance<typename begin<Sequeue>::type,N>::type iterator;

		typedef typename end<Sequeue>::type end;

		typedef typename linear_generator_helper<Base,iterator,end>::base_type type;
	};
}}

#endif	//GHCA_STDEXT_MPL_GENERATE_HPP
