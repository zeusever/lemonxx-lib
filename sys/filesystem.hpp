/**
* 
* @file     filesystem
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/05/30
*/
#ifndef LEMONXX_SYS_FILESYSTEM_HPP
#define LEMONXX_SYS_FILESYSTEM_HPP

#include <stack>
#include <string>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>

#include <lemon/sys/filesystem.h>

namespace lemon{namespace fs{
	inline String current_directory()
	{
		LemonErrorInfo errorCode;

		lemon_char_t buffer[LEMON_MAX_PATH];

		LemonGetCurrentDirectory(buffer,LEMON_MAX_PATH,&errorCode);

		if(LEMON_FAILED(errorCode)) throw lemon::Exception(errorCode);

		return buffer;
	}

	inline void current_directory(const String& current)
	{
		LemonErrorInfo errorCode;

		LemonSetCurrentDirectory(current.c_str(),&errorCode);

		if(LEMON_FAILED(errorCode)) throw lemon::Exception(errorCode);
	}

	inline void remove_directory(const String& dir)
	{
		LemonErrorInfo errorCode;

		LemonRemoveDirectory(dir.c_str(),&errorCode);

		if(LEMON_FAILED(errorCode)) throw lemon::Exception(errorCode);

	}

	inline void create_directory(const String& dir)
	{
		LemonErrorInfo errorCode;

		LemonCreateDirectory(dir.c_str(),&errorCode);

		if(LEMON_FAILED(errorCode)) throw lemon::Exception(errorCode);
	}

	inline bool is_directory(const String & dir)
	{
		LemonErrorInfo errorCode;

		lemon_bool result = LemonIsDirectory(dir.c_str(),&errorCode);

		if(LEMON_FAILED(errorCode)) throw lemon::Exception(errorCode);

		return result?true:false;
	}

	inline bool exists(const String & current)
	{
		LemonErrorInfo errorCode;

		lemon_bool result = LemonCheckFileExist(current.c_str(),&errorCode);

		if(LEMON_FAILED(errorCode)) throw lemon::Exception(errorCode);

		return result?true:false;
	}

	inline void remove_file(const String & file)
	{
		LemonErrorInfo errorCode;

		LemonDeleteFile(file.c_str(),&errorCode);

		if(!LEMON_SUCCESS(errorCode)) throw lemon::Exception(errorCode);
	}

	inline void copy(const String & source,const String & target)
	{
		LemonErrorInfo errorCode;

		LemonCopyFile(source.c_str(),target.c_str(),&errorCode);

		if(!LEMON_SUCCESS(errorCode)) throw lemon::Exception(errorCode);
	}

	inline void move(const String & source,const String & target)
	{
		LemonErrorInfo errorCode;

		LemonMoveFile(source.c_str(),target.c_str(),&errorCode);

		if(!LEMON_SUCCESS(errorCode)) throw lemon::Exception(errorCode);
	}

	class directory_iteartor_t 
		: public iterator_t<directory_iteartor_t,const String,ptrdiff_t> 
		, lemon::nocopyable
	{
	public:
		directory_iteartor_t()
			:_enumerator(LEMON_HANDLE_NULL_VALUE)
		{

		}

		directory_iteartor_t(const String& directory)
		{
			LemonErrorInfo errorCode;

			_enumerator = LemonCreateDirectoryEnumerator(directory.c_str(),&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

			increment();
		}

		~directory_iteartor_t()
		{
			if(_enumerator) LemonCloseDirectoryEnumerator(_enumerator);
		}

		bool equal(const directory_iteartor_t & rhs) const
		{
			return _enumerator == rhs._enumerator;
		}

		const String& dereference() const
		{
			return _current;
		}

		const String * ptr()
		{
			return &_current;
		}

		void increment()
		{
			LemonErrorInfo errorCode;

			const lemon_char_t * next  = LemonDirectoryEnumeratorNextItem(_enumerator,&errorCode);

			if(!LEMON_SUCCESS(errorCode)) throw lemon::Exception(errorCode);

			if(!next)
			{

				LemonCloseDirectoryEnumerator(_enumerator);

				_enumerator = LEMON_HANDLE_NULL_VALUE;
			}
			else
			{
				_current = next;
			}
		}

	private:

		String				_current;

		LemonDirectoryEnumerator _enumerator;
	};

	inline bool is_empty(const String& dir)
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


	inline void remove_directories(const String& dir)
	{
		std::stack<String> directories;

		directories.push(dir);

		while(!directories.empty())
		{
			String	current = directories.top();

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

				String path = current + LEMON_TEXT("/") + *iter;

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

#endif //LEMONXX_SYS_FILESYSTEM_HPP
