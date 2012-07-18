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
#include <lemonxx/configure.h>
#include <lemon/lua/lua.hpp>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/errorcode.h>
#include <lemon/memory/fixobj.h>
#include <lemonxx/utility/utility.hpp>


LEMONXX_API LemonFixObjectAllocator LemonCreateLuaBindAllocator(__lemon_inout LemonErrorInfo *errorCode);

LEMONXX_API void LemonReleaseLuaBindAllocator(__lemon_inout LemonFixObjectAllocator allocator);

namespace lemon{namespace luabind{

	class state : private lemon::nocopyable
	{
	public:

		state();

		~state();
		
		state(lua_State * L):_L(L) {}

	public:

		void * alloc();

		void free(void * data);

	public:

		operator lua_State * () { return _L; }

	private:

		lua_State						*_L;

		LemonFixObjectAllocator			_allocator;
	};

	//////////////////////////////////////////////////////////////////////////
	//
	// the state implement functions 
	// 
	//////////////////////////////////////////////////////////////////////////


	inline state::state()
		:_L(luaL_newstate())
	{
		error_info errorCode;

		if(!_L)
		{
			LEMON_USER_ERROR(errorCode,LEMONXX_OPEN_LUA_ERROR);

			throw errorCode;
		}

		_allocator = LemonCreateLuaBindAllocator(errorCode);

		errorCode.check_throw();
	}

	inline state::~state()
	{
		LemonReleaseLuaBindAllocator(_allocator);

		lua_close(_L);
	}

	inline void * state::alloc()
	{
		return LemonFixObjectAlloc(_allocator);
	}

	inline void state::free(void * data)
	{
		LemonFixObjectFree(_allocator,data);
	}
}}

#endif // LEMONXX_LUABIND_LSTATE_HPP