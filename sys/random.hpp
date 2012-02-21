/**
* 
* @file     random
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/01/15
*/
#ifndef LEMON_CXX_SYS_RANDOM_HPP
#define LEMON_CXX_SYS_RANDOM_HPP
#include <lemon/sys/random.h>
#include <lemonxx/sys/exception.hpp>
#include <lemonxx/utility/nocopyable.hpp>
namespace lemon{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	random_t
	///
	/// @brief	Random t. 
	///
	/// @author	Yuki
	/// @date	2012/1/15
	////////////////////////////////////////////////////////////////////////////////////////////////////

	class random_t : private nocopyable
	{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	random_t()
		///
		/// @brief	Default constructor. 
		///
		/// @author	Yuki
		/// @date	2012/1/15
		///
		/// @exception	Exception	Thrown when . 
		////////////////////////////////////////////////////////////////////////////////////////////////////

		random_t()
		{
			LEMON_DECLARE_ERRORINFO(errorinfo);

			_device = LemonCreateRandomDevice(&errorinfo);

			if(LEMON_FAILED(errorinfo)) throw Exception("call LemonCreateRandomDevice exception",errorinfo);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	~random_t()
		///
		/// @brief	Finaliser. 
		///
		/// @author	Yuki
		/// @date	2012/1/15
		////////////////////////////////////////////////////////////////////////////////////////////////////

		~random_t()
		{
			LemonReleaseRandomDevice(_device);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	operator size_t () const
		///
		/// @brief	get the new random number;
		///
		/// @author	Yuki
		/// @date	2012/1/15
		///
		/// @exception	Exception	Thrown when . 
		///
		/// @return	The result of the operation. 
		////////////////////////////////////////////////////////////////////////////////////////////////////

		operator size_t () const
		{
			return next();
		}

		size_t next() const
		{
			LEMON_DECLARE_ERRORINFO(errorinfo);

			size_t result = LemonRandomDeviceNext(_device,&errorinfo);

			if(LEMON_FAILED(errorinfo)) throw Exception("call LemonRandomDeviceNext exception",errorinfo);

			return result;
		}

	private:

		//! the random device. 
		LemonRandomDevice _device;
	};
}
#endif //LEMON_CXX_SYS_RANDOM_HPP