/**
 * 
 * @file     begin
 * @brief    Copyright (C) 2010  yayanyang All Rights Reserved 
 * @author   yayanyang
 * @version  1.0.0.0  
 * @date     2010/12/06
 */
#ifndef GHCA_STDEXT_MPL_CONTAINER_LIST_BEGIN_HPP
#define GHCA_STDEXT_MPL_CONTAINER_LIST_BEGIN_HPP

#include <lemonxx/mpl/list/iterator.hpp>

namespace lemon{namespace mpl{

	template<typename Head,typename Tail>
	struct begin< list<Head,Tail> >
	{
		typedef iterator< list<Head,Tail> > type;
	};

}}

#endif	//GHCA_STDEXT_MPL_CONTAINER_LIST_BEGIN_HPP
