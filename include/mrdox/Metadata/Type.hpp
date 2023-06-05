//
// This is a derivative work. originally part of the LLVM Project.
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// Copyright (c) 2023 Vinnie Falco (vinnie.falco@gmail.com)
//
// Official repository: https://github.com/cppalliance/mrdox
//

#ifndef MRDOX_API_METADATA_TYPE_HPP
#define MRDOX_API_METADATA_TYPE_HPP

#include <mrdox/Platform.hpp>
#include <mrdox/Metadata/Reference.hpp>

namespace clang {
namespace mrdox {

/** Metadata for naming a type.

    A TypeInfo object names a type.

    Builtin types:

    @li void
    @li std::nullptr_t
    @li bool
    @li char, unsigned char
    @li float, double
    @li short, int, long, long long
    @li unsigned short, unsignd int
    @li unsigned long, unsigned long long
*/
struct TypeInfo
    : Reference
{
    TypeInfo() = default;

    explicit
    TypeInfo(
        Reference const& R) noexcept
        : Reference(R)
    {
    }

    // Convenience constructor for when there is no symbol ID or info type
    // (normally used for built-in types in tests).
    explicit
    TypeInfo(
        std::string_view Name)
        : Reference(
            SymbolID::zero, Name, InfoKind::Default)
    {
    }

#if 0
    // VFALCO What was this for?
    bool operator==(TypeInfo const& Other) const
    {
        return Type == Other.Type;
    }
#endif
};

} // mrdox
} // clang

#endif
