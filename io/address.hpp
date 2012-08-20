/**
* 
* @file     address
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/02/18
*/
#ifndef LEMONXX_IO_ADDRESS_HPP
#define LEMONXX_IO_ADDRESS_HPP
#include <string>
#include <lemon/io/address.h>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>

namespace lemon{namespace io{namespace ip{

	namespace v4{

		class address : public in_addr
		{
		public:

			address(){}
		
			address(const in_addr & rhs)
			{
				memcpy(this,&rhs,sizeof(rhs));
			}
		
			static address from(const char * source)
			{
				error_info errorCode;

				address addr;

				LemonAddressFromString(AF_INET,source,strlen(source),&addr,sizeof(addr),&errorCode);

				errorCode.check_throw();

				return addr;
			}

			std::string string() const
			{
				error_info errorCode;

				char buffer[sizeof("255.255.255.255")];

				LemonAddressToString(AF_INET,(void*)this,sizeof(in_addr),buffer,sizeof(buffer),&errorCode);

				errorCode.check_throw();

				return buffer;
			}


			inline bool operator == (const address & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) == 0;
			}

			inline bool operator != (const address & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) != 0;
			}

			inline bool operator > (const address & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) > 0;
			}

			inline bool operator < (const address & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) < 0;
			}


			inline bool operator >= (const address & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) >= 0;
			}

			inline bool operator <= (const address & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) <= 0;
			}

			inline bool operator == (const in_addr & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) == 0;
			}

			inline bool operator != (const in_addr & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) != 0;
			}

			inline bool operator > (const in_addr & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) > 0;
			}

			inline bool operator < (const in_addr & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) < 0;
			}


			inline bool operator >= (const in_addr & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) >= 0;
			}

			inline bool operator <= (const in_addr & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) <= 0;
			}
		};

		inline bool operator == (const in_addr & lhs,const address & rhs)
		{
			return memcmp(&lhs,&rhs,sizeof(rhs)) == 0;
		}

		inline bool operator != (const in_addr & lhs,const address & rhs)
		{
			return memcmp(&lhs,&rhs,sizeof(rhs)) != 0;
		}

		inline bool operator > (const in_addr & lhs,const address & rhs)
		{
			return memcmp(&lhs,&rhs,sizeof(rhs)) > 0;
		}

		inline bool operator < (const in_addr & lhs,const address & rhs)
		{
			return memcmp(&lhs,&rhs,sizeof(rhs)) < 0;
		}


		inline bool operator >= (const in_addr & lhs,const address & rhs)
		{
			return memcmp(&lhs,&rhs,sizeof(rhs)) >= 0;
		}

		inline bool operator <= (const in_addr & lhs,const address & rhs)
		{
			return memcmp(&lhs,&rhs,sizeof(rhs)) <= 0;
		}

	}





	namespace v6{

		class address : public in6_addr
		{
		public:

			address(){}

			address(const in6_addr & rhs)
			{
				memcpy(this,&rhs,sizeof(rhs));
			}

			static address from(const char * source)
			{
				error_info errorCode;

				address addr;

				LemonAddressFromString(AF_INET6,source,strlen(source),&addr,sizeof(addr),&errorCode);

				errorCode.check_throw();

				return addr;
			}

			std::string string() const
			{
				error_info errorCode;

				char buffer[sizeof("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255")];

				LemonAddressToString(AF_INET6,(void*)this,sizeof(in6_addr),buffer,sizeof(buffer),&errorCode);

				errorCode.check_throw();

				return buffer;
			}


			inline bool operator == (const address & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) == 0;
			}

			inline bool operator != (const address & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) != 0;
			}

			inline bool operator > (const address & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) > 0;
			}

			inline bool operator < (const address & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) < 0;
			}


			inline bool operator >= (const address & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) >= 0;
			}

			inline bool operator <= (const address & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) <= 0;
			}

			inline bool operator == (const in6_addr & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) == 0;
			}

			inline bool operator != (const in6_addr & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) != 0;
			}

			inline bool operator > (const in6_addr & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) > 0;
			}

			inline bool operator < (const in6_addr & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) < 0;
			}


			inline bool operator >= (const in6_addr & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) >= 0;
			}

			inline bool operator <= (const in6_addr & rhs) const
			{
				return memcmp(this,&rhs,sizeof(rhs)) <= 0;
			}
		};

		inline bool operator == (const in6_addr & lhs,const address & rhs)
		{
			return memcmp(&lhs,&rhs,sizeof(rhs)) == 0;
		}

		inline bool operator != (const in6_addr & lhs,const address & rhs)
		{
			return memcmp(&lhs,&rhs,sizeof(rhs)) != 0;
		}

		inline bool operator > (const in6_addr & lhs,const address & rhs)
		{
			return memcmp(&lhs,&rhs,sizeof(rhs)) > 0;
		}

		inline bool operator < (const in6_addr & lhs,const address & rhs)
		{
			return memcmp(&lhs,&rhs,sizeof(rhs)) < 0;
		}


		inline bool operator >= (const in6_addr & lhs,const address & rhs)
		{
			return memcmp(&lhs,&rhs,sizeof(rhs)) >= 0;
		}

		inline bool operator <= (const in6_addr & lhs,const address & rhs)
		{
			return memcmp(&lhs,&rhs,sizeof(rhs)) <= 0;
		}

	}


	class address
	{
	public:
		address(){}

		address(const in6_addr & addr)
			:_af(AF_INET6)
		{
			_buffer.v6 = addr;
		}

		address(const in_addr & addr)
			:_af(AF_INET)
		{
			_buffer.v4 = addr;
		}

		int af() const
		{
			return _af;
		}

		bool ipv4() const{return _af == AF_INET;}

		bool ipv6() const{return _af == AF_INET6;}

		v4::address v4() const
		{
			return _buffer.v4;
		}

		v6::address v6() const
		{
			return _buffer.v6;
		}

		size_t length() const
		{
			if(ipv4()) return sizeof(in_addr);

			else return sizeof(in6_addr);
		}

	private:

		union{

			in_addr v4;

			in6_addr v6;

		} _buffer;

		int _af;
	};

	inline bool operator < (const address & lhs,const address & rhs)
	{
		if(lhs.length() != rhs.length())
		{
			return lhs.length() < rhs.length();
		}
		else
		{
			return memcmp(&lhs,&rhs,lhs.length()) < 0;
		}

		
	}

	inline bool operator == (const address & lhs,const address & rhs)
	{
		return (lhs.ipv4() == lhs.ipv4()) && (memcmp(&lhs,&rhs,lhs.length()) == 0);
	}

}}}

#endif //LEMONXX_IO_ADDRESS_HPP
