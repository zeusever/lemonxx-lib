/**
 * 
 * @file     sys
 * @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
 * @author   yayanyang
 * @version  1.0.0.0  
 * @date     2012/08/21
 */
#ifndef LEMONXX_SYS_HPP
#define LEMONXX_SYS_HPP

#include <lemonxx/sys/coroutine.hpp>
#include <lemonxx/sys/datetime.hpp>
#include <lemonxx/sys/errorcode.hpp>
#include <lemonxx/sys/ld.hpp>
#include <lemonxx/sys/random.hpp>
#include <lemonxx/sys/text.hpp>
#include <lemonxx/sys/thread.hpp>
#include <lemonxx/sys/inttypes.hpp>
#include <lemonxx/sys/handle.hpp>
#include <lemonxx/sys/errorcode.hpp>
#include <lemonxx/sys/filesystem.hpp>
#include <lemonxx/sys/environment.hpp>
#include <lemonxx/sys/resource.hpp>
#include <lemonxx/sys/ostream.hpp>
#include <lemonxx/sys/converter.hpp>
#include <lemonxx/utility/nocopyable.hpp>

namespace lemon{namespace io{

	struct seek
	{
		enum Value
		{
			begin = LEMON_IO_BEGIN, current = LEMON_IO_CURRENT, end = LEMON_IO_END
		};
	};

	struct reader : private nocopyable
	{
		virtual ~reader() {}
		
		virtual size_t read( byte_t * source,size_t length) = 0;

		virtual size_t read( byte_t * source,size_t length,error_info & errorCode) = 0;
	};

	struct writer : private nocopyable
	{
		virtual ~writer() {}

		virtual size_t write( const byte_t * source,size_t length) = 0;

		virtual size_t write( const byte_t * source,size_t length,error_info & errorCode) = 0;
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

}}

#endif // LEMONXX_SYS_HPP