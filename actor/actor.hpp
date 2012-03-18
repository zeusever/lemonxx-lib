/**
* 
* @file     actor
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/03/15
*/
#ifndef LEMONXX_ACTOR_ACTOR_HPP
#define LEMONXX_ACTOR_ACTOR_HPP
#include <lemon/actor/abi.h>
#include <lemonxx/sys/sys.hpp>
#include <lemonxx/utility/utility.hpp>
#include <lemonxx/function/function.hpp>

namespace lemon{namespace concurrency{

	class actor_engine;

	typedef lemon::function<void(actor_engine& engine)> actor_handle_type;

	void ActorProc(LemonActorEngine engine,void *userData);

	class actor_engine : public basic_handle_object<LemonActorEngine,&LemonReleaseActorEngine>	
	{
	public:
		typedef basic_handle_object<LemonActorEngine,&LemonReleaseActorEngine> base_type;

		actor_engine(LemonActorEngine engine)
			:base_type(engine)
		{

		}

		actor_engine(size_t backGroundThreads)
			:base_type(Create(backGroundThreads))
		{

		}

		void join()
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonActorEngineJoin(*this,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

		}

		template<typename Handle>
		LemonActor create_actor(Handle handle)
		{
			actor_handle_type wrapper(handle);

			LEMON_DECLARE_ERRORINFO(errorCode);

			actor_handle_type::wrapper_type data = wrapper.release();

			LemonActor actor = LemonCreateActor(*this,&ActorProc,data,&errorCode);

			if(LEMON_FAILED(errorCode)){

				actor_handle_type collection(data);
				
				throw Exception(errorCode);
			}

			return actor;
		}

		void stop()
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonActorEngineStop(*this,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
		}

		void join_actor(LemonActor actor)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonActorJoin(*this,actor,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
		}

	private:

		static LemonActorEngine Create(size_t backGroundThreads)
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonActorEngine engine = LemonCreateActorEngine(backGroundThreads,&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);

			return engine;
		}
	};

	inline void ActorProc(LemonActorEngine engine,void *userData)
	{
		actor_handle_type cb((actor_handle_type::wrapper_type)userData);

		actor_engine eg(engine);

		cb(eg);

		eg.release();
	}
}}

#endif //LEMONXX_ACTOR_ACTOR_HPP