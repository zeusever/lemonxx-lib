/**
* 
* @file     uuid
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/01/14
*/
#ifndef LEMON_CXX_SYS_UUID_HPP
#define LEMON_CXX_SYS_UUID_HPP
#include <string>
#include <lemon/sys/uuid.h>
#include <lemonxx/sys/exception.hpp>

namespace lemon{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	uuid_t
	///
	/// @brief	Uuid t. 
	///
	/// @author	Yuki
	/// @date	2012/1/14
	////////////////////////////////////////////////////////////////////////////////////////////////////

	class uuid_t : public LemonUuid
	{
	public:

		uuid_t()
		{
			LEMON_DECLARE_ERRORINFO(errorInfo);

			(LemonUuid&)*this = LemonUuidGenerate(&errorInfo);

			if(LEMON_FAILED(errorInfo)) throw Exception("call LemonUuidGenerate exception",errorInfo);
		}
		
		uuid_t(const LemonUuid & rhs)
		{
			memcpy(this,&rhs,sizeof(LemonUuid));
		}


		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	uuid_t(const char * source)
		///
		/// @brief	Constructor. 
		///
		/// @author	Yuki
		/// @date	2012/1/14
		///
		/// @param [in,out]	source	If non-null, source for the. 
		////////////////////////////////////////////////////////////////////////////////////////////////////

		uuid_t(const char * source) {fromstring(source);}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	uuid_t(const std::string & source)
		///
		/// @brief	Constructor. 
		///
		/// @author	Yuki
		/// @date	2012/1/14
		///
		/// @param	source	Source for the. 
		////////////////////////////////////////////////////////////////////////////////////////////////////

		uuid_t(const std::string & source) {fromstring(source.c_str());}

		std::string tostring() const
		{
			LEMON_DECLARE_ERRORINFO(errorInfo);

			char buffer[64] = {0};

			LemonUuidToString(this,buffer,sizeof(buffer),&errorInfo);

			if(LEMON_FAILED(errorInfo)) throw Exception("call LemonUuidToString exception",errorInfo);

			return buffer;
		}
		///////////////////////////////////////////////////////////////////
		//below is operator overload
		bool operator == (const uuid_t & rhs) const
		{
			return memcmp(this,&rhs,sizeof(uuid_t)) == 0;
		}

		bool operator != (const uuid_t & rhs) const 
		{
			return memcmp(this,&rhs,sizeof(uuid_t)) != 0;
		}

		bool operator > (const uuid_t & rhs) const 
		{
			return memcmp(this,&rhs,sizeof(uuid_t)) > 0;
		}

		bool operator < (const uuid_t & rhs) const 
		{
			return memcmp(this,&rhs,sizeof(uuid_t)) < 0;
		}

		bool operator >= (const uuid_t & rhs) const 
		{
			return memcmp(this,&rhs,sizeof(uuid_t)) >= 0;
		}

		bool operator <= (const uuid_t & rhs) const 
		{
			return memcmp(this,&rhs,sizeof(uuid_t)) <= 0;
		}

	private:

		void fromstring(const char * source)
		{
			LEMON_DECLARE_ERRORINFO(errorInfo);

			(LemonUuid&)*this = LemonUuidFromString(source,&errorInfo);

			if(LEMON_FAILED(errorInfo)) throw Exception("call LemonUuidFromString exception",errorInfo);
		}

		
	};
}
#endif //LEMON_CXX_SYS_UUID_HPP