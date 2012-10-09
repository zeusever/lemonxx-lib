/**
* 
* @file     object
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/10/08
*/
#ifndef LEMONXX_WMI_OBJECT_HPP
#define LEMONXX_WMI_OBJECT_HPP
#include <vector>
#include <lemonxx/assembly.h>
#include <lemonxx/wmi/COM.hpp>
#include <lemonxx/type_traits/type_traits.hpp>

namespace lemon{namespace wmi{

	class object 
	{
	public:

		typedef std::vector<std::pair<lemon::String,ATL::CComVariant> >	properties_type;

		object(){}

		object(const ATL::CComPtr<IUnknown> & obj)
		{
			__lemon_com_check_throw(obj->QueryInterface(IID_IWbemClassObject,(void**)&_classObject));
		}

		object(const ATL::CComPtr<IWbemClassObject> & obj):_classObject(obj) {}

		bool empty() const { return !_classObject; }

		object clone()
		{
			ATL::CComPtr<IWbemClassObject> obj;

			__lemon_com_check_throw(_classObject->Clone(&obj));

			return obj;
		}

		properties_type properties(long flags) const
		{
			properties_type collection;

			_classObject->BeginEnumeration(flags);

			for(;;)
			{
				ATL::CComBSTR key;

				ATL::CComVariant val;

				HRESULT hr = _classObject->Next(0,&key,&val,0,0);

				if(FAILED(hr))
				{
					error_info errorCode;

					LEMON_COM_ERROR(errorCode,hr);

					errorCode.check_throw();
				}

				if(WBEM_S_NO_MORE_DATA == hr) break;

				if(!key)
				{
					collection.push_back(std::make_pair(LEMON_TEXT(""),val));
				}
				else
				{
					collection.push_back(std::make_pair((lemon::String)key,val));
				}
				
			}

			return collection;
		}

		ATL::CComVariant property(const lemon::String & key) const
		{
			ATL::CComVariant val;

			__lemon_com_check_throw(_classObject->Get(BSTR(key.c_str()),0,&val,0,0));

			return val;
		}

		void property(const lemon::String & key,const ATL::CComVariant & var)
		{
			_classObject->Put(BSTR(key.c_str()),0,&const_cast<ATL::CComVariant&>(var),0);
		}

		ATL::CComVariant qualifier(const lemon::String & key) const
		{
			ATL::CComVariant val;

			ATL::CComPtr<IWbemQualifierSet> qs = NULL;

			__lemon_com_check_throw(_classObject->GetQualifierSet(&qs));

			__lemon_com_check_throw(qs->Get(BSTR(key.c_str()),0,&val,0));

			return val;
		}

		ATL::CComVariant operator[](const lemon::String & key) const
		{
			return property(key);
		}

		operator IWbemClassObject * () const
		{
			return _classObject;
		}

		object newobj() const
		{
			ATL::CComPtr<IWbemClassObject> obj;

			__lemon_com_check_throw(_classObject->SpawnInstance(0,&obj));

			return obj;
		}

		void release()
		{
			_classObject.Release();
		}

	private:

		ATL::CComPtr<IWbemClassObject>	_classObject;
	};

	class method 
	{
	public:
		
		method(const lemon::String & name,object & classObj)
		{
			ATL::CComPtr<IWbemClassObject> inSignature,outSignature;

			__lemon_com_check_throw(((IWbemClassObject *)classObj)->GetMethod(name.c_str(),0,&inSignature,&outSignature));

			_inSignature = inSignature;

			_outSignature = outSignature;

			ATL::CComBSTR className;

			__lemon_com_check_throw(((IWbemClassObject *)classObj)->GetMethodOrigin(name.c_str(),&className));

			_className = className;
		}

		object parameters(size_t args, ATL::CComVariant * argv) const
		{
			if(_inSignature.empty()) return object();

			object::properties_type properties = _inSignature.properties(WBEM_FLAG_LOCAL_ONLY);

			if(properties.size() != args)
			{

			}

			object p = _inSignature.newobj();

			for(size_t i = 0; i < properties.size(); ++ i)
			{
				p[properties[i].first] = argv[i];
			}

			return p;
		}

		const lemon::String & classname() const { return _className; }

		const lemon::String & name() const { return _name; }

	private:

		lemon::String				_name;

		lemon::String				_className;

		object						_inSignature;

		object						_outSignature;
	};

	template<bool Const>
	class basic_object_iterator_t 
		: public iterator_t<basic_object_iterator_t<Const>,typename lemon::conditional<Const,const object,object>::type,ptrdiff_t> 
		, private nocopyable
	{
		typedef typename lemon::conditional<Const,const object,object>::type	value_type;

		typedef value_type														*pointer_type;

		typedef value_type														&reference_type;

	public:

		basic_object_iterator_t(){}

		template<bool ConstRHS>
		basic_object_iterator_t(const basic_object_iterator_t<ConstRHS> & rhs)
			:_enumerator(rhs.enumerator()),_current(rhs.dereference())
		{

		}

		basic_object_iterator_t(const ATL::CComPtr<IEnumWbemClassObject> & enumerator)
			:_enumerator(enumerator)
		{
			if(*this != basic_object_iterator_t()) increment();
		}

		bool equal(const basic_object_iterator_t & rhs) const
		{
			return _enumerator == rhs._enumerator && _current == rhs._current;
		}

		reference_type dereference() const
		{
			return _current;
		}

		pointer_type ptr() const
		{
			return &_current;
		}
		void increment()
		{
			ATL::CComPtr<IWbemClassObject> obj;

			ULONG counter = 0;

			__lemon_com_check_throw(_enumerator->Next(WBEM_INFINITE,1,&obj,&counter));

			if(0 == counter)
			{
				_enumerator.Release();

				_current.release();

				return;
			}

			_current = obj;
		}

		ATL::CComPtr<IEnumWbemClassObject> enumerator() const{return _enumerator;}

	private:

		mutable object							_current;

		ATL::CComPtr<IEnumWbemClassObject>		_enumerator;
	};
}}

#endif //LEMONXX_WMI_OBJECT_HPP

