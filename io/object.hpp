/**
* 
* @file     object
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/08/30
*/
#ifndef LEMONXX_IO_OBJECT_HPP
#define LEMONXX_IO_OBJECT_HPP

#include <lemon/io/abi.h>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>

namespace lemon{namespace io{

	class object : public basic_handle_object<LemonIO,&LemonCloseIO>
	{
	public:

		typedef basic_handle_object<LemonIO,&LemonCloseIO> base_type;

		object(LemonIO io) : base_type(io) {}
	};

}}

#endif //LEMONXX_IO_OBJECT_HPP