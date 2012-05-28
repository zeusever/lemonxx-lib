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
#include <lemonxx/utility/nocopyable.hpp>
#include <lemonxx/sys/text.hpp>

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
			LEMON_DECLARE_ERRORINFO(errorCode);

			if(LEMON_CHECK_HANDLE(_lib)) LemonUnloadLibrary(_lib,&errorCode);
		}

		template<typename Func>
		Func get(const char* name)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			void * address = LemonGetProcAddress(_lib,name,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

			return reinterpret_cast<Func>(address);
		}

		void load(const lemon_char_t * path)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			_lib = LemonLoadLibrary(path,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
		}

		void load(const std::string & path)
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
