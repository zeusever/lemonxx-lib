/**
* 
* @file     errorcode
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/02/22
*/
#ifndef LEMONXX_SYS_ERRORCODE_HPP
#define LEMONXX_SYS_ERRORCODE_HPP
#include <sstream>
#include <lemon/sys/abi.h>
#include <lemonxx/sys/uuid.hpp>
#include <lemonxx/sys/text.hpp>

namespace lemon{

	inline std::ostream & operator << (std::ostream & stream,const LemonErrorInfo & errorCode)
	{
		 stream << "lemon error info :" << std::endl;

		 stream << "\terror code :" << errorCode.Error.Code << std::endl;

		 stream << "\terror catalog :" << lemon::uuid_t(*errorCode.Error.Catalog).tostring() << std::endl;

		 stream << "\traise file :" << errorCode.File << "(" << errorCode.Lines << ")" <<std::endl;

		 return stream;
	}

	class error_info : public LemonErrorInfo
	{
	public:

		error_info() { reset(); }

		void reset() { LEMON_RESET_ERRORINFO(*this); _message.clear(); }

		const lemon::String & error_msg() const { return _message; }

		void error_msg(const lemon::String & message) { _message = message; }

		operator LemonErrorInfo * () { return this; }

		operator const LemonErrorInfo * () const { return this; }

		void check_throw()
		{
			if(LEMON_FAILED(*this)) throw *this;
		}

	private:

		lemon::String				_message;
	};

}

#endif //LEMONXX_SYS_ERRORCODE_HPP