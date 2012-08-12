/**
* 
* @file     trace-classes
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/08/12
*/
#ifndef LEMONXX_DIAGNOSIS_TRACE_CLASSES_HPP
#define LEMONXX_DIAGNOSIS_TRACE_CLASSES_HPP
#include <vector>
#include <lemon/sys/assembly.h>
#include <lemon/diagnosis/abi.h>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>
#include <lemonxx/function/bind.hpp>
namespace lemon{namespace dtrace{

	class service : public basic_handle_object<LemonDTraceService,&LemonCloseDTraceService>
	{
	public:
		typedef basic_handle_object<LemonDTraceService,&LemonCloseDTraceService> base_type;

		service() :base_type(Create()) {}

	private:

		static LemonDTraceService Create()
		{
			error_info errorCode;

			LemonDTraceService service = LemonCreateDTraceService(&errorCode);

			errorCode.check_throw(LEMON_TEXT("create dtrace service error."));

			return service;
		}
	};

	class provider : public basic_handle_object<LemonDTraceProvider,&LemonCloseDTraceProvider>
	{
	public:
		typedef basic_handle_object<LemonDTraceProvider,&LemonCloseDTraceProvider> base_type;

		provider(service & s,const LemonUuid * id):base_type(Create(s,id)) {}

	private:

		LemonDTraceProvider Create(service & s,const LemonUuid * id)
		{
			error_info errorCode;

			LemonDTraceProvider provider = LemonCreateDTraceProvider(s,id,&errorCode);

			errorCode.check_throw(LEMON_TEXT("create dtrace service error."));

			return provider;
		}
	};

	class commit_message : private lemon::nocopyable
	{
	public:

		commit_message(provider & p,LemonDTraceFlags flags)
			:_provider(p)
		{
			error_info errorCode;

			_event = LemonTrace(p,flags,&errorCode);

			if(LEMON_FAILED(errorCode)) _event = LEMON_HANDLE_NULL_VALUE;
		}

		~commit_message()
		{
			commit();
		}

		operator LemonDTraceEvent ()
		{
			return _event;
		}

		bool want() const
		{
			return LEMON_CHECK_HANDLE(_event);
		}

		void commit()
		{
			error_info errorCode;

			if(LEMON_CHECK_HANDLE(_event)) 
			{	
				LemonCommitTrace(_provider,_event,errorCode);

				_event = LEMON_HANDLE_NULL_VALUE;
			}
		}

		template<typename ConstBuffer>
		size_t write_rawdata(ConstBuffer buffer)
		{
			return write_rawdata(buffer.Data,buffer.Length);
		}

		size_t write_rawdata(const lemon_byte_t * buffer,size_t length)
		{
			error_info errorCode;

			length = LemonTraceWrite(_event,buffer,length,errorCode);

			errorCode.check_throw();

			return length;
		}

		void write_number(lemon::uint32_t val)
		{
			error_info errorCode;

			LemonTraceWriteInteger(_event,val,errorCode);

			errorCode.check_throw();
		}


		void write_boolean(bool val)
		{
			error_info errorCode;

			LemonTraceWriteBoolean(_event,val? lemon_true : lemon_false,errorCode);

			errorCode.check_throw();
		}

		void write_utf8_string(const std::string & utf8)
		{
			error_info errorCode;

			LemonTraceWriteUTF8String(_event,utf8.c_str(),errorCode);

			errorCode.check_throw();
		}

		template<typename ConstBuffer>
		void write_userdata(const ConstBuffer & buffer)
		{
			error_info errorCode;

			LemonTraceWriteUserData(_event,buffer.Data,buffer.Length,errorCode);

			errorCode.check_throw();
		}

	private:

		provider				&_provider;

		LemonDTraceEvent		_event;
	};

	class controller : public basic_handle_object<LemonDTraceController,&LemonCloseDTraceController>
	{
	public:
		typedef basic_handle_object<LemonDTraceController,&LemonCloseDTraceController> base_type;

		controller(service & s):base_type(Create(s)) {}

		void open_trace(const LemonUuid * provider,LemonDTraceFlags flags)
		{
			error_info errorCode;

			LemonOpenTrace(*this,provider,flags,&errorCode);

			errorCode.check_throw();
		}

		void close_trace(const LemonUuid * provider,LemonDTraceFlags flags)
		{
			error_info errorCode;

			LemonCloseTrace(*this,provider,flags,&errorCode);

			errorCode.check_throw();
		}

	private:

		LemonDTraceController Create(service & s)
		{
			error_info errorCode;

			LemonDTraceController controller = LemonCreateDTraceController(s,&errorCode);

			errorCode.check_throw(LEMON_TEXT("create dtrace service error."));

			return controller;
		}
	};

	class message : private lemon::nocopyable
	{
	public:
		explicit message(LemonDTraceEvent traceEvent)
			:_event(traceEvent)
		{
			reset();
		}

		void reset()
		{
			error_info errorCode;

			LemonTraceOffset(_event,LEMON_IO_BEGIN,0,errorCode);

			errorCode.check_throw();
		}

		const LemonUuid * provider() const
		{
			return LemonGetTraceProvider(_event);
		}

		LemonDTraceFlags flags() const
		{
			return LemonGetTraceFlags(_event);
		}

		size_t length() const
		{
			return LemonTraceLength(_event);
		}

		template<typename Buffer>
		size_t read_rawdata(Buffer buffer) const
		{
			return read_rawdata(buffer.Data,buffer.Length);
		}

		size_t read_rawdata(lemon_byte_t * buffer,size_t length) const
		{
			error_info errorCode;

			length = LemonTraceRead(_event,buffer,length,errorCode);

			errorCode.check_throw();

			return length;
		}

		lemon::uint32_t read_integer() const
		{
			error_info errorCode;

			lemon::uint32_t val = LemonTraceReadInteger(_event,errorCode);

			errorCode.check_throw();

			return val;
		}

		bool read_boolean() const
		{
			error_info errorCode;

			lemon_bool val = LemonTraceReadBoolean(_event,errorCode);

			errorCode.check_throw();

			return val ? true : false;
		}

		std::string read_utf8_string() const
		{
			error_info errorCode;

			size_t length = LemonTraceReadUTF8String(_event,NULL,0,errorCode);

			if(!LEMON_ERRORINOF_EQ(errorCode.Error,LEMON_SYS_RESOURCE_ERROR))
			{
				errorCode.check_throw();
			}

			if(0 == length) return "";

			std::vector<char> buffer(length);

			LemonTraceReadUTF8String(_event,&buffer[0],buffer.size(),errorCode);

			errorCode.check_throw();

			return std::string(buffer.begin(),buffer.end());
		}

		template<typename Buffer>
		size_t read_userdata(Buffer buffer) const
		{
			return read_userdata(buffer.Data,buffer.Length);
		}

		size_t read_userdata(lemon::byte_t * buffer,size_t bufferSize) const
		{
			error_info errorCode;

			size_t length = LemonTraceReadUserData(_event,buffer,bufferSize,errorCode);

			errorCode.check_throw();

			return length;
		}

		lemon::byte_t type() const
		{
			error_info errorCode;

			lemon::byte_t val = LemonTraceType(_event,errorCode);

			errorCode.check_throw();

			return val;
		}

	private:

		LemonDTraceEvent _event;
	};

	class consumer :public basic_handle_object<LemonDTraceConsumer,&LemonCloseDTraceConsumer>
	{
	public:

		typedef lemon::function<void(const message&)> handle_type;

		typedef basic_handle_object<LemonDTraceConsumer,&LemonCloseDTraceConsumer> base_type;

		template<typename Handle>
		consumer(controller & c,Handle handle)
			:_handle(handle)
		{
			error_info errorCode;

			base_type::reset(LemonCreateDTraceConsumer(c,this,&consumer::Call,&errorCode));

			errorCode.check_throw();
		}

	private:

		static void Call(void * userData,const LemonDTraceEvent traceEvent)
		{
			((consumer*)userData)->_handle(message(traceEvent));
		}

	private:
		handle_type		_handle;
	};

}}

#endif // LEMONXX_DIAGNOSIS_TRACE_CLASSES_HPP

