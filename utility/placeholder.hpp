/**
 * 
 * @file     placeholder
 * @brief    Copyright (C) 2010  yayanyang All Rights Reserved 
 * @author   yayanyang
 * @version  1.0.0.0  
 * @date     2010/12/09
 */
#ifndef GHCA_STDEXT_PLACEHOLDER_HPP
#define GHCA_STDEXT_PLACEHOLDER_HPP

#include <lemonxx/mpl/inttypes.hpp>

namespace lemon{

	template<size_t N>
	struct placeholder : public mpl::size_t_<N>
	{

	};

	template<typename T>
	struct is_placeholder
		:public mpl::false_type
	{

	};

	template<size_t N>
	struct is_placeholder< placeholder<N> >
		:public mpl::true_type
	{

	};

	template<typename T>
	struct type_placeholder
	{
		typedef T type;
	};

	template<typename T>
	struct placeholder_value
		: public mpl::size_t_<0>
	{
		
	};

	template<size_t N>
	struct placeholder_value<placeholder<N> >
		:public mpl::size_t_<N>
	{

	};

}

namespace lemon{
	
	static placeholder<0> _0;
	static placeholder<1> _1;
	static placeholder<2> _2;
	static placeholder<3> _3;
	static placeholder<4> _4;
	static placeholder<5> _5;
	static placeholder<6> _6;
	static placeholder<7> _7;
	static placeholder<8> _8;
	static placeholder<9> _9;

	namespace{


		template<size_t N>
		inline void disablewarningcall(placeholder<N>)
		{

		}

		inline void disablewarning()
		{
			disablewarningcall(_0);
			disablewarningcall(_1);
			disablewarningcall(_2);
			disablewarningcall(_3);
			disablewarningcall(_4);
			disablewarningcall(_5);
			disablewarningcall(_6);
			disablewarningcall(_7);
			disablewarningcall(_8);
			disablewarningcall(_9);
		}

	}



}
#endif	//GHCA_STDEXT_PLACEHOLDER_HPP
