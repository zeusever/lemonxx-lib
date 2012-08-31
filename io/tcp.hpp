/**
* 
* @file     tcp
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/08/31
*/
#ifndef LEMONXX_IO_TCP_HPP
#define LEMONXX_IO_TCP_HPP
#include <lemonxx/io/socket.hpp>

namespace lemon{namespace io{namespace tcp{

	class basic_stream_socket : public basic_socket<SOCK_STREAM,IPPROTO_TCP,net::endpoint>
	{
	public:

		typedef basic_socket<SOCK_STREAM,IPPROTO_TCP,net::endpoint> base_type;

		basic_stream_socket(int af,io_service & device) :base_type(af,device){}

		basic_stream_socket(const net::endpoint & ep,io_service & device) :base_type(ep,device){}

	public:

		template<typename MutableBuffer>
		size_t receive(MutableBuffer buffer,int flags)
		{
			return receive(buffer.Data,buffer.Length,flags);
		}

		template<typename MutableBuffer>
		size_t receive(MutableBuffer buffer)
		{
			return receive(buffer.Data,buffer.Length);
		}

		template<typename MutableBuffer>
		size_t receive(MutableBuffer buffer,int flags,error_info & errorCode)
		{
			return receive(buffer.Data,buffer.Length,flags,errorCode);
		}

		template<typename MutableBuffer>
		size_t receive(MutableBuffer buffer,error_info & errorCode)
		{
			return receive(buffer.Data,buffer.Length,errorCode);
		}

		size_t receive(byte_t * buffer, size_t bufferSize)
		{
			return receive(buffer,bufferSize,0);
		}

		size_t receive(byte_t * buffer, size_t bufferSize,error_info & errorCode)
		{
			return receive(buffer,bufferSize,0,errorCode);
		}

		size_t receive(byte_t * buffer, size_t bufferSize,int flags)
		{
			scope_error_info errorCode;

			return receive(buffer,bufferSize,flags,errorCode);

		}

		size_t receive(byte_t * buffer, size_t bufferSize,int flags,error_info & errorCode)
		{
			return LemonRecv(*this,buffer,bufferSize,flags,errorCode);
		}

		//////////////////////////////////////////////////////////////////////////

		template<typename MutableBuffer,typename Handle>
		void async_receive(MutableBuffer buffer,int flags,Handle handle)
		{
			async_receive(buffer.Data,buffer.Length,flags,handle);
		}

		template<typename MutableBuffer>
		void async_receive(MutableBuffer buffer)
		{
			async_receive(buffer.Data,buffer.Length);
		}

		template<typename MutableBuffer,typename Handle>
		void async_receive(MutableBuffer buffer,int flags,Handle handle,error_info & errorCode)
		{
			async_receive(buffer.Data,buffer.Length,flags,handle,errorCode);
		}

		template<typename MutableBuffer,typename Handle>
		void async_receive(MutableBuffer buffer,Handle handle,error_info & errorCode)
		{
			async_receive(buffer.Data,buffer.Length,handle,errorCode);
		}
		template<typename Handle>
		void async_receive(byte_t * buffer, size_t bufferSize,Handle handle)
		{
			async_receive(buffer,bufferSize,0,handle);
		}
		template<typename Handle>
		void async_receive(byte_t * buffer, size_t bufferSize,Handle handle,error_info & errorCode)
		{
			async_receive(buffer,bufferSize,0,handle,errorCode);
		}
		template<typename Handle>
		void async_receive(byte_t * buffer, size_t bufferSize,int flags,Handle handle)
		{
			scope_error_info errorCode;

			async_receive(buffer,bufferSize,flags,handle,errorCode);

		}
		template<typename Handle>
		void async_receive(byte_t * buffer, size_t bufferSize,int flags,Handle handle,error_info & errorCode)
		{
			Callback cb(handle);

			Callback::wrapper_type data = cb.release();

			LemonAsyncRecv(*this,buffer,bufferSize,flags,&CallbackWrapper,data,errorCode);

			if(LEMON_FAILED(errorCode)) cb = data;

		}

		//////////////////////////////////////////////////////////////////////////

		template<typename ConstBuffer>
		size_t send(ConstBuffer buffer,int flags)
		{
			return send(buffer.Data,buffer.Length,flags);
		}

		template<typename ConstBuffer>
		size_t send(ConstBuffer buffer)
		{
			return send(buffer.Data,buffer.Length);
		}

		template<typename ConstBuffer>
		size_t send(ConstBuffer buffer,int flags,error_info & errorCode)
		{
			return send(buffer.Data,buffer.Length,flags,errorCode);
		}

		template<typename ConstBuffer>
		size_t send(ConstBuffer buffer,error_info & errorCode)
		{
			return send(buffer.Data,buffer.Length,errorCode);
		}

		size_t send(const byte_t * buffer, size_t bufferSize)
		{
			return send(buffer,bufferSize,0);
		}

		size_t send(const byte_t * buffer, size_t bufferSize,error_info & errorCode)
		{
			return send(buffer,bufferSize,0,errorCode);
		}

		size_t send(const byte_t * buffer, size_t bufferSize,int flags)
		{
			scope_error_info errorCode;

			return send(buffer,bufferSize,flags,errorCode);

		}

		size_t send(const byte_t * buffer, size_t bufferSize,int flags,error_info & errorCode)
		{
			return LemonSend(*this,buffer,bufferSize,flags,errorCode);
		}

		//////////////////////////////////////////////////////////////////////////

		template<typename ConstBuffer,typename Handle>
		void async_send(ConstBuffer buffer,int flags,Handle handle)
		{
			async_send(buffer.Data,buffer.Length,flags,handle);
		}

		template<typename ConstBuffer>
		void async_send(ConstBuffer buffer)
		{
			async_send(buffer.Data,buffer.Length);
		}

		template<typename ConstBuffer,typename Handle>
		void async_send(ConstBuffer buffer,int flags,Handle handle,error_info & errorCode)
		{
			async_send(buffer.Data,buffer.Length,flags,handle,errorCode);
		}

		template<typename ConstBuffer,typename Handle>
		void async_send(ConstBuffer buffer,Handle handle,error_info & errorCode)
		{
			async_send(buffer.Data,buffer.Length,handle,errorCode);
		}
		template<typename Handle>
		void async_send(const byte_t * buffer, size_t bufferSize,Handle handle)
		{
			async_send(buffer,bufferSize,0,handle);
		}
		template<typename Handle>
		void async_send(const byte_t * buffer, size_t bufferSize,Handle handle,error_info & errorCode)
		{
			async_send(buffer,bufferSize,0,handle,errorCode);
		}
		template<typename Handle>
		void async_send(const byte_t * buffer, size_t bufferSize,int flags,Handle handle)
		{
			scope_error_info errorCode;

			async_send(buffer,bufferSize,flags,handle,errorCode);

		}
		template<typename Handle>
		void async_send(const byte_t * buffer, size_t bufferSize,int flags,Handle handle,error_info & errorCode)
		{
			Callback cb(handle);

			Callback::wrapper_type data = cb.release();

			LemonAsyncSend(*this,buffer,bufferSize,flags,&CallbackWrapper,data,errorCode);

			if(LEMON_FAILED(errorCode)) cb = data;

		}
	};


	class connection : public basic_stream_socket
	{
	public:

		typedef basic_stream_socket base_type;

		connection(int af,io_service & device) :base_type(af,device){}

		connection(const net::endpoint & ep,io_service & device) :base_type(ep,device){}
	};

	//////////////////////////////////////////////////////////////////////////

	class server : public basic_socket<SOCK_STREAM,IPPROTO_TCP,net::endpoint>
	{
	public:

		typedef basic_socket base_type;

		server(int af,io_service & device) :base_type(af,device){}

		server(const net::endpoint & ep,io_service & device) :base_type(ep,device){}
	};

	//////////////////////////////////////////////////////////////////////////

	class client : public basic_stream_socket
	{
	public:

		typedef basic_stream_socket base_type;

		client(int af,io_service & device) :base_type(af,device){}

		client(const net::endpoint & ep,io_service & device) :base_type(ep,device){}

	public:

		//////////////////////////////////////////////////////////////////////////

		void connect(const net::endpoint &remote)
		{
			scope_error_info errorCode;

			connect(remote,errorCode);
		}

		void connect(const net::endpoint &remote,error_info & errorCode)
		{
			LemonConnect(*this,remote.ptr(),(socklen_t)remote.length(),errorCode);
		}

		template<typename Handle>
		void async_connect(const net::endpoint &remote,Handle handle)
		{
			scope_error_info errorCode;

			async_connect(remote,handle,errorCode);
		}

		template<typename Handle>
		void async_connect(const net::endpoint &remote,Handle handle,error_info & errorCode)
		{
			Callback cb(handle);

			Callback::wrapper_type data = cb.release();

			LemonAsyncConnect(*this,remote.ptr(),(socklen_t)remote.length(),&CallbackWrapper,data,errorCode);

			if(LEMON_FAILED(errorCode)) cb = data;
		}
	};

}}}


#endif //LEMONXX_IO_TCP_HPP
