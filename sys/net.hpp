/**
* 
* @file     net
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/08/30
*/
#ifndef LEMONXX_SYS_NET_HPP
#define LEMONXX_SYS_NET_HPP
#include <cassert>
#include <lemon/sys/net.h>
#include <lemonxx/sys/inttypes.hpp>
#include <lemonxx/sys/errorcode.hpp>
#include <lemonxx/mpl/inttypes.hpp>
#include <lemonxx/utility/utility.hpp>

namespace lemon{namespace net{

	inline std::string tostring(const in_addr &addr)
	{
		char buffer[sizeof("255.255.255.255")] = {0};

		scope_error_info errorCode;

		LemonAddressToString(AF_INET,&addr,sizeof(addr),buffer,sizeof(buffer),errorCode);

		return buffer;
	}
#ifdef LEMON_SUPPORT_IPV6
	inline std::string tostring(const in6_addr & addr)
	{
		char buffer[sizeof("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255")] = {0};

		scope_error_info errorCode;

		LemonAddressToString(AF_INET6,&addr,sizeof(addr),buffer,sizeof(buffer),errorCode);

		return buffer;
	}
#endif //#ifdef LEMON_SUPPORT_IPV6
	//////////////////////////////////////////////////////////////////////////


	class address_v4 : public in_addr
	{
	public:

		address_v4(){ s_addr = 0; }

		explicit address_v4(const in_addr & address)
		{
			s_addr = address.s_addr;
		}

		address_v4( uint8_t a1 , uint8_t a2 , uint8_t a3 , uint8_t a4 )
		{
			byte_t * buffer = (byte_t *)this;

			buffer[0] = a1;
			
			buffer[1] = a2;

			buffer[2] = a3;

			buffer[3] = a4;
		}

		explicit address_v4(const char * message)
		{
			fromstring(message);
		}

		explicit address_v4(const std::string & message)
		{
			fromstring(message.c_str());
		}

		void fromstring(const char * message)
		{
			scope_error_info errorCode;

			LemonAddressFromString(AF_INET,message,strlen(message),ptr(),length(),errorCode);
		}

		std::string tostring() const
		{
			return lemon::net::tostring(*this);
		}

		size_t length()
		{
			return sizeof(in_addr);
		}

		byte_t * ptr()
		{
			return (byte_t*)this;
		}

		const byte_t * ptr() const
		{
			return (const byte_t*)this;
		}
	};

	inline bool operator == (const in_addr & lhs, const in_addr & rhs)
	{
		return memcmp(&lhs,&rhs,sizeof(in_addr)) == 0;
	}

	inline bool operator > (const in_addr & lhs,const in_addr & rhs) 
	{
		return memcmp(&lhs,&rhs,sizeof(in_addr)) > 0;
	}

	inline bool operator >= (const in_addr & lhs,const in_addr & rhs) 
	{
		return memcmp(&lhs,&rhs,sizeof(in_addr)) >= 0;
	}

	inline bool operator < (const in_addr & lhs,const in_addr & rhs) 
	{
		return memcmp(&lhs,&rhs,sizeof(in_addr)) < 0;
	}

	inline bool operator <= (const in_addr & lhs,const in_addr & rhs) 
	{
		return memcmp(&lhs,&rhs,sizeof(in_addr)) <= 0;
	}

	inline bool operator != (const in_addr & lhs,const in_addr & rhs) 
	{
		return memcmp(&lhs,&rhs,sizeof(in_addr)) != 0;
	}

	//////////////////////////////////////////////////////////////////////////
#ifdef LEMON_SUPPORT_IPV6
	class address_v6 : public in6_addr
	{
	public:
		address_v6(){ memset(this,0,sizeof(in6_addr)); }

		explicit address_v6(const in6_addr & address)
		{
			memcpy(this,&address,sizeof(address));
		}

		explicit address_v6(const char * message)
		{
			fromstring(message);
		}

		explicit address_v6(const std::string & message)
		{
			fromstring(message.c_str());
		}

		void fromstring(const char * message)
		{
			scope_error_info errorCode;

			LemonAddressFromString(AF_INET6,message,strlen(message),ptr(),length(),errorCode);
		}

		std::string tostring() const
		{
			return lemon::net::tostring(*this);
		}

		size_t length()
		{
			return sizeof(in6_addr);
		}

		byte_t * ptr()
		{
			return (byte_t*)this;
		}

		const byte_t * ptr() const
		{
			return (const byte_t*)this;
		}
	};
	

	inline bool operator == (const in6_addr & lhs, const in6_addr & rhs)
	{
		return memcmp(&lhs,&rhs,sizeof(in6_addr)) == 0;
	}

	inline bool operator > (const in6_addr & lhs,const in6_addr & rhs) 
	{
		return memcmp(&lhs,&rhs,sizeof(in6_addr)) > 0;
	}

	inline bool operator >= (const in6_addr & lhs,const in6_addr & rhs) 
	{
		return memcmp(&lhs,&rhs,sizeof(in6_addr)) >= 0;
	}

	inline bool operator < (const in6_addr & lhs,const in6_addr & rhs) 
	{
		return memcmp(&lhs,&rhs,sizeof(in6_addr)) < 0;
	}

	inline bool operator <= (const in6_addr & lhs,const in6_addr & rhs) 
	{
		return memcmp(&lhs,&rhs,sizeof(in6_addr)) <= 0;
	}

	inline bool operator != (const in6_addr & lhs,const in6_addr & rhs) 
	{
		return memcmp(&lhs,&rhs,sizeof(in6_addr)) != 0;
	}

#endif //#ifdef LEMON_SUPPORT_IPV6

	//////////////////////////////////////////////////////////////////////////

	class address 
	{
	public:

		union buffer_type
		{
			in_addr			v4;
#ifdef LEMON_SUPPORT_IPV6
			in6_addr		v6;
#endif //
		};

	public:

		address():_af(AF_UNSPEC) {}

		address(const in_addr & rhs) :_af(AF_INET)
		{
			memcpy(&_buffer,&rhs,sizeof(in_addr));
		}

		address(const in6_addr & rhs) :_af(AF_INET6)
		{
			memcpy(&_buffer,&rhs,sizeof(in6_addr));
		}

		address(int af,const char * message) :_af(af)
		{
#ifdef LEMON_SUPPORT_IPV6
			assert(af == AF_INET || af == AF_INET6);
#else
			assert(af == AF_INET);
#endif

			fromstring(message);
		}

		address(int af,const std::string & message):_af(af)
		{
#ifdef LEMON_SUPPORT_IPV6
			assert(af == AF_INET || af == AF_INET6);
#else
			assert(af == AF_INET);
#endif

			fromstring(message.c_str());
		}

		void fromstring(const char * message)
		{
			scope_error_info errorCode;

			LemonAddressFromString(_af,message,strlen(message),ptr(),length(),errorCode);
		}

		int af() const
		{
			return _af;
		}

		size_t length() const
		{
			if(af() == AF_INET)
			{
				return sizeof(in_addr);
			}
#ifdef LEMON_SUPPORT_IPV6
			else if(af() == AF_INET6)
			{
				return sizeof(in6_addr);
			}
#endif //#ifdef LEMON_SUPPORT_IPV6
			else
			{
				return 0;
			}

		}

		size_t capacity() const
		{
			return sizeof(_buffer);
		}

		byte_t * ptr()
		{
			return (byte_t*)&_buffer;
		}

		std::string tostring() const
		{
			if(af() == AF_INET)
			{
				return lemon::net::tostring(_buffer.v4);
			}
#ifdef LEMON_SUPPORT_IPV6
			else if(af() == AF_INET6)
			{
				return lemon::net::tostring(_buffer.v6);
			}
#endif //LEMON_SUPPORT_IPV6
			else
			{
				assert(false && "invalid address");
			}
		}

		address_v4 & to_v4()
		{
			assert(_af == AF_INET);

			return *(address_v4*)&_buffer.v4;
		}

		const address_v4 & to_v4() const
		{
			assert(_af == AF_INET);

			return *(const address_v4*)&_buffer.v4;
		}

		address_v6 & to_v6()
		{
			assert(_af == AF_INET6);

			return *(address_v6*)&_buffer.v6;
		}

		const address_v6 & to_v6() const
		{
			assert(_af == AF_INET6);

			return *(const address_v6*)&_buffer.v6;
		}

		bool operator == (const address & rhs) const
		{
			return _af == rhs._af && memcmp(this,&rhs,length()) == 0;
		}

		bool operator != (const address & rhs) const
		{
			return _af != rhs._af || memcmp(this,&rhs,length()) != 0;
		}

		bool operator < (const address & rhs) const
		{
			return _af < rhs._af || (_af == rhs._af && memcmp(this,&rhs,length()) < 0);
		}

		bool operator <= (const address & rhs) const
		{
			return _af <= rhs._af || (_af == rhs._af && memcmp(this,&rhs,length()) <= 0);
		}

		bool operator > (const address & rhs) const
		{
			return _af > rhs._af || (_af == rhs._af && memcmp(this,&rhs,length()) > 0);
		}

		bool operator >= (const address & rhs) const
		{
			return _af >= rhs._af || (_af == rhs._af && memcmp(this,&rhs,length()) >= 0);
		}

	private:

		int				_af;

		buffer_type		_buffer;
	};


	//////////////////////////////////////////////////////////////////////////

	class endpoint
	{
	public:
		
		union buffer_type
		{
			sockaddr_in		v4;

			sockaddr_in6	v6;

			sockaddr		addr;
		};

		typedef mpl::size_t_<sizeof(buffer_type)>	buffer_length;

		endpoint()
		{
			_buffer.addr.sa_family = AF_UNSPEC;
		}

		explicit endpoint(const sockaddr_in & addr)
		{
			assert(addr.sin_family == AF_INET);

			memcpy(&_buffer,&addr,sizeof(sockaddr_in));
		}

#ifdef LEMON_SUPPORT_IPV6
		
		explicit endpoint(const sockaddr_in6 & addr)
		{
			assert(addr.sin6_family == AF_INET6);

			memcpy(&_buffer,&addr,sizeof(sockaddr_in6));
		}

#endif //LEMON_SUPPORT_IPV6

		explicit endpoint(const sockaddr * addr)
		{

#ifdef LEMON_SUPPORT_IPV6
			assert(addr->sa_family == AF_INET6 || addr->sa_family == AF_INET);

			if(addr->sa_family == AF_INET6) memcpy(&_buffer,addr,sizeof(sockaddr_in6));

			else memcpy(&_buffer,addr,sizeof(sockaddr_in));
#else
			assert(addr->sa_family == AF_INET6 || addr->sa_family == AF_INET);

			memcpy(&_buffer,addr,sizeof(sockaddr_in));

#endif //LEMON_SUPPORT_IPV6

		}

		size_t capacity() const 
		{
			return buffer_length::value;
		}

		size_t length() const
		{
			if(_buffer.addr.sa_family == AF_INET)
			{
				return sizeof(sockaddr_in);
			}
#ifdef LEMON_SUPPORT_IPV6
			else if(_buffer.addr.sa_family == AF_INET6)
			{
				return sizeof(sockaddr_in6);
			}
#endif //LEMON_SUPPORT_IPV6
			else
			{
				return 0;
			}
		}

		sockaddr * ptr() 
		{
			return &_buffer.addr;
		}

		const sockaddr * ptr() const
		{
			return &_buffer.addr;
		}

		int af() const
		{
			return _buffer.addr.sa_family;
		}

		address_v4 & to_v4()
		{
			assert(af() == AF_INET);

			return *(address_v4*)&_buffer.v4;
		}

		const address_v4 & to_v4() const
		{
			assert(af() == AF_INET);

			return *(address_v4*)&_buffer.v4;
		}

		address_v6 & to_v6()
		{
			assert(af() == AF_INET6);

			return *(address_v6*)&_buffer.v6;
		}

		const address_v6 & to_v6() const
		{
			assert(af() == AF_INET6);

			return *(address_v6*)&_buffer.v6;
		}

		uint16_t port() const
		{
			return _buffer.v4.sin_port;
		}

		void port(uint16_t val)
		{
			_buffer.v4.sin_port = val;
		}

		bool operator == (const endpoint & rhs)
		{
			return length() == rhs.length() && memcmp(&_buffer,&rhs._buffer,length()) == 0;
		}

		bool operator != (const endpoint & rhs)
		{
			return !(*this == rhs);
		}

		bool operator < (const endpoint & rhs)
		{
			return length() < rhs.length() || ( length() == rhs.length() && memcmp(&_buffer,&rhs._buffer,length()) < 0);
		}

		bool operator <= (const endpoint & rhs)
		{
			return length() <= rhs.length() || ( length() == rhs.length() && memcmp(&_buffer,&rhs._buffer,length()) <= 0);
		}

		bool operator > (const endpoint & rhs)
		{
			return length() > rhs.length() || ( length() == rhs.length() && memcmp(&_buffer,&rhs._buffer,length()) > 0);
		}

		bool operator >= (const endpoint & rhs)
		{
			return length() >= rhs.length() || ( length() == rhs.length() && memcmp(&_buffer,&rhs._buffer,length()) >= 0);
		}

	private:

		buffer_type				_buffer;
	};

	//////////////////////////////////////////////////////////////////////////
	class resolver_iterator 
		: public iterator_t<resolver_iterator,const addrinfo,ptrdiff_t>
		, private lemon::nocopyable
	{
	public:

		resolver_iterator():_resolver(LEMON_HANDLE_NULL_VALUE) {}

		resolver_iterator(const char * nodename, const char * servername) 
			:_resolver(Create(nodename,servername))
		{
			increment();
		}

		resolver_iterator(const std::string & nodename, const std::string & servername) 
			:_resolver(Create(nodename.c_str(),servername.c_str()))

		{
			increment();
		}

		bool equal(const resolver_iterator & rhs) const
		{
			return _resolver == rhs._resolver;
		}

		const addrinfo& dereference() const
		{
			return *_current;
		}

		const addrinfo* ptr()
		{
			return _current;
		}

		void increment()
		{
			if(_resolver)
			{
				scope_error_info errorCode;

				_current = LemonResovlerNext(_resolver,errorCode);

				if(!_current) close();
			}
		}

	private:

		void close()
		{
			if(LEMON_CHECK_HANDLE(_resolver))
			{
				LemonReleaseResolver(_resolver);

				_resolver = LEMON_HANDLE_NULL_VALUE;
			}
		}

		static LemonResovler Create(const char * nodename, const char * servername)
		{
			scope_error_info errorCode;

			return LemonCreateResolver(nodename,servername,errorCode);
		}
	private:

		const addrinfo			*_current;

		LemonResovler			_resolver;
	};
}}

#endif //LEMONXX_SYS_NET_HPP
