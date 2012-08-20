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

	inline void IoCallback(void *userData,size_t	numberOfBytesTransferred,const LemonErrorInfo * errorCode)
	{
		AsyncIoCallback cb(reinterpret_cast<AsyncIoCallback::wrapper_type>(userData));

		cb(numberOfBytesTransferred,*errorCode);
	}

	class io_device 
		: public basic_handle_object<LemonIoDevice,LemonReleaseIoDevice>
	{
	public:

		typedef basic_handle_object<LemonIoDevice,LemonReleaseIoDevice> base_type;

		io_device()
		{
			error_info errorCode;

			base_type::reset(LemonCreateIoDevice(&errorCode));

			errorCode.check_throw();
		}

		void run()
		{
			error_info errorCode;

			LemonJoinAsIoDeviceWorkThread(*this,&errorCode);

			errorCode.check_throw();
		}

		void stop()
		{
			error_info errorCode;

			LemonStopAllIoDeviceWorkThread(*this,&errorCode);

			errorCode.check_throw();
		}

		template<typename Handle>
		void post_done(Handle handle)
		{
			AsyncIoCallback cb(handle);

			error_info errorCode;	

			LemonPostIoDeviceCompeleteEvent(*this,&IoCallback,cb.release(),0,&errorCode);

			errorCode.check_throw();
		}
	};
}}

#endif //LEMONXX_IO_IO_DEVICE_HPP