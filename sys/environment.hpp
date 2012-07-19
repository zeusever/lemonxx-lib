/**
* 
* @file     environment
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/07/17
*/
#ifndef LEMONXX_SYS_ENVIROMENT_HPP
#define LEMONXX_SYS_ENVIROMENT_HPP


#include <lemonxx/sys/text.hpp>
#include <lemon/sys/environment.h>

namespace lemon{

	inline lemon::String getenv(const lemon::String & varname)
	{
		LEMON_DECLARE_ERRORINFO(errorCode);

		std::vector<lemon_char_t> buffer(0);

		size_t length = LemonGetEnv(varname.c_str(),NULL,0,&errorCode);

		if(LEMON_FAILED(errorCode)) throw lemon::Exception(errorCode);

		if(length == 0) return lemon::String();

		buffer.resize(length + 1);

		LemonGetEnv(varname.c_str(),&buffer[0],buffer.size(),&errorCode);

		return &buffer[0];
	}

	inline void setenv(const lemon::String & varname,const lemon::String & val)
	{
		LEMON_DECLARE_ERRORINFO(errorCode);

		LemonSetEnv(varname.c_str(),val.c_str(),&errorCode);

		if(LEMON_FAILED(errorCode)) throw lemon::Exception(errorCode);
	}

	inline lemon::String get_homedirectory(const lemon::String & varname)
	{
		lemon::String val = getenv(varname);

#ifdef WIN32

		if(val.empty())
		{
			lemon_char_t buffer[MAX_PATH] = {0};

			GetModuleFileNameW(NULL,buffer,MAX_PATH);

			val = buffer;

			val = val.substr(0,val.find_last_of(LEMON_TEXT('\\')));

			val += LEMON_TEXT("\\..\\");
		}
		
#endif //WIN32

		return val;
	}

}

#endif //LEMONXX_SYS_ENVIROMENT_HPP