//
// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#ifndef TF_OSTREAMMETHODS_H
#define TF_OSTREAMMETHODS_H

#include "pxr/base/tf/hashmap.h"
#include "pxr/base/arch/defines.h"
#include <ciso646>
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <type_traits>

#include <boost/type_traits/has_left_shift.hpp>

/*!
 * \file tf/ostreamMethods.h
 * \brief Handy ostream output for various lib/tf and STL containers.
 * \ingroup group_tf_DebuggingOutput
 *
 * These functions are useful when you need to quickly output various STL
 * containers.  The stream operators are only available if the contained types
 * have stream operators.
 *
 * This facility should \e not be used to output data for later input: this is
 * essentially a "write-only" facility meant for diagnostics or human-readable
 * display; the formats described herein are subject to change without notice.
 */

template <class T>
constexpr bool Tf_IsOstreamable() {
    return boost::has_left_shift<
        std::ostream &, /* << */ T, /* -> */ std::ostream &>::value;
}


// These operator<< overloads need to go in the std namespace for
// Koenig lookup to work.
namespace std {

//! \brief Output an STL vector using [ ] as delimiters.
// \ingroup group_tf_DebuggingOutput
template <class T>
typename std::enable_if<Tf_IsOstreamable<T>(), std::ostream &>::type
operator<<(std::ostream &out, const std::vector<T> &v)
{
    out << "[ ";
    for (auto const &obj: v)
        out << obj << " ";
    out << "]";

    return out;
}

//! \brief Output an STL set using ( ) as delimiters.
// \ingroup group_tf_DebuggingOutput
template <class T>
typename std::enable_if<Tf_IsOstreamable<T>(), std::ostream &>::type
operator<<(std::ostream &out, const std::set<T> &v)
{
    out << "( ";
    for (auto const &obj: v)
        out << obj << " ";
    out << ")";

    return out;
}

//! \brief Output an STL list using { } as delimiters.
// \ingroup group_tf_DebuggingOutput
template <class T>
typename std::enable_if<Tf_IsOstreamable<T>(), std::ostream &>::type
operator<<(std::ostream &out, const std::list<T> &l)
{
    out << "{ ";
    for (auto const &obj: l)
        out << obj << " ";
    out << "}";

    return out;
}

//! \brief Output an TfHashMap using < > as delimiters.
// \ingroup group_tf_DebuggingOutput
template <class K, class M, class H, class C, class A>
typename std::enable_if<
    Tf_IsOstreamable<K>() and Tf_IsOstreamable<M>(), std::ostream &>::type
operator<<(std::ostream &out, const TfHashMap<K, M, H, C, A> &h)
{
    out << "< ";
    for (auto const &p: h)
        out << "<" << p.first << ": " << p.second << "> ";
    out << ">";
    return out;
}

//! \brief Output an STL map using < > as delimiters.
// \ingroup group_tf_DebuggingOutput
template <class K, class M>
typename std::enable_if<
    Tf_IsOstreamable<K>() and Tf_IsOstreamable<M>(), std::ostream &>::type
operator<<(std::ostream &out, const std::map<K, M> &h)
{
    out << "< ";
    for (auto const &p: h)
        out << "<" << p.first << ": " << p.second << "> ";
    out << ">";
    return out;
}

} // namespace std



#endif /* TF_OSTREAMMETHODS_H */
