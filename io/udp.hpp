/**
* 
* @file     udp
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/02/20
*/
#ifndef LEMONXX_IO_UDP_HPP
#define LEMONXX_IO_UDP_HPP

#include <lemonxx/io/socket.hpp>

namespace lemon{namespace io{namespace ip{namespace udp{

	class socket : public basic_socket<SOCK_DGRAM,IPPROTO_UDP,net::endpoint>
	{
	public:

		typedef basic_socket<SOCK_DGRAM,IPPROTO_UDP,net::endpoint> base_type;

		socket(){}

		socket(LemonIO handle) :base_type(handle){}

		socket(int af,io_service & device) :base_type(af,device){}

		socket(const net::endpoint & ep,io_service & device) :base_type(ep,device){}

	public:

		template<typename ConstBuffer>
		size_t sendto(ConstBuffer buffer, const net::endpoint & remote)
		{
			return sendto(buffer.Data,buffer.Length,remote);
		}

		size_t sendto(const byte_t * buffer, size_t bufferSize, const net::endpoint & remote)
		{
			error_info errorCode;

			size_t nresult = sendto(buffer,bufferSize,0,remote,errorCode);

			errorCode.check_throw();

			return nresult;
		}

		template<typename ConstBuffer>
		size_t sendto(ConstBuffer buffer, int flags , const net::endpoint & remote)
		{
			return sendto(buffer.Data,buffer.Length,flags,remote);
		}

		size_t sendto(const byte_t * buffer, size_t bufferSize, int flags, const net::endpoint & remote)
		{
			error_info errorCode;

			size_t nresult = sendto(buffer,bufferSize,flags,remote,errorCode);

			errorCode.check_throw();

			return nresult;
		}

		template<typename ConstBuffer>
		size_t sendto(ConstBuffer buffer, const net::endpoint & remote,error_info & errorCode)
		{
			return sendto(buffer.Data,buffer.Length,remote,errorCode);
		}

		size_t sendto(const byte_t * buffer, size_t bufferSize, const net::endpoint & remote,error_info & errorCode)
		{
			return sendto(buffer,bufferSize,0,remote,errorCode);
		}

		template<typename ConstBuffer>
		size_t sendto(ConstBuffer buffer, int flags , const net::endpoint & remote,error_info & errorCode)
		{
			return sendto(buffer.Data,buffer.Length,flags,remote,errorCode);
		}

		size_t sendto(const byte_t * buffer, size_t bufferSize, int flags, const net::endpoint & remote,error_info & errorCode)
		{
			return LemonSendTo(*this,buffer,bufferSize,flags,remote.ptr(),(socklen_t)remote.length(),errorCode);
		}

		//////////////////////////////////////////////////////////////////////////

		template<typename ConstBuffer, typename Handle>
		void async_sendto(ConstBuffer buffer, const net::endpoint & remote, Handle handle)
		{
			async_sendto(buffer.Data,buffer.Length,0,remote,handle);
		}
		template<typename Handle>
		void async_sendto(const byte_t * buffer, size_t bufferSize, const net::endpoint & remote, Handle handle)
		{
			error_info errorCode;

			async_sendto(buffer,bufferSize,0,remote,handle,errorCode);

			errorCode.check_throw();
		}

		template<typename ConstBuffer, typename Handle>
		void async_sendto(ConstBuffer buffer, int flags , const net::endpoint & remote, Handle handle)
		{
			async_sendto(buffer.Data,buffer.Length,flags,remote,handle);
		}
		template<typename Handle>
		void async_sendto(const byte_t * buffer, size_t bufferSize, int flags, const net::endpoint & remote, Handle handle)
		{
			error_info errorCode;

			async_sendto(buffer,bufferSize,flags,remote,handle,errorCode);

			errorCode.check_throw();
		}

		template<typename ConstBuffer, typename Handle>
		void async_sendto(ConstBuffer buffer, const net::endpoint & remote, Handle handle,error_info & errorCode)
		{
			async_sendto(buffer.Data,buffer.Length,0,remote,handle,errorCode);
		}
		template<typename Handle>
		void async_sendto(const byte_t * buffer, size_t bufferSize, const net::endpoint & remote, Handle handle,error_info & errorCode)
		{
			async_sendto(buffer,bufferSize,0,remote,handle,errorCode);
		}

		template<typename ConstBuffer, typename Handle>
		void async_sendto(ConstBuffer buffer, int flags , const net::endpoint & remote, Handle handle,error_info & errorCode)
		{
			async_sendto(buffer.Data,buffer.Length,flags,remote,handle,errorCode);
		}
		template<typename Handle>
		void async_sendto(const byte_t * buffer, size_t bufferSize, int flags, const net::endpoint & remote, Handle handle,error_info & errorCode)
		{
			Callback cb(handle);

			Callback::wrapper_type data = cb.release();

			LemonAsyncSendTo(*this,buffer,bufferSize,flags,remote.ptr(),(socklen_t)remote.length(),&IOCallback,data,errorCode);

			if(LEMON_FAILED(errorCode)) cb = data;
		}

		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////


		template<typename MutableBuffer>
		size_t recvfrom(MutableBuffer buffer, net::endpoint & remote)
		{
			return recvfrom(buffer.Data,buffer.Length,remote);
		}

		size_t recvfrom(byte_t * buffer, size_t bufferSize, net::endpoint & remote)
		{
			error_info errorCode;

			size_t nresult = recvfrom(buffer,bufferSize,0,remote,errorCode);

			errorCode.check_throw();

			return nresult;
		}

		template<typename MutableBuffer>
		size_t recvfrom(MutableBuffer buffer, int flags , net::endpoint & remote)
		{
			return recvfrom(buffer.Data,buffer.Length,flags,remote);
		}

		size_t recvfrom(byte_t * buffer, size_t bufferSize, int flags, net::endpoint & remote)
		{
			error_info errorCode;

			size_t nresult =  recvfrom(buffer,bufferSize,flags,remote,errorCode);

			errorCode.check_throw();

			return nresult;
		}

		template<typename MutableBuffer>
		size_t recvfrom(MutableBuffer buffer, net::endpoint & remote,error_info & errorCode)
		{
			return recvfrom(buffer.Data,buffer.Length,remote,errorCode);
		}

		size_t recvfrom(byte_t * buffer, size_t bufferSize, net::endpoint & remote,error_info & errorCode)
		{
			return recvfrom(buffer,bufferSize,0,remote,errorCode);
		}

		template<typename MutableBuffer>
		size_t recvfrom(MutableBuffer buffer, int flags , net::endpoint & remote,error_info & errorCode)
		{
			return recvfrom(buffer.Data,buffer.Length,flags,remote,errorCode);
		}

		size_t recvfrom(byte_t * buffer, size_t bufferSize, int flags, net::endpoint & remote,error_info & errorCode)
		{
			socklen_t length = (socklen_t)remote.capacity();

			return LemonReceiveFrom(*this,buffer,bufferSize,flags,remote.ptr(),&length,errorCode);
		}

		//////////////////////////////////////////////////////////////////////////

		template<typename MutableBuffer, typename Handle>
		void async_recvfrom(MutableBuffer buffer, net::endpoint & remote, Handle handle)
		{
			async_recvfrom(buffer.Data,buffer.Length,remote,handle);
		}
		template<typename Handle>
		void async_recvfrom(byte_t * buffer, size_t bufferSize, net::endpoint & remote, Handle handle)
		{
			error_info errorCode;

			async_recvfrom(buffer,bufferSize,0,remote,handle,errorCode);

			errorCode.check_throw();
		}

		template<typename MutableBuffer, typename Handle>
		void async_recvfrom(MutableBuffer buffer, int flags , net::endpoint & remote, Handle handle)
		{
			async_recvfrom(buffer.Data,buffer.Length,flags,remote,handle);
		}
		template<typename Handle>
		void async_recvfrom(byte_t * buffer, size_t bufferSize, int flags, net::endpoint & remote, Handle handle)
		{
			error_info errorCode;

			async_recvfrom(buffer,bufferSize,flags,remote,handle,errorCode);

			errorCode.check_throw();
		}

		template<typename MutableBuffer, typename Handle>
		void async_recvfrom(MutableBuffer buffer, net::endpoint & remote, Handle handle,error_info & errorCode)
		{
			async_recvfrom(buffer.Data,buffer.Length,remote,handle,errorCode);
		}
		template<typename Handle>
		void async_recvfrom(byte_t * buffer, size_t bufferSize, net::endpoint & remote, Handle handle,error_info & errorCode)
		{
			async_recvfrom(buffer,bufferSize,0,remote,handle,errorCode);
		}

		template<typename MutableBuffer, typename Handle>
		void async_recvfrom(MutableBuffer buffer, int flags , net::endpoint & remote, Handle handle,error_info & errorCode)
		{
			async_recvfrom(buffer.Data,buffer.Length,flags,remote,handle,errorCode);
		}
		template<typename Handle>
		void async_recvfrom(byte_t * buffer, size_t bufferSize, int flags, net::endpoint & remote, Handle handle,error_info & errorCode)
		{
			Callback cb(handle);

			Callback::wrapper_type data = cb.release();

			LemonAsyncReceiveFrom(*this,buffer,bufferSize,flags,remote.ptr(),&remote.capacity(),&IOCallback,data,errorCode);

			if(LEMON_FAILED(errorCode)) cb = data;
		}
	};

}}}}

#endif //LEMONXX_IO_UDP_HPP