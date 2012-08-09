/**
* 
* @file     ppc
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/08/06
*/
#ifndef LEMONXX_PPC_PPC_HPP
#define LEMONXX_PPC_PPC_HPP
#include <cassert>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>
#include <lemon/ppc/abi.h>

namespace lemon{namespace ppc{

	struct types
	{
		enum
		{
			integer = 0,integer64
		};
	};

	template<typename T> struct type_trait;

	template<> struct type_trait<int32_t>
	{
		static size_t length(int32_t)
		{
			return sizeof(int32_t) + 1;
		}

		static size_t write(LemonTraceMessage * message,size_t offset,int32_t val)
		{
			assert(offset <  message->DataLength);

			lemon::byte_t * data  = (lemon::byte_t*)message + sizeof(LemonTraceMessage);

			data[offset] = (lemon::byte_t)types::integer;

			memcpy(&data[offset + 1],&val,sizeof(int32_t));

			return offset + length(val);
		}
	};

}}
#endif //LEMONXX_PPC_PPC_HPP