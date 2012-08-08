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
#include <lemon/sys/resource.h>
#include <lemonxx/sys/inttypes.hpp>
#include <lemonxx/sys/handle.hpp>
#include <lemonxx/sys/errorcode.hpp>
#include <lemonxx/mpl/type2type.hpp>
#include <lemonxx/utility/iterator.hpp>
#include <lemonxx/mpl/inttypes.hpp>
#include <lemonxx/type_traits/type_traits.hpp>
namespace lemon{

	/*
	 * the trace event sequence id.
	 */
	class trace_event_id
	{
	public:

		trace_event_id(lemon::uint16_t fileid,lemon::uint16_t lines)
		{
			_val = LEMON_MAKE_TRACE_EVENT_SEQUENCE(fileid,lines);
		}

		operator lemon::uint32_t () const 
		{
			return _val;
		}

	private:

		lemon::uint32_t			_val;
	};

	class resource_errorinfo : public LemonResourceErrorInfo
	{
	public:

		typedef mpl::size_t_<LEMON_RESOURCE_TERRORINFO>		type;

		typedef LemonResourceErrorInfo	base_type;

		resource_errorinfo(const LemonResourceErrorInfo * rhs)
			:_name(rhs->Name),_description(rhs->Description)
		{
			Code = rhs->Code;

			Name = _name.c_str();

			Description = _description.c_str();
		}
		
		resource_errorinfo(lemon::uint32_t code,const lemon::String & name,const lemon::String &description)
			:_name(name),_description(description)
		{
			Code = code;

			Name = _name.c_str();

			Description = _description.c_str();
		}

		bool operator == (const resource_errorinfo & rhs)
		{
			return _name == rhs._name && _description == rhs._description && Code == rhs.Code;
		}

	private:
		lemon::String		_name;

		lemon::String		_description;
	};

	class resource_text : public LemonResourceText
	{
	public:

		typedef mpl::size_t_<LEMON_RESOURCE_TTEXT>		type;

		typedef LemonResourceText	base_type;

		resource_text(const LemonResourceText * rhs)
			:_global(rhs->Global),_locale(rhs->Locale)
		{
			Global = _global.c_str();

			Locale = _locale.c_str();
		}

		resource_text(const lemon::String & global,const lemon::String &locale)
			:_global(global),_locale(locale)
		{
			Global = _global.c_str();

			Locale = _locale.c_str();
		}

		bool operator == (const resource_text & rhs)
		{
			return _global == rhs._global && _locale == rhs._locale;
		}

	private:
		lemon::String		_global;

		lemon::String		_locale;
	};

	class resource_trace_catalog : public LemonResourceTraceCatalog
	{
	public:

		typedef mpl::size_t_<LEMON_RESOURCE_TTRACECATALOG>		type;

		typedef LemonResourceTraceCatalog	base_type;

		resource_trace_catalog(const LemonResourceTraceCatalog *rhs)
			:_name(rhs->Name),_description(rhs->Description)
		{
			Value = rhs->Value;

			Name = _name.c_str();

			Description = _description.c_str();
		}
		resource_trace_catalog(lemon::uint32_t val,const lemon::String & name,const lemon::String &description)
			:_name(name),_description(description)
		{
			Value = val;

			Name = _name.c_str();

			Description = _description.c_str();
		}

		bool operator == (const resource_trace_catalog & rhs)
		{
			return _name == rhs._name && _description == rhs._description && Value == rhs.Value;
		}

	private:
		lemon::String		_name;

		lemon::String		_description;
	};

	class resource_trace_event : public LemonResourceTraceEvent
	{
	public:

		typedef mpl::size_t_<LEMON_RESOURCE_TTRACEEVENT>		type;

		typedef LemonResourceTraceEvent	base_type;

		resource_trace_event(const LemonResourceTraceEvent *rhs)
			:_text(rhs->Text)
		{
			Sequence = rhs->Sequence;

			Text = _text.c_str();
		}

		resource_trace_event(lemon::uint32_t val,const lemon::String & text)
			:_text(text)
		{

			Sequence = val;

			Text = _text.c_str();
		}

		bool operator == (const resource_trace_event & rhs)
		{
			return _text == rhs._text && Sequence == rhs.Sequence;
		}

	private:
		lemon::String		_text;
	};

	template<typename T>
	class resource_iterator 
		: public iterator_t<
		resource_iterator<T>,
		typename lemon::conditional<lemon::is_const<T>::value,const typename T::base_type,typename T::base_type>::type,
		ptrdiff_t> 
	{
	public:
		typedef typename lemon::conditional<lemon::is_const<T>::value,const typename T::base_type,typename T::base_type>::type value_type;

		resource_iterator():_enumerator(NULL),_val(NULL) {}

		resource_iterator(LemonResourceIterator val)
			:_enumerator(val)
		{
			increment();
		}

		template<typename T1>
		resource_iterator(resource_iterator<T1> & rhs)
			:_enumerator(rhs.Handle()),_val(rhs.Current())
		{

		}

		LemonResourceIterator  Handle() const { return _enumerator; }

		value_type*  Current() const { return _val; }

		bool equal(const resource_iterator & rhs) const
		{
			return _val == rhs._val;
		}

		value_type & dereference() const
		{
			return *_val;
		}

		value_type * ptr()
		{
			return _val;
		}

		void increment()
		{
			_val = (value_type*)LemonResourceIteratorNext(&_enumerator,T::type::value);
		}

	private:

		value_type							*_val;

		LemonResourceIterator				_enumerator;
	};


	class resource : public basic_handle_object<LemonResource,&LemonReleaseResource>
	{
	public:

		typedef basic_handle_object<LemonResource,&LemonReleaseResource>	base_type;

		typedef resource_iterator<resource_text>							resource_text_iterator;

		typedef resource_iterator<const resource_text>						const_resource_text_iterator;

		typedef resource_iterator<resource_errorinfo>						resource_errorinfo_iterator;

		typedef resource_iterator<const resource_errorinfo>					const_resource_errorinfo_iterator;

		typedef resource_iterator<resource_trace_catalog>					resource_trace_catalog_iterator;

		typedef resource_iterator<const resource_trace_catalog>				const_resource_trace_catalog_iterator;

		typedef resource_iterator<resource_trace_event>						resource_trace_event_iterator;

		typedef resource_iterator<const resource_trace_event>				const_resource_trace_event_iterator;

		resource():base_type(create()) {}

		const LemonVersion * version() const
		{
			return LemonResourceVersion(*this);
		}

		LemonResourceIterator begin() const { return LemonGetResourceIterator(*this); }

		LemonResourceIterator end() const { return LEMON_HANDLE_NULL_VALUE; }

		const LemonVersion * version(const lemon::char_t * versionstring) const
		{
			error_info  errorCode;

			const LemonVersion  *  v = LemonResetResourceVersion(*this,versionstring,&errorCode);

			errorCode.check_throw();

			return v;
		}

		template<typename T> void add(const T & t) { add(t,mpl::type2type<T>()); }

		const LemonResourceText * text(const lemon::char_t * global) const
		{
			error_info errorCode;

			const LemonResourceText * text = LemonGetResourceText(*this,global,&errorCode);

			return text;
		}

		const LemonResourceErrorInfo* errorinfo(lemon::uint32_t code) const
		{
			error_info errorCode;

			const LemonResourceErrorInfo * text = LemonGetResourceErrorInfo(*this,code,&errorCode);

			return text;
		}

		const LemonResourceTraceCatalog* event_catalog(lemon::uint32_t code) const
		{
			error_info errorCode;

			const LemonResourceTraceCatalog * text = LemonGetResourceTraceCatalog(*this,code,&errorCode);

			return text;
		}

		const LemonResourceTraceEvent* event(lemon::uint32_t s) const
		{
			error_info errorCode;

			const LemonResourceTraceEvent * text = LemonGetResourceTraceEvent(*this,s,&errorCode);

			return text;
		}

		lemon::uuid_t guid() const
		{
			return *LemonResourceUuid(*this);
		}

	private:
		

		void add(const resource_errorinfo & val,mpl::type2type<resource_errorinfo>)
		{
			error_info  errorCode;

			LemonAddResourceErrorInfo(*this,&val,&errorCode);

			errorCode.check_throw();
		}

		void add(const resource_text & val,mpl::type2type<resource_text>)
		{
			error_info  errorCode;

			LemonAddResourceText(*this,&val,&errorCode);

			errorCode.check_throw();
		}

		void add(const resource_trace_catalog & val,mpl::type2type<resource_trace_catalog>)
		{
			error_info  errorCode;

			LemonAddResourceTraceCatalog(*this,&val,&errorCode);

			errorCode.check_throw();
		}

		void add(const resource_trace_event & val,mpl::type2type<resource_trace_event>)
		{
			error_info  errorCode;

			LemonAddResourceTraceEvent(*this,&val,&errorCode);

			errorCode.check_throw();
		}

	private:

		static LemonResource create()
		{
			error_info errorCode;

			LemonResource resource = LemonCreateResource(&errorCode);

			errorCode.check_throw(LEMON_TEXT("create resource exception"));

			return resource;
		}

	};

}

#endif // LEMONXX_SYS_RESOURCE_HPP

