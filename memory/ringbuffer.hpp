/**
* 
* @file     ringbuffer
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012
*/
#ifndef LEMONXX_MEMORY_RINGBUFFER_HPP
#define LEMONXX_MEMORY_RINGBUFFER_HPP
#include <lemonxx/sys/sys.hpp>
#include <lemon/memory/ringbuffer.h>
#include <lemonxx/utility/utility.hpp>
#include <lemonxx/type_traits/type_traits.hpp>
#include <lemonxx/mpl/inttypes.hpp>
namespace lemon{namespace memory{namespace ringbuffer{



	template<bool Const>
	class basic_iterator 
		: public lemon::iterator_t<
		basic_iterator<Const>,
		typename lemon::conditional<Const,const void*,void*>::type,
		ptrdiff_t>
	{
	public:

		typedef typename lemon::conditional<Const,
			const void*,void*>::type							value_type;

		typedef std::forward_iterator_tag						iterator_category;

		basic_iterator()
			:_length(0),_iter(LEMON_HANDLE_NULL_VALUE),_buffer(LEMON_HANDLE_NULL_VALUE)
		{}

		template<bool C1>
		basic_iterator(const basic_iterator<C1> & rhs)
			:_length(rhs.length()),_iter(rhs.handle()),_buffer(rhs.buffer())
		{

		}

		basic_iterator(size_t length,LemonRingBuffer buffer,LemonRingBufferIterator iter)
			:_length(length),_iter(iter),_buffer(buffer)
		{}

		bool equal(const basic_iterator & rhs) const
		{
			return _length == rhs._length;
		}

		value_type dereference() const
		{
			return LemonRingBufferIteratorDereference(_iter);
		}


		void increment()
		{
			_iter = LemonRingBufferIteratorIncrement(_iter);

			-- _length;
		}

		void decrement()
		{
			_iter = LemonRingBufferIteratorDecrement(_iter);

			++ _length;
		}

		LemonRingBufferIterator handle() const {return _iter;}

		LemonRingBuffer buffer() const {return _buffer;}

		size_t	length() const { return _length; }

	private:

		size_t							_length;

		LemonRingBufferIterator			_iter;

		LemonRingBuffer					_buffer;
	};



	template<size_t BlockSize,size_t BlocksPerPage = 1024 * 1024 / BlockSize>
	class allocator : private nocopyable
	{
	public:
		typedef basic_iterator<true>					const_iterator;

		typedef basic_iterator<false>					iterator;

		typedef lemon::mpl::size_t_<BlockSize>			block_size;
	public:

		const_iterator front() const { return const_iterator(LemonRingBufferLength(_allocator),_allocator,LemonRingBufferFront(_allocator)); }

		const_iterator back() const { return const_iterator(1,_allocator,LemonRingBufferBack(_allocator)); }

		iterator front() { return iterator(LemonRingBufferLength(_allocator),_allocator,LemonRingBufferFront(_allocator)); }

		iterator back() { return iterator(1,_allocator,LemonRingBufferBack(_allocator)); }

		const_iterator end() const { return const_iterator(); }

		iterator end() { return iterator(); }

	public:
		allocator():_allocator(LEMON_HANDLE_NULL_VALUE) {}

		allocator(size_t blocks)
		{
			create(blocks);
		}

		void create(size_t blocks)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			_allocator = LemonCreateRingBuffer(blocks,BlockSize,BlocksPerPage,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
		}

		~allocator()
		{
			LemonReleaseRingBuffer(_allocator);
		}

		size_t capacity() const 
		{
			return LemonRingBufferCapacity(_allocator);
		}

		size_t length() const
		{
			return LemonRingBufferLength(_allocator);
		}

		bool empty() const {return 0 == length();}

		bool full() const {return length() == capacity();}

		void * push_front(bool &used)
		{
			used = full();

			return LemonRingBufferWriteFront(_allocator);
		}

		void * push_front(void * data,size_t dataLength)
		{
			bool used = full();

			void * target = LemonRingBufferWriteFront(_allocator);

			if(used) return target;

			memcpy(target,data,dataLength);

			return NULL;
		}

		void * push_back(bool &used)
		{
			used = full();

			return LemonRingBufferWriteBack(_allocator);
		}

		void * push_back(void * data,size_t dataLength)
		{
			bool used = full();

			void * target = LemonRingBufferWriteBack(_allocator);

			if(used) return target;

			memcpy(target,data,dataLength);

			return NULL;
		}

		void * pop_front()
		{
			return LemonRingBufferReadFront(_allocator);
		}

		void * pop_back()
		{
			return LemonRingBufferReadBack(_allocator);
		}

	private:

		LemonRingBuffer		_allocator;
	};

}}}
#endif // LEMONXX_MEMORY_RINGBUFFER_HPP
