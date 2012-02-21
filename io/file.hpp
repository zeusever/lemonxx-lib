/**
* 
* @file     file
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/02/21
*/
#ifndef LEMONXX_IO_FILE_HPP
#define LEMONXX_IO_FILE_HPP
#include <string>
#include <stack>
#include <lemon/io/file.h>
#include <lemonxx/io/io_device.hpp>
#include <lemonxx/io/object.hpp>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>

namespace lemon{namespace io{

	class file : public basic_object<LemonFile,&LemonCloseFile>
	{
	public:
		typedef basic_object<LemonFile,&LemonCloseFile> base_type;

		file(
			const char * name,
			LemonFileDesiredAccess desiredAccess,
			LemonFileShareMode shareMode,
			LemonFileCreationDisposition createionDisposition)
			:base_type(Create(name,desiredAccess,shareMode,createionDisposition,LEMON_HANDLE_NULL_VALUE))
		{

		}

		file(
			const char * name,
			LemonFileDesiredAccess desiredAccess,
			LemonFileCreationDisposition createionDisposition)
			:base_type(Create(name,desiredAccess,(LemonFileShareMode)0,createionDisposition,LEMON_HANDLE_NULL_VALUE))
		{

		}

		file(const char * name,LemonFileCreationDisposition createionDisposition)
			:base_type(Create(name,LEMON_FILE_ALL,(LemonFileShareMode)0,createionDisposition,LEMON_HANDLE_NULL_VALUE))
		{

		}

		file(const char * name)
			:base_type(Create(name,LEMON_FILE_ALL,(LemonFileShareMode)0,LEMON_FILE_OPEN_EXISTING,LEMON_HANDLE_NULL_VALUE))
		{

		}


		file(
			const char * name,
			LemonFileDesiredAccess desiredAccess,
			LemonFileShareMode shareMode,
			LemonFileCreationDisposition createionDisposition,io_device & device)
			:base_type(Create(name,desiredAccess,shareMode,createionDisposition,device))
		{

		}

		file(
			const char * name,
			LemonFileDesiredAccess desiredAccess,
			LemonFileCreationDisposition createionDisposition,io_device & device)
			:base_type(Create(name,desiredAccess,(LemonFileShareMode)0,createionDisposition,device))
		{

		}

		file(const char * name,LemonFileCreationDisposition createionDisposition,io_device & device)
			:base_type(Create(name,LEMON_FILE_ALL,(LemonFileShareMode)0,createionDisposition,device))
		{

		}

		file(const char * name,io_device & device)
			:base_type(Create(name,LEMON_FILE_ALL,(LemonFileShareMode)0,LEMON_FILE_OPEN_EXISTING,device))
		{

		}


	private:
		static LemonFile Create(
			const char * name,
			LemonFileDesiredAccess desiredAccess,
			LemonFileShareMode shareMode,
			LemonFileCreationDisposition createionDisposition,
			LemonIoDevice device)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonFile file = LemonCreateFile(name,desiredAccess,shareMode,createionDisposition,device,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

			return file;
		}
	};
}}

namespace lemon{namespace io{


	inline std::string current_directory()
	{
		LemonErrorInfo errorCode;

		char buffer[MAX_PATH];

		LemonGetCurrentDirectory(buffer,MAX_PATH,&errorCode);

		if(LEMON_FAILED(errorCode)) throw lemon::Exception(errorCode);
	
		return buffer;
	}

	inline void current_directory(const std::string& current)
	{
		LemonErrorInfo errorCode;

		LemonSetCurrentDirectory(current.c_str(),&errorCode);

		if(LEMON_FAILED(errorCode)) throw lemon::Exception(errorCode);
	}

	inline void remove_directory(const std::string& dir)
	{
		LemonErrorInfo errorCode;

		LemonRemoveDirectory(dir.c_str(),&errorCode);

		if(LEMON_FAILED(errorCode)) throw lemon::Exception(errorCode);
	
	}

	inline void create_directory(const std::string& dir)
	{
		LemonErrorInfo errorCode;

		LemonCreateDirectory(dir.c_str(),&errorCode);

		if(LEMON_FAILED(errorCode)) throw lemon::Exception(errorCode);
	}

	inline bool is_directory(const std::string & dir)
	{
		LemonErrorInfo errorCode;

		lemon_bool result = LemonIsDirectory(dir.c_str(),&errorCode);

		if(LEMON_FAILED(errorCode)) throw lemon::Exception(errorCode);

		return result?true:false;
	}

	inline bool exists(const std::string & current)
	{
		LemonErrorInfo errorCode;

		lemon_bool result = LemonCheckFileExist(current.c_str(),&errorCode);

		if(LEMON_FAILED(errorCode)) throw lemon::Exception(errorCode);

		return result?true:false;
	}

	inline void remove_file(const std::string & file)
	{
		LemonErrorInfo errorCode;

		LemonDeleteFile(file.c_str(),&errorCode);

		if(!LEMON_SUCCESS(errorCode)) throw lemon::Exception(errorCode);
	}

	inline void move(const std::string & source,const std::string & target)
	{
		LemonErrorInfo errorCode;

		LemonMoveFile(source.c_str(),target.c_str(),&errorCode);

		if(!LEMON_SUCCESS(errorCode)) throw lemon::Exception(errorCode);
	}

	class directory_iteartor_t 
		: public iterator_t<directory_iteartor_t,const std::string,ptrdiff_t> 
		, lemon::nocopyable
	{
	public:
		directory_iteartor_t()
			:_enumerator(LEMON_HANDLE_NULL_VALUE)
		{

		}

		directory_iteartor_t(const std::string& directory)
		{
			LemonErrorInfo errorCode;

			_enumerator = LemonDirectoryChildren(directory.c_str(),&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

			increment();
		}

		~directory_iteartor_t()
		{
			if(_enumerator) LemonReleaseDirectoryEnumerator(_enumerator);
		}

		bool equal(const directory_iteartor_t & rhs) const
		{
			return _enumerator == rhs._enumerator;
		}

		const std::string& dereference() const
		{
			return _current;
		}

		const std::string * ptr()
		{
			return &_current;
		}

		void increment()
		{
			LemonErrorInfo errorCode;

			const char * next  = LemonDirectoryEnumeratorNext(_enumerator,&errorCode);

			if(!LEMON_SUCCESS(errorCode)) throw lemon::Exception(errorCode);

			if(!next)
			{

				LemonReleaseDirectoryEnumerator(_enumerator);

				_enumerator = LEMON_HANDLE_NULL_VALUE;
			}
			else
			{
				_current = next;
			}
		}

	private:

		std::string				_current;

		LemonDirectoryEnumerator _enumerator;
	};

	inline bool is_empty(const std::string& dir)
	{
		directory_iteartor_t iter(dir.c_str()),end;

		for(;iter != end; ++ iter)
		{
			if("." == *iter) continue;

			if(".." == *iter) continue;

			return false;
		}

		return true;
	}


	inline void remove_directories(const std::string& dir)
	{
		std::stack<std::string> directories;

		directories.push(dir);

		while(!directories.empty())
		{
			std::string	current = directories.top();

			if(is_empty(current))
			{
				remove_directory(current);

				directories.pop();

				continue;
			}

			directory_iteartor_t iter(current),end;

			for(;iter != end; ++ iter)
			{
				if("." == *iter) continue;

				if(".." == *iter) continue;

				std::string path = current + "/" + *iter;

				if(is_directory(path))
				{
					if(is_empty(path)) remove_directory(path);

					else directories.push(path);
				}
				else
				{
					remove_file(path);
				}
			}
		}
	}


}}

#endif //LEMONXX_IO_FILE_HPP