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
#include <lemonxx/luabind/stack.hpp>
#include <lemonxx/luabind/lstate.hpp>

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

}}
#endif //LEMONXX_LUABIND_LUAPI_HPP