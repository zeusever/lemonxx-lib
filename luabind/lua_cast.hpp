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
#include <typeinfo>
#include <lemonxx/utility/utility.hpp>
#include <lemonxx/type_traits/type_traits.hpp>
#include <lemonxx/luabind/lstate.hpp>
#include <lemonxx/luabind/extension/mem_function_table.hpp>

#define LEMON_LUABIND_INTEGER_TYPE_CAST(T) \
	template<> struct lua_cast<T>\
	{\
	static T from(lua_State *L,int index)\
	{\
	luaL_checknumber(L,index);\
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

			const mem_function_table * calltable = context(L)->register_class(typeid(typename remove_cv<T>::type));

			if(calltable)
			{
				calltable->wrapper(L,(void*)t);

				/**(T**)lua_newuserdata(L,sizeof(T*)) = t;

				luaL_setmetatable(L,calltable->name().c_str());*/
			}
			else
			{
				lua_pushlightuserdata(L,(void*)t);
			}
		}

		static T * from(lua_State *L,int index)
		{
			const mem_function_table * calltable = context(L)->register_class(typeid(typename remove_cv<T>::type));

			if(calltable)
			{
				luaL_checktype(L,index,LUA_TTABLE);

				return (T*)calltable->unwrapper(L,index);
			}
			else
			{
				luaL_checktype(L,index,LUA_TLIGHTUSERDATA);

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
			luaL_checktype(L,index,LUA_TSTRING);

			return lua_tostring(L,index);
		}
	};

	template<size_t N> struct lua_cast<lemon::byte_t[N]>
	{
		static void to(lua_State *L,lemon::byte_t * val)
		{
			lua_checkstack(L,1);

			lua_pushlstring(L,(const char*)val,N);
		}
	};

	template<> struct lua_cast<lemon::const_buffer>
	{
		static void to(lua_State *L,const lemon::const_buffer &buffer)
		{
			lua_checkstack(L,1);

			lua_pushlstring(L,(const char*)buffer.Data,buffer.Length);
		}

		static lemon::const_buffer from(lua_State *L,int index)
		{
			luaL_checktype(L,index,LUA_TSTRING);

			size_t length = 0;

			const char * buffer = lua_tolstring(L,index,&length);

			return lemon::cbuf(buffer,length);
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
			luaL_checktype(L,index,LUA_TSTRING);

			return lua_tostring(L,index);
		}
	};

	template<> struct lua_cast<char*>
	{
		static void to(lua_State *L,const char* val)
		{
			lua_checkstack(L,1);

			lua_pushstring(L,val);
		}

		static const char* from(lua_State *L,int index)
		{
			luaL_checktype(L,index,LUA_TSTRING);

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
			luaL_checktype(L,index,LUA_TBOOLEAN);

			return lua_toboolean(L,index) ? true : false;
		}
	};

	template<typename T> struct lua_cast< std::vector<T> >
	{
		static void to(lua_State *L,const std::vector<T> & val)
		{
			lua_newtable(L);

			std::vector<T>::const_iterator iter,end = val.end();

			int index = 1;

			for(iter = val.begin(); iter != end; ++ iter)
			{
				lua_pushnumber(L,index);

				lua_cast<T>::to(L,*iter);

				lua_settable(L,-3);

				++ index ;
			}
		}

		static std::vector<T> from(lua_State *L,int index)
		{
			luaL_checktype(L,index,LUA_TTABLE);

			std::vector<T> val;

			lua_pushnil(L); 

			while (lua_next(L, index - 1) != 0)
			{
				val.push_back(lua_cast<T>::from(L,-1));

				lua_pop(L, 1);
			}

			lua_pop(L, 1);
		}
	};

	LEMON_LUABIND_INTEGER_TYPE_CAST(int);

	LEMON_LUABIND_INTEGER_TYPE_CAST(unsigned int);

	LEMON_LUABIND_INTEGER_TYPE_CAST(short);

	LEMON_LUABIND_INTEGER_TYPE_CAST(unsigned short);

	LEMON_LUABIND_INTEGER_TYPE_CAST(char);

	LEMON_LUABIND_INTEGER_TYPE_CAST(unsigned char);
}}

#endif //LEMONXX_LUABIND_LUA_CAST_HPP
