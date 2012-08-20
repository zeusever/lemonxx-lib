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
#include <lemonxx/io/io_device.hpp>

namespace lemon{namespace io{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @property	template<int type,
	/// 			int protocol> class basic_socket : public basic_handle_object<LemonSocket,
	/// 			&LemonCloseSocket>
	///
	/// @brief	 the basic handle object< lemon socket,& lemon close socket> 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<int type,int protocol,typename endpoint>
	class basic_socket 
		: public basic_handle_object<LemonSocket,&LemonCloseSocket>
	{
	public:
		//! . 

		typedef basic_handle_object<LemonSocket,&LemonCloseSocket>	base_type;

		typedef endpoint											endpoint_type;

		typedef base_type::wrapper_type								handle_type;

		basic_socket(){}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	basic_socket(LemonSocket handle)
		///
		/// @brief	Constructor. 
		///
		/// @author	Yuki
		/// @date	2012/2/19
		///
		/// @param	handle	The handle. 
		////////////////////////////////////////////////////////////////////////////////////////////////////

		basic_socket(LemonSocket handle):base_type(handle){}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	basic_socket(int af)
		///
		/// @brief	Constructor. 
		///
		/// @author	Yuki
		/// @date	2012/2/19
		///
		/// @param	af	The af. 
		////////////////////////////////////////////////////////////////////////////////////////////////////

		basic_socket(int af):base_type(Create(af,LEMON_HANDLE_NULL_VALUE)) {}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	basic_socket(const endpoint_type & ep)
		///
		/// @brief	Constructor. 
		///
		/// @author	Yuki
		/// @date	2012/2/19
		///
		/// @param	ep	The ep. 
		////////////////////////////////////////////////////////////////////////////////////////////////////

		basic_socket(const endpoint_type & ep)
			:base_type(Create(ep.af(),LEMON_HANDLE_NULL_VALUE))
		{
			bind(ep);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	basic_socket(int af,io_device & device)
		///
		/// @brief	Constructor. 
		///
		/// @author	Yuki
		/// @date	2012/2/19
		///
		/// @param	af				The af. 
		/// @param [in,out]	device	the device. 
		////////////////////////////////////////////////////////////////////////////////////////////////////

		basic_socket(int af,io_device & device):base_type(Create(af,device)) {}

		basic_socket(const endpoint_type & ep,io_device & device)
			:base_type(Create(ep.af(),device)) 
		{
			bind(ep);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	void shutdown(int how)
		///
		/// @brief	showdown the socket will disable some operator on this socket
		///
		/// @author	Yuki
		/// @date	2012/2/19
		///
		/// @exception	Exception	Thrown when . 
		///
		/// @param	how	The how. 
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void shutdown(int how)
		{
			error_info errorCode;

			LemonShutdownSocket(*this,how,&errorCode);

			errorCode.check_throw();
		}

		endpoint_type name()
		{
			byte_t buffer[128];

			socklen_t length = (socklen_t)sizeof(buffer);

			error_info errorCode;

			LemonGetSockName(*this,(sockaddr*)buffer,&length,&errorCode);

			errorCode.check_throw();

			return (const sockaddr*)buffer;
		}

		void bind(const endpoint_type & ep)
		{
			error_info errorCode;

			LemonBind(*this,ep.ptr(),(socklen_t)ep.length(),&errorCode);

			errorCode.check_throw();
		}

		void create(int af,LemonIoDevice device)
		{
			if(empty()) reset(Create(af,device));
		}

		void create(int af)
		{
			if(empty()) reset(Create(af,LEMON_HANDLE_NULL_VALUE));
		}

	private:

		static LemonSocket Create(int af,LemonIoDevice device)
		{
			error_info errorCode;

			LemonSocket socket = LemonCreateSocket(af,type,protocol,device,&errorCode);

			errorCode.check_throw();

			return socket;
		}
	};


}}


#endif //LEMONXX_IO_BASIC_SOCKET_HPP