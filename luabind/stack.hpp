/**
* 
* @file     stack
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/07/17
*/
#ifndef LEMONXX_LUABIND_STACK_HPP
#define LEMONXX_LUABIND_STACK_HPP

#include <lemon/lua/lua.hpp>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/luabind/lstate.hpp>
#include <lemonxx/utility/utility.hpp>

namespace lemon{namespace luabind{

	class auto_pop_stack : private lemon::nocopyable
	{
	public:

		auto_pop_stack(state & L) :_L(L),_top(lua_gettop(_L)) {}

		~auto_pop_stack() { lua_settop(_L,_top); }

	private:

		state	&_L;

		int		_top;
	};

}}


#endif //LEMONXX_LUA_STACK_HPP
