/**
* 
* @file     file
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/06/15
*/
#ifndef LEMONXX_IO_FILE_HPP
#define LEMONXX_IO_FILE_HPP

#include <lemon/io/abi.h>
#include <lemon/io/file.h>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/io/io_device.hpp>
#include <lemonxx/utility/utility.hpp>
#include <lemonxx/io/object.hpp>

namespace lemon{namespace io{

	class file : public basic_object<LemonIo,&LemonCloseFile>
	{
	public:
		typedef basic_object<LemonIo,&LemonCloseFile> base_type;

		file():base_type(LEMON_HANDLE_NULL_VALUE){}

		file(LemonFileHandle native)
			:base_type(WrapHandle(native,LEMON_HANDLE_NULL_VALUE))
		{

		}

		file(LemonFileHandle native,io_device & device)
			:base_type(WrapHandle(native,device))
		{

		}
		
		static LemonIo WrapHandle(LemonFileHandle native,LemonIoDevice device)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonIo io = LemonNativeFileHandle(native,device,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

			return io;
		}
	};

}}

#endif //LEMONXX_IO_FILE_HPP
