/**
* 
* @file     connection
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/10/08
*/
#ifndef LEMONXX_WMI_CONNECT_HPP
#define LEMONXX_WMI_CONNECT_HPP
#include <lemonxx/wmi/context.hpp>
#include <lemonxx/wmi/object.hpp>
#include <lemonxx/wmi/async.hpp>

namespace lemon{namespace wmi{

	class WmiEvent
	{
	public:

		WmiEvent(const ATL::CComPtr<IEnumWbemClassObject> & e)
			:_event(e)
		{}

		bool empty() const{return !_event;}

		object wait()
		{
			ATL::CComPtr<IWbemClassObject> object;

			ULONG counter = 0;

			__lemon_com_check_throw(_event->Next(WBEM_INFINITE,1,&object,&counter));

			return object;
		}

	private:

		ATL::CComPtr<IEnumWbemClassObject> _event;
	};

	class connection : private lemon::nocopyable
	{
	public:

		typedef basic_object_iterator_t<false>			query_result_iterator;

		typedef basic_object_iterator_t<true>			const_query_result_iterator;

		connection(const char_t * URL) { connect(URL); }

		connection(
			const char_t * URL,const char_t * userName, 
			const char_t * password, const char_t * authority,
			context & ctx
			) 
		{
			connect(URL,userName,password,authority,ctx); 
		}

		void connect(const char_t * URL)
		{
			ATL::CComPtr<IWbemLocator> locator;

			__lemon_com_check_throw(CoCreateInstance(
				CLSID_WbemLocator,             
				0, 
				CLSCTX_INPROC_SERVER, 
				IID_IWbemLocator, (LPVOID *) &locator
				));

			__lemon_com_check_throw(locator->ConnectServer(
				BSTR(URL), NULL, NULL, 0, 
				WBEM_FLAG_CONNECT_USE_MAX_WAIT, 0, 0, &_services));

			__lemon_com_check_throw(CoSetProxyBlanket(
				_services,                   // Indicates the proxy to set
				RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx 
				RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx 
				NULL,                        // Server principal name 
				RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
				RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
				NULL,                        // client identity
				EOAC_NONE                    // proxy capabilities 
				));
		}

		void connect(
			const char_t * URL,const char_t * userName, 
			const char_t * password, const char_t * authority,
			context & ctx
			)
		{
			ATL::CComPtr<IWbemLocator> locator;

			__lemon_com_check_throw(CoCreateInstance(
				CLSID_WbemLocator,             
				0, 
				CLSCTX_INPROC_SERVER, 
				IID_IWbemLocator, (LPVOID *) &locator
				));

			//safe cast const char_t * to BSTR
			__lemon_com_check_throw(locator->ConnectServer(
				BSTR(URL), BSTR(userName), BSTR(password), 0, 
				WBEM_FLAG_CONNECT_USE_MAX_WAIT, BSTR(authority), ctx, &_services));

			__lemon_com_check_throw(CoSetProxyBlanket(
				_services,                   // Indicates the proxy to set
				RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx 
				RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx 
				NULL,                        // Server principal name 
				RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
				RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
				NULL,                        // client identity
				EOAC_NONE                    // proxy capabilities 
				));
		}

		object get_object(const lemon::String & path) const
		{
			ATL::CComPtr<IWbemClassObject> obj;

			__lemon_com_check_throw(_services->GetObject(BSTR(path.c_str()),WBEM_FLAG_RETURN_WBEM_COMPLETE,0,&obj,0));

			return obj;
		}

		object invoke(const lemon::String & classInstance,const method & m,size_t args, ATL::CComVariant * argv)
		{
			ATL::CComPtr<IWbemClassObject> outParameters;

			object parameters = m.parameters(args,argv);

			__lemon_com_check_throw(_services->ExecMethod(
				BSTR(classInstance.c_str()),
				BSTR(m.name().c_str()),
				0,
				0,
				parameters,
				&outParameters,
				0
				));

			return outParameters;
		}

		object operator[] (const lemon::String & path) const
		{
			return get_object(path);
		}


		query_result_iterator query(const lemon::String & Q)
		{
			return QueryCore(Q);
		}

		query_result_iterator query(const lemon::String & Q,const context & ctx) 
		{
			return QueryCore(Q,ctx);
		}

		const_query_result_iterator query(const lemon::String & Q) const
		{
			return QueryCore(Q);
		}

		const_query_result_iterator query(const lemon::String & Q,const context & ctx) const
		{
			return QueryCore(Q,ctx);
		}

		WmiEvent query_notify(const lemon::String & wql)
		{
			ATL::CComPtr<IEnumWbemClassObject> obj;

			__lemon_com_check_throw(_services->ExecNotificationQuery(
				BSTR(L"WQL"),
				BSTR(wql.c_str()),
				WBEM_FLAG_RETURN_IMMEDIATELY | WBEM_FLAG_FORWARD_ONLY,
				0,
				&obj
				));

			return obj;
		}

		WmiEvent query_notify(const lemon::String & wql,const context & ctx)
		{
			ATL::CComPtr<IEnumWbemClassObject> obj;

			__lemon_com_check_throw(_services->ExecNotificationQuery(
				BSTR(L"WQL"),
				BSTR(wql.c_str()),
				WBEM_FLAG_RETURN_IMMEDIATELY | WBEM_FLAG_FORWARD_ONLY,
				ctx,
				&obj
				));

			return obj;
		}


		//////////////////////////////////////////////////////////////////////////


		void async_get_object(const lemon::String & path,const async_observer & observer) const
		{
			__lemon_com_check_throw(_services->GetObjectAsync(BSTR(path.c_str()),WBEM_FLAG_SEND_STATUS,0,observer));
		}

		void async_query(const lemon::String & Q,const async_observer & observer) const
		{
			__lemon_com_check_throw(_services->ExecQueryAsync(
				BSTR(L"WQL"),
				BSTR(Q.c_str()),
				WBEM_FLAG_SEND_STATUS ,
				0,
				observer
				));
		}

		void async_query(const lemon::String & Q,const context & ctx,const async_observer & observer) const
		{
			__lemon_com_check_throw(_services->ExecQueryAsync(
				BSTR(L"WQL"),
				BSTR(Q.c_str()),
				WBEM_FLAG_SEND_STATUS,
				ctx,
				observer
				));
		}

		void async_query_notify(const lemon::String & wql,const async_observer & observer)
		{
			ATL::CComPtr<IEnumWbemClassObject> object;

			__lemon_com_check_throw(_services->ExecNotificationQueryAsync(
				BSTR(L"WQL"),
				BSTR(wql.c_str()),
				WBEM_FLAG_SEND_STATUS,
				0,
				observer
				));
		}

		void async_query_notify(const lemon::String & wql,const context & ctx,const async_observer & observer)
		{
			ATL::CComPtr<IEnumWbemClassObject> object;

			__lemon_com_check_throw(_services->ExecNotificationQueryAsync(
				BSTR(L"WQL"),
				BSTR(wql.c_str()),
				WBEM_FLAG_SEND_STATUS,
				ctx,
				observer
				));
		}

	private:

		ATL::CComPtr<IEnumWbemClassObject> QueryCore(const lemon::String & Q) const
		{
			ATL::CComPtr<IEnumWbemClassObject> result;

			__lemon_com_check_throw(_services->ExecQuery(
				BSTR(L"WQL"),
				BSTR(Q.c_str()),
				WBEM_FLAG_RETURN_IMMEDIATELY | WBEM_FLAG_FORWARD_ONLY,
				0,
				&result
				));

			return result;
		}

		ATL::CComPtr<IEnumWbemClassObject> QueryCore(const lemon::String & Q,const context & ctx) const
		{
			ATL::CComPtr<IEnumWbemClassObject> result;

			__lemon_com_check_throw(_services->ExecQuery(
				BSTR(L"WQL"),
				BSTR(Q.c_str()),
				WBEM_FLAG_RETURN_IMMEDIATELY | WBEM_FLAG_FORWARD_ONLY,
				ctx,
				&result
				));

			return result;
		}

	private:
		ATL::CComPtr<IWbemServices> _services;
	};

}}

#endif //LEMONXX_WMI_CONNECT_HPP

