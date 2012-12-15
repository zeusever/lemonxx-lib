/**
* 
* @file     job
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/12/15
*/
#ifndef LEMONXX_RUNQ_JOB_HPP
#define LEMONXX_RUNQ_JOB_HPP
#include <lemon/sys/assembly.h>
#include <lemonxx/runQ/service.hpp>
#include <lemonxx/runQ/functions.hpp>

namespace lemon{namespace runQ{

	template<typename Job>
	class basic_job_class 
	{
	public:

		typedef Job job_type;

		typedef basic_job_class<job_type>	self_type;

		static job_id create(LemonRunQ service)
		{
			LemonJobClass jobClass = 
			{
				&self_type::__initialize,
				
				&self_type::__timeout,

				&self_type::__recv,

				&self_type::__uninitialize
			};

			error_info errorCode;

			job_id id = LemonCreateJob(service,&jobClass,errorCode);

			errorCode.check_throw();

			return id;
		}

	public:

		void initialize() {}

		void uninitialize() {}

		void timeout() {}

		void recv(lemon_job_id, LemonBuffer buff)
		{
			//do nothing, release the buffer
			if(LEMON_CHECK_BUFF(buff)) runQ::free(Q,buff);
		}

	public:

		template<typename Buffer>
		void send(lemon_job_id target, Buffer buffer)
		{
			runQ::send(Q,_id,target,mutable_buffer_cast(buffer));
		}

		job_id self() const { return _id; }

		LemonRunQ service() const { return Q; }

		void close()
		{
			runQ::close_job(Q,self());
		}

		void exit()
		{
			error_info errorCode;

			LemonRunQStop(Q,errorCode);
		}

		mutable_buffer alloc(size_t block)
		{
			return runQ::alloc(Q,block);
		}

		template<typename Buffer>
		void free(Buffer buffer)
		{
			runQ::free(Q,buffer);
		}

		void start_timer(job_id job,size_t milliseconds)
		{
			runQ::start_timer(Q,job,milliseconds);
		}

		void start_timer(size_t milliseconds)
		{
			runQ::start_timer(Q,_id,milliseconds);
		}

		void stop_timer(job_id job)
		{
			runQ::stop_timer(Q,job);
		}

		void stop_timer()
		{
			runQ::start_timer(Q,_id);
		}

		void send_timeout()
		{
			runQ::send_timeout(Q,_id);
		}

		void send_timeout(job_id job)
		{
			runQ::send_timeout(Q,job);
		}

	private:

		static void* __initialize(LemonRunQ Q,lemon_job_id id,LemonErrorInfo* errorCode)
		{
			mutable_buffer block;

			try
			{
				block = runQ::alloc(Q,sizeof(job_type));

				if(block.empty())
				{
					LEMON_USER_ERROR(*errorCode,LEMON_SYS_RESOURCE_ERROR);

					return NULL;
				}

				job_type * job = new(block.Data)job_type();

				self_type * self = job;

				self->_id = id;

				self->Q = Q;

				job->initialize();

				return job;
			}
			catch(const error_info & e)
			{
				if(!block.empty()) runQ::free(Q,block);

				*errorCode = e;

				return NULL;
			}
		}

		static void __uninitialize(LemonRunQ Q,void * userdata)
		{
			job_type* job = (job_type*)userdata;

			job->uninitialize();

			runQ::free(Q,buf((byte_t*)userdata,sizeof(job_type)));
		}

		static void __timeout(LemonRunQ, void * userdata, lemon_job_id)
		{
			job_type* job = (job_type*)userdata;

			job->timeout();
		}

		static void __recv(LemonRunQ, void * userdata, lemon_job_id,lemon_job_id source, LemonBuffer buff)
		{
			job_type* job = (job_type*)userdata;

			job->recv(source,buff);
		}

	private:

		job_id						_id;

		LemonRunQ					Q;
	};

}}

#endif //LEMONXX_RUNQ_JOB_HPP
