/**
* 
* @file     luapi
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/07/20
*/
#ifndef LEMONXX_LUABIND_LUAPI_HPP
#define LEMONXX_LUABIND_LUAPI_HPP

#include <lemonxx/assembly.h>
#include <lemonxx/luabind/stack.hpp>
#include <lemonxx/luabind/lstate.hpp>
#include <lemonxx/luabind/lua_cast.hpp>

namespace lemon{namespace luabind{
	//
	// get the register lua_state object.
	// 
	inline lua_state * context(lua_State * L)
	{
		auto_pop_stack stack(L);

		lua_pushlightuserdata(L,LEMON_LUABIND_REGISTRY_KEY);

		lua_gettable(L,LUA_REGISTRYINDEX);

		if(!lua_islightuserdata(L,-1)) assert(false && "the L is not register for luabind");

		lua_state * s = (lua_state *)lua_touserdata(L,-1);

		return s;
	}

	inline void dofile(lua_State * L,const char * file)
	{
		error_info errorCode;

		if(luaL_dofile(L,file))
		{
			LEMON_USER_ERROR(errorCode,LEMONXX_LUA_DOFILE_ERROR);

			errorCode.error_msg(lemon::from_utf8(lua_tostring(L,-1)));

			errorCode.check_throw();
		}
	}

	template<typename T>
	inline void setglobal(lua_State * L ,const char * varname,T t)
	{
		lua_cast<T>::to(L,t);

		lua_setglobal(L,varname);
	}

	inline void dostring(lua_State * L,const char * message)
	{
		error_info errorCode;

		if(luaL_dostring(L,message))
		{
			LEMON_USER_ERROR(errorCode,LEMONXX_LUA_DOFILE_ERROR);

			errorCode.error_msg(lemon::from_utf8(lua_tostring(L,-1)));

			errorCode.check_throw();
		}
	}
}}
#endif //LEMONXX_LUABIND_LUAPI_HPP