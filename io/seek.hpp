/**
* 
* @file     seek
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/08/30
*/
#ifndef LEMONXX_IO_SEEK_HPP
#define LEMONXX_IO_SEEK_HPP
#include <lemon/io/abi.h>

namespace lemon{namespace io{

	struct seek
	{
		enum Value
		{
			begin = LEMON_IO_BEGIN, current = LEMON_IO_CURRENT, end = LEMON_IO_END
		};
	};
}}

#endif //LEMONXX_IO_SEEK_HPP