/**
* 
* @file     intrinsics
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/01/31
*/
#ifndef LEMONXX_TYPE_TRAITS_INTRINSICS_HPP
#define LEMONXX_TYPE_TRAITS_INTRINSICS_HPP
#include <lemonxx/configure.h>
#include <lemonxx/mpl/inttypes.hpp>
#include <lemon/sys/abi.h>

#ifdef LEMON_COMPILER_SUPPORT_IS_ABSTRACT
#	define LEMON_IS_ABSTRACT(T) __is_abstract(T)
#else
#	define LEMON_IS_ABSTRACT(T) false
#endif

#ifdef LEMON_COMPILER_SUPPORT_IS_BASE_OF
#	define LEMON_IS_BASE_OF(B,D) __is_base_of(B,D)
#else
#	define LEMON_IS_BASE_OF(T) false
#endif

#ifdef LEMON_COMPILER_SUPPORT_IS_CLASS
#	define LEMON_IS_CLASS(T) __is_class(T)
#else
#	define LEMON_IS_CLASS(T) false
#endif

#ifdef LEMON_COMPILER_SUPPORT_IS_ENUM
#	define LEMON_IS_ENUM(T) __is_enum(T)
#else
#	define LEMON_IS_ENUM(T) false
#endif

#ifdef LEMON_COMPILER_SUPPORT_IS_POD
#	define LEMON_IS_POD(T) __is_pod(T)
#else
#	define LEMON_IS_POD(T) false
#endif

#ifdef LEMON_COMPILER_SUPPORT_HAS_TRIVIAL_CONSTRUCTOR
#	define LEMON_HAS_TRIVIAL_CONSTRUCTOR(T) __has_trivial_constructor(T)
#else
#	define LEMON_HAS_TRIVIAL_CONSTRUCTOR(T) false
#endif

namespace lemon{

	using lemon::mpl::bool_;
	using lemon::mpl::true_type;
	using lemon::mpl::false_type;
	using lemon::mpl::inttypes_;
	using lemon::mpl::size_t_;
}

namespace lemon{

	template<class T> struct _is_integral: public false_type {};

	template<> struct _is_integral<char>: public true_type {};

	template<> struct _is_integral<short>: public true_type {};

	template<> struct _is_integral<int>: public true_type {};

	template<> struct _is_integral<long>: public true_type {};
#ifdef LEMON_COMPILER_SUPPORT_LONGLONG
	template<> struct _is_integral<long long>: public true_type {};
#endif //LEMON_COMPILER_SUPPORT_LONGLONG
}

namespace lemon{

	template<class T> struct _is_signed_integral: public false_type {};

	template<> struct _is_signed_integral<signed char>: public true_type {};

	template<> struct _is_signed_integral<signed short>: public true_type {};

	template<> struct _is_signed_integral<signed int>: public true_type {};

	template<> struct _is_signed_integral<signed long>: public true_type {};
#ifdef LEMON_COMPILER_SUPPORT_LONGLONG
	template<> struct _is_signed_integral<signed long long>: public true_type {};
#endif //LEMON_COMPILER_SUPPORT_LONGLONG
}

namespace lemon{

	template<class T> struct _is_unsigned_integral: public false_type {};

	template<> struct _is_unsigned_integral<unsigned  char>: public true_type {};

	template<> struct _is_unsigned_integral<unsigned  short>: public true_type {};

	template<> struct _is_unsigned_integral<unsigned  int>: public true_type {};

	template<> struct _is_unsigned_integral<unsigned  long>: public true_type {};
#ifdef LEMON_COMPILER_SUPPORT_LONGLONG
	template<> struct _is_unsigned_integral<unsigned  long long>: public true_type {};
#endif //LEMON_COMPILER_SUPPORT_LONGLONG
}


namespace lemon{

	template<class T> struct _is_lemon_integral : public false_type{};

	template<> struct _is_lemon_integral<lemon_int8_t> : public false_type{};

	template<> struct _is_lemon_integral<lemon_uint8_t> : public false_type{};

	template<> struct _is_lemon_integral<lemon_int16_t> : public false_type{};

	template<> struct _is_lemon_integral<lemon_uint16_t> : public false_type{};

	template<> struct _is_lemon_integral<lemon_int32_t> : public false_type{};

	template<> struct _is_lemon_integral<lemon_uint32_t> : public false_type{};

	template<> struct _is_lemon_integral<lemon_int64_t> : public false_type{};

	template<> struct _is_lemon_integral<lemon_uint64_t> : public false_type{};
}


#endif //LEMONXX_TYPE_TRAITS_INTRINSICS_HPP
