/**
* 
* @file     director
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/03/19
*/
#ifndef LEMONXX_DRAMA_DIRECTOR_HPP
#define LEMONXX_DRAMA_DIRECTOR_HPP
#include <lemon/drama/drama.h>

#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>
#include <lemonxx/function/function.hpp>

namespace lemon{namespace concurrency{


	class drama : public basic_handle_object<LemonDrama,&LemonReleaseDrama>
	{
	public:

		typedef basic_handle_object<LemonDrama,&LemonReleaseDrama> base_type;

		drama(LemonDrama da):base_type(da){}

		drama(size_t backgroundThreads)
			:base_type(Create(backgroundThreads))
		{}

		void join()
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonDramaJoin(*this,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
		}

		void stop()
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonDramaStop(*this,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
		}

	private:

		static LemonDrama Create(size_t backgroundThreads)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonDrama object = LemonCreateDrama(backgroundThreads,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

			return object;
		}
	};

	typedef lemon::function<void(drama & da)> actor_handle_type;

	class actor
	{
	public:

		actor():_drama(0){}
		
		actor(drama & da,LemonActor id)
			:_drama(&da),_handle(id)
		{}

		template<typename Handle>
		actor(drama & da,Handle handle)
			:_drama(&da)
		{
			Create(handle);
		}

		void join()
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonActorJoin(*_drama,_handle,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
		}

	private:

		template<class Handle>
		void Create(Handle handle)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			actor_handle_type cb(handle);

			actor_handle_type::wrapper_type userData = cb.release();

			_handle = LemonCreateActor(*_drama,&actor::Proc,userData,&errorCode);

			if(LEMON_FAILED(errorCode))
			{
				cb.reset(userData);

				throw Exception(errorCode);
			}
		}

		static void Proc(LemonDrama director,void *userData)
		{
			drama da(director);

			actor_handle_type cb((actor_handle_type::wrapper_type)userData);

			cb(da);

			da.release();
		}

	private:

		drama			*_drama;


		LemonActor		_handle;
	};

}}

#endif //LEMONXX_DRAMA_DIRECTOR_HPP