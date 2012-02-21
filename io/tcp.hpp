/**
* 
* @file     tcp
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/02/19
*/
#ifndef LEMONXX_IO_TCP_HPP
#define LEMONXX_IO_TCP_HPP

#include <lemonxx/io/endpoint.hpp>
#include <lemonxx/io/basic_socket.hpp>
#include <lemonxx/io/io_device.hpp>
#include <lemonxx/utility/tuple.hpp>
#include <lemonxx/utility/buffer.hpp>
namespace lemon{namespace io{namespace ip{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	basic_stream_socket
	///
	/// @brief	Basic stream socket. 
	///
	/// @author	Yuki
	/// @date	2012/2/19
	////////////////////////////////////////////////////////////////////////////////////////////////////

	class basic_stream_socket : public basic_socket<SOCK_STREAM,IPPROTO_TCP,endpoint>
	{
	public:

		typedef basic_socket<SOCK_STREAM,IPPROTO_TCP,endpoint> base_type;

		basic_stream_socket(LemonSocket handle) :base_type(handle){}

		basic_stream_socket(int af) :base_type(af){}

		basic_stream_socket(const endpoint & ep):base_type(ep){}

		basic_stream_socket(int af,io_device & device) :base_type(af,device){}

		basic_stream_socket(const endpoint & ep,io_device & device) :base_type(ep,device){}

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @class	flags
		///
		/// @brief	Flags. 
		///
		/// @author	Yuki
		/// @date	2012/2/20
		////////////////////////////////////////////////////////////////////////////////////////////////////

		template<class ConstBuffer>
		size_t send(ConstBuffer buffer,int flags)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			size_t length = LemonSend(*this,buffer.Data,buffer.Length,flags,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

			return length;
		}

		template<class ConstBuffer>
		size_t send(ConstBuffer buffer)
		{
			return send(buffer,0);
		}

		template<class ConstBuffer,typename Handle>
		void async_send(ConstBuffer buffer,int flags,Handle handle)
		{
			AsyncIoCallback cb(handle);

			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonAsyncSend(*this,buffer.Data,buffer.Length,flags,&IoCallback,cb.release(),&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
		}

		template<class ConstBuffer,typename Handle>
		void async_send(ConstBuffer buffer,Handle handle)
		{
			async_send(buffer,0,handle);
		}

		template<class MutableBuffer>
		size_t receive(MutableBuffer buffer,int flags)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			size_t length = LemonReceive(*this,buffer.Data,buffer.Length,flags,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

			return length;
		}

		template<class MutableBuffer>
		size_t receive(MutableBuffer buffer)
		{
			return receive(buffer,0);
		}

		template<class MutableBuffer,typename Handle>
		void async_receive(MutableBuffer buffer,int flags,Handle handle)
		{
			AsyncIoCallback cb(handle);

			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonAsyncReceive(*this,buffer.Data,buffer.Length,flags,&IoCallback,cb.release(),&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
		}
		
		template<class MutableBuffer,typename Handle>
		void async_receive(MutableBuffer buffer,Handle handle)
		{
			async_receive(buffer,0,handle);
		}
	};

	namespace tcp{

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @class	connection
		///
		/// @brief	Connection. 
		///
		/// @author	Yuki
		/// @date	2012/2/19
		////////////////////////////////////////////////////////////////////////////////////////////////////

		class connection : public basic_stream_socket
		{
		public:

			typedef basic_stream_socket base_type;

			connection(LemonSocket handle) : base_type(handle){}

			connection(int af) :base_type(af){}

			connection(const endpoint & ep):base_type(ep){}

			connection(int af,io_device & device) :base_type(af,device){}

			connection(const endpoint & ep,io_device & device) :base_type(ep,device){}
		};

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @class	server
		///
		/// @brief	Server. 
		///
		/// @author	Yuki
		/// @date	2012/2/19
		////////////////////////////////////////////////////////////////////////////////////////////////////

		class server : public basic_stream_socket
		{
		public:

			typedef basic_stream_socket base_type;

			server(int af) :base_type(af){}

			server(const endpoint & ep):base_type(ep){}

			server(int af,io_device & device) :base_type(af,device){}

			server(const endpoint & ep,io_device & device) :base_type(ep,device){}

		public:

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// @fn	void listen(int backlog)
			///
			/// @brief	Listens. 
			///
			/// @author	Yuki
			/// @date	2012/2/19
			///
			/// @param	backlog	The backlog. 
			////////////////////////////////////////////////////////////////////////////////////////////////////

			void listen(int backlog)
			{
				LEMON_DECLARE_ERRORINFO(errorCode);

				LemonListen(*this,backlog,&errorCode);

				if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
			}

			tuple<connection::handle_type,endpoint> accept()
			{
				byte_t buffer[128];

				socklen_t length = (socklen_t)sizeof(buffer);

				LEMON_DECLARE_ERRORINFO(errorCode);

				connection::handle_type handle = LemonAccept(*this,(sockaddr*)buffer,&length,&errorCode);

				if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

				return tuple<connection::handle_type,endpoint>(handle,endpoint((sockaddr*)buffer));
			}

			template<typename Handle>
			void async_accept(connection & conn,endpoint & ep,Handle handle)
			{
				AsyncIoCallback cb(handle);

				LEMON_DECLARE_ERRORINFO(errorCode);

				LemonAsyncAccept(*this,conn,ep.ptr(),&ep.buffersize(),&IoCallback,cb.release(),&errorCode);

				if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
			}
		};

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @class	client
		///
		/// @brief	Client. 
		///
		/// @author	Yuki
		/// @date	2012/2/19
		////////////////////////////////////////////////////////////////////////////////////////////////////

		class client : public basic_stream_socket
		{
		public:

			typedef basic_stream_socket base_type;

			client(int af) :base_type(af){}

			client(const endpoint & ep):base_type(ep){}

			client(int af,io_device & device) :base_type(af,device){}

			client(const endpoint & ep,io_device & device) :base_type(ep,device){}

		public:

			void connect(const endpoint & ep)
			{
				LEMON_DECLARE_ERRORINFO(errorCode);

				LemonConnect(*this,ep.ptr(),(socklen_t)ep.length(),&errorCode);

				if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
			}

			template<typename Handle>
			void async_connect(const endpoint & ep,Handle handle)
			{
				AsyncIoCallback cb(handle);

				LEMON_DECLARE_ERRORINFO(errorCode);

				LemonAsyncConnect(*this,ep.ptr(),(socklen_t)ep.length(),&IoCallback,cb.release(),&errorCode);

				if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
			}
		};

	}

}}}

#endif //LEMONXX_IO_TCP_HPP