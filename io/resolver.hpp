/**
* 
* @file     resolver
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/02/19
*/
#ifndef LEMONXX_IO_RESOLVER_HPP
#define LEMONXX_IO_RESOLVER_HPP
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/io/endpoint.hpp>
#include <lemonxx/utility/utility.hpp>
#include <lemon/io/resolver.h>

namespace lemon{namespace io{

	class resolver_iterator  : public iterator_t<resolver_iterator,const addrinfo,ptrdiff_t>
	{
	public:
		resolver_iterator():_resolver(LEMON_HANDLE_NULL_VALUE){}

		resolver_iterator(const char * nodeName,const char * serverName)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			_resolver = LemonCreateResolver(nodeName,serverName,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

			increment();
		}

		~resolver_iterator()
		{
			reset();
		}

		void reset()
		{
			if(!empty()) LemonReleaseResolver(_resolver);

			_resolver = LEMON_HANDLE_NULL_VALUE;
		}

		bool empty()
		{
			return _resolver == LEMON_HANDLE_NULL_VALUE;
		}

		bool equal(const resolver_iterator & rhs) const
		{
			return _resolver == rhs._resolver;
		}

		const addrinfo & dereference() const
		{
			return *_current;
		}

		const addrinfo * ptr()		
		{
			return _current;		
		}

		void increment()
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			_current = LemonResovlerNext(_resolver,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

			if(!_current){reset();}
		}

	private:
		const addrinfo * _current;

		LemonResovler _resolver;
	};

}}

#endif //LEMONXX_IO_RESOLVER_HPP