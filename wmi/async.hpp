/**
* 
* @file     async
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/10/09
*/
#ifndef LEMONXX_WMI_ASYNC_HPP
#define LEMONXX_WMI_ASYNC_HPP

#include <lemonxx/wmi/COM.hpp>
#include <lemonxx/function/function.hpp>

namespace lemon{namespace wmi{

	class WmiAsyncOperationObserverImpl 
		: public ATL::CComObjectRootEx<ATL::CComMultiThreadModel>
		, public IWbemObjectSink
	{
	public:
		typedef lemon::function<void(LONG, IWbemClassObject**)> WmiResultHandle;

		typedef lemon::function<void(LONG, HRESULT, BSTR, IWbemClassObject*)> WmiStatusHandle;

		BEGIN_COM_MAP(WmiAsyncOperationObserverImpl)
			COM_INTERFACE_ENTRY(IWbemObjectSink)
		END_COM_MAP()


		void SetWmiAsyncResultEventHandle(const WmiResultHandle &handle)
		{
			assert(_resultHandle.empty());

			_resultHandle = handle;
		}

		void SetWmiAsyncStatusEventHandle(const WmiStatusHandle &handle)
		{
			assert(_statusHandle.empty());

			_statusHandle = handle;
		}


	private:

		HRESULT STDMETHODCALLTYPE Indicate( 
			/* [in] */			LONG lObjectCount,
			/* [size_is][in] */	IWbemClassObject __RPC_FAR *__RPC_FAR *apObjArray
			)
		{
			if(!_resultHandle.empty())
			{
				_resultHandle(lObjectCount,apObjArray);
			}

			return WBEM_S_NO_ERROR;
		}

		HRESULT STDMETHODCALLTYPE SetStatus( 
			/* [in] */ LONG lFlags,
			/* [in] */ HRESULT hResult,
			/* [in] */ BSTR strParam,
			/* [in] */ IWbemClassObject __RPC_FAR *pObjParam
			)
		{
			if(!_statusHandle.empty())
			{
				_statusHandle(lFlags,hResult,strParam,pObjParam);
			}

			return WBEM_S_NO_ERROR;
		}
	private:
		WmiResultHandle						_resultHandle;

		WmiStatusHandle						_statusHandle;
	};


	class async_observer : private lemon::nocopyable
	{
	public:

		typedef ATL::CComObject<WmiAsyncOperationObserverImpl> Impl;

		async_observer(WmiAsyncOperationObserverImpl::WmiResultHandle resultHandle,WmiAsyncOperationObserverImpl::WmiStatusHandle statusHandle)
		{
			Impl * sink;

			__lemon_com_check_throw(Impl::CreateInstance(&sink));

			_sink = sink;

			_sink->SetWmiAsyncResultEventHandle(resultHandle);

			_sink->SetWmiAsyncStatusEventHandle(statusHandle);
		}

		operator IWbemObjectSink * () const
		{
			ATL::CComPtr<IWbemObjectSink> sink;

			__lemon_com_check_throw(_sink->QueryInterface(__uuidof(IWbemObjectSink),(void**)&sink));

			return sink;
		}
	private:

		ATL::CComPtr<Impl> _sink;
	};
}}

#endif //LEMONXX_WMI_ASYNC_HPP

