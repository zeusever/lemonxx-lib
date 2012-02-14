/**
* 
* @file     ref
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/01/19
*/
#ifndef LEMON_CXX_STDEXT_UTILITY_REF_HPP
#define LEMON_CXX_STDEXT_UTILITY_REF_HPP

namespace lemon{

	template<typename T>
	struct refrence_wrapper
	{
	public:

		refrence_wrapper():_t(0){}
		
		refrence_wrapper(T * t):_t(t){}

		bool empty() const{return _t == 0;}

		refrence_wrapper& operator = ( T &t)
		{
			_t = &t;

			return *this;
		}

		operator T & ()
		{
			return *_t;
		}

		operator T & () const
		{
			return *_t;
		}

	private:
		T * _t;
	};

	template<typename T>
	inline refrence_wrapper<const T> cref(const T & t)
	{
		return refrence_wrapper<const T>(&t);
	}

	template<typename T>
	inline refrence_wrapper<T> ref(T & t)
	{
		return refrence_wrapper<T>(&t);
	}
}

#endif //LEMON_CXX_STDEXT_UTILITY_REF_HPP