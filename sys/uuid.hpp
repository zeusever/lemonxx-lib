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
#include <lemonxx/sys/errorcode.hpp>

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
			error_info errorCode;

			(LemonUuid&)*this = LemonUuidGenerate(errorCode);

			errorCode.check_throw();
		}
		
		explicit uuid_t(const LemonUuid & rhs)
		{
			memcpy(this,&rhs,sizeof(LemonUuid));
		}

		uuid_t & operator = (const LemonUuid & rhs)
		{
			memcpy(this,&rhs,sizeof(LemonUuid));

			return *this;
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
			error_info errorCode;

			char buffer[64] = {0};

			LemonUuidToString(this,buffer,sizeof(buffer),&errorCode);

			errorCode.check_throw();

			return buffer;
		}
		///////////////////////////////////////////////////////////////////
		//below is operator overload
		bool operator == (const LemonUuid & rhs) const
		{
			return memcmp(this,&rhs,sizeof(uuid_t)) == 0;
		}

		bool operator != (const LemonUuid & rhs) const 
		{
			return memcmp(this,&rhs,sizeof(uuid_t)) != 0;
		}

		bool operator > (const LemonUuid & rhs) const 
		{
			return memcmp(this,&rhs,sizeof(uuid_t)) > 0;
		}

		bool operator < (const LemonUuid & rhs) const 
		{
			return memcmp(this,&rhs,sizeof(uuid_t)) < 0;
		}

		bool operator >= (const LemonUuid & rhs) const 
		{
			return memcmp(this,&rhs,sizeof(uuid_t)) >= 0;
		}

		bool operator <= (const LemonUuid & rhs) const 
		{
			return memcmp(this,&rhs,sizeof(uuid_t)) <= 0;
		}

	private:

		void fromstring(const char * source)
		{
			error_info errorCode;

			(LemonUuid&)*this = LemonUuidFromString(source,errorCode);

			errorCode.check_throw();
		}

		
	};
}
#endif //LEMON_CXX_SYS_UUID_HPP