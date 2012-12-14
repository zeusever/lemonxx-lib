/**
* 
* @file     hashmap
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/12/13
*/
#ifndef LEMON_MEMORY_HASHMAP_HPP
#define LEMON_MEMORY_HASHMAP_HPP

#include <lemonxx/sys/sys.hpp>
#include <lemon/memory/hashmap.h>
#include <lemonxx/mpl/inttypes.hpp>
#include <lemonxx/memory/fixobj.hpp>
#include <lemonxx/utility/utility.hpp>
#include <lemonxx/type_traits/parameters.hpp>

namespace lemon{namespace memory{

	template<typename Key> struct hash;

	template<typename Key> struct compare;

	template<> struct hash<size_t>
	{
		size_t operator()(size_t key) const
		{
			return key;
		}
	};

	template<> struct compare<size_t>
	{
		int operator()(size_t lhs, size_t rhs) const
		{
			if(lhs > rhs) return 1;

			if(lhs == rhs) return 0;

			return -1;
		}
	};
}}

namespace lemon{namespace memory{

	template<
		typename Key,
		typename CompareF,
		bool Pointer = is_pointer<Key>::value
	> 
	struct Compare;

	template<typename Key,typename CompareF> struct Compare<Key,CompareF,true>
	{
		static int Call(const void * lhs, const void * rhs)
		{
			return CompareF()((Key)lhs,(Key)rhs);
		}
	};

	template<typename Key,typename CompareF> struct Compare<Key,CompareF,false>
	{
		static int Call(const void * lhs, const void * rhs)
		{
			return CompareF()(*(Key*)lhs,*(Key*)rhs);
		}
	};


	template<
		typename Key,
		typename F,
		bool Pointer = is_pointer<Key>::value
	> 
	struct Hash;

	template<typename Key,typename F> struct Hash<Key,F,true>
	{
		static size_t Call(const void * lhs)
		{
			return F()((Key)lhs);
		}
	};

	template<typename Key,typename F> struct Hash<Key,F,false>
	{
		static size_t Call(const void * lhs)
		{
			return F()(*(Key*)lhs);
		}
	};
}}

namespace lemon{namespace memory{

	template<
		typename Key, 
		typename Value, 
		typename HashF = hash<Key>,
		typename CompareF = compare<Key>
	>
	class hash_map : private nocopyable
	{
	public:

		typedef Key										key_type;

		typedef Value									value_type;

		typedef HashF									hash_type;

		typedef CompareF								compare_type;

		typedef hash_map<
			key_type,
			value_type,
			hash_type,
			compare_type>								self_type;

		typedef fixed::allocator<sizeof(key_type)>		key_allocator;

		typedef fixed::allocator<sizeof(value_type)>	value_allocator;

	public:

		static size_t default_buckets() { return 1024; }

		static double default_factor() { return 0.5f; }

	public:
		
		hash_map() :_map(create(default_buckets())) {}

		hash_map(size_t buckets) : _map(create(buckets)) {}

	public:

		
			
	private:

		static LemonHashMap create(size_t buckets)
		{
			error_info errorCode;

			LemonHashMap map = LemonCreateHashMap
				(
				buckets,
				default_factor(),
				&Hash<key_type,hash_type>::Call,
				&Compare<key_type,compare_type>::Call,
				errorCode
				);

			errorCode.check_throw();

			return map;
		}

	private:

		LemonHashMap												_map;

		key_allocator												_keyAllocator;

		value_allocator												_valueAllocator;
	};

}}
#endif //LEMON_MEMORY_HASHMAP_HPP

