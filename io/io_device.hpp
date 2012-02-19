/**
* 
* @file     io_device
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/02/16
*/
#ifndef LEMONXX_IO_IO_DEVICE_HPP
#define LEMONXX_IO_IO_DEVICE_HPP

#include <lemon/io/abi.h>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>
#include <lemonxx/function/function.hpp>

namespace lemon{namespace io{

	typedef lemon::function<void(size_t	numberOfBytesTransferred,const LemonErrorInfo &errorCode)> AsyncIoCallback;

	class io_device 
		: public basic_handle_object<LemonIoDevice,LemonReleaseIoDevice>
	{
	public:

		typedef basic_handle_object<LemonIoDevice,LemonReleaseIoDevice> base_type;

		io_device()
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			base_type::reset(LemonCreateIoDevice(&errorCode));

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
		}

		void run()
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonJoinAsIoDeviceWorkThread(*this,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
		}

		size_t stop()
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			size_t result = LemonStopAllIoDeviceWorkThread(*this,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

			return result;
		}

		template<typename Handle>
		void post_done(Handle handle)
		{
			AsyncIoCallback cb(handle);

			LEMON_DECLARE_ERRORINFO(errorCode);	

			LemonPostIoDeviceCompeleteEvent(*this,&io_device::IoCallback,cb.release(),0,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
		}

	private:

		static void IoCallback(void *userData,size_t	numberOfBytesTransferred,const LemonErrorInfo * errorCode)
		{
			AsyncIoCallback cb(reinterpret_cast<AsyncIoCallback::wrapper_type>(userData));

			cb(numberOfBytesTransferred,*errorCode);
		}
	};
}}

#endif //LEMONXX_IO_IO_DEVICE_HPP