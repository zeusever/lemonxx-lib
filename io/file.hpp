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
#include <lemon/io/filesystem.h>
#include <lemonxx/io/io_device.hpp>
#include <lemonxx/io/object.hpp>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>

namespace lemon{namespace io{


	inline systring current_directory()
	{
		LemonErrorInfo errorCode;

		lemon_syschar_t buffer[LEMON_MAX_PATH];

		LemonGetCurrentDirectory(buffer,LEMON_MAX_PATH,&errorCode);

		if(LEMON_FAILED(errorCode)) throw lemon::Exception(errorCode);
	
		return buffer;
	}

	inline void current_directory(const systring& current)
	{
		LemonErrorInfo errorCode;

		LemonSetCurrentDirectory(current.c_str(),&errorCode);

		if(LEMON_FAILED(errorCode)) throw lemon::Exception(errorCode);
	}

	inline void remove_directory(const systring& dir)
	{
		LemonErrorInfo errorCode;

		LemonRemoveDirectory(dir.c_str(),&errorCode);

		if(LEMON_FAILED(errorCode)) throw lemon::Exception(errorCode);
	
	}

	inline void create_directory(const systring& dir)
	{
		LemonErrorInfo errorCode;

		LemonCreateDirectory(dir.c_str(),&errorCode);

		if(LEMON_FAILED(errorCode)) throw lemon::Exception(errorCode);
	}

	inline bool is_directory(const systring & dir)
	{
		LemonErrorInfo errorCode;

		lemon_bool result = LemonIsDirectory(dir.c_str(),&errorCode);

		if(LEMON_FAILED(errorCode)) throw lemon::Exception(errorCode);

		return result?true:false;
	}

	inline bool exists(const systring & current)
	{
		LemonErrorInfo errorCode;

		lemon_bool result = LemonCheckFileExist(current.c_str(),&errorCode);

		if(LEMON_FAILED(errorCode)) throw lemon::Exception(errorCode);

		return result?true:false;
	}

	inline void remove_file(const systring & file)
	{
		LemonErrorInfo errorCode;

		LemonDeleteFile(file.c_str(),&errorCode);

		if(!LEMON_SUCCESS(errorCode)) throw lemon::Exception(errorCode);
	}

	inline void move(const systring & source,const systring & target)
	{
		LemonErrorInfo errorCode;

		LemonMoveFile(source.c_str(),target.c_str(),&errorCode);

		if(!LEMON_SUCCESS(errorCode)) throw lemon::Exception(errorCode);
	}

	class directory_iteartor_t 
		: public iterator_t<directory_iteartor_t,const systring,ptrdiff_t> 
		, lemon::nocopyable
	{
	public:
		directory_iteartor_t()
			:_enumerator(LEMON_HANDLE_NULL_VALUE)
		{

		}

		directory_iteartor_t(const systring& directory)
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

		const systring& dereference() const
		{
			return _current;
		}

		const systring * ptr()
		{
			return &_current;
		}

		void increment()
		{
			LemonErrorInfo errorCode;

			const lemon_syschar_t * next  = LemonDirectoryEnumeratorNext(_enumerator,&errorCode);

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

		systring				_current;

		LemonDirectoryEnumerator _enumerator;
	};

	inline bool is_empty(const systring& dir)
	{
		directory_iteartor_t iter(dir.c_str()),end;

		for(;iter != end; ++ iter)
		{
			if(LEMON_TEXT(".") == *iter) continue;

			if(LEMON_TEXT("..") == *iter) continue;

			return false;
		}

		return true;
	}


	inline void remove_directories(const systring& dir)
	{
		std::stack<systring> directories;

		directories.push(dir);

		while(!directories.empty())
		{
			systring	current = directories.top();

			if(is_empty(current))
			{
				remove_directory(current);

				directories.pop();

				continue;
			}

			directory_iteartor_t iter(current),end;

			for(;iter != end; ++ iter)
			{
				if(LEMON_TEXT(".") == *iter) continue;

				if(LEMON_TEXT("..") == *iter) continue;

				systring path = current + LEMON_TEXT("/") + *iter;

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
