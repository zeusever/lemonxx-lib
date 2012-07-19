/**
* 
* @file     function
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/07/19
*/
#ifndef LEMONXX_LUABIND_FUNCTION_HPP
#define LEMONXX_LUABIND_FUNCTION_HPP
#include <cassert>
#include <lemonxx/errorcode.h>
#include <lemonxx/luabind/stack.hpp>
#include <lemonxx/luabind/lstate.hpp>

namespace lemon{namespace luabind{

	inline void call_function(state & L, const char * name,int nargs, int nresults)
	{
		error_info errorCode;

		if(!lua_isfunction(L,-1 - nargs))
		{
			LEMON_USER_ERROR(errorCode,LEMONXX_LUA_PCALL_ERROR);

			std::stringstream stream;

			stream << "expect function(" << name << ") ,got " << lua_typename(L,-1);

			errorCode.error_msg(lemon::from_locale(stream.str()));

			errorCode.check_throw();
		}

		int c = lua_pcall(L,nargs,nresults,0);

		if(c != LUA_OK)
		{
			LEMON_USER_ERROR(errorCode,LEMONXX_LUA_PCALL_ERROR);

			if(c == LUA_ERRRUN || c == LUA_ERRGCMM) errorCode.error_msg(lemon::from_utf8(lua_tostring(L,-1)));

			errorCode.check_throw();
		}
	}

	inline void dofile(state & L,const char * file)
	{
		error_info errorCode;

		if(0 != luaL_dofile(L,file))
		{
			LEMON_USER_ERROR(errorCode,LEMONXX_LUA_DOFILE_ERROR);

			errorCode.error_msg(lemon::from_utf8(lua_tostring(L,-1)));

			throw errorCode;
		}
	}

	inline void dofile(state & L,const std::string & file) 
	{
		dofile(L,file.c_str()); 
	}
}}
#endif //LEMONXX_LUABIND_FUNCTION_HPP