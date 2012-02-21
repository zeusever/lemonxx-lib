/**
* 
* @file     endpoint
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/02/19
*/
#ifndef LEMONXX_IO_ENDPOINT_HPP
#define LEMONXX_IO_ENDPOINT_HPP
#include <string>
#include <lemon/io/abi.h>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>
#include <lemonxx/io/address.hpp>

namespace lemon{namespace io{namespace ip{

	namespace v4{

		class endpoint : public sockaddr_in
		{
		public:
			endpoint(){}

			endpoint(const sockaddr_in & rhs)
			{
				memcpy(this,&rhs,sizeof(rhs));
			}

			unsigned short port() const
			{
				return ntohs(sockaddr_in::sin_port);
			}

			endpoint& port(unsigned short val)
			{
				sockaddr_in::sin_port = htons(val);

				return *this;
			}

			v4::address address()
			{
				return sockaddr_in::sin_addr;
			}

			inline bool operator == (const endpoint & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) == 0;
			}

			inline bool operator != (const endpoint & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) != 0;
			}

			inline bool operator > (const endpoint & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) > 0;
			}

			inline bool operator < (const endpoint & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) < 0;
			}


			inline bool operator >= (const endpoint & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) >= 0;
			}

			inline bool operator <= (const endpoint & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) <= 0;
			}

			inline bool operator == (const sockaddr_in & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) == 0;
			}

			inline bool operator != (const sockaddr_in & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) != 0;
			}

			inline bool operator > (const sockaddr_in & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) > 0;
			}

			inline bool operator < (const sockaddr_in & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) < 0;
			}


			inline bool operator >= (const sockaddr_in & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) >= 0;
			}

			inline bool operator <= (const sockaddr_in & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) <= 0;
			}
		};

		inline bool operator == (const sockaddr_in & lhs,const endpoint & rhs)
		{
			return memcmp(&lhs,&rhs,sizeof(rhs)) == 0;
		}

		inline bool operator != (const sockaddr_in & lhs,const endpoint & rhs)
		{
			return memcmp(&lhs,&rhs,sizeof(rhs)) != 0;
		}

		inline bool operator > (const sockaddr_in & lhs,const endpoint & rhs)
		{
			return memcmp(&lhs,&rhs,sizeof(rhs)) > 0;
		}

		inline bool operator < (const sockaddr_in & lhs,const endpoint & rhs)
		{
			return memcmp(&lhs,&rhs,sizeof(rhs)) < 0;
		}


		inline bool operator >= (const sockaddr_in & lhs,const endpoint & rhs)
		{
			return memcmp(&lhs,&rhs,sizeof(rhs)) >= 0;
		}

		inline bool operator <= (const sockaddr_in & lhs,const endpoint & rhs)
		{
			return memcmp(&lhs,&rhs,sizeof(rhs)) <= 0;
		}

	}


	namespace v6{

		class endpoint : public sockaddr_in6
		{
		public:
			endpoint(){}

			endpoint(const sockaddr_in6 & rhs)
			{
				memcpy(this,&rhs,sizeof(rhs));
			}

			unsigned short port() const
			{
				return ntohs(sockaddr_in6::sin6_port);
			}

			endpoint& port(unsigned short val)
			{
				sockaddr_in6::sin6_port = htons(val);

				return *this;
			}

			v6::address address()
			{
				return sockaddr_in6::sin6_addr;
			}


			inline bool operator == (const endpoint & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) == 0;
			}

			inline bool operator != (const endpoint & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) != 0;
			}

			inline bool operator > (const endpoint & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) > 0;
			}

			inline bool operator < (const endpoint & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) < 0;
			}


			inline bool operator >= (const endpoint & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) >= 0;
			}

			inline bool operator <= (const endpoint & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) <= 0;
			}

			inline bool operator == (const sockaddr_in6 & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) == 0;
			}

			inline bool operator != (const sockaddr_in6 & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) != 0;
			}

			inline bool operator > (const sockaddr_in6 & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) > 0;
			}

			inline bool operator < (const sockaddr_in6 & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) < 0;
			}


			inline bool operator >= (const sockaddr_in6 & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) >= 0;
			}

			inline bool operator <= (const sockaddr_in6 & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) <= 0;
			}
		};

		inline bool operator == (const sockaddr_in6 & lhs,const endpoint & rhs)
		{
			return memcmp(&lhs,&rhs,sizeof(rhs)) == 0;
		}

		inline bool operator != (const sockaddr_in6 & lhs,const endpoint & rhs)
		{
			return memcmp(&lhs,&rhs,sizeof(rhs)) != 0;
		}

		inline bool operator > (const sockaddr_in6 & lhs,const endpoint & rhs)
		{
			return memcmp(&lhs,&rhs,sizeof(rhs)) > 0;
		}

		inline bool operator < (const sockaddr_in6 & lhs,const endpoint & rhs)
		{
			return memcmp(&lhs,&rhs,sizeof(rhs)) < 0;
		}


		inline bool operator >= (const sockaddr_in6 & lhs,const endpoint & rhs)
		{
			return memcmp(&lhs,&rhs,sizeof(rhs)) >= 0;
		}

		inline bool operator <= (const sockaddr_in6 & lhs,const endpoint & rhs)
		{
			return memcmp(&lhs,&rhs,sizeof(rhs)) <= 0;
		}

	}

	class endpoint
	{
	public:
		endpoint():_length(sizeof(_buffer)){}

		endpoint(const sockaddr* addr)
		{
			if(addr->sa_family == AF_INET)
			{
				_buffer.v4 = *(sockaddr_in*)addr;

				_length = sizeof(sockaddr_in);
			}
			else if(addr->sa_family == AF_INET6)
			{
				_buffer.v6 = *(sockaddr_in6*)addr;

				_length = sizeof(sockaddr_in6);
			}
		}

		endpoint(const sockaddr_in & rhs)
		{
			_buffer.v4 = rhs;

			_length = sizeof(sockaddr_in);
		}

		endpoint(const sockaddr_in6 & rhs)
		{
			_buffer.v6 = rhs;

			_length = sizeof(sockaddr_in6);
		}

		int af() const
		{
			return _buffer.addr.sa_family;
		}

		bool ipv4() const{return af() == AF_INET;}

		bool ipv6() const{return af() == AF_INET6;}

		v4::endpoint v4() const
		{
			return _buffer.v4;
		}

		v6::endpoint v6() const
		{
			return _buffer.v6;
		}

		const sockaddr * ptr() const
		{
			return &_buffer.addr;
		}

		sockaddr * ptr()
		{
			return &_buffer.addr;
		}

		const socklen_t & buffersize() const
		{
			return _length;
		}

		socklen_t & buffersize()
		{
			return _length;
		}

		size_t length() const
		{
			if(ipv4()) return sizeof(sockaddr_in);

			else return sizeof(sockaddr_in6);
		}

		bool operator == (const endpoint & ep) const
		{
			return _length == ep._length && memcmp(&_buffer,&ep._buffer,_length) == 0;
		}

	private:

		union{
			sockaddr		addr;

			sockaddr_in		v4;

			sockaddr_in6	v6;

		} _buffer;

		socklen_t			_length;
	};

}}}

#endif //LEMONXX_IO_ENDPOINT_HPP