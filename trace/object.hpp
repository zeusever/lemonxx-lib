/**
 * 
 * @file     object
 * @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
 * @author   yayanyang
 * @version  1.0.0.0  
 * @date     2012/08/25
 */
#ifndef LEMONXX_TRACE_OBJECT_HPP
#define LEMONXX_TRACE_OBJECT_HPP
#include <lemon/trace/abi.h>
#include <lemonxx/io/io.hpp>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/function/function.hpp>
#include <lemonxx/utility/utility.hpp>

namespace lemon{namespace trace{

	typedef lemon_trace_flag flag_t;

	typedef LemonTraceDescription description_t;

	class message : private lemon::nocopyable
	{
	public:
		
		message(LemonTraceMessage msg):_msg(msg) {}

		bool empty() const { return _msg == LEMON_HANDLE_NULL_VALUE; }

		LemonTraceMessage release() 
		{
			LemonTraceMessage R = _msg;

			_msg = LEMON_HANDLE_NULL_VALUE;

			return R;
		}

		void description(LemonTraceDescription & val) const
		{
			LemonGetTraceDescription(_msg,&val);
		}

		size_t write(const void * data, size_t length)
		{
			error_info errorCode;

			size_t nresult = LemonTraceWrite(_msg,data,length,errorCode);

			errorCode.check_throw();

			return nresult;
		}

		size_t read(void * data, size_t length) const
		{
			error_info errorCode;

			size_t nresult = LemonTraceRead(_msg,data,length,errorCode);

			errorCode.check_throw();

			return nresult;
		}

		template<typename Buffer>
		size_t read(Buffer buffer) const
		{
			return read(buffer.Data,buffer.Length);
		}

		template<typename ConstBuffer>
		size_t write(ConstBuffer buffer)
		{
			return write(buffer.Data,buffer.Length);
		}

		size_t seek(int offset,lemon::io::seek::Value position) const
		{
			return LemonTraceSeek(_msg,offset,position);
		}

	public:

		size_t dump(LemonIoWriter writer) const
		{
			error_info errorCode;

			size_t nresult = LemonTraceDump(_msg,writer,errorCode);

			errorCode.check_throw();

			return nresult;
		}

		size_t load(LemonIoReader reader)
		{
			error_info errorCode;

			size_t nresult = LemonTraceLoad(_msg,reader,errorCode);

			errorCode.check_throw();

			return nresult;
		}

		size_t dump(std::ostream& stream) const
		{
			error_info errorCode;

			LemonIoWriter writer = {&stream,&message::ostream_writer};

			size_t nresult = LemonTraceDump(_msg,writer,errorCode);

			errorCode.check_throw();

			return nresult;
		}

		size_t load(std::istream& stream)
		{
			error_info errorCode;

			LemonIoReader reader = {&stream,&message::istream_reader};

			size_t nresult =  LemonTraceLoad(_msg,reader,errorCode);

			errorCode.check_throw();

			return nresult;
		}

	private:

		static size_t ostream_writer(void * userdata,const lemon_byte_t * source,size_t length,LemonErrorInfo *errorCode)
		{
			LEMON_RESET_ERRORINFO(*errorCode);

			reinterpret_cast<std::ostream*>(userdata)->write((const char*)source,length);

			return length;
		}

		static size_t istream_reader(void * userdata, lemon_byte_t * target,size_t length,LemonErrorInfo *errorCode)
		{
			LEMON_RESET_ERRORINFO(*errorCode);

			reinterpret_cast<std::istream*>(userdata)->read((char*)target,length);

			return length;
		}

	private:

		LemonTraceMessage			_msg;
	};

	//////////////////////////////////////////////////////////////////////////

	class service : public basic_handle_object<LemonTraceService,&LemonCloseTraceService>
	{
	public:
		typedef basic_handle_object<LemonTraceService,&LemonCloseTraceService> base_type;

		service():base_type(Create(NULL)) {}

		service(const char * url):base_type(Create(url)) {}

		service(const std::string & url):base_type(Create(url.c_str())) {}

	private:

		static LemonTraceService Create(const char * URL)
		{
			error_info errorCode;

			LemonTraceService service =  LemonCreateTraceService(URL,errorCode);

			errorCode.check_throw();

			return service;
		}

	};

	//////////////////////////////////////////////////////////////////////////

	class controller : public basic_handle_object<LemonTraceController,&LemonCloseTraceController>
	{
	public:
		typedef basic_handle_object<LemonTraceController,&LemonCloseTraceController> base_type;

		controller(service & s):base_type(Create(s)) {}

		controller(const char * url):base_type(Create(url)) {}

		controller(const std::string & url):base_type(Create(url.c_str())) {}

		void open_trace(const LemonUuid * provider, flag_t flag)
		{
			error_info errorCode;

			LemonOpenTrace(*this,provider,flag,errorCode);

			errorCode.check_throw();
		}

		void close_trace(const LemonUuid * provider, flag_t flag)
		{
			error_info errorCode;

			LemonCloseTrace(*this,provider,flag,errorCode);

			errorCode.check_throw();
		}

	private:

		static LemonTraceController Create(const char * URL)
		{
			error_info errorCode;

			LemonTraceController controller =  LemonCreateRemoteTraceController(URL,errorCode);

			errorCode.check_throw();

			return controller;
		}

		static LemonTraceController Create(LemonTraceService s)
		{
			error_info errorCode;

			LemonTraceController controller =  LemonCreateTraceController(s,errorCode);

			errorCode.check_throw();

			return controller;
		}

	};

	//////////////////////////////////////////////////////////////////////////
	class provider : public basic_handle_object<LemonTraceProvider,&LemonCloseTraceProvider>
	{
	public:
		typedef basic_handle_object<LemonTraceProvider,&LemonCloseTraceProvider> base_type;

		provider(service & s,const LemonUuid * id):base_type(Create(s,id)) {}

		provider(const char * url,const LemonUuid * id):base_type(Create(url,id)) {}

		provider(const std::string & url,const LemonUuid * id):base_type(Create(url.c_str(),id)) {}

	private:

		static LemonTraceProvider Create(const char * URL,const LemonUuid * id)
		{
			error_info errorCode;

			LemonTraceProvider provider = LemonCreateRemoteTraceProvider(URL,id,errorCode);

			errorCode.check_throw();

			return provider;
		}

		static LemonTraceProvider Create(LemonTraceService s,const LemonUuid * id)
		{
			error_info errorCode;

			LemonTraceProvider provider = LemonCreateTraceProvider(s,id,errorCode);

			errorCode.check_throw();

			return provider;
		}

	};

	//////////////////////////////////////////////////////////////////////////

	class message_commiter : public message
	{
	public:
		message_commiter(provider & p,lemon_trace_flag flag) : message(Create(p,flag)),_p(p) {}

		~message_commiter()
		{
			commit();
		}

		void commit()
		{
			if(empty()) return;

			error_info errorCode;

			LemonTrace(_p,release(),errorCode);

			errorCode.check_throw();
		}
	private:
		static LemonTraceMessage Create(LemonTraceProvider provider,lemon_trace_flag flag)
		{
			return LemonNewTraceMessage(provider,flag);
		}

		provider &_p;
	};

	//////////////////////////////////////////////////////////////////////////

	class conumser : public basic_handle_object<LemonTraceConsumer,&LemonCloseTraceConsumer>
	{
	public:
		typedef lemon::function<void(const message & msg)> handle_type;

		typedef basic_handle_object<LemonTraceConsumer,&LemonCloseTraceConsumer> base_type;

		conumser() {}

		template<typename Handle>
		conumser(controller & c,Handle handle)
		{
			start(c,handle);
		}

		template<typename Handle>
		void start(controller & c,Handle handle)
		{
			error_info errorCode;

			_handle = handle;

			reset(LemonCreateTraceConsumer(c,&conumser::__traceproc,this,errorCode));

			errorCode.check_throw();
		}

	private:

		static void __traceproc(LemonTraceMessage msg,void * userdata)
		{
			((conumser*)userdata)->_handle(message(msg));
		}

	private:

		handle_type		_handle;
	};
}}

#endif // LEMONXX_TRACE_OBJECT_HPP
