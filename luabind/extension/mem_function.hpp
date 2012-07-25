/**
* 
* @file     mem_function
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/07/25
*/
#ifndef LEMONXX_LUABIND_MEM_FUNCTION_HPP
#define LEMONXX_LUABIND_MEM_FUNCTION_HPP
#include <map>
#include <cassert>
#include <lemonxx/errorcode.h>
#include <lemonxx/luabind/lstate.hpp>
#include <lemonxx/luabind/extension.hpp>

namespace lemon{namespace luabind{

	struct mem_handle
	{
		std::string				Name;

		mem_handle(const char * name):Name(name) {}

		virtual int call(lua_State * L) = 0;
	};

}}


namespace lemon{namespace luabind{

	inline int __call_object_function(lua_State * L)
	{
		assert(lua_islightuserdata(L,lua_upvalueindex(2)));

		mem_handle * handle = (mem_handle *)lua_touserdata(L,lua_upvalueindex(2));

		return handle->call(L);
	}

	class mem_function_table : private lemon::nocopyable
	{
	public:

		typedef std::map<std::string,mem_handle*> handles_type;

		std::string						_name;

		~mem_function_table()
		{
			handles_type::const_iterator iter,end = _set.end();

			for(iter = _set.begin(); iter != end; ++ iter)
			{
				delete iter->second;
			}
		}

		void name(const std::string & val) {_name = val; }

		const std::string & name() const { return _name; }

		void add(mem_handle * handle) 
		{ 
			_set[handle->Name] = handle;
		}

		mem_handle * find(const std::string & name)
		{
			return _set[name];
		}

		void wrapper(lua_State * L,void * data) const
		{
			lua_newtable(L);

			handles_type::const_iterator iter,end = _set.end();

			for(iter = _set.begin(); iter != end; ++ iter)
			{
				lua_pushstring(L,iter->first.c_str());

				lua_pushlightuserdata(L,data);

				lua_pushlightuserdata(L,iter->second);

				lua_pushcclosure(L,&__call_object_function,2);

				lua_settable(L,-3);
			}
		}

	private:

		handles_type			_set;
	};

	template<typename Signature> struct classfunction;


	template<typename Class> struct classfunction<void(Class::*)()> : public mem_handle
	{
		typedef										void(Class::*raw_type)();

		raw_type									_ptr;

		classfunction(const char * name,raw_type ptr)
			:mem_handle(name),_ptr(ptr)
		{}

		int call(lua_State * L) 
		{
			assert(lua_islightuserdata(L,lua_upvalueindex(1)));

			Class* obj = (Class*)lua_touserdata(L,lua_upvalueindex(1));

			(obj->*_ptr)(); 

			return 0;
		}
	};
}}
#endif //LEMONXX_LUABIND_MEM_FUNCTION_HPP