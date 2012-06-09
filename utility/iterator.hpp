/**
 * 
 * @file     iterator
 * @brief    Copyright (C) 2011  yayanyang All Rights Reserved 
 * @author   yayanyang
 * @version  1.0.0.0  
 * @date     2011/03/21
 */
#ifndef LEMON_STDEX_ITERATOR_HPP
#define LEMON_STDEX_ITERATOR_HPP

#include <iterator>

#include <lemonxx/mpl/inttypes.hpp>

#include <lemonxx/type_traits/type_traits.hpp>

namespace lemon{

	template<class Derived,typename ValueT,typename DifferenceT>
	struct iterator_t
	{	
		typedef ValueT value_type;
		
		typedef DifferenceT difference_type;
		
		typedef ValueT* pointer;

		typedef const lemon::remove_const<pointer> const_pointer;
		
		typedef typename lemon::add_lvalue_reference<ValueT>::type reference;

		typedef const lemon::remove_const<reference> const_reference;

		Derived & derived() 
		{
			return *reinterpret_cast<Derived*>(this);
		}

		const Derived & derived() const
		{
			return *reinterpret_cast<const Derived*>(this);
		}

		Derived & operator = (const Derived & rhs)
		{
			Derived temp(rhs);

			derived().swap(temp);

			return derived();
		}

		bool operator == (const Derived & rhs) const
		{
			return derived().equal(rhs);
		}

		bool operator != (const Derived & rhs) const
		{
			return !(derived() == rhs);
		}

		reference operator * ()
		{
			return derived().dereference();
		}

		const_reference operator * () const
		{
			return derived().dereference();
		}

		pointer operator -> () 
		{
			return derived().ptr();
		}

		const_pointer operator -> () const
		{
			return derived().ptr();
		}

		Derived& operator ++ ()
		{
			derived().increment();

			return derived();
		}

		Derived operator ++ (int)
		{
			Derived temp(derived());

			derived().increment();

			return temp;
		}

		Derived& operator -- ()
		{
			derived().decrement();

			return derived();
		}

		Derived operator -- (int)
		{
			Derived temp(derived());

			derived().decrement();

			return temp;
		}

		Derived & operator += (difference_type offset)
		{
			derived().advance(offset);

			return derived();
		}

		Derived & operator -= (difference_type offset)
		{
			derived().advance(-offset);

			return derived();
		}

		Derived operator + (difference_type offset)
		{
			Derived temp = derived();

			temp += offset;

			return temp;
		}

		Derived operator - (difference_type offset)
		{
			Derived temp = *this;

			temp -= offset;

			return temp;
		}

		difference_type operator - (const Derived& rhs)
		{
			return derived().distance(rhs);
		}

		value_type & operator[](difference_type offset)
		{
			return *(*this + offset);
		}

		bool operator < (const Derived &rhs) const
		{
			return derived().distance(rhs) < 0;
		}

		bool operator <= (const Derived &rhs) const
		{
			return derived().distance(rhs) <= 0;
		}

		bool operator > (const Derived &rhs) const
		{
			return derived().distance(rhs) > 0;
		}

		bool operator >= (const Derived &rhs) const
		{
			return derived().distance(rhs) >= 0;
		}
	};

}


#endif	//LEMON_STDEX_ITERATOR_HPP
