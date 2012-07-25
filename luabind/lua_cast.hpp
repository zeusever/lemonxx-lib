/**
* 
* @file     lua_cast
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/07/24
*/
#ifndef LEMONXX_LUABIND_LUA_CAST_HPP
#define LEMONXX_LUABIND_LUA_CAST_HPP
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>
#include <lemonxx/type_traits/type_traits.hpp>
#include <lemonxx/luabind/extension/mem_function.hpp>

#define LEMON_LUABIND_INTEGER_TYPE_CAST(T) \
	template<> struct lua_cast<T>\
	{\
	typedef mpl::inttypes_<int,1> nresults;\
	\
	static T from(lua_State *L,int index)\
	{\
	return (T)lua_tonumber(L,index);\
	}\
	\
	static void to(lua_State *L,T val)\
	{\
	lua_pushnumber(L,(lua_Number)val);\
	}\
	};

namespace lemon{namespace luabind{

	template<typename T> struct lua_cast;

	template<> struct lua_cast<void>
	{
		static void from(lua_State *,int ){}
	};

	template<typename T> struct lua_cast<T*>
	{
		static void to(lua_State *L,T *t)
		{
			lua_checkstack(L,1);

			const mem_function_table * calltable = context(L)->register_class(typeid(T));

			if(calltable)
			{
				//calltable->wrapper(L,t);

				(T**)lua_newuserdata(L,sizeof(T*));

				luaL_setmetatable(L,calltable->name().c_str());
			}
			else
			{
				lua_pushlightuserdata(L,t);
			}
		}

		static T * from(lua_State *L,int index)
		{
			const char * name = context(L)->register_class(typeid(T));

			if(name)
			{
				return *(T**)lua_touserdata(L,index);
			}
			else
			{
				return (T*)lua_touserdata(L,index);
			}
		}
	};

	template<> struct lua_cast<std::string>
	{
		static void to(lua_State *L,const std::string & val)
		{
			lua_checkstack(L,1);

			lua_pushstring(L,val.c_str());
		}

		static std::string from(lua_State *L,int index)
		{
			return lua_tostring(L,index);
		}
	};

	template<size_t N> struct lua_cast<lemon::byte_t[N]>
	{
		static void to(lua_State *L,lemon::byte_t * val)
		{
			lua_checkstack(L,1);

			lua_pushlstring(L,val,N);
		}
	};

	template<> struct lua_cast<const char*>
	{
		static void to(lua_State *L,const char* val)
		{
			lua_checkstack(L,1);

			lua_pushstring(L,val);
		}

		static const char* from(lua_State *L,int index)
		{
			return lua_tostring(L,index);
		}
	};

	template<> struct lua_cast<bool>
	{
		static void to(lua_State *L,bool val)
		{
			lua_checkstack(L,1);

			lua_pushboolean(L,val? 1 : 0);
		}

		static bool from(lua_State *L,int index)
		{
			return lua_toboolean(L,index) ? true : false;
		}
	};


	LEMON_LUABIND_INTEGER_TYPE_CAST(int);

	LEMON_LUABIND_INTEGER_TYPE_CAST(unsigned int);

	LEMON_LUABIND_INTEGER_TYPE_CAST(long);

	LEMON_LUABIND_INTEGER_TYPE_CAST(unsigned long);

	LEMON_LUABIND_INTEGER_TYPE_CAST(float);

	LEMON_LUABIND_INTEGER_TYPE_CAST(double);

	LEMON_LUABIND_INTEGER_TYPE_CAST(short);

	LEMON_LUABIND_INTEGER_TYPE_CAST(unsigned short);

	LEMON_LUABIND_INTEGER_TYPE_CAST(unsigned char);

	LEMON_LUABIND_INTEGER_TYPE_CAST(int64_t);

	LEMON_LUABIND_INTEGER_TYPE_CAST(uint64_t);
}}

#endif //LEMONXX_LUABIND_LUA_CAST_HPP