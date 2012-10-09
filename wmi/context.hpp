/**
* 
* @file     context
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/10/08
*/
#ifndef LEMONXX_WMI_CONTEXT_HPP
#define LEMONXX_WMI_CONTEXT_HPP

#include <lemonxx/wmi/COM.hpp>

namespace lemon{namespace wmi{

	class context 
	{
	public:

		class KeyValueRef
		{
		public:
			KeyValueRef(const char_t * key, context * ctx)
				:_context(ctx),_key(key)
			{
				_context->try_get_value(key,_val);
			}

			operator const ATL::CComVariant & () const
			{
				return _val;
			}

			KeyValueRef & operator = (const ATL::CComVariant &rhs)
			{
				_val = rhs;

				_context->set_value(_key.c_str(),const_cast<ATL::CComVariant &>(_val));

				return *this;
			}

			bool operator == (const ATL::CComVariant &rhs) const
			{
				return rhs == _val;
			}

			bool operator != (const ATL::CComVariant &rhs) const
			{
				return rhs != _val;
			}

			bool operator < (const ATL::CComVariant &rhs) const
			{
				return rhs < _val;
			}

			bool operator > (const ATL::CComVariant &rhs) const
			{
				return rhs > _val;
			}

		private:
			context				*_context;

			lemon::String		_key;

			ATL::CComVariant	_val;
		};

		typedef	ATL::CComVariant							value_type;

		typedef KeyValueRef									reference_type;

		context()
		{
			__lemon_com_check_throw(CoCreateInstance(
				CLSID_WbemContext,             
				0, 
				CLSCTX_INPROC_SERVER, 
				IID_IWbemContext, (LPVOID *) &_context
				));
		}

		void clear()
		{
			__lemon_com_check_throw(_context->DeleteAll());
		}

		void remove(const char_t * key)
		{
			__lemon_com_check_throw(_context->DeleteValue(key,0));
		}

		void get_value(const char_t * key,ATL::CComVariant & var) const
		{
			__lemon_com_check_throw(_context->GetValue(key, 0, &var));
		}

		bool try_get_value(const char_t * key,ATL::CComVariant & var) const
		{
			HRESULT hr = _context->GetValue(key, 0, &var);

			if(FAILED(hr))
			{
				if(WBEM_E_NOT_FOUND != hr)
				{
					error_info errorCode;

					LEMON_COM_ERROR(errorCode,hr);

					errorCode.check_throw();
				}

				return false;
			}

			return true;
		}

		void set_value(const char_t * key, ATL::CComVariant & var)
		{
			__lemon_com_check_throw(_context->SetValue(key, 0, &var));
		}

		reference_type operator[](const char_t * key)
		{
			return KeyValueRef(key,this);
		}

		value_type operator[](const char_t * key) const
		{
			value_type val;

			get_value(key,val);

			return val;
		}

		operator IWbemContext* () const
		{
			return _context;
		}

	private:
		ATL::CComPtr<IWbemContext> _context;
	};
}}

#endif //LEMONXX_WMI_CONTEXT_HPP

