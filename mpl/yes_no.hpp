/**
 * 
 * @file     yes_no
 * @brief    Copyright (C) 2010  yayanyang All Rights Reserved 
 * @author   yayanyang
 * @version  1.0.0.0  
 * @date     2010/12/07
 */
#ifndef GHCA_STDEXT_MPL_YES_NO_HPP
#define GHCA_STDEXT_MPL_YES_NO_HPP

#include <lemonxx/mpl/inttypes.hpp>

namespace lemon{namespace mpl{

	typedef char (&yes)[1];
	
	typedef char (&no)[2];
}}

#define LEMON_MPL_IS_YES(T) sizeof(T) == sizeof(lemon::mpl::yes)

#endif	//GHCA_STDEXT_MPL_YES_NO_HPP

