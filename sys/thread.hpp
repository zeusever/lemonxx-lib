/**
* 
* @file     thread
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/01/19
*/
#ifndef LEMON_CXX_SYS_THREAD_HPP
#define LEMON_CXX_SYS_THREAD_HPP

#include <lemon/sys/thread.h>
#include <lemonxx/sys/exception.hpp>
#include <lemonxx/utility/utility.hpp>
#include <lemonxx/function/function.hpp>
#include <lemonxx/sys/inttypes.hpp>

namespace lemon{

	template<typename T>
	class tlsptr : private nocopyable
	{
	private:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	static void Destructor(void * T)
		///
		/// @brief	Default destructor of T
		///
		/// @author	Yayanyang
		/// @date	2011/12/15
		///
		/// @param [in,out]	T	If non-null, the. 
		////////////////////////////////////////////////////////////////////////////////////////////////////

		static void Destructor(void * data)
		{
			delete ((T*)data);
		}

	public:

		tlsptr()
		{
			LEMON_DECLARE_ERRORINFO(errorcode);

			_tls = LemonCreateTls(&tlsptr<T>::Destructor,&errorcode);

			if(LEMON_FAILED(errorcode))
			{
				throw Exception(errorcode);
			}
		}

		tlsptr(void(*destructor)(void*))
		{
			LEMON_DECLARE_ERRORINFO(errorcode);

			_tls = LemonCreateTls(destructor,&errorcode);

			if(LEMON_FAILED(errorcode))
			{
				throw Exception(errorcode);
			}
		}

		~tlsptr()
		{
			//LEMON_STATIC_ASSERT((!is_pointer<T>::value),"T must not a pointer type");

			LemonReleaseTls(_tls);
		}

		void set(T * val)
		{
			LEMON_DECLARE_ERRORINFO(errorcode);

			LemonTlsSet(_tls,val,&errorcode);

			if(LEMON_FAILED(errorcode))
			{
				throw Exception(errorcode);
			}
		}

		T * get() const
		{
			LEMON_DECLARE_ERRORINFO(errorcode);

			void * data = LemonTlsGet(_tls,&errorcode);

			if (LEMON_FAILED(errorcode))
			{
				throw Exception(errorcode);
			}

			return reinterpret_cast<T*>(data);
		}

		bool empty() const{return NULL  == get();}

		T* operator -> () const
		{
			return get();
		}

		T & operator * () const
		{
			return *get();
		}

		T * reset(T * newValue)
		{
			T * old = get();

			set(newValue);

			return old;
		}

		T * release()
		{
			return reset(NULL);
		}

	private:
		LemonTls _tls;
	};

	inline lemon_thread_id_t current_thread_id()
	{
		LEMON_DECLARE_ERRORINFO(errorinfo);

		lemon_thread_id_t id = LemonGetCurrentThreadId(&errorinfo);

		if(LEMON_FAILED(errorinfo)) throw Exception(errorinfo);

		return id;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	thread_t
	///
	/// @brief	The Thread Class
	///
	/// @author	Yuki
	/// @date	2012/1/19
	////////////////////////////////////////////////////////////////////////////////////////////////////

	class thread_t : private nocopyable
	{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @property	typedef func_t<void()> proc_type
		///
		/// @brief	 the type of the thread process function. 
		///
		////////////////////////////////////////////////////////////////////////////////////////////////////
		typedef function<void()> proc_type;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	thread_t()
		///
		/// @brief	Default constructor. 
		///
		/// @author	Yuki
		/// @date	2012/1/19
		////////////////////////////////////////////////////////////////////////////////////////////////////

		thread_t()
			:_thread(LEMON_HANDLE_NULL_VALUE)
		{}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	thread_t()
		///
		/// @brief	Default constructor. 
		///
		/// @author	Yuki
		/// @date	2012/1/19
		///
		/// @exception	Exception	Thrown when . 
		////////////////////////////////////////////////////////////////////////////////////////////////////

		thread_t(const proc_type & proc)
			:_thread(LEMON_HANDLE_NULL_VALUE)
		{
			start(proc);
		}

		~thread_t()
		{
			reset();
		}

		void start(const proc_type & proc)
		{
			if(empty())
			{
				_proc = proc;

				LEMON_DECLARE_ERRORINFO(errorinfo);

				_thread = LemonCreateThread(&thread_t::Proc,this,&errorinfo);

				if(LEMON_FAILED(errorinfo)) throw Exception("LemonCreateThread exception",errorinfo);
			}
		}

		void reset()
		{
			join();

			if(LEMON_CHECK_HANDLE(_thread)) LemonReleaseThread(_thread);

			_thread = LEMON_HANDLE_NULL_VALUE;
		}

		bool empty() const
		{
			return !LEMON_CHECK_HANDLE(_thread);
		}

		void join()
		{
			if(!empty())
			{
				LEMON_DECLARE_ERRORINFO(errorinfo);
				
				LemonThreadJoin(_thread,&errorinfo);

				if(LEMON_FAILED(errorinfo)) throw Exception("LemonCreateThread exception",errorinfo);
			}
		}

		lemon_thread_id_t id()
		{
			if(empty()) return 0;

			return LemonGetThreadId(_thread);
		}

	private:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	static void Proc(void * data)
		///
		/// @brief	the wrapper proc function. 
		///
		/// @author	Yuki
		/// @date	2012/1/19
		///
		/// @param [in,out]	data	If non-null, the data. 
		////////////////////////////////////////////////////////////////////////////////////////////////////

		static void Proc(void * data)
		{
			reinterpret_cast<thread_t*>(data)->_proc();
		}

	private:

		proc_type	_proc;

		LemonThread _thread;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	basic_scope_lock
	///
	/// @brief	Basic scope lock. 
	///
	/// @author	Yayanyang
	/// @date	2011/12/15
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Mutex> class basic_scope_lock;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	basic_scope_trylock
	///
	/// @brief	Basic scope trylock. 
	///
	/// @author	Yayanyang
	/// @date	2011/12/15
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Mutex> class basic_scope_trylock;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	mutex_t
	///
	/// @brief	Mutex t. 
	///
	/// @author	Yuki
	/// @date	2012/1/20
	////////////////////////////////////////////////////////////////////////////////////////////////////

	class mutex_t
	{
	public:

		typedef basic_scope_lock<mutex_t> scope_lock;

		typedef basic_scope_trylock<mutex_t> scope_trylock;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	mutex_t()
		///
		/// @brief	Default constructor. 
		///
		/// @author	Yuki
		/// @date	2012/1/20
		////////////////////////////////////////////////////////////////////////////////////////////////////

		mutex_t()
		{
			LEMON_DECLARE_ERRORINFO(errorinfo);

			_mutex = LemonCreateMutex(&errorinfo);

			if(LEMON_FAILED(errorinfo)) throw Exception("call LemonCreateMutex exception",errorinfo);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	~mutex_t()
		///
		/// @brief	Finaliser. 
		///
		/// @author	Yuki
		/// @date	2012/1/20
		////////////////////////////////////////////////////////////////////////////////////////////////////

		~mutex_t()
		{
			LemonReleaseMutex(_mutex);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	void lock()
		///
		/// @brief	Locks this object. 
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void lock()
		{
			LEMON_DECLARE_ERRORINFO(errorinfo);

			LemonMutexLock(_mutex,&errorinfo);

			if(LEMON_FAILED(errorinfo)) throw Exception("call LemonMutexLock exception",errorinfo);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	bool trylock()
		///
		/// @brief	Trylocks this object. 
		///
		/// @return	true if it succeeds, false if it fails. 
		////////////////////////////////////////////////////////////////////////////////////////////////////

		bool trylock()
		{
			LEMON_DECLARE_ERRORINFO(errorinfo);

			lemon_bool result = LemonMutexTryLock(_mutex,&errorinfo);

			if(LEMON_FAILED(errorinfo)) throw Exception("call LemonMutexTryLock exception",errorinfo);

			return result?true:false;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	void unlock()
		///
		/// @brief	Unlocks this object. 
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void unlock()
		{
			LEMON_DECLARE_ERRORINFO(errorinfo);

			LemonMutexUnLock(_mutex,&errorinfo);

			if(LEMON_FAILED(errorinfo)) throw Exception("call LemonMutexUnLock exception",errorinfo);
		}

		operator LemonMutex ()
		{
			return _mutex;
		}

		operator const LemonMutex () const
		{
			return _mutex;
		}

	private:

		LemonMutex _mutex;
	};

	typedef mutex_t mutex;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	basic_scope_lock
	///
	/// @brief	Basic scope lock. 
	///
	/// @author	Yayanyang
	/// @date	2011/12/15
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Mutex>
	class basic_scope_lock : private nocopyable
	{
	public:

		basic_scope_lock(Mutex & mutex):_mutex(mutex){ lock();}

		~basic_scope_lock(){ unlock();}

		void lock()
		{
			_mutex.lock();
		}

		void unlock()
		{
			_mutex.unlock();
		}

		Mutex & mutex(){return _mutex;}

		const Mutex & mutex() const {return _mutex;}

	private:
		Mutex &_mutex;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	basic_scope_trylock
	///
	/// @brief	Basic scope trylock. 
	///
	/// @author	Yayanyang
	/// @date	2011/12/15
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Mutex>
	class basic_scope_trylock : private nocopyable
	{
	public:
		basic_scope_trylock(Mutex & mutex):_mutex(mutex){ _locked = trylock();}

		~basic_scope_trylock(){ unlock();}

		bool trylock()
		{
			return _mutex.trylock();
		}

		void unlock()
		{
			_mutex.unlock();
		}

		operator bool() const
		{
			return _locked;
		}

		Mutex & mutex(){return _mutex;}

		const Mutex & mutex() const {return _mutex;}

	private:
		bool _locked;

		Mutex &_mutex;
	};


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	atomic_t
	///
	/// @brief	Atomic t. 
	///
	/// @author	Yayanyang
	/// @date	2011/12/16
	////////////////////////////////////////////////////////////////////////////////////////////////////

	class atomic_t
	{
	public:

		atomic_t():_value(0){}

		atomic_t(int32_t i):_value(i){}

		int32_t operator ++ ()
		{
			return LemonAtomicIncrement(&_value);
		}

		int32_t operator -- ()
		{
			return LemonAtomicDecrement(&_value);
		}

		int32_t operator ++ (int32_t)
		{
			int32_t i = LemonAtomicIncrement(&_value);

			return -- i;
		}

		int32_t operator -- (int32_t)
		{
			int32_t i = LemonAtomicDecrement(&_value);

			return ++ i;
		}

		operator int32_t()
		{
			return _value;
		}

		bool operator == (int32_t rhs) const
		{
			return _value == rhs;
		}

		bool operator != (int32_t rhs) const
		{
			return _value != rhs;
		}

		bool operator < (int32_t rhs) const
		{
			return _value < rhs;
		}

		bool operator > (int32_t rhs) const
		{
			return _value > rhs;
		}

		bool operator <= (int32_t rhs) const
		{
			return _value <= rhs;
		}

		bool operator >=(int32_t rhs) const
		{
			return _value >= rhs;
		}

	private:

		lemon_atomic_t _value;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	condition_variable
	///
	/// @brief	Condition variable. 
	///
	/// @author	Yayanyang
	/// @date	2011/12/16
	////////////////////////////////////////////////////////////////////////////////////////////////////

	class condition_variable : private nocopyable
	{
	public:

		condition_variable()
		{
			LEMON_DECLARE_ERRORINFO(errorcode);

			_cv = LemonCreateConditionVariable(&errorcode);

			if (LEMON_FAILED(errorcode)) {

				throw Exception(errorcode);
			}
		}

		~condition_variable()
		{
			LemonReleaseConditionVariable(_cv);
		}

		template<typename Lock>
		void wait(Lock & lock)
		{
			LEMON_DECLARE_ERRORINFO(errorcode);

			LemonConditionVariableWait(_cv,lock.mutex(),&errorcode);

			if (LEMON_FAILED(errorcode)) throw Exception(errorcode);
		}

		void notify()
		{
			LEMON_DECLARE_ERRORINFO(errorcode);

			LemonConditionVariableNotify(_cv,&errorcode);

			if (LEMON_FAILED(errorcode)) throw Exception(errorcode);
		}

		void notifyall()
		{
			LEMON_DECLARE_ERRORINFO(errorcode);

			LemonConditionVariableNotifyAll(_cv,&errorcode);

			if (LEMON_FAILED(errorcode)) throw Exception(errorcode);
		}

	private:
		LemonConditionVariable _cv;
	};
}

#endif //LEMON_CXX_SYS_THREAD_HPP