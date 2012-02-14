/**
* 
* @file     nocopyable
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/01/14
*/
#ifndef LEMON_CXX_UTILITY_NOCOPYABLE_HPP
#define LEMON_CXX_UTILITY_NOCOPYABLE_HPP
namespace lemon{

	class nocopyable{
	public:
		nocopyable(){}
	private:

		nocopyable(const nocopyable & rhs);

		const nocopyable & operator = (const nocopyable & rhs);
	};

}
#endif //LEMON_CXX_UTILITY_NOCOPYABLE_HPP