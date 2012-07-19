/**
* 
* @file     type_trait
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/07/19
*/
#ifndef LEMONXX_LUABIND_TYPE_TRAIT_HPP
#define LEMONXX_LUABIND_TYPE_TRAIT_HPP

#include <lemonxx/luabind/lstate.hpp>
#include <lemonxx/type_traits/type_traits.hpp>

#define LEMON_LUABIND_INTEGER_TYPE_TRAIT(T) \
template<> struct type_trait<T>\
{\
	typedef mpl::inttypes_<int,1> nresults;\
	\
	static T from_lua(state & L)\
	{\
		return (T)lua_tonumber(L,-1);\
	}\
	\
	static void to_lua(state & L,T val)\
	{\
		lua_pushnumber(L,(lua_Number)val);\
	}\
};


namespace lemon{namespace luabind{

	template<typename T> struct	type_trait;


	template<> struct type_trait<void> 
	{
		typedef mpl::inttypes_<int,0> nresults;

		static void from_lua(state & /*L*/);
	};

	template<> struct type_trait<std::string> 
	{
		typedef mpl::inttypes_<int,1> nresults;

		static std::string from_lua(state & L)
		{
			std::string result = lua_tostring(L,-1);

			return result;
		}

		static void to_lua(state & L,const std::string & val)
		{
			lua_pushstring(L,val.c_str());
		}
	};

	template<> struct type_trait<const char*> 
	{
		typedef mpl::inttypes_<int,1> nresults;

		static const char* from_lua(state & L)
		{
			return lua_tostring(L,-1);
		}

		static void to_lua(state & L,const char* val)
		{
			lua_pushstring(L,val);
		}
	};

	template<> struct type_trait<char*> 
	{
		typedef mpl::inttypes_<int,1> nresults;

		/*static const char* from_lua(state & L)
		{
			return lua_tostring(L,-1);
		}*/

		static void to_lua(state & L,const char* val)
		{
			lua_pushstring(L,val);
		}
	};

	template<> struct type_trait<bool> 
	{
		typedef mpl::inttypes_<int,1> nresults;

		static bool from_lua(state & L)
		{
			return lua_toboolean(L,-1)? true : false;
		}

		static void to_lua(state & L,bool val)
		{
			lua_pushboolean(L,val? 1 : 0);
		}	
	};

	LEMON_LUABIND_INTEGER_TYPE_TRAIT(int);

	LEMON_LUABIND_INTEGER_TYPE_TRAIT(unsigned int);

	LEMON_LUABIND_INTEGER_TYPE_TRAIT(long);

	LEMON_LUABIND_INTEGER_TYPE_TRAIT(unsigned long);

	LEMON_LUABIND_INTEGER_TYPE_TRAIT(float);

	LEMON_LUABIND_INTEGER_TYPE_TRAIT(double);

	LEMON_LUABIND_INTEGER_TYPE_TRAIT(short);

	LEMON_LUABIND_INTEGER_TYPE_TRAIT(unsigned short);

	LEMON_LUABIND_INTEGER_TYPE_TRAIT(unsigned char);

	LEMON_LUABIND_INTEGER_TYPE_TRAIT(int64_t);

	LEMON_LUABIND_INTEGER_TYPE_TRAIT(uint64_t);
}}


namespace lemon{namespace luabind{

	template<
		typename Tuple,
		size_t Index = 1,
		bool flag = (mpl::size<Tuple>::value == Index)
	> 
	struct tupe_getter;


	template<
		typename Tuple,
		size_t Index = 1,
		bool flag = (mpl::size<Tuple>::value == Index)
	> 
	struct tupe_setter;

	template<typename Tuple,size_t Index,bool flag> 
	struct tupe_getter : public tupe_getter<Tuple,Index + 1>
	{
		typedef Tuple tuple_type;

		typedef mpl::size_t_<Index - 1> current_index;

		typedef typename basic_tuple_cast<typename Tuple::Seq,current_index::value>::origin_type value_type;

		typedef tupe_getter<Tuple,Index + 1> base_type;

		tupe_getter(state & L,tuple_type & result) : base_type(L,result)
		{
			result.set<current_index::value>(type_trait<value_type>::from_lua(L));

			lua_pop(L,1);
		}
	};

	template<typename Tuple,size_t Index> 
	struct tupe_getter<Tuple,Index,true>
	{
		typedef Tuple tuple_type;

		typedef mpl::size_t_<Index - 1> current_index;

		typedef typename basic_tuple_cast<typename Tuple::Seq,current_index::value>::origin_type value_type;

		tupe_getter(state & L,tuple_type & result)
		{
			result.set<current_index::value>(type_trait<value_type>::from_lua(L));

			lua_pop(L,1);
		}
	};

	template<size_t Index,bool flag>
	struct tupe_getter<tuple<>,Index,flag>
	{
		tupe_getter(state & ,tuple<> &){}
	};


	//////////////////////////////////////////////////////////////////////////


	template<typename Tuple,size_t Index,bool flag> 
	struct tupe_setter : public tupe_setter<Tuple,Index + 1>
	{
		typedef Tuple tuple_type;

		typedef mpl::size_t_<Index - 1> current_index;

		typedef typename basic_tuple_cast<typename Tuple::Seq,current_index::value>::origin_type value_type;

		typedef tupe_setter<Tuple,Index + 1> base_type;

		tupe_setter(state & L,tuple_type & result) : base_type(L,result)
		{
			type_trait<value_type>::to_lua(L,result.get<current_index::value>());
		}
	};

	template<typename Tuple,size_t Index> 
	struct tupe_setter<Tuple,Index,true>
	{
		typedef Tuple tuple_type;

		typedef mpl::size_t_<Index - 1> current_index;

		typedef typename basic_tuple_cast<typename Tuple::Seq,current_index::value>::origin_type value_type;

		tupe_setter(state & L,tuple_type & result)
		{
			type_trait<value_type>::to_lua(L,result.get<current_index::value>());
		}
	};

	template<size_t Index,bool flag>
	struct tupe_setter<tuple<>,Index,flag>
	{
		tupe_setter(state & ,tuple<> &){}
	};

}}

#include <lemonxx/luabind/type_trait_tuple.hpp>

#endif //LEMONXX_LUABIND_TYPE_TRAIT_HPP