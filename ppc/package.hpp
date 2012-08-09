/**
* 
* @file     package
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/08/06
*/
#ifndef LEMONXX_PPC_PACKAGE_HPP
#define LEMONXX_PPC_PACKAGE_HPP
#include <lemon/ppc/abi.h>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>

namespace lemon{namespace ppc{

	class package : public basic_handle_object<LemonPPCPackage,&LemonClosePPC>
	{
	public:

		typedef basic_handle_object<LemonPPCPackage,&LemonClosePPC>		base_type;
		
		package(const lemon::char_t * path) : base_type(create(path))
		{

		}

		package(const lemon::String &path) : base_type(create(path.c_str()))
		{

		}

		void scan(const lemon::char_t * cxxsource,const lemon::char_t * cxxgen)
		{
			error_info errorCode;

			LemonPPCScanFile(*this,cxxsource,cxxgen,&errorCode);

			errorCode.check_throw();
		}

		void write(const lemon::char_t * object)
		{
			error_info errorCode;

			LemonGeneratePPC(*this,object,&errorCode);

			errorCode.check_throw();
		}

		const lemon::char_t * name()
		{
			error_info errorCode;

			const lemon::char_t * val = LemonPPCPackageName(*this,&errorCode);

			errorCode.check_throw();

			return val;
		}

	public:

	    static LemonPPCPackage create(const lemon::char_t * path)
		{
			error_info errorCode;

			LemonPPCPackage handle = LemonCreatePPC(path,&errorCode);

			errorCode.check_throw();

			return handle;
		}
	};

}}

#endif //LEMONXX_PPC_PACKAGE_HPP