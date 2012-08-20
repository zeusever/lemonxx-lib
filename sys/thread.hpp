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
#include <vector>
#include <lemon/sys/thread.h>
#include <lemonxx/sys/handle.hpp>
#include <lemonxx/sys/errorcode.hpp>
#include <lemonxx/utility/utility.hpp>
#include <lemonxx/function/function.hpp>
#include <lemonxx/sys/inttypes.hpp>
#include <lemonxx/sys/errorcode.hpp>


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
			error_info errorCode;

			_tls = LemonCreateTls(&tlsptr<T>::Destructor,errorCode);

			errorCode.check_throw();
		}

		tlsptr(void(*destructor)(void*))
		{
			error_info errorCode;

			_tls = LemonCreateTls(destructor,errorCode);

			errorCode.check_throw();
		}

		~tlsptr()
		{
			//LEMON_STATIC_ASSERT((!is_pointer<T>::value),"T must not a pointer type");

			LemonReleaseTls(_tls);
		}

		void set(T * val)
		{
			error_info errorCode;

			LemonTlsSet(_tls,val,errorCode);

			errorCode.check_throw();
		}

		T * get() const
		{
			error_info errorCode;

			void * data = LemonTlsGet(_tls,errorCode);

			errorCode.check_throw();

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
		error_info errorCode;

		lemon_thread_id_t id = LemonGetCurrentThreadId(errorCode);

		errorCode.check_throw();

		return id;
	}

	inline void sleep(size_t milliseconds)
	{
		LemonSleep(milliseconds);
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
		template<typename Handle>
		thread_t(Handle handle)
			:_thread(LEMON_HANDLE_NULL_VALUE)
		{
			start(handle);
		}

		~thread_t()
		{
			reset();
		}
		template<typename Handle>
		void start(Handle handle)
		{
			if(empty())
			{
				proc_type cb = handle;

				proc_type::wrapper_type data = cb.release();

				error_info errorCode;

				_thread = LemonCreateThread(&thread_t::Proc,data,errorCode);

				if(LEMON_FAILED(errorCode))
				{
					cb = data;

					throw errorCode;
				}
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
				error_info errorCode;
				
				LemonThreadJoin(_thread,errorCode);

				errorCode.check_throw();
			}
		}

		lemon_thread_id_t id() const
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
			proc_type cb = reinterpret_cast<proc_type::wrapper_type>(data);

			cb();
		}

	private:

		LemonThread _thread;
	};

	/*
	 *
	 */
	class thread_group : public lemon::basic_handle_object<LemonThreadGroup,&LemonCloseThreadGroup>
	{
	public:

		typedef lemon::function<void()> proc_type;


		typedef lemon::basic_handle_object<LemonThreadGroup,&LemonCloseThreadGroup> base_type;

		thread_group() :base_type(Create()) { }

		template<typename Handle>
		thread_group(Handle handle) :base_type(Create())
		{
			start(handle);
		}

		template<typename Handle>
		thread_group(Handle handle, size_t number) :base_type(Create())
		{
			start(handle,number);
		}

		/*
		 * @brief Create one thread in thread group.
		 *
		 */
		template<typename Handle>
		void start(Handle handle)
		{
			error_info errorCode;

			proc_type callee(handle);

			proc_type::wrapper_type userdata = callee.release();

			LemonThreadGroupCreateThread(*this,&thread_group::Proc,userdata,errorCode);

			if(LEMON_FAILED(errorCode)) callee = userdata;

			errorCode.check_throw();
		}

		template<typename Handle>
		void start(Handle handle, size_t number)
		{
			while(number -- > 0) start(handle);
		}

		void join() const
		{
			error_info errorCode;

			LemonThreadGroupJoin(*this,errorCode);
		}

		size_t size() const
		{
			return LemonThreadGroupSize(*this);
		}

		bool empty() const { return size() == 0; }

		void reset()
		{
			error_info errorCode;

			LemonThreadGroupReset(*this,&errorCode);
		}
		
	private:

		static LemonThreadGroup Create()
		{
			error_info  errorCode;

			LemonThreadGroup group = LemonCreateThreadGroup(errorCode);

			errorCode.check_throw();

			return group;
		}

		static void Proc(void * data)
		{
			proc_type cb = reinterpret_cast<proc_type::wrapper_type>(data);

			cb();
		}
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
	//////////////////////////////////////////////////////////////////////////////////////////////////// 


	template<typename Mutex> class basic_scope_unlock;

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
			error_info errorCode;

			_mutex = LemonCreateMutex(errorCode);

			errorCode.check_throw();
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
			error_info errorCode;

			LemonMutexLock(_mutex,&errorCode);

			errorCode.check_throw();
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
			error_info errorCode;

			lemon_bool result = LemonMutexTryLock(_mutex,errorCode);

			errorCode.check_throw();

			return result?true:false;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	void unlock()
		///
		/// @brief	Unlocks this object. 
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void unlock()
		{
			error_info errorCode;

			LemonMutexUnLock(_mutex,errorCode);

			errorCode.check_throw();
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

	template<typename Mutex> class basic_scope_unlock;

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

		typedef basic_scope_unlock< basic_scope_lock<Mutex> > scope_unlock;

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

		typedef basic_scope_unlock< basic_scope_lock<Mutex> > scope_unlock;

		basic_scope_trylock(Mutex & mutex):_mutex(mutex){ _locked = trylock();}

		~basic_scope_trylock(){ unlock();}

		bool trylock()
		{
			return _mutex.trylock();
		}

		void lock()
		{
			_mutex.lock();
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


	template<typename Mutex>
	class basic_scope_unlock : private nocopyable
	{
	public:

		basic_scope_unlock(Mutex & mutex):_mutex(mutex){ _mutex.unlock();}

		~basic_scope_unlock(){ _mutex.lock();}

	private:
		Mutex	 &_mutex;
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

		operator int32_t() const
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
			error_info errorCode;

			_cv = LemonCreateConditionVariable(errorCode);

			errorCode.check_throw();
		}

		~condition_variable()
		{
			LemonReleaseConditionVariable(_cv);
		}

		template<typename Lock>
		void wait(Lock & lock)
		{
			error_info errorCode;

			LemonConditionVariableWait(_cv,lock.mutex(),errorCode);

			errorCode.check_throw();
		}

		void notify()
		{
			error_info errorCode;

			LemonConditionVariableNotify(_cv,errorCode);

			errorCode.check_throw();
		}

		void notifyall()
		{
			error_info errorCode;

			LemonConditionVariableNotifyAll(_cv,errorCode);

			errorCode.check_throw();
		}

	private:
		LemonConditionVariable _cv;
	};
}

#endif //LEMON_CXX_SYS_THREAD_HPP