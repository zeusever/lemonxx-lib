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
#include <lemonxx/sys/text.hpp>

namespace lemon{

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

		void check_throw(const lemon::char_t * errormessage)
		{
			if(LEMON_FAILED(*this))
			{
				error_msg(errormessage);

				throw *this;
			}
		}

	private:

		lemon::String				_message;
	};

	struct scope_error_info : public error_info
	{
		~scope_error_info()
		{
			check_throw();
		}
	};
}

#endif //LEMONXX_SYS_ERRORCODE_HPP