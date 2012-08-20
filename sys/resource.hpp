/**
* 
* @file     resource
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/08/07
*/
#ifndef LEMONXX_SYS_RESOURCE_HPP
#define LEMONXX_SYS_RESOURCE_HPP
#include <ostream>
#include <lemon/resource/abi.h>
#include <lemonxx/sys/uuid.hpp>
#include <lemonxx/sys/inttypes.hpp>
#include <lemonxx/sys/handle.hpp>
#include <lemonxx/sys/errorcode.hpp>
#include <lemonxx/mpl/type2type.hpp>
#include <lemonxx/utility/iterator.hpp>
#include <lemonxx/mpl/inttypes.hpp>
#include <lemonxx/type_traits/type_traits.hpp>

namespace lemon{namespace resource{

	class package : public basic_handle_object<LemonResource,&LemonCloseResource>
	{
	public:
		typedef  basic_handle_object<LemonResource,&LemonCloseResource> base_type;

		package():base_type(Create()){}

		package(const lemon::String & path) : base_type(Create(path)) {}

		package(LemonIoReader reader) : base_type(Create(reader)) {}

		package(std::istream & stream) : base_type(Create(stream)) {}

		const LemonUuid * uuid() const { return LemonResourceUuid(*this); }

		void uuid(const LemonUuid * val) 
		{
			error_info errorCode;

			LemonSetResourceUuid(*this,val,errorCode); 

			errorCode.check_throw();
		}

		const LemonVersion * version() const { return LemonResourceVersion(*this); }

		void version(const lemon::String & val) 
		{
			version(val.c_str());
		}

		void version(const char_t * val) 
		{
			error_info errorCode;

			LemonSetResourceVersion(*this,val,errorCode);

			errorCode.check_throw();
		}


		//////////////////////////////////////////////////////////////////////////
		const char_t * text(const char_t* key,const char_t* culture) const 
		{
			return LemonResourceText(*this,key,culture);
		}

		const char_t * text(const lemon::String & key,const lemon::String & culture) const 
		{
			return text(key.c_str(),culture.c_str());
		}

		const char_t * text(const char_t * key) const 
		{
			return text(key,LEMON_TEXT(""));
		}

		const char_t * text(const lemon::String & key) const 
		{
			return text(key.c_str());
		}

		void text(const char_t * key,const char_t * value,const char_t * culture)
		{
			error_info errorCode;

			LemonNewResourceText(*this,key,value,culture,errorCode);

			errorCode.check_throw();
		}

		void text(const lemon::String & key,const lemon::String & value,const lemon::String & culture)
		{
			text(key.c_str(),value.c_str(),culture.c_str());
		}

		void text(const char_t * key,const char_t * value)
		{
			text(key,value,LEMON_TEXT(""));
		}

		void text(const lemon::String & key,const lemon::String & value)
		{
			text(key.c_str(),value.c_str());
		}

		//////////////////////////////////////////////////////////////////////////
		const char_t* trace(uint32_t id,const char_t * culture) const
		{
			return LemonResourceTraceMessage(*this,id,culture);
		}

		const char_t* trace(uint32_t id,const lemon::String & culture) const
		{
			return trace(id,culture.c_str());
		}

		const char_t* trace(uint32_t id) const
		{
			return trace(id,LEMON_TEXT(""));
		}

		void trace(uint32_t id,const char_t * message, const char_t * culture)
		{
			error_info errorCode;

			LemonNewResourceTraceText(*this,id,message,culture,errorCode);

			errorCode.check_throw();
		}

		void trace(uint32_t id,const lemon::String & message,const lemon::String & culture)
		{
			trace(id,message.c_str(),culture.c_str());
		}

		void trace(uint32_t id,const char_t * message)
		{
			trace(id,message,LEMON_TEXT(""));
		}

		void trace(uint32_t id,const lemon::String & message)
		{
			trace(id,message.c_str());
		}

		//////////////////////////////////////////////////////////////////////////
		LemonResourceInfo trace_catalog(uint32_t id,const char_t * culture) const
		{
			return LemonResourceTraceCatalog(*this,id,culture);
		}

		LemonResourceInfo trace_catalog(uint32_t id,const lemon::String & culture) const
		{
			return trace_catalog(id,culture.c_str());
		}

		LemonResourceInfo trace_catalog(uint32_t id) const
		{
			return trace_catalog(id,LEMON_TEXT(""));
		}

		void trace_catalog(uint32_t id,const char_t * name, const char_t * desciption,const char_t * culture)
		{
			error_info errorCode;

			LemonNewResourceTraceCatalog(*this,id,name,desciption,culture,errorCode);

			errorCode.check_throw();
		}

		void trace_catalog(uint32_t id,const lemon::String & name, const lemon::String & desciption,const lemon::String & culture)
		{
			trace_catalog(id,name.c_str(),desciption.c_str(),culture.c_str());
		}

		void trace_catalog(uint32_t id,const char_t * name, const char_t * desciption)
		{
			trace_catalog(id,name,desciption,LEMON_TEXT(""));
		}

		void trace_catalog(uint32_t id,const lemon::String & name, const lemon::String & desciption)
		{
			trace_catalog(id,name.c_str(),desciption.c_str());
		}

		//////////////////////////////////////////////////////////////////////////
		LemonResourceInfo error_message(uint32_t id,const char_t * culture) const
		{
			return LemonResourceErrorInfo(*this,id,culture);
		}

		LemonResourceInfo error_message(uint32_t id,const lemon::String & culture) const
		{
			return error_message(id,culture.c_str());
		}

		LemonResourceInfo error_message(uint32_t id) const
		{
			return error_message(id,LEMON_TEXT(""));
		}

		void error_message(uint32_t id,const char_t * name, const char_t * desciption,const char_t * culture)
		{
			error_info errorCode;

			LemonNewResourceErrorInfo(*this,id,name,desciption,culture,errorCode);

			errorCode.check_throw();
		}

		void error_message(uint32_t id,const lemon::String & name, const lemon::String & desciption,const lemon::String & culture)
		{
			error_message(id,name.c_str(),desciption.c_str(),culture.c_str());
		}

		void error_message(uint32_t id,const char_t * name, const char_t * desciption)
		{
			error_message(id,name,desciption,LEMON_TEXT(""));
		}

		void error_message(uint32_t id,const lemon::String & name, const lemon::String & desciption)
		{
			error_message(id,name.c_str(),desciption.c_str());
		}

		//////////////////////////////////////////////////////////////////////////

	public:

		void write(LemonIoWriter writer) 
		{
			error_info errorCode;

			LemonWriteResource(*this,writer,errorCode);

			errorCode.check_throw();
		}

		void write(const lemon::String& path) 
		{
			error_info errorCode;

			LemonWriteResourceFile(*this,path.c_str(),errorCode);

			errorCode.check_throw();
		}

		void write(std::ostream & stream) 
		{
			error_info errorCode;

			LemonIoWriter writer = {&stream,&package::ostream_writer};

			write(writer);
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

		static LemonResource Create()
		{
			error_info errorCode;

			LemonResource rc = LemonCreateResource(errorCode);

			errorCode.check_throw();

			return rc;
		}

		static LemonResource Create(const lemon::String & path)
		{
			error_info errorCode;

			LemonResource rc = LemonReadResourceFile(path.c_str(),errorCode);

			errorCode.check_throw();

			return rc;
		}

		static LemonResource Create(LemonIoReader reader)
		{
			error_info errorCode;

			LemonResource rc = LemonReadResource(reader,errorCode);

			errorCode.check_throw();

			return rc;
		}

		static LemonResource Create(std::istream & stream)
		{
			LemonIoReader reader = {&stream,&package::istream_reader};

			return Create(reader);
		}
	};

}}

#endif // LEMONXX_SYS_RESOURCE_HPP

