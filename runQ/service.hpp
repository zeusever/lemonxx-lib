/**
* 
* @file     service
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/12/15
*/
#ifndef LEMONXX_RUNQ_SERVICE_HPP
#define LEMONXX_RUNQ_SERVICE_HPP
#include <lemon/runQ/abi.h>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>

namespace lemon{

	typedef lemon_job_id job_id;

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
			error_info errorCode;

			LemonRunQReset(*this,&errorCode);

			errorCode.check_throw();
		}

		size_t jobs() const
		{
			return LemonRunQJobs(*this);
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
}
#endif //LEMONXX_RUNQ_SERVICE_HPP
