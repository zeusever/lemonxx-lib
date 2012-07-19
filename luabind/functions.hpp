/**
* 
* @file     functions
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/07/17
*/
#ifndef LEMONXX_LUABIND_FUNCTIONS_HPP
#define LEMONXX_LUABIND_FUNCTIONS_HPP

#include <lemonxx/errorcode.h>
#include <lemonxx/luabind/stack.hpp>
#include <lemonxx/luabind/state.hpp>

namespace lemon{namespace luabind{

	inline void dofile(state & L,const char * file)
	{
		LEMON_DECLARE_ERRORINFO(errorCode);

		auto_pop_stack stack(L);

		if(0 != luaL_dofile(L.ptr(),file))
		{
			LEMON_USER_ERROR(errorCode,LEMONXX_LUA_DOFILE_ERROR);

			throw lemon::Exception(lua_tostring(L.ptr(),-1),errorCode);
		}
	}

	inline void dofile(state & L,const std::string & file)
	{
		dofile(L,file.c_str());
	}

}}
#endif //LEMONXX_LUABIND_FUNCTIONS_HPP