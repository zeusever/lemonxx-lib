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
			return create(service,NULL);
		}

		static job_id create(LemonRunQ service,void * param)
		{
			const static LemonJobClass jobClass = 
			{
				&self_type::__initialize,

				&self_type::__recv,

				&self_type::__uninitialize
			};

			error_info errorCode;

			job_id id = LemonCreateJob(service,param,&jobClass,errorCode);

			errorCode.check_throw();

			return id;
		}

	public:

		void initialize(void*) {}

		void uninitialize() {}

		void timeout() {}

		void recv(lemon_job_id, LemonBuffer buff)
		{
			//do nothing, release the buffer
			if(LEMON_CHECK_BUFF(buff)) runQ::free(Q,buff);
		}

		void proxy(lemon_job_id, lemon_job_id, LemonBuffer buff)
		{
			//do nothing, release the buffer
			if(LEMON_CHECK_BUFF(buff)) runQ::free(Q,buff);
		}

		void multicast(lemon_job_id, const_buffer) {}

		void broadcast(lemon_job_id, LemonBuffer buff)
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
			runQ::stop_timer(Q,_id);
		}

		void send_timeout()
		{
			runQ::send_timeout(Q,_id);
		}

		void send_timeout(job_id job)
		{
			runQ::send_timeout(Q,job);
		}

		job_id create_group()
		{
			return runQ::create_group(Q);
		}

		void close_group(job_id group)
		{
			runQ::close_group(Q,group);
		}

		void entry_group(job_id group)
		{
			runQ::entry_group(Q,group,_id);
		}

		void leave_group(job_id group)
		{
			runQ::leave_group(Q,group,_id);
		}

	private:

		static void* __initialize(LemonRunQ Q,void * param,lemon_job_id id,LemonErrorInfo* errorCode)
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

				job->initialize(param);

				return job;
			}
			catch(const error_info & e)
			{
				if(!block.empty()) runQ::free(Q,block);

				*errorCode = e;

				return NULL;
			}
		}

		static void __uninitialize(void * userdata)
		{
			job_type* job = (job_type*)userdata;

			job->uninitialize();

			job->~job_type();

			runQ::free(job->Q,buf((byte_t*)userdata,sizeof(job_type)));
		}

		static void __recv(void * userdata, lemon_job_id source,lemon_job_id target, LemonBuffer buff)
		{
			job_type* job = (job_type*)userdata;

			if(job->_id == target)
			{
				job->recv(source,buff);
			}
			else if(LEMON_TIMEOUT_JOBID == target)
			{
				job->timeout();
			}
			else if(LEMON_JOBID_IS_REMOTE(target))
			{
				job->proxy(source,target,buff);
			}
			else if(LEMON_JOBID_IS_MULTICAST(target))
			{
				job->multicast(source,const_buffer(buff));
			}
			else if(LEMON_JOBID_IS_BROADCAST(target))
			{
				job->broadcast(source,buff);
			}
			
		}

	private:

		job_id						_id;

		LemonRunQ					Q;
	};

}}

#endif //LEMONXX_RUNQ_JOB_HPP
