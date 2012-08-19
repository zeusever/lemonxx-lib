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
#include <lemonxx/io/endpoint.hpp>

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
		message(){}

		explicit message(LemonDTraceEvent traceEvent)
			:_event(traceEvent)
		{
			reset();
		}

		void reset()
		{
			reset(_event);
		}

		void reset(LemonDTraceEvent e)
		{
			error_info errorCode;

			_event = e;

			LemonTraceOffset(_event,LEMON_IO_BEGIN,0,errorCode);

			errorCode.check_throw();
		}

		const lemon::time_t & timestamp() const
		{
			return *(const lemon::time_t*)LemonTraceTimeStamp(_event);
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


		lemon::byte_t peek() const
		{
			error_info errorCode;

			lemon::byte_t t = LemonTracePeek(_event,&errorCode);

			errorCode.check_throw();

			return t;
		}

	/*	template<typename Buffer>
		size_t dump(Buffer buffer) const
		{
			error_info errorCode;

			size_t length = LemonTraceDump(_event,buffer.Data,buffer.Length,errorCode);

			errorCode.check_throw();

			return length;
		}*/

		void dump(std::ostream &stream) const
		{
			error_info errorCode;

			LemonIoWriter writer = {&stream,&message::Write};

			LemonTraceDump(_event,writer,errorCode);

			errorCode.check_throw();
		}

	private:

		static size_t Write(void * userdata,const lemon_byte_t * source,size_t length,LemonErrorInfo *errorCode)
		{
			LEMON_RESET_ERRORINFO(*errorCode);

			std::ostream &stream = *reinterpret_cast<std::ostream*>(userdata);

			stream.write((const char*)source,length);

			return length;
		}

	private:

		LemonDTraceEvent _event;
	};

	class consumer :public basic_handle_object<LemonDTraceConsumer,&LemonCloseDTraceConsumer>
	{
	public:

		typedef lemon::function<void(const message&)> handle_type;

		typedef basic_handle_object<LemonDTraceConsumer,&LemonCloseDTraceConsumer> base_type;

		consumer(){}

		template<typename Handle>
		consumer(controller & c,Handle handle)
		{
			start(c,handle);
		}

		~consumer()
		{
			//must release LemonDTraceConsumer first, then release _handle.
			base_type::close();
		}

		template<typename Handle>
		void start(controller & c,Handle handle)
		{
			if(!empty()) return;

			_handle = handle;

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

