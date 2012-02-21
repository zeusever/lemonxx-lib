/**
* 
* @file     pipe
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/02/20
*/
#ifndef LEMONXX_IO_PIPE_HPP
#define LEMONXX_IO_PIPE_HPP
#include <lemon/io/abi.h>
#include <lemon/io/pipe.h>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/io/io_device.hpp>
#include <lemonxx/utility/utility.hpp>
#include <lemonxx/io/object.hpp>

namespace lemon{namespace io{namespace pipe{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	server
	///
	/// @brief	Server. 
	///
	/// @author	Yuki
	/// @date	2012/2/20
	////////////////////////////////////////////////////////////////////////////////////////////////////

	class server : public basic_object<LemonPipe,&LemonReleasePipe>
	{
	public:

		typedef basic_object<LemonPipe,&LemonReleasePipe> base_type;

		server(const char * name,LemonPipeOpenMode openMode,uint32_t timeout)
			:base_type(Create(name,openMode,timeout,LEMON_HANDLE_NULL_VALUE))
		{

		}

		server(const char * name,LemonPipeOpenMode openMode)
			:base_type(Create(name,openMode,0,LEMON_HANDLE_NULL_VALUE))
		{

		}

		server(const char * name)
			:base_type(Create(name,LEMON_PIPE_DUPLEX,0,LEMON_HANDLE_NULL_VALUE))
		{

		}

		server(const char * name,LemonPipeOpenMode openMode,uint32_t timeout,io_device & device)
			:base_type(Create(name,openMode,timeout,device))
		{

		}

		server(const char * name,LemonPipeOpenMode openMode,io_device & device)
			:base_type(Create(name,openMode,0,device))
		{

		}

		server(const char * name,io_device & device)
			:base_type(Create(name,LEMON_PIPE_DUPLEX,0,device))
		{

		}

		void accept()
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonPipeServerAccept(*this,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
		}

		
		
	private:

		static LemonPipe Create(const char * name,LemonPipeOpenMode openMode,uint32_t timeout,LemonIoDevice device)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonPipe pipe = LemonCreatePipeServer(name,openMode,timeout,device,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

			return pipe;
		}

	};


	class client : public basic_object<LemonPipe,&LemonReleasePipe>
	{
	public:
		typedef basic_object<LemonPipe,&LemonReleasePipe> base_type;

		client(const char * name,LemonPipeOpenMode openMode)
			:base_type(Create(name,openMode,LEMON_HANDLE_NULL_VALUE))
		{

		}

		client(const char * name)
			:base_type(Create(name,LEMON_PIPE_DUPLEX,LEMON_HANDLE_NULL_VALUE))
		{

		}

		client(const char * name,LemonPipeOpenMode openMode,io_device & device)
			:base_type(Create(name,openMode,device))
		{

		}

		client(const char * name,io_device & device)
			:base_type(Create(name,LEMON_PIPE_DUPLEX,device))
		{

		}

	private:
		static LemonPipe Create(const char * name,LemonPipeOpenMode openMode,LemonIoDevice device)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonPipe pipe = LemonCreatePipeClient(name,openMode,device,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

			return pipe;
		}
	};
}}}

#endif //LEMONXX_IO_PIPE_HPP