/**
* 
* @file     io
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/02/21
*/
#ifndef LEMONXX_IO_IO_HPP
#define LEMONXX_IO_IO_HPP
#include <lemon/io/abi.h>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>
#include <lemonxx/io/io_device.hpp>

namespace lemon{namespace io{

	template<typename T,void(*Release)(T)>
	class basic_object 
		: public basic_handle_object<T,Release>
	{
	public:
		
		typedef basic_handle_object<T,Release> base_type;

	public:

	    basic_object(typename base_type::handle_type h):base_type(h){}

		operator LemonIo()
		{
		  return (LemonIo) base_type::native();
		}

		operator const LemonIo() const
		{
		  return (const LemonIo) base_type::native();
		}

		template<class ConstBuffer>
		size_t write(ConstBuffer buffer)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			size_t length = LemonIoWrite(*this,buffer.Data,buffer.Length,0,buffer.Length,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

			return length;
		}

		template<class ConstBuffer,typename Handle>
		void async_write(ConstBuffer buffer,Handle handle)
		{
			AsyncIoCallback cb(handle);

			LEMON_DECLARE_ERRORINFO(errorCode);

			AsyncIoCallback::wrapper_type data = cb.release();

			LemonIoAsyncWrite(*this,buffer.Data,buffer.Length,0,buffer.Length,&IoCallback,data,&errorCode);

			if(LEMON_FAILED(errorCode))
			{
				cb = data;

				throw Exception(errorCode);
			}
		}

		template<class MutableBuffer>
		size_t read(MutableBuffer buffer)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			size_t length = LemonIoRead(*this,buffer.Data,buffer.Length,0,buffer.Length,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

			return length;
		}

		
		template<class MutableBuffer,typename Handle>
		void async_read(MutableBuffer buffer,Handle handle)
		{
			AsyncIoCallback cb(handle);

			LEMON_DECLARE_ERRORINFO(errorCode);

			AsyncIoCallback::wrapper_type data = cb.release();

			LemonIoAsyncRead(*this,buffer.Data,buffer.Length,0,buffer.Length,&IoCallback,data,&errorCode);

			if(LEMON_FAILED(errorCode))
			{
				cb = data;

				throw Exception(errorCode);
			}
		}
	};

}}

#endif //LEMONXX_IO_IO_HPP
