/**
 * 
 * @file     static-assert
 * @brief    Copyright (C) 2010  yayanyang All Rights Reserved 
 * @author   yayanyang
 * @version  1.0.0.0  
 * @date     2010/10/12
 */
#ifndef FUSION_STATIC_ASSERT_HPP
#define FUSION_STATIC_ASSERT_HPP

#include <lemonxx/configure.h>

#ifndef LEMON_HAS_STATIC_ASSERT

namespace lemon{
	template<bool> struct CompileTimeError;
	template<> struct CompileTimeError<true> {};
}
#	define	LEMON_STATIC_ASSERT(expression_t,commit_message) { lemon::CompileTimeError<((expression_t) != false)> ERROR_; (void)ERROR_; } 
#else
#	define  LEMON_STATIC_ASSERT(exp,msg)  static_assert(exp,msg);
#endif //LEMON_HAS_STATIC_ASSERT

#endif	//FUSION_STATIC_ASSERT_HPP
