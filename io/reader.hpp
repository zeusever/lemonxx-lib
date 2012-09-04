/**
* 
* @file     reader
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/08/30
*/
#ifndef LEMONXX_IO_READER_HPP
#define LEMONXX_IO_READER_HPP
#include <lemon/io/abi.h>
#include <lemonxx/io/seek.hpp>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>

namespace lemon{namespace io{
	struct reader : private nocopyable
	{
		virtual ~reader() {}

		virtual size_t read( byte_t * source,size_t length) = 0;

		virtual size_t read( byte_t * source,size_t length,error_info & errorCode) = 0;
	};

	struct c_reader : public reader
	{
		LemonIoReader				_r;

		c_reader(LemonIoReader r):_r(r) {}

		size_t read( byte_t * source,size_t length)
		{
			scope_error_info errorCode;

			return _r.Read(_r.UserData,source,length,errorCode);
		}

		size_t read( byte_t * source,size_t length,error_info & errorCode)
		{
			return _r.Read(_r.UserData,source,length,errorCode);
		}
	};


	struct buffer_reader : public reader
	{
		const void	*Data;

		size_t		Length;

		size_t		Offset;

		buffer_reader(const void * data, size_t length)
			:Data(data)
			,Length(length) 
			,Offset(0)
		{}

		size_t read( byte_t * source,size_t length)
		{
			if( Offset + length > Length ) length = Length - Offset;

			memcpy(source,&((const byte_t*)Data)[Offset],length);

			Offset += length;

			return length;
		}

		size_t read( byte_t * source,size_t length,error_info & errorCode)
		{
			LEMON_RESET_ERRORINFO(errorCode);

			if( Offset + length > Length ) length = Length - Offset;

			memcpy(source,&((const byte_t*)Data)[Offset],length);

			Offset += length;

			return length;
		}
	};

}}

#endif //LEMONXX_IO_READER_HPP