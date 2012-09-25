/**
* 
* @file     socket
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/08/31
*/
#ifndef LEMONXX_IO_SOCKET_HPP
#define LEMONXX_IO_SOCKET_HPP
#include <cassert>
#include <lemonxx/io/object.hpp>
#include <lemonxx/io/io_service.hpp>

namespace lemon{namespace io{

	template<int type,int protocol,typename endpoint>
	class basic_socket : public object
	{
	public:

		basic_socket(){}

		basic_socket(LemonIO handle):object(handle){}

		basic_socket(const endpoint & ep,io_service & service)
		{
			open(ep.af(),service);

			bind(ep);
		}
		
		basic_socket(int af,io_service & service) 
		{
			open(af,service);
		}

		void open(int af,io_service & service)
		{
			assert(empty() && "re open the same socket");

			reset(Create(af,service));
		}

		void bind(const endpoint & ep)
		{
			error_info errorCode;

			LemonBind(*this,ep.ptr(),(socklen_t)ep.length(),errorCode);

			errorCode.check_throw();
		}

		void shutdown(int how)
		{
			error_info errorCode;

			LemonShutdown(*this,how,errorCode);

			errorCode.check_throw();
		}

		endpoint sockname()
		{
			error_info errorCode;

			endpoint ep;

			socklen_t length = (socklen_t)ep.capacity();

			LemonGetSockName(*this,ep.ptr(),&length,errorCode);

			errorCode.check_throw();

			assert(length == ep.length());

			return ep;
		}

	private:

		static LemonIO Create(int af,LemonIOService service)
		{
			error_info errorCode;

			LemonIO io = LemonSock(af,type,protocol,service,errorCode);

			errorCode.check_throw();

			return io;
		}
	};

}}

#endif //LEMONXX_IO_SOCKET_HPP
