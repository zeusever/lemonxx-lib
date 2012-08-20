/**
* 
* @file     dtrace
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/08/20
*/
#ifndef LEMONXX_DTRACE_DTRACE_HPP
#define LEMONXX_DTRACE_DTRACE_HPP
#include <lemon/dtrace/abi.h>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>

namespace lemon{namespace dtrace{
	
	class service : basic_handle_object<LemonDTraceService,&LemonCloseDTraceService>
	{
	public:
		
		typedef basic_handle_object<LemonDTraceService,&LemonCloseDTraceService> base_type;

		service():base_type(Create(NULL)) {}

		service(const char * url):base_type(Create(url)) {}

	private:

		static LemonDTraceService Create(const char * url)
		{
			scope_error_info errorCode;

			return LemonCreateDTraceService(url,errorCode);
		}
	};

}}

#endif //LEMONXX_DTRACE_DTRACE_HPP