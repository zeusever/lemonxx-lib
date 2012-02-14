/**
 * 
 * @file     end
 * @brief    Copyright (C) 2010  yayanyang All Rights Reserved 
 * @author   yayanyang
 * @version  1.0.0.0  
 * @date     2010/12/07
 */
#ifndef GHCA_STDEXT_MPL_CONTAINER_LIST_END_HPP
#define GHCA_STDEXT_MPL_CONTAINER_LIST_END_HPP

#include <lemonxx/mpl/list/iterator.hpp>


namespace lemon{namespace mpl{
	
	template<typename Head,typename Tail>
	struct end< list<Head,Tail> >
	{
		typedef iterator< list<null,null> > type;
	};
	
}}

#endif	//GHCA_STDEXT_MPL_CONTAINER_LIST_END_HPP
