/**
* 
* @file     exception
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/01/14
*/
#ifndef LEMON_CXX_SYS_EXCEPTION_HPP
#define LEMON_CXX_SYS_EXCEPTION_HPP

#include <stdexcept>
#include <lemon/sys/abi.h>

namespace lemon{
	
	class Exception : public std::runtime_error
	{
	public:

		Exception(const LemonErrorInfo & ec)
			:std::runtime_error("lemon exception"),_ec(ec)
		{

		}
		Exception(const std::string & message,const LemonErrorInfo & ec)
			:std::runtime_error(message),_ec(ec)
		{

		}
		const LemonErrorInfo & ErrorInfo() const {return _ec;}
	private:
		LemonErrorInfo _ec;
	};

}

#endif //LEMON_CXX_SYS_EXCEPTION_HPP