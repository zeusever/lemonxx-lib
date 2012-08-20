/**
* 
* @file     ostream
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/08/20
*/
#ifndef LEMONXX_OSTREAM_HPP
#define LEMONXX_OSTREAM_HPP
#include <lemonxx/sys/uuid.hpp>
#include <lemonxx/sys/errorcode.hpp>
#include <lemonxx/sys/converter.hpp>
namespace lemon{

	inline std::ostream & operator << (std::ostream & stream,const LemonErrorInfo & errorCode)
	{
		stream << "lemon error info :" << std::endl;

		stream << "\terror code :" << errorCode.Error.Code << std::endl;

		stream << "\terror catalog :" << lemon::uuid_t(*errorCode.Error.Catalog).tostring() << std::endl;

		stream << "\traise file :" << errorCode.File << "(" << errorCode.Lines << ")" <<std::endl;

		return stream;
	}

	inline std::ostream & operator << (std::ostream & stream,const error_info & errorCode)
	{
		stream << "lemon error info :" << lemon::to_locale(errorCode.error_msg()) << std::endl;

		stream << "\terror code :" << errorCode.Error.Code << std::endl;

		stream << "\terror catalog :" << lemon::uuid_t(*errorCode.Error.Catalog).tostring() << std::endl;

		stream << "\traise file :" << errorCode.File << "(" << errorCode.Lines << ")" <<std::endl;

		return stream;
	}

}


#endif //LEMONXX_OSTREAM_HPP