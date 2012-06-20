/**
* 
* @file     play
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/03/24
*/
#ifndef LEMONXX_PLAY_PLAY_HPP
#define LEMONXX_PLAY_PLAY_HPP
#include <lemon/play/play.h>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>
#include <lemonxx/function/function.hpp>

namespace lemon{namespace concurrency{

	class play : public basic_handle_object<LemonPlay,&LemonReleasePlay>
	{
	public:
		typedef basic_handle_object<LemonPlay,&LemonReleasePlay> base_type;

		play(size_t backgroundThreads)
			:base_type(Create(backgroundThreads))
		{}

		play(LemonPlay handle)
			:base_type(handle)
		{

		}

		~play()
		{
			if(!empty())
			{
				stop();

				join();
			}
		}

		void join()
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonPlayJoin(*this,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
		}

		void stop()
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonPlayStop(*this,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
		}

	private:

		static LemonPlay Create(size_t backgroundThreads)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonPlay p = LemonCreatePlay(backgroundThreads,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

			return p;
		}
	};

	typedef lemon::function<void(play & engine)> actor_handle_type;

	class actor 
	{
	public:

		actor()
		{}

		template<typename Handle>
		actor(play &p,Handle handle)
			:_play(&p)
		{
			start(handle);
		}

		template<typename Handle>
		void start(Handle handle)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			actor_handle_type cb(handle);

			actor_handle_type::wrapper_type userData = cb.release();

			_actor = LemonCreateActor(*_play,&actor::Proc,userData,&errorCode);

			if(LEMON_FAILED(errorCode))
			{
				actor_handle_type(userData);

				throw Exception(errorCode);
			}
		}

		void join()
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonActorJoin(*_play,_actor,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
		}

	private:

		static void Proc(LemonPlay engine,void *userData)
		{
			actor_handle_type cb(reinterpret_cast<actor_handle_type::wrapper_type>(userData));

			play p(engine);

			cb(p);

			p.release();
		}

	private:

		play			*_play;

		LemonActor		_actor;
	};
}}
#endif  //LEMONXX_PLAY_PLAY_HPP
 