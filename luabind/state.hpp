/**
* 
* @file     state
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/07/17
*/
#ifndef LEMONXX_LUABIND_STATE_HPP
#define LEMONXX_LUABIND_STATE_HPP

#include <lemon/lua/lua.hpp>
#include <lemonxx/errorcode.h>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>

namespace lemon{namespace luabind{

	class state : private lemon::nocopyable
	{
	public:

		state()
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			_L = luaL_newstate();

			if(NULL == _L)
			{
				LEMON_USER_ERROR(errorCode,LEMONXX_LUA_NEWSTATE_ERROR);

				throw lemon::Exception(errorCode);
			}

			luaL_openlibs(_L);
		}

		~state()
		{
			lua_close(_L);
		}

		lua_State * ptr() { return _L; }

		const lua_State * ptr() const { return _L; }

		operator lua_State * (){ return _L; }

		operator const lua_State * () const { return _L; }

	private:

		lua_State			*_L;
	};

}}
#endif //LEMONXX_LUABIND_STATE_HPP