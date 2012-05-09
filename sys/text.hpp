/**
* 
* @file     text
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/01/22
*/
#ifndef LEMON_CXX_SYS_TEXT_HPP
#define LEMON_CXX_SYS_TEXT_HPP
#include <vector>
#include <sstream>
#include <lemon/sys/text.h>
#include <lemonxx/sys/exception.hpp>
#include <lemonxx/utility/utility.hpp>

namespace lemon{

	typedef std::basic_string<lemon_char_t> String;

	typedef std::basic_stringstream<lemon_char_t> StringStream;
}

#endif  //LEMON_CXX_SYS_TEXT_HPP

