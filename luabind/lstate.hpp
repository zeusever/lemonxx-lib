/**
* 
* @file     lstate
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012
*/
#ifndef LEMONXX_LUABIND_LSTATE_HPP
#define LEMONXX_LUABIND_LSTATE_HPP

#include <lemon/lua/lua.hpp>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/errorcode.h>
#include <lemonxx/utility/utility.hpp>


namespace lemon{namespace luabind{

	class state : private lemon::nocopyable
	{
	public:

		state();
		
		state(lua_State * L):_L(L) {}

	private:

		lua_State				*_L;
	};

	inline state::state()
		:_L(luaL_newstate())
	{
		error_info errorCode;

		if(!_L)
		{
			LEMON_USER_ERROR(errorCode,LEMONXX_OPEN_LUA_ERROR);
		}
	}
}}

#endif // LEMONXX_LUABIND_LSTATE_HPP