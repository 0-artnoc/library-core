////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/Containers/Triple.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Core_Containers_Triple__
#define __Library_Core_Containers_Triple__

#include <Library/Core/Containers/Tuple.hpp>
#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Size.hpp>
#include <Library/Core/Types/Index.hpp>

#include <utility>
#include <ostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace core
{
namespace ctnr
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Index ;
using library::core::types::Size ;
using library::core::types::String ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Triple container

template <typename T, typename U, typename V>
struct Triple
{

    T                           first ; 
    U                           second ;
    V                           third ;

} ;

template <typename T, typename U, typename V>
Triple<T,U,V>                   make_triple                                (    const   T&                          aFirstElement,
                                                                                const   U&                          aSecondElement,
                                                                                const   V&                          aThirdElement                               ) ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/Containers/Triple.tpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////