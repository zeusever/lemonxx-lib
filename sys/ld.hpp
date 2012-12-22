/**
* 
* @file     ld
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/01/21
*/
#ifndef LEMON_CXX_SYS_LD_HPP
#define LEMON_CXX_SYS_LD_HPP
#include <string>
#include <lemon/sys/ld.h>
#include <lemonxx/sys/text.hpp>
#include <lemonxx/sys/converter.hpp>
#include <lemonxx/utility/nocopyable.hpp>

namespace lemon{
	class sharedlibrary : private nocopyable
	{
	public:

		sharedlibrary():_lib(LEMON_HANDLE_NULL_VALUE){}

		sharedlibrary(const lemon::String & path)
		{
			load(path.c_str());
		}

		~sharedlibrary()
		{
			error_info errorCode;

			if(LEMON_CHECK_HANDLE(_lib)) LemonUnloadLibrary(_lib,&errorCode);
		}

		template<typename Func>
		Func get(const char* name)
		{
			error_info errorCode;

			void * address = LemonGetProcAddress(_lib,name,&errorCode);

			errorCode.check_throw();

			return reinterpret_cast<Func>(address);
		}

		void load(const lemon_char_t * path)
		{
			error_info errorCode;

			_lib = LemonLoadLibrary(path,&errorCode);

			errorCode.check_throw();
		}
#ifdef WIN32
		void load(const std::string & path)
		{
			load(from_locale(path));
		}
#endif //WIN32
		void load(const String & path)
		{
			load(path.c_str());
		}

		bool loaded() const
		{
			return LEMON_CHECK_HANDLE(_lib);
		}

	private:
		LemonDLL _lib;
	};
}

#endif  //LEMON_CXX_SYS_LD_HPP
