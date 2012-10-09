/**
* 
* @file     COM
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/10/08
*/
#ifndef LEMONXX_WMI_COM_HPP
#define LEMONXX_WMI_COM_HPP

#include <atlbase.h>
#include <atlcom.h>

#define _WIN32_DCOM
#include <wbemidl.h>

#pragma comment(lib, "comsuppw.lib")

#pragma comment(lib, "wbemuuid.lib")

#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>

#define __lemon_com_check_throw(exp) \
	{ \
		HRESULT hr = exp; \
		\
		if(FAILED(hr)) \
		{\
			error_info errorCode; LEMON_COM_ERROR(errorCode,exp); errorCode.check_throw();\
		}\
	}

namespace lemon{namespace win32{

	template<size_t COINIT>
	struct basic_com_model : private lemon::nocopyable
	{
		basic_com_model(){::CoInitializeEx(0,COINIT);}

		~basic_com_model(){::CoUninitialize();}
	};

	typedef basic_com_model<COINIT_APARTMENTTHREADED>	single_thread_comodel;

	typedef basic_com_model<COINIT_MULTITHREADED>		multi_thread_comodel;
}}


#endif //LEMONXX_WMI_COM_HPP

