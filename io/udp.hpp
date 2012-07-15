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
#include <lemonxx/io/endpoint.hpp>
#include <lemonxx/io/io_device.hpp>
#include <lemonxx/utility/tuple.hpp>
#include <lemonxx/io/basic_socket.hpp>

namespace lemon{namespace io{namespace ip{namespace udp{

	class socket : public basic_socket<SOCK_DGRAM,IPPROTO_UDP,endpoint>
	{
	public:

		typedef basic_socket<SOCK_DGRAM,IPPROTO_UDP,endpoint> base_type;

		socket(){}

		socket(LemonSocket handle) :base_type(handle){}

		socket(int af) :base_type(af){}

		socket(const endpoint & ep):base_type(ep){}

		socket(int af,io_device & device) :base_type(af,device){}

		socket(const endpoint & ep,io_device & device) :base_type(ep,device){}

	public:

		template<class ConstBuffer>
		size_t sendto(ConstBuffer buffer,int flags,const endpoint & ep)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			size_t length = LemonSendTo(*this,buffer.Data,buffer.Length,flags,ep.ptr(),(socklen_t)ep.length(),&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

			return length;
		}

		template<class ConstBuffer>
		size_t sendto(ConstBuffer buffer,int flags,const endpoint & ep,LemonErrorInfo & errorCode)
		{
			return LemonSendTo(*this,buffer.Data,buffer.Length,flags,ep.ptr(),(socklen_t)ep.length(),&errorCode);
		}

		template<class ConstBuffer>
		size_t sendto(ConstBuffer buffer,const endpoint & ep)
		{
			return sendto(buffer,0,ep);
		}

		template<class ConstBuffer>
		size_t sendto(ConstBuffer buffer,const endpoint & ep,LemonErrorInfo & errorCode)
		{
			return sendto(buffer,0,ep,errorCode);
		}

		template<class ConstBuffer,typename Handle>
		void async_sendto(ConstBuffer buffer,int flags,const endpoint & ep,Handle handle)
		{
			AsyncIoCallback cb(handle);

			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonAsyncSendTo(*this,buffer.Data,buffer.Length,flags,ep.ptr(),(socklen_t)ep.length(),&IoCallback,cb.release(),&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
		}

		template<class ConstBuffer,typename Handle>
		void async_sendto(ConstBuffer buffer,const endpoint & ep,Handle handle)
		{
			async_sendto(buffer,0,ep,handle);
		}

		template<class MutableBuffer>
		size_t receivefrom(MutableBuffer buffer,endpoint & ep,int flags)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			size_t length = LemonReceiveFrom(*this,buffer.Data,buffer.Length,flags,ep.ptr(),&ep.buffersize(),&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

			return length;
		}

		template<class MutableBuffer>
		size_t receivefrom(MutableBuffer buffer,endpoint & ep)
		{
			return receivefrom(buffer,ep,0);
		}

		template<class MutableBuffer,typename Handle>
		void async_receivefrom(MutableBuffer buffer,int flags,endpoint & ep,Handle handle)
		{
			AsyncIoCallback cb(handle);

			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonAsyncReceiveFrom(*this,buffer.Data,buffer.Length,flags,ep.ptr(),&ep.buffersize(),&IoCallback,cb.release(),&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
		}

		template<class MutableBuffer,typename Handle>
		void async_receivefrom(MutableBuffer buffer,endpoint & ep,Handle handle)
		{
			async_receivefrom(buffer,0,ep,handle);
		}
	};

}}}}

#endif //LEMONXX_IO_UDP_HPP