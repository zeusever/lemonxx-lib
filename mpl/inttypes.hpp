/**
 * 
 * @file     inttypes
 * @brief    Copyright (C) 2010  yayanyang All Rights Reserved 
 * @author   yayanyang
 * @version  1.0.0.0  
 * @date     2010/12/04
 */
#ifndef GHCA_STDEXT_INTTYPES_HPP
#define GHCA_STDEXT_INTTYPES_HPP
#include <cstddef>
namespace lemon{namespace mpl{

	template<typename Type,Type val>
	struct inttypes_
	{
		static const Type value = val;

		operator Type() { return value; }
	};

	template<bool val>
	struct bool_ : public inttypes_<bool,val> {};

	typedef bool_<true> true_type;

	typedef bool_<false> false_type;

	template<int val>
	struct int_ : public inttypes_<int,val>{};

	template<size_t val>
	struct size_t_ : public inttypes_<size_t,val>{};
}}
#endif	//GHCA_STDEXT_INTTYPES_HPP
