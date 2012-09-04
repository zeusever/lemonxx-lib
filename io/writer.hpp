/**
* 
* @file     writer
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/08/30
*/
#ifndef LEMONXX_IO_WRITER_HPP
#define LEMONXX_IO_WRITER_HPP
#include <lemon/io/abi.h>
#include <lemonxx/io/seek.hpp>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>

namespace lemon{namespace io{

	struct writer : private nocopyable
	{
		virtual ~writer() {}

		virtual size_t write( const byte_t * source,size_t length) = 0;

		virtual size_t write( const byte_t * source,size_t length,error_info & errorCode) = 0;
	};

	struct c_writer : public writer
	{
		LemonIoWriter				_w;

		c_writer(LemonIoWriter r):_w(r) {}

		size_t write( const byte_t * source,size_t length)
		{
			scope_error_info errorCode;

			return _w.Write(_w.UserData,source,length,errorCode);
		}

		size_t write( const byte_t * source,size_t length,error_info & errorCode)
		{
			return _w.Write(_w.UserData,source,length,errorCode);
		}
	};

	struct buffer_writer : public writer
	{
		void	*Data;

		size_t		Length;

		size_t		Offset;

		buffer_writer(void * data, size_t length)
			:Data(data)
			,Length(length) 
			,Offset(0)
		{}

		size_t write(const byte_t * source,size_t length)
		{
			if( Offset + length > Length ) length = Length - Offset;

			memcpy(&((byte_t*)Data)[Offset],source,length);

			Offset += length;

			return length;
		}

		size_t write(const byte_t * source,size_t length,error_info & errorCode)
		{
			LEMON_RESET_ERRORINFO(errorCode);

			if( Offset + length > Length ) length = Length - Offset;

			memcpy(&((byte_t*)Data)[Offset],source,length);

			Offset += length;

			return length;
		}
	};
}}
#endif //LEMONXX_IO_READER_HPP