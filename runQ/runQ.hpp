/**
* 
* @file     runQ
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/12/14
*/
#ifndef LEMON_RUNQ_RUNQ_HPP
#define LEMON_RUNQ_RUNQ_HPP

#include <lemon/runQ/abi.h>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>

namespace lemon{

	class runQ_service : public basic_handle_object<LemonRunQ,&LemonCloseRunQ>
	{
	public:
		typedef basic_handle_object<LemonRunQ,&LemonCloseRunQ> base_type;

		runQ_service(LemonRunQ Q) :base_type(Q){}

		runQ_service() :base_type(Create()){}

		template<typename Rounter>
		runQ_service(Rounter &rounter) :base_type(Create(&rounter)){}

		void run()
		{
			error_info errorCode;

			LemonRunQLoop(*this,errorCode);

			errorCode.check_throw();
		}

		void stop()
		{
			error_info errorCode;

			LemonRunQStop(*this,errorCode);

			errorCode.check_throw();
		}

		void reset()
		{
			LemonRunQReset(*this);
		}

		mutable_buffer alloc(size_t size)
		{
			return LemonRunQAlloc(*this,size);
		}

		void free(mutable_buffer buffer)
		{
			return LemonRunQFree(*this,buffer);
		}

		void free(const_buffer buffer)
		{
			return LemonRunQFree(*this,mutable_buffer((byte_t*)buffer.Data,buffer.Length));
		}

		void send(lemon_job_id self,lemon_job_id target, mutable_buffer buffer)
		{
			error_info errorCode;

			LemonRunQSend(*this,self,target,buffer,errorCode);

			errorCode.check_throw();
		}

		void close_job(lemon_job_id id)
		{
			LemonCloseJob(*this,id);
		}

	private:

		static LemonRunQ Create()
		{
			error_info errorCode;

			LemonRunQ Q = LemonCreateRunQ(NULL,NULL,errorCode);

			errorCode.check_throw();

			return Q;
		}

		template<class Router>
		static LemonRunQ Create(Router & router)
		{
			error_info errorCode;

			LemonRunQ Q = LemonCreateRunQ(&router,&Router::Call,errorCode);

			errorCode.check_throw();

			return Q;
		}
	};
	
namespace runQ{

	typedef lemon_job_id job_id;

	template<typename Job>
	class basic_job_class 
	{
	public:

		typedef basic_job_class<Job>		self_type;

		static job_id create(runQ_service & s)
		{
			LemonJobClass jobClass = {&self_type::start,&self_type::recv,&self_type::stop};

			error_info errorCode;

			job_id id = LemonCreateJob(s,&jobClass,errorCode);

			errorCode.check_throw();

			return id;
		}

		basic_job_class(runQ_service & s) :_service(&s),_id(create(s)) {}

		~basic_job_class() { LemonCloseJob(*_service,_id); }

		operator job_id() const
		{
			return _id;
		}

		void send(lemon_job_id target, mutable_buffer buffer)
		{
			_service->send(_id,target,buffer);
		}

	private:

		static void* start(LemonRunQ Q,job_id self,LemonErrorInfo* errorCode)
		{
			try
			{
				runQ_service S(Q);

				Job * job = new Job(S,self);

				S.release();

				return job;
			}
			catch(const error_info & e)
			{
				*errorCode = e;

				return NULL;
			}
		}

		static void recv(LemonRunQ Q,void * userdata, job_id self, lemon_job_id source, LemonBuffer buff)
		{
			runQ_service S(Q);

			try
			{
				Job * job = (Job*)userdata;

				job->recv(S,self,source,buff);

				S.release();
			}
			catch(...)
			{
				S.release();

				throw;
			}
		}

		static void stop(LemonRunQ /*Q*/,void * userdata)
		{
			delete (Job*)userdata;
		}

	private:

		runQ_service				*_service;

		job_id						_id;
	};
}}


#endif //LEMON_RUNQ_RUNQ_HPP


