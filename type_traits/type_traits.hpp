/**
* 
* @file     type_traits
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/01/31
*/
#ifndef LEMONXX_TYPE_TRAITS_HPP
#define LEMONXX_TYPE_TRAITS_HPP
#include <lemonxx/configure.h>
#include <lemonxx/mpl/inttypes.hpp>
#include <lemonxx/utility/placeholder.hpp>
#include <lemonxx/type_traits/intrinsics.hpp>
#include <lemonxx/type_traits/is_functionptr.hpp>

namespace lemon{
	
	using lemon::mpl::bool_;
	using lemon::mpl::true_type;
	using lemon::mpl::false_type;
	using lemon::mpl::inttypes_;
	using lemon::mpl::size_t_;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	is_same
	///
	/// @brief	An instance of the type predicate holds true if the types 
	///			Ty1 and Ty2 are the same type, otherwise it holds false.
	///
	/// @author	Yuki
	/// @date	2012/1/31
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class T1,class T2> struct is_same;
	
	template<typename T1,typename T2> 
	struct is_same : false_type 
	{
		typedef false_type type;
	};

	template<typename T> 
	struct is_same<T,T> : true_type 
	{
		typedef true_type type;
	};


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	add_const
	///
	/// @brief	An instance of the type modifier holds a modified-type that 
	///			is Ty if Ty is a reference, a function, or a const-qualified 
	///			type, otherwise const Ty
	///
	/// @author	Yuki
	/// @date	2012/1/31
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class T> struct add_const;

	template<class T> struct add_const
	{
		typedef T const type;
	};

	template<class T> struct add_const<T&>
	{
		typedef T& type;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	add_volatile
	///
	/// @brief	An instance of the type modifier holds a modified-type that 
	///			is Ty if Ty is a reference, a function, or a volatile-qualified 
	///			type, otherwise volatile Ty. 
	///
	/// @author	Yuki
	/// @date	2012/1/31
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class T> struct add_volatile;

	template<class T> struct add_volatile
	{
		typedef T volatile type;
	};

	template<class T> struct add_volatile<T&>
	{
		typedef T& type;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	add_cv
	///
	/// @brief	An instance of the type modifier holds the modified-type add_volatile Class< add_const Class<Ty> >. 
	///
	/// @author	Yuki
	/// @date	2012/1/31
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class T> struct add_cv
	{
		typedef typename add_const<typename add_volatile<T>::type>::type type;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	remove_const
	///
	/// @brief	The same type as T, but with any top level const-qualifier removed 
	///
	/// @author	Yuki
	/// @date	2012/2/1
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class T> struct remove_const
	{
		typedef T type;
	};

	template<class T> struct remove_const<T const>
	{
		typedef T type;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	remove_volatile
	///
	/// @brief	The same type as T, but with any top level volatile-qualifier removed
	///
	/// @author	Yuki
	/// @date	2012/2/1
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template <class T> struct remove_volatile
	{
		typedef T type;
	};

	template <class T> struct remove_volatile<T volatile>
	{
		typedef T type;
	};

	template<class T> struct remove_cv
	{
		typedef typename remove_const<typename remove_volatile<T>::type>::type type;
	};


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	add_lvalue_reference
	///
	/// @brief	If T names an object or function type then the member 
	///			typedef type shall name T&; otherwise, if T names a type 
	///			rvalue reference to U then the member typedef type shall name U&; 
	///			otherwise, type shall name T. 
	///
	/// @author	Yuki
	/// @date	2012/1/31
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class T> struct add_lvalue_reference;

	template<class T> struct add_lvalue_reference
	{
		typedef T & type;
	};

	template<class T> struct add_lvalue_reference<T&>
	{
		typedef T & type;
	};

	template<class T> struct add_lvalue_reference<T*>
	{
		typedef T* & type;
	};
#ifdef LEMON_COMPILER_SUPPORT_RVALUE
	template<class T> struct add_lvalue_reference<T&&>
	{
		typedef T & type;
	};								
#endif //LEMON_COMPILER_SUPPORT_RVALUE

	template<> struct add_lvalue_reference<void>
	{
		typedef void type;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	remove_reference
	///
	/// @brief	Remove reference. 
	///
	/// @author	Yuki
	/// @date	2012/1/31
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class T> struct remove_reference;

	template<class T> struct remove_reference
	{
		typedef T type;
	};

	template<class T> struct remove_reference<T&>
	{
		typedef T type;
	};
#ifdef LEMON_COMPILER_SUPPORT_RVALUE
	template<class T> struct remove_reference<T&&>
	{
		typedef T type;
	};
#endif //LEMON_COMPILER_SUPPORT_RVALUE

	template<class T> struct remove_lvalue_reference;

	template<class T> struct remove_lvalue_reference
	{
		typedef T type;
	};

	template<class T> struct remove_lvalue_reference<T&>
	{
		typedef T type;
	};

#ifdef LEMON_COMPILER_SUPPORT_RVALUE

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	add_rvalue_reference
	///
	/// @brief	 If T names an object or function type then the member 
	///			 typedef type shall name T&&; otherwise, type shall name T. 
	///			 [Note: This rule reflects the semantics of reference collapsing. 
	///			 For example, when a type T names a type U&, the type 
	///			 add_rvalue_reference<T>::type is not an rvalue reference. -end note].  
	///
	/// @author	Yuki
	/// @date	2012/1/31
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template <class T> struct add_rvalue_reference;

	template <class T> struct add_rvalue_reference
	{
		typedef T && type;
	};

	template <class T> struct add_rvalue_reference<T&>
	{
		typedef T& type;
	};

	template <class T> struct add_rvalue_reference<T&&>
	{
		typedef T&& type;
	};

	template <> struct add_rvalue_reference<void>
	{
		typedef void type;
	};

#endif //LEMON_COMPILER_SUPPORT_RVALUE
	

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	add_pointer
	///
	/// @brief	The rationale for this template is that it produces 
	///			the same type as TYPEOF(&t), where t is an object of type T. 
	///
	/// @author	Yuki
	/// @date	2012/1/31
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class T> struct add_pointer;

	template<class T> struct add_pointer
	{
		typedef typename remove_reference<T>::type * type;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	alignment_of
	///
	/// @brief	Class template alignment_of inherits from integral_constant<std::size_t, ALIGNOF(T)>,
	///			where ALIGNOF(T) is the alignment of type T. 
	///
	/// @author	Yuki
	/// @date	2012/1/31
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class T> struct alignment_of;

	template<class T> struct alignment_getter
	{
		struct POD{T t1;char t2;T t3;};

		typedef inttypes_<size_t,sizeof(POD) - 2*sizeof(T)> type;
	};

	template<class T> 
	struct alignment_of : public alignment_getter<T>::type
	{
		
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	aligned_storage
	///
	/// @brief	a built-in or POD type with size Size and an alignment that is a multiple of Align. 
	///
	///
	/// @author	Yuki
	/// @date	2012/1/31
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template<size_t Size, size_t Align> struct aligned_storage;

	template<class T,size_t Length>
	struct aligned_storage_type
	{
		typedef union{T val;char pad[Length];} type;
	};

	template<
		size_t Size,
		size_t Align,
		class T,
		bool OK = alignment_of<T>::value == Align 
	> 
	struct aligned_storage_selector;

	template<size_t Size,size_t Align,class T> 
	struct aligned_storage_selector<Size,Align,T,true>
	{
		typedef typename aligned_storage_type<T,Size>::type type;
	};

	template<size_t Size,size_t Align> 
	struct aligned_storage_selector<Size,Align,lemon_int64_t,false>
	{
		typedef typename aligned_storage_type<lemon_int64_t,Size>::type type;
	};

	template<size_t Size,size_t Align> 
	struct aligned_storage_selector<Size,Align,lemon_int32_t,false>
	{
		typedef typename aligned_storage_selector<Size,Align,lemon_int64_t>::type type;
	};

	template<size_t Size,size_t Align> 
	struct aligned_storage_selector<Size,Align,lemon_int16_t,false>
	{
		typedef typename aligned_storage_selector<Size,Align,lemon_int32_t>::type type;
	};

	template<size_t Size,size_t Align> 
	struct aligned_storage_selector<Size,Align,char,false>
	{
		typedef typename aligned_storage_selector<Size,Align,lemon_int16_t>::type type;
	};
		
	template<size_t Size, size_t Align> struct aligned_storage
	{
		typedef typename aligned_storage_selector<Size,Align,char>::type type;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	conditional
	///
	/// @brief	If B is true, the member typedef type shall equal T. If B is 
	///			false, the member typedef type shall equal U.  
	///
	/// @author	Yuki
	/// @date	2012/1/31
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<bool B,class T,class U> struct conditional;

	template<class T,class U> struct conditional<true,T,U>
	{
		typedef T type;
	};

	template<class T,class U> struct conditional<false,T,U>
	{
		typedef U type;
	};

	//not implement common_type

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	remove_extent
	///
	/// @brief	If T is an array type, then removes the topmost array bound, otherwise leaves T unchanged
	///
	/// @author	Yuki
	/// @date	2012/2/1
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class T> struct remove_extent;

	template<class T> struct remove_extent
	{
		typedef T type;
	};

	template<class T,size_t N> struct remove_extent<T[N]>
	{
		typedef T type;
	};

	template<class T> struct remove_extent<T[]>
	{
		typedef T type;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	is_array
	///
	/// @brief	If T is a (possibly cv-qualified) array type then inherits 
	///			from true_type, otherwise inherits from false_type 
	///
	/// @author	Yuki
	/// @date	2012/2/1
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class T> struct is_array;

	template<class T> struct is_array : false_type
	{

	};

	template<class T> struct is_array<T[]> : true_type
	{

	};

	template<class T,size_t N> struct is_array<T[N]> : true_type
	{

	};

	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	decay
	///
	/// @brief	 Let U be the result of remove_reference<T>::type, 
	///			 then if U is an array type, the result is remove_extent<U>::type*, 
	///			 otherwise if U is a function type then the result is U*, otherwise the result is U. 
	///
	/// @author	Yuki
	/// @date	2012/2/1
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template <class T> struct decay;

	template <class T>struct decay
	{
		typedef typename remove_lvalue_reference<T>::type noname;

		typedef typename conditional<
			is_array<noname>::value,
			typename remove_extent<noname>::type*,
			typename conditional<
			is_function<noname>::value,
			noname*,
			noname
			>::type
		>::type type;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	N
	///
	/// @brief	Class template extent inherits from integral_constant<std::size_t, EXTENT(T,N)>, 
	///			where EXTENT(T,N) is the number of elements in the N'th array dimension of type T. 
	///
	/// @author	Yuki
	/// @date	2012/2/1
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class T,size_t N = 0> struct extent;

	template<class T,size_t N> struct _extent;

	template<class T,size_t N> 
	struct _extent	: public size_t_<0>
	{

	};

	template<class T,size_t N> 
	struct _extent<T[N],0>	: public size_t_<N>
	{

	};

	template<class T,size_t N,size_t N1> 
	struct _extent<T[N],N1>	: public _extent<T,N1 - 1>
	{

	};

	template<class T,size_t N> 
	struct _extent<T[],N>	: public _extent<T,N - 1>
	{

	};

	template<class T,size_t N>
	struct extent : public _extent<T,N>
	{

	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	is_abstract
	///
	/// @brief	If T is a (possibly cv-qualified) abstract type then 
	///			inherits from true_type, otherwise inherits from false_type.
	///
	/// @author	Yuki
	/// @date	2012/2/1
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class T> struct is_abstract : bool_<LEMON_IS_ABSTRACT(T)>
	{

	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @struct	is_integral
	///
	/// @brief	If T is a (possibly cv-qualified) integral type then 
	///			inherits from true_type, otherwise inherits from false_type. 
	///
	/// @author	Yayanyang
	/// @date	2012/2/2
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class T> struct is_integral
		: public bool_<
		_is_integral<T>::value ||
		_is_signed_integral<T>::value ||
		_is_unsigned_integral<T>::value ||
		_is_lemon_integral<T>::value>
	{

	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @struct	is_floating_point : public false_type {};
	///
	/// @brief	If T is a (possibly cv-qualified) floating point type then 
	///			inherits from true_type, otherwise inherits from false_type. 
	///
	/// @author	Yayanyang
	/// @date	2012/2/2
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class T> struct is_floating_point : public false_type {};

	template<> struct is_floating_point<float> : public true_type {};

	template<> struct is_floating_point<double> : public true_type {};

	template<> struct is_floating_point<long double> : public true_type {};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @struct	is_arithmetic;
	///
	/// @brief	If T is a (possibly cv-qualified) arithmetic type then 
	///			inherits from true_type, otherwise inherits from false_type. 
	///			Arithmetic types include integral and floating point types 
	///			(see also is_integral and is_floating_point). 
	///
	/// @author	Yayanyang
	/// @date	2012/2/2
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class T> struct is_arithmetic
		:public bool_<is_integral<T>::value || is_floating_point<T>::value>
	{

	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @struct	is_base_of : public bool_<LEMON_IS_BASE_OF(Base,Derived)>
	///
	/// @brief	If Base is base class of type Derived or if both types are 
	///			the same class type then inherits from true_type, otherwise 
	///			inherits from false_type.
	///
	/// @author	Yayanyang
	/// @date	2012/2/2
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template <class Base, class Derived> 
	struct is_base_of : public bool_<LEMON_IS_BASE_OF(Base,Derived)>
	{

	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @property	template<class T> is_class : public bool_<LEMON_IS_CLASS(T)>
	///
	/// @brief	If T is a (possibly cv-qualified) class type (and not a union type) 
	///			then inherits from true_type, otherwise inherits from false_type. 
	///
	/// @value	. 
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class T> struct is_class : public bool_<LEMON_IS_CLASS(T)>{};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @struct	is_enum : public bool_<LEMON_IS_ENUM(T)>{};
	///
	/// @brief	If T is a (possibly cv-qualified) enum type then inherits 
	///			from true_type, otherwise inherits from false_type. 

	///
	/// @author	Yayanyang
	/// @date	2012/2/2
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class T> struct is_enum  : public bool_<LEMON_IS_ENUM(T)>{};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @struct	is_member_function_pointer : public _is_memfunptr<T> {};
	///
	/// @brief	.
	///
	/// @author	Yayanyang
	/// @date	2012/2/2
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template <class T>
	struct is_member_function_pointer : public _is_memfunptr<T> {};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @struct	is_member_object_pointer ;
	///
	/// @brief	If T is a (possibly cv-qualified) pointer to a member object 
	///			(a data member) then inherits from true_type, otherwise 
	///			inherits from false_type. 
	///
	/// @author	Yayanyang
	/// @date	2012/2/2
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template <class T> struct is_member_object_pointer : public false_type {};

	template <class R,class Class> 
	struct is_member_object_pointer<R Class::*>
		: public bool_<!_is_memfunptr<R Class::*>::value>
	{};

	template<class T> struct is_member_pointer 
		: public bool_<is_member_object_pointer<T>::value || is_member_function_pointer<T>::value>
	{};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @struct	is_void
	///
	/// @brief	.
	///
	/// @author	Yayanyang
	/// @date	2012/2/2
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T> struct _is_void : public false_type{};

	template<> struct _is_void<void> : public true_type{};

	template<typename T> struct is_void 
		: public _is_void<typename remove_cv<T>::type>
	{};
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @struct	is_reference;
	///
	/// @brief	If T is a reference type (either an lvalue reference or an rvalue reference) 
	///			then inherits from true_type, otherwise inherits from false_type. 
	///
	/// @author	Yayanyang
	/// @date	2012/2/2
	////////////////////////////////////////////////////////////////////////////////////////////////////
	

	template<class T> struct is_reference;

	template<class T> struct is_lvalue_reference: public false_type {};

	template<class T> struct is_lvalue_reference<T&>: public true_type {};

#ifdef LEMON_COMPILER_SUPPORT_RVALUE
	template<class T> struct is_rvalue_reference : public false_type {};

	template<class T> struct is_rvalue_reference<T&&>: public true_type {};

	template<class T> struct is_reference : public bool_<is_lvalue_reference<T>::value || is_rvalue_reference<T>::value>{};
#else
	template<class T> struct is_reference : public bool_<is_lvalue_reference<T>::value>{};
#endif //LEMON_COMPILER_SUPPORT_RVALUE

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @struct	is_object
	///
	/// @brief	If T is a (possibly cv-qualified) object type then inherits 
	///			from true_type, otherwise inherits from false_type. 
	///			All types are object types except references, void, and function types. 
	///
	/// @author	Yayanyang
	/// @date	2012/2/2
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class T> struct is_object 
		: public bool_<
		!is_function<T>::value &&
		!is_reference<T>::value &&
		!is_void<T>::value
		>
	{};
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @struct	is_pointer;
	///
	/// @brief	.
	///
	/// @author	Yayanyang
	/// @date	2012/2/2
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class T> struct is_pointer;

	template<class T> struct _is_pointer
		:public false_type
	{

	};

	template<class T> struct _is_pointer<T*>
		:public bool_<!is_member_object_pointer<T*>::value || !is_member_function_pointer<T*>::value>
	{

	};

	template<class T> struct is_pointer
		:public bool_<_is_pointer<typename remove_cv<T>::type>::value>
	{

	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @struct	is_scalar;
	///
	/// @brief	.
	///
	/// @author	Yayanyang
	/// @date	2012/2/2
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class T> struct is_scalar
		:public bool_<
		is_arithmetic<T>::value||
		is_enum<T>::value||
		is_pointer<T>::value||
		is_member_pointer<T>::value
		>
	{

	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @struct	remove_all_extents;
	///
	/// @brief	.
	///
	/// @author	Yayanyang
	/// @date	2012/2/2
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class T> struct remove_all_extents;

	template<class T> struct remove_all_extents
	{
		typedef T type;
	};

	template<class T, size_t N> struct remove_all_extents<T[N]>
	{
		typedef typename remove_all_extents<T>::type type;
	};

	template<class T> struct remove_all_extents<T[]>
	{
		typedef typename remove_all_extents<T>::type type;
	};



	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @struct	is_pod;
	///
	/// @brief	If T is a (possibly cv-qualified) POD type then inherits 
	///			from true_type, otherwise inherits from false_type. 
	///
	/// @author	Yayanyang
	/// @date	2012/2/2
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class T> struct is_pod;

	template<class T> struct _is_pod
		:public bool_<
		is_scalar<T>::value||
		is_void<T>::value||
		is_scalar<T>::value||
		LEMON_HAS_TRIVIAL_CONSTRUCTOR(T) && 
		LEMON_IS_POD(T)
		>
	{

	};

	template<class T> struct is_pod
		:public bool_<_is_pod<typename remove_all_extents<T>::type>::value>
	{

	};

	template<size_t N>
	struct is_pod<placeholder<N> > :public true_type
	{
	};
}


#endif //LEMONXX_TYPE_TRAITS_HPP
