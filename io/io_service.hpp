/**
* 
* @file     io_service
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/08/31
*/
#ifndef LEMONXX_IO_IO_SERVICE_HPP
#define LEMONXX_IO_IO_SERVICE_HPP
#include <lemon/io/abi.h>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>
#include <lemonxx/function/function.hpp>

namespace lemon{namespace io{

	typedef lemon::function<void(size_t numberOfBytesTransferred , const LemonErrorInfo & errorCode)> Callback;

	inline void IOCallback( void * userdata , size_t numberOfBytesTransferred , const LemonErrorInfo *errorCode )
	{
		Callback cb((Callback::wrapper_type)userdata);

		cb(numberOfBytesTransferred,*errorCode);
	}

	class io_service : public basic_handle_object<LemonIOService,&LemonCloseIOService>
	{
	public:

		typedef basic_handle_object<LemonIOService,&LemonCloseIOService> base_type;

		io_service():base_type(Create()) {}

		void reset()
		{
			lemon::error_info errorCode;

			LemonResetIOService(*this,errorCode);

			errorCode.check_throw();
		}

		void stop()
		{
			lemon::error_info errorCode;

			LemonStopIOService(*this,errorCode);

			errorCode.check_throw();
		}

		bool stopped() const
		{
			return LemonIOServiceStatus(*this) == lemon_true ? true:false;
		}

		void dispatch()
		{
			lemon::error_info errorCode;

			LemonIODispatch(*this,errorCode);
		}

	private:

		static LemonIOService Create()
		{
			error_info errorCode;

			LemonIOService service = LemonCreateIOService(NULL,errorCode);

			errorCode.check_throw();

			return service;
		}
	};

}}

#endif //LEMONXX_IO_IO_SERVICE_HPP
