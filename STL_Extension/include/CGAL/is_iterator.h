// Copyright (c) 2011  INRIA Saclay Ile-de-France (France).
// All rights reserved.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
// 
//
// Author(s)     : Marc Glisse


#ifndef CGAL_IS_ITERATOR_H
#define CGAL_IS_ITERATOR_H

#include <iterator>
#include <boost/type_traits.hpp>
#include <boost/mpl/has_xxx.hpp>

namespace CGAL {
namespace internal {
BOOST_MPL_HAS_XXX_TRAIT_DEF(iterator_category)
template <class T> struct is_iterator_ {
	enum { value = has_iterator_category<T>::value
	       	|| boost::is_pointer<T>::value }; 
};
template <class T,class U,bool=is_iterator_<T>::value>
struct is_iterator_type_ {
	enum { value=false };
};
template <class T,class U> struct is_iterator_type_<T,U,true> :
	//boost::is_base_of<U,typename std::iterator_traits<T>::iterator_category>
	boost::is_convertible<typename std::iterator_traits<T>::iterator_category,U>
	{};

template <class T> struct decay_array { typedef T type; };
template <class T> struct decay_array<T[]> { typedef T* type; };
template <class T,int d> struct decay_array<T[d]> { typedef T* type; };
}

// NOTE: we don't want the real std::decay or functions are included
template <class T> struct is_iterator :
	internal::is_iterator_<typename internal::decay_array<typename boost::remove_cv<typename boost::remove_reference<T>::type>::type>::type> {};

template <class T,class Tag> struct is_iterator_type :
	internal::is_iterator_type_<typename internal::decay_array<typename boost::remove_cv<typename boost::remove_reference<T>::type>::type>::type,Tag> {};

}

#endif // CGAL_IS_ITERATOR_H
