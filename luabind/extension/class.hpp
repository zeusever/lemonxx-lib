/**
* 
* @file     class
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/07/25
*/
#ifndef LEMONXX_LUABIND_EXTENSION_CLASS_HPP
#define LEMONXX_LUABIND_EXTENSION_CLASS_HPP
#include <sstream>
#include <lemonxx/luabind/lstate.hpp>
#include <lemonxx/luabind/extension.hpp>
#include <lemonxx/luabind/extension/mem_function.hpp>
namespace lemon{namespace luabind{

	inline int __call_index(lua_State * L)
	{
		assert(lua_islightuserdata(L,lua_upvalueindex(1)));

		mem_handle * handle = (mem_handle *)lua_touserdata(L,lua_upvalueindex(1));

		return handle->call(L);
	}

	inline int __class_index(lua_State * L)
	{
		luaL_checkstring(L,-1);

		assert(lua_islightuserdata(L,lua_upvalueindex(1)));

		mem_function_table * self = (mem_function_table *)lua_touserdata(L,lua_upvalueindex(1));

		mem_handle * handle = self->find(lua_tostring(L,-1));

		if(handle)
		{
			lua_pushlightuserdata(L,handle);

			lua_pushcclosure(L,&__call_index,1);

			return 1;
		}

		return 0;
	}

	template<typename T> struct class_ 
	{	
		typedef T						class_type;

		std::string						_name;

		mutable mem_function_table		*_calltable;
	
		class_(const char * name);

		~class_(){ if(_calltable) delete _calltable; }

		void call(module_ & module) const;

		template<class F> class_<T> & def(const char * name, F f);
	};

	template<typename T> inline class_<T>::class_(const char * name) 
		:_name(name),_calltable(new mem_function_table())
	{

	}

	template<typename T> inline void class_<T>::call(module_ & module) const
	{
		assert(_calltable);

		std::stringstream stream;

		stream << module.name() << "_" << _name;

		std::string className = stream.str().c_str();

		luaL_newmetatable(module,className.c_str());

		_calltable->name(className);

		lua_pushstring(module,"__index");

		lua_pushlightuserdata(module,(void*)_calltable);

		lua_pushcclosure(module,&__class_index,1);

		lua_rawset(module,-3);

		module.state().register_class(typeid(T),_calltable);

		_calltable = NULL;
	}

	template<typename T> 
	template<class F> 
	inline class_<T> & class_<T>::def(const char * name, F f)
	{
		_calltable->add(new classfunction<F>(name,f));

		return *this;
	}

}}

#endif //LEMONXX_LUABIND_EXTENSION_CLASS_HPP