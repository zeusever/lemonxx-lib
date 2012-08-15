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

#include <list>
#include <stack>
#include <string>
#include <sstream>
#include <algorithm>

#include <lemon/sys/filesystem.h>
#include <lemonxx/utility/utility.hpp>
#include <lemonxx/sys/text.hpp>


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


	//////////////////////////////////////////////////////////////////////////

	class path
	{
	public:

		typedef std::list<lemon::String>			nodes_type;

		typedef nodes_type::iterator				iterator;

		typedef nodes_type::const_iterator			const_iterator;

		path() {}
		
		explicit path(const lemon::String & source)
		{
			lemon::String newsource = string_replaceall<lemon::char_t>(source,LEMON_TEXT("\\"),LEMON_TEXT("/"));

			lemon::String::size_type offset = 0,start;

			offset = newsource.find(LEMON_TEXT('/'),offset);

			if(offset != 0) _root = newsource.substr(0,offset);

			start = offset + 1;

			while(start < newsource.length() && (offset = newsource.find(LEMON_TEXT('/'),start)) != lemon::String::npos)
			{
				if(offset -  start > 0) { _nodes.push_back(newsource.substr(start ,offset - start)); }

				start = offset + 1;
			}

			if(start < newsource.length())
			{
				_nodes.push_back(newsource.substr(start));
			}
		}

		template<typename Iterator>
		path(Iterator begin,Iterator end) :_nodes(begin,end) {}

		template<typename Iterator>
		path(const lemon::String & root,Iterator begin,Iterator end) :_root(root),_nodes(begin,end) {}

		const lemon::String & root() const { return _root; }

		void root(const lemon::String & val) {_root = val;}

		const lemon::String leaf() const 
		{
			if(has_leaf()) return _nodes.back();

			return lemon::String();
		}

		bool has_leaf() const { return !_nodes.empty(); }

		bool relative_path() const { return _root == LEMON_TEXT(".") || _root == LEMON_TEXT(".."); }

		iterator begin() { return _nodes.begin(); }

		iterator end() { return _nodes.end(); }

		const_iterator begin() const { return _nodes.begin(); }

		const_iterator end() const { return _nodes.end(); }

		lemon::String native() const
		{
#ifdef WIN32
			return tostring(LEMON_TEXT('\\'));
#else
			return tostring(LEMON_TEXT('/'));
#endif //WIN32
		}

		lemon::String string() const
		{
			return tostring(LEMON_TEXT('/'));
		}

		void compress()
		{
			iterator iter,end = _nodes.end();

			for(iter = _nodes.begin(); iter != end;)
			{
				if(*iter == LEMON_TEXT("..") && iter != _nodes.begin())
				{
					iterator begin = iter;

					iter = _nodes.erase(-- begin,++ iter);

					continue;
				}
				else if(*iter == LEMON_TEXT("."))
				{
					iter = _nodes.erase(iter);

					continue;
				}


				++ iter;
			}

		}

		path parent() const
		{
			if(empty()) return path();

			else
			{
				if(_nodes.empty()) return path(_root);

				return path(_root,_nodes.begin(),-- _nodes.end());
			}
		}

		bool empty() const {return _root.empty() && _nodes.empty(); }

		path & operator / (const lemon::char_t * node)
		{
			_nodes.push_back(node);

			return *this;
		}

		path & operator / (const path & rhs)
		{
			_nodes.insert(_nodes.end(),rhs.begin(),rhs.end());

			return *this;
		}

		bool operator == (const fs::path & rhs) const
		{
			return _root == rhs._root && _nodes ==  rhs._nodes;
		}

	private:

		lemon::String tostring(lemon::char_t splitchar) const
		{
			lemon::StringStream stream;

			stream << _root;

			const_iterator iter,end = _nodes.end();

			for(iter = _nodes.begin(); iter != end; ++ iter) stream << splitchar << *iter;

			return stream.str();
		}

	private:

		lemon::String		_root;

		nodes_type			_nodes;
	};

	inline lemon::String extension(const fs::path & source)
	{
		if(!source.has_leaf()) return lemon::String();

		lemon::String leaf = source.leaf();

		lemon::String::size_type offset = leaf.rfind(LEMON_TEXT('.')) + 1;

		if(offset < leaf.length())
		{
			return leaf.substr(offset);
		}
		else
		{
			return LEMON_TEXT("");
		}
	}

	inline lemon::String extension(const lemon::String & source)
	{
		return extension(path(source));
	}

	inline fs::path relative(fs::path lhs,fs::path rhs)
	{
		lhs.compress();rhs.compress();

		if(lhs.relative_path() || lhs.relative_path()) return fs::path();

		if(lhs.root() !=  rhs.root()) return fs::path();

		fs::path::const_iterator iter1 = lhs.begin(),iter2 = rhs.begin(),end1 = lhs.end(),end2 = rhs.end();

		for(;iter1 != end1 && iter2 != end2; ++ iter1,++ iter2) if(*iter1 != *iter2) break;
		
		size_t counter = std::distance(iter1,end1);

		fs::path result;

		if(counter > 0)
		{
			result.root(LEMON_TEXT(".."));

			-- counter;

			for(size_t i = 0 ; i < counter ; ++ i) result / LEMON_TEXT("..");
		}
		else
		{
			result.root(LEMON_TEXT("."));
		}


		return result / fs::path(iter2,end2);

	}
}}

#endif //LEMONXX_SYS_FILESYSTEM_HPP
