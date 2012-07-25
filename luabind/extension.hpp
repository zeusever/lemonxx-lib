/**
* 
* @file     extension
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/07/24
*/
#ifndef LEMONXX_LUABIND_EXTENSION_HPP
#define LEMONXX_LUABIND_EXTENSION_HPP
#include <map>
#include <typeinfo>
#include <lemonxx/luabind/luapi.hpp>
#include <lemonxx/luabind/lstate.hpp>

namespace lemon{namespace luabind{

	class module_ 
	{
	public:

		module_(lua_state & L,const std::string & name):_L(&L),_name(name) {}

		template<typename Reg> inline module_& operator <= (const Reg &reg);

		operator lua_State * () { return *_L; }

		lua_state & state() { return *_L;}

		const std::string & name() const { return _name; }

		

	private:

		lua_state							*_L;

		std::string							_name;

		
	};

	inline module_ module(lua_state & L,const char * name)
	{
		return module_(L,name);
	}

	template<typename Reg>
	inline module_& module_::operator <= (const Reg &reg)
	{
		pop_stack stack(*_L);

		lua_getglobal(*_L,_name.c_str());

		if(!lua_istable(*_L,-1))
		{
			lua_newtable(*_L);

			lua_pushvalue(*_L,-1);

			lua_setglobal(*_L,_name.c_str());
		}
	
		reg.call(*this);

		return *this;
	}


}}


#endif //LEMONXX_LUABIND_EXTENSION_HPP