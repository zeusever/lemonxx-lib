/**
* 
* @file     basic_socket
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/02/17
*/
#ifndef LEMONXX_IO_BASIC_SOCKET_HPP
#define LEMONXX_IO_BASIC_SOCKET_HPP

#include <lemon/io/socket.h>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>

namespace lemon{namespace io{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @property	template<int type,
	/// 			int protocol> class basic_socket : public basic_handle_object<LemonSocket,
	/// 			&LemonCloseSocket>
	///
	/// @brief	 the basic handle object< lemon socket,& lemon close socket> 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<int type,int protocol>
	class basic_socket 
		: public basic_handle_object<LemonSocket,&LemonCloseSocket>
	{
	public:

		typedef basic_handle_object<LemonSocket,&LemonCloseSocket> base_type;

		basic_socket(){}

		basic_socket(int af):base_type(Create(af,LEMON_HANDLE_NULL_VALUE)) {}

		basic_socket(int af,io_device & device):base_type(Create(af,device)) {}

	private:

		static LemonSocket Create(int af,LemonIoDevice device)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonSocket socket = LemonCreateSocket(af,type,protocol,LEMON_HANDLE_NULL_VALUE,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

			return socket;
		}
	};


}}


#endif //LEMONXX_IO_BASIC_SOCKET_HPP