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

namespace lemon{

	inline std::ostream & operator << (std::ostream & stream,const LemonErrorInfo & errorCode)
	{
		 stream << "lemon error info :" << std::endl;

		 stream << "\terror code :" << errorCode.Error.Code << std::endl;

		 stream << "\terror catalog :" << uuid_t(*errorCode.Error.Catalog).tostring() << std::endl;

		 stream << "\traise file :" << errorCode.File << "(" << errorCode.Lines << ")" <<std::endl;

		 return stream;
	}

}

#endif //LEMONXX_SYS_ERRORCODE_HPP