/**
* 
* @file     trace
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/08/12
*/
#ifndef LEMONXX_DIAGNOSIS_TRACE_HPP
#define LEMONXX_DIAGNOSIS_TRACE_HPP

#include <lemonxx/diagnosis/trace-classes.hpp>

namespace lemon{namespace dtrace{

	inline void write(commit_message & cm,const char * message)
	{
		cm.write_utf8_string(message);
	}

	inline void write(commit_message & cm,lemon::uint32_t val)
	{
		cm.write_number(val);
	}

}}

#endif // LEMONXX_DIAGNOSIS_TRACE_HPP



