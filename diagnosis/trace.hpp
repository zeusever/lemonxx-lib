/**
* 
* @file     trace
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/08/12
*/
#ifndef LEMONXX_DIAGNOSIS_TRACE_HPP
#define LEMONXX_DIAGNOSIS_TRACE_HPP
#include <vector>
#include <lemonxx/io/endpoint.hpp>
#include <lemonxx/diagnosis/trace-classes.hpp>
#include <lemon/diagnosis/assembly.h>

namespace lemon{namespace dtrace{

	enum types
	{
		T_STRING = 0x01,

		T_NUMBER = 0x02,

		T_ERRORCODE = 0x03,

		T_ENDPOINT = 0x04,
	};

	inline void write(commit_message & cm,const char * message)
	{
		byte_t t = (byte_t)T_STRING;

		cm.write_rawdata(&t,sizeof(t));

		uint16_t length = (uint16_t)strlen(message);

		uint16_t l = htons(length);

		cm.write_rawdata((const byte_t*)&l,sizeof(l));

		cm.write_rawdata((const byte_t*)message,length);
	}

	inline std::string read_string(const message & cm)
	{
		byte_t t;

		cm.read_rawdata((byte_t*)&t,sizeof(t));

		if(t != T_STRING)
		{
			error_info errorCode;

			LEMON_USER_ERROR(errorCode,LEMON_DIAGNOSIS_TRACE_TYPE_ERROR);

			errorCode.check_throw();
		}

		uint16_t length = 0;

		cm.read_rawdata((byte_t*)&length,sizeof(length));

		length = ntohs(length);

		if(length == 0) return "";

		std::vector<char> buffer(length,0);

		cm.read_rawdata((byte_t*)&buffer[0],buffer.size());

		return std::string(buffer.begin(),buffer.end());
	}

	inline void write(commit_message & cm,const std::string & message)
	{
		write(cm,message.c_str());
	}
#ifdef WIN32
	inline void write(commit_message & cm,const char_t * message)
	{
		write(cm,to_utf8(message));
	}

	inline void write(commit_message & cm,const lemon::String & message)
	{
		write(cm,to_utf8(message));
	}
#endif //WIN32
	inline void write(commit_message & cm,lemon::uint32_t val)
	{
		byte_t t = (byte_t)T_NUMBER;

		val = htonl(val);

		cm.write_rawdata(&t,sizeof(t));

		cm.write_rawdata((const byte_t*)&val,sizeof(val));
	}

	inline uint32_t read_number(const message & cm)
	{
		byte_t t;

		cm.read_rawdata((byte_t*)&t,sizeof(t));

		if(t != T_NUMBER)
		{
			error_info errorCode;

			LEMON_USER_ERROR(errorCode,LEMON_DIAGNOSIS_TRACE_TYPE_ERROR);

			errorCode.check_throw();
		}

		uint32_t length = 0;

		cm.read_rawdata((byte_t*)&length,sizeof(length));

		return ntohl(length);
	}

	inline void write(commit_message & cm,const LemonErrorInfo* errorCode)
	{
		byte_t t = (byte_t)T_ERRORCODE;

		cm.write_rawdata(&t,sizeof(t));

		uint32_t code = htonl((uint32_t)errorCode->Error.Code);

		cm.write_rawdata((const byte_t*)&code,sizeof(code));

		cm.write_rawdata((const byte_t*)errorCode->Error.Catalog,sizeof(LemonUuid));
	}


	inline uint32_t read_errorcode(const message & cm,lemon::uuid_t & id)
	{
		byte_t t;

		cm.read_rawdata((byte_t*)&t,sizeof(t));

		if(t != T_ERRORCODE)
		{
			error_info errorCode;

			LEMON_USER_ERROR(errorCode,LEMON_DIAGNOSIS_TRACE_TYPE_ERROR);

			errorCode.check_throw();
		}

		uint32_t code = 0;

		cm.read_rawdata((byte_t*)&code,sizeof(code));

		cm.read_rawdata((byte_t*)&id,sizeof(LemonUuid));

		return ntohl(code);
	}

	inline void write(commit_message & cm,const io::ip::endpoint & ep)
	{
		byte_t t = (byte_t)T_ENDPOINT;

		cm.write_rawdata(&t,sizeof(t));

		uint8_t code = (uint8_t)ep.length();

		cm.write_rawdata((const byte_t*)&code,sizeof(code));

		cm.write_rawdata((const byte_t*)ep.ptr(),ep.length());
	}

	inline io::ip::endpoint read_endpoint(const message & cm)
	{
		byte_t t;

		cm.read_rawdata((byte_t*)&t,sizeof(t));

		if(t != T_ENDPOINT)
		{
			error_info errorCode;

			LEMON_USER_ERROR(errorCode,LEMON_DIAGNOSIS_TRACE_TYPE_ERROR);

			errorCode.check_throw();
		}

		uint8_t length = 0;

		cm.read_rawdata((byte_t*)&length,sizeof(length));

		io::ip::endpoint ep;

		cm.read_rawdata((byte_t*)ep.ptr(),length);

		return ep;
	}
}}

#endif // LEMONXX_DIAGNOSIS_TRACE_HPP



