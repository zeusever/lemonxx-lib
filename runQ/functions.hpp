/**
* 
* @file     functions
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/12/15
*/
#ifndef LEMONXX_RUNQ_FUNCTIONS_HPP
#define LEMONXX_RUNQ_FUNCTIONS_HPP
#include <lemonxx/runQ/service.hpp>

namespace lemon{ namespace runQ{

	inline mutable_buffer alloc(LemonRunQ s,size_t size)
	{
		return LemonRunQAlloc(s,size);
	}
	
	template<typename Buffer>
	inline void free(LemonRunQ s,Buffer buffer)
	{
		return LemonRunQFree(s,mutable_buffer_cast(buffer));
	}

	inline void send(LemonRunQ s,lemon_job_id self,lemon_job_id target, mutable_buffer buffer)
	{
		error_info errorCode;

		LemonRunQSend(s,self,target,buffer,errorCode);

		errorCode.check_throw();
	}

	inline void close_job(LemonRunQ s,lemon_job_id id)
	{
		LemonCloseJob(s,id);
	}

	inline void start_timer(LemonRunQ s, lemon_job_id id,size_t milliseconds)
	{
		error_info errorCode;

		LemonRunQTimerStart(s,id,milliseconds * 1000 * 10,errorCode);

		errorCode.check_throw();
	}

	inline void stop_timer(LemonRunQ s, lemon_job_id id)
	{
		LemonRunQTimerStop(s,id);
	}

	inline void send_timeout(LemonRunQ s, lemon_job_id id)
	{
		LemonJobTimeout(s,id);
	}

	inline size_t jobs(LemonRunQ s)
	{
		return LemonRunQJobs(s);
	}

	inline void bind_proxy(LemonRunQ s, lemon_job_id proxy)
	{
		LemonCreateProxyJob(s,proxy);
	}

}}

#endif //LEMONXX_RUNQ_FUNCTIONS_HPP
