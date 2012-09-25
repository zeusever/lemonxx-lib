/**
 * 
 * @file     type_rw
 * @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
 * @author   yayanyang
 * @version  1.0.0.0  
 * @date     2012/09/25
 */
#ifndef LEMONXX_TRACE_TYPE_RW_HPP
#define LEMONXX_TRACE_TYPE_RW_HPP

#include <lemonxx/trace/object.hpp>

namespace lemon{namespace trace{

	enum buildin_type
	{
		cstring_type = 0x01,

		int8_type, uint8_type,

		int16_type, uint16_type,

		int32_type, uint32_type,

		int64_type, uint64_type,
	};

	inline void write(message & msg, int8_t val)
	{
		byte_t type = int8_type;

		msg.write((const byte_t*)&type,1);

		msg.write((const byte_t*)&val,sizeof(val));
	}

	inline void write(message & msg, uint8_t val)
	{
		byte_t type = uint8_type;

		msg.write((const byte_t*)&type,1);

		msg.write((const byte_t*)&val,sizeof(val));
	}


	inline void write(message & msg, int16_t val)
	{
		byte_t type = int16_type;

		msg.write((const byte_t*)&type,1);

		msg.write((const byte_t*)&val,sizeof(val));
	}

	inline void write(message & msg, uint16_t val)
	{
		byte_t type = uint16_type;

		msg.write((const byte_t*)&type,1);

		msg.write((const byte_t*)&val,sizeof(val));
	}

	inline void write(message & msg, int32_t val)
	{
		byte_t type = int32_type;

		msg.write((const byte_t*)&type,1);

		msg.write((const byte_t*)&val,sizeof(val));
	}

	inline void write(message & msg, uint32_t val)
	{
		byte_t type = uint32_type;

		msg.write((const byte_t*)&type,1);

		msg.write((const byte_t*)&val,sizeof(val));
	}

	inline void write(message & msg, int64_t val)
	{
		byte_t type = int64_type;

		msg.write((const byte_t*)&type,1);

		msg.write((const byte_t*)&val,sizeof(val));
	}

	inline void write(message & msg, uint64_t val)
	{
		byte_t type = uint64_type;

		msg.write((const byte_t*)&type,1);

		msg.write((const byte_t*)&val,sizeof(val));
	}

	inline void write(message & msg, const char * message)
	{
		byte_t type = cstring_type;

		uint16_t length = (uint16_t)strlen(message);

		msg.write((const byte_t*)&type,1);

		uint16_t l = ntohs(length);

		msg.write((const byte_t*)&l,sizeof(l));

		msg.write((const byte_t*)&message,length);
	}

}}

#endif // LEMONXX_TRACE_TYPE_RW_HPP
