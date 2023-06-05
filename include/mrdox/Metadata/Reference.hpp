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

#ifndef MRDOX_API_METADATA_REFERENCE_HPP
#define MRDOX_API_METADATA_REFERENCE_HPP

#include <mrdox/Platform.hpp>
#include <mrdox/Metadata/Symbols.hpp>
#include <string>
#include <string_view>
#include <utility>

namespace clang {
namespace mrdox {

struct Reference
{
    /** Unique identifier of the referenced symbol.
    */
    SymbolID id = SymbolID::zero;

    // Name of type (possibly unresolved). Not including namespaces or template
    // parameters (so for a std::vector<int> this would be "vector"). See also
    // QualName.
    std::string Name;

    /** The type of the referenced symbol.
    */
    InfoKind RefKind = InfoKind::Default;

    //--------------------------------------------

    // This variant (that takes no qualified name parameter) uses the Name as the
    // QualName (very useful in unit tests to reduce verbosity). This can't use an
    // empty string to indicate the default because we need to accept the empty
    // string as a valid input for the global namespace (it will have
    // "GlobalNamespace" as the name, but an empty QualName).
    Reference(
        SymbolID ID = SymbolID::zero,
        std::string_view Name = "",
        InfoKind kind = InfoKind::Default)
        : id(ID)
        , Name(Name)
        , RefKind(kind)
    {
    }

#if 0
    // VFALCO What was this for?
    bool
    operator==(
        Reference const& Other) const
    {
        // VFALCO Is this function only needed
        //        for the old unit tests?
        return
            std::tie(id, Name, RefKind) ==
            std::tie(Other.id, Other.Name, Other.RefKind);
    }
#endif
};

} // mrdox
} // clang

#endif
