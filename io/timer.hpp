/**
* 
* @file     timer
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/02/21
*/
#ifndef LEMONXX_IO_TIMER_HPP
#define LEMONXX_IO_TIMER_HPP
#include <lemon/io/timer.h>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>
#include <lemonxx/function/function.hpp>
#include <lemonxx/io/io_device.hpp>
namespace lemon{namespace io{

	typedef lemon::function<void()> TimerCallback;

	class timer 
		: public basic_handle_object<LemonTimer,&LemonCloseTimer>
	{
	public:
		
		basic_handle_object<LemonTimer,&LemonCloseTimer> base_type;

		timer(){}

		template<typename Handle>
		timer(io_device & device,size_t milliseconds,Handle handle)
		{
			start(device,milliseconds,handle);
		}

		template<typename Handle>
		void start(io_device & device,size_t milliseconds,Handle handle)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			_callback = handle;

			reset(LemonCreateTimer(milliseconds,&Callback,this,device,&errorCode));
		}

		void stop()
		{
			LemonTimer handle = release();

			if(LEMON_CHECK_HANDLE(handle))
			{
				LemonCloseTimer(handle);

				handle = LEMON_HANDLE_NULL_VALUE;
			}
		}

	private:

		static void Callback(void * userData)
		{
			((timer*)userData)->_callback();
		}

		TimerCallback _callback;
	};

}}

#endif //LEMONXX_IO_TIMER_HPP