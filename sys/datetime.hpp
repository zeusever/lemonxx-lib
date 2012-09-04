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
#include <lemonxx/sys/errorcode.hpp>
#include <lemonxx/utility/nocopyable.hpp>
#include <lemonxx/sys/inttypes.hpp>
namespace lemon{

	typedef LemonTimeDuration time_duration;

	class time_t : public LemonTime
	{
	public:
		time_t()
		{
			//*this = now();
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
			error_info errorCode;
		    
			lemon::time_t t = LemonNow(errorCode);

			errorCode.check_throw();

			return t;
		}

		lemon::time_t & operator = (const LemonTime & rhs)
		{
			time_t tmp(rhs);

			tmp.swap(*this);

			return *this;
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
			return LEMON_TIME_TO_INT64(*this);
		}

		void fromduration(time_duration duration)
		{
			LEMON_TIME_FROM_INT64(*this,duration);
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
		/*basic_datetime_t()
		{
			Type::fromtime(reinterpret_cast<Type*>(this),time_t::now());
		}*/
		basic_datetime_t(time_t source)
		{
			Type::fromtime(reinterpret_cast<Type*>(this),source);
		}

		lemon::time_t time() const
		{
			error_info errorCode;

			lemon::time_t result  = LemonDateTimeToTime(this,errorCode);

			errorCode.check_throw();

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
		/*localtime_t()
			:basic_datetime_t<localtime_t>()
		{}*/

		localtime_t(time_t source)
			:basic_datetime_t<localtime_t>(source)
		{}
	
		static void fromtime(localtime_t * datetime,lemon::time_t source)
		{
			error_info errorCode;

			LemonLocalDateTime(datetime,source,errorCode);

			errorCode.check_throw();
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
		/*utctime_t()
			:basic_datetime_t<utctime_t>()
		{}*/

		utctime_t(time_t source)
			:basic_datetime_t<utctime_t>(source)
		{}

		static void fromtime(utctime_t * datetime,lemon::time_t source)
		{
			error_info errorCode;

			LemonUTCDateTime(datetime,source,errorCode);

			errorCode.check_throw();
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

		void reset(){_start = time_t::now();}

		time_duration duration() const { return time_t::now() - _start;}

	private:
		time_t _start;
	};
}
#endif //LEMON_CXX_SYS_DATETIME_HPP

