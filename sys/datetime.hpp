/**
* 
* @file     datetime
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/01/15
*/
#ifndef LEMON_CXX_SYS_DATETIME_HPP
#define LEMON_CXX_SYS_DATETIME_HPP
#include <algorithm>
#include <lemon/sys/datetime.h>
#include <lemonxx/sys/exception.hpp>
#include <lemonxx/utility/nocopyable.hpp>
#include <lemonxx/sys/inttypes.hpp>
namespace lemon{

	typedef int64_t time_duration;

	class time_t : public LemonTime
	{
	public:
		time_t()
		{
			*this = now();
		}
		time_t(time_duration duration)
		{
			fromduration(duration);
		}

		time_t(const LemonTime & current)
		{
			memcpy(this,&current,sizeof(LemonTime));
		}

		void swap(lemon::time_t & rhs)
		{
			std::swap(Seconds,rhs.Seconds);

			std::swap(Microseconds,rhs.Microseconds);
		}

		static lemon::time_t now()
		{
			LEMON_DECLARE_ERRORINFO(errorinfo);
		    
			lemon::time_t t = LemonNow(&errorinfo);

			if(LEMON_FAILED(errorinfo)) throw Exception("call LemonNow exception",errorinfo);

			return t;
		}

		lemon::time_t & operator = (const LemonTime & rhs)
		{
			time_t tmp(rhs);

			tmp.swap(*this);
		}

		time_duration operator - (const lemon::time_t & rhs) const
		{
			return toduration() - rhs.toduration();
		}

		lemon::time_t & operator -= (const lemon::time_t & rhs)
		{
			fromduration(*this - rhs);

			return *this;
		}

		lemon::time_t operator + (time_duration rhs) const
		{
			return toduration() + rhs;
		}

		lemon::time_t & operator += (time_duration rhs)
		{
			fromduration(toduration() +  rhs);

			return *this;
		}

		bool operator > (const lemon::time_t & rhs) const
		{
			return toduration() > rhs.toduration();
		}

		bool operator >= (const lemon::time_t & rhs) const
		{
			return toduration() >= rhs.toduration();
		}

		bool operator < (const lemon::time_t & rhs) const
		{
			return toduration() < rhs.toduration();
		}

		bool operator <= (const lemon::time_t & rhs) const
		{
			return toduration() <= rhs.toduration();
		}

		bool operator == (const lemon::time_t & rhs) const
		{
			return toduration() == rhs.toduration();
		}

		bool operator != (const lemon::time_t & rhs) const
		{
			return toduration() != rhs.toduration();
		}

	private:
		time_duration toduration() const
		{
			return Seconds * 10000000 + Microseconds * 10;
		}

		void fromduration(time_duration duration)
		{
			Seconds = duration / 10000000 ;

			Microseconds = (duration % 10000000) / 10;
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @property	template<typename Type> class basic_datetime_t : public LemonDateTime
	///
	/// @brief	 the time of the lemon date. 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Type>
	class basic_datetime_t : public LemonDateTime
	{
	public:
		basic_datetime_t()
		{
			Type::fromtime(reinterpret_cast<Type*>(this),time_t());
		}
		basic_datetime_t(time_t source)
		{
			Type::fromtime(reinterpret_cast<Type*>(this),source);
		}

		lemon::time_t time() const
		{
			LEMON_DECLARE_ERRORINFO(errorinfo);

			lemon::time_t result  = LemonDateTimeToTime(this,&errorinfo);

			if(LEMON_FAILED(errorinfo)) throw Exception("call LemonDateTimeToTime exception",errorinfo);

			return result;
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	localtime_t
	///
	/// @brief	Localtime t. 
	///
	/// @author	Yuki
	/// @date	2012/1/15
	////////////////////////////////////////////////////////////////////////////////////////////////////

	class localtime_t : public basic_datetime_t<localtime_t>
	{
	public:
		localtime_t()
			:basic_datetime_t<localtime_t>()
		{}

		localtime_t(time_t source)
			:basic_datetime_t<localtime_t>(source)
		{}
	
		static void fromtime(localtime_t * datetime,lemon::time_t source)
		{
			LEMON_DECLARE_ERRORINFO(errorinfo);

			LemonLocalDateTime(datetime,source,&errorinfo);

			if(LEMON_FAILED(errorinfo)) throw Exception("call LemonLocalDateTime exception",errorinfo);
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	utctime_t
	///
	/// @brief	Utctime t. 
	///
	/// @author	Yuki
	/// @date	2012/1/15
	////////////////////////////////////////////////////////////////////////////////////////////////////

	class utctime_t : public basic_datetime_t<utctime_t>
	{
	public:
		utctime_t()
			:basic_datetime_t<utctime_t>()
		{}

		utctime_t(time_t source)
			:basic_datetime_t<utctime_t>(source)
		{}

		static void fromtime(utctime_t * datetime,lemon::time_t source)
		{
			LEMON_DECLARE_ERRORINFO(errorinfo);

			LemonUTCDateTime(datetime,source,&errorinfo);

			if(LEMON_FAILED(errorinfo)) throw Exception("call LemonUTCDateTime exception",errorinfo);
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	timer_t
	///
	/// @brief	Timer t. 
	///
	/// @author	Yayanyang
	/// @date	2012/2/2
	////////////////////////////////////////////////////////////////////////////////////////////////////

	class timer_t : private nocopyable
	{
	public:
		timer_t(){reset();}

		void reset(){_start = time_t();}

		time_duration duration() const { return time_t() - _start;}

	private:
		time_t _start;
	};
}
#endif //LEMON_CXX_SYS_DATETIME_HPP