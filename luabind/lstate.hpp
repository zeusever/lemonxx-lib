/**
* 
* @file     lstate
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/07/20
*/
#ifndef LEMONXX_LUABIND_LSTATE_HPP
#define LEMONXX_LUABIND_LSTATE_HPP

#include <cassert>
#include <lemon/lua/lua.hpp>
#include <lemonxx/errorcode.h>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>

LUA_API const void * LEMON_LUABIND_REGISTRY_KEY_VALUE;

#define LEMON_LUABIND_REGISTRY_KEY &LEMON_LUABIND_REGISTRY_KEY_VALUE

namespace lemon{namespace luabind{

	class lua_state : private lemon::nocopyable
	{
	public:

		lua_state();

		lua_state(lua_State * L);

		~lua_state() { unbound(); }

		operator lua_State * () { return _L; }

	private:

		void bind();

		void unbound();

	private:

		lua_State		*_L;
	};


	inline lua_state::lua_state()
		:_L(luaL_newstate())
	{
		error_info errorCode;

		if(!_L)
		{
			LEMON_USER_ERROR(errorCode,LEMONXX_OPEN_LUA_ERROR);
		}

		bind();
	}

	inline lua_state::lua_state(lua_State * L)
		:_L(L)
	{
		assert(_L && "L must not null");

		bind();
	}

	inline void lua_state::bind()
	{
		//first open the standard libraries
		luaL_openlibs(_L);
		
		//second register the lua_state * 
		lua_pushlightuserdata(_L,LEMON_LUABIND_REGISTRY_KEY);

		lua_pushlightuserdata(_L,this);

		lua_settable(_L,LUA_REGISTRYINDEX);
	}

	inline void lua_state::unbound()
	{
		lua_pushlightuserdata(_L,LEMON_LUABIND_REGISTRY_KEY);

		lua_pushnil(_L);

		lua_settable(_L,LUA_REGISTRYINDEX);
	}
}}


#endif //LEMONXX_LUABIND_LSTATE_HPP