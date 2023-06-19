//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// Copyright (c) 2023 Vinnie Falco (vinnie.falco@gmail.com)
//
// Official repository: https://github.com/cppalliance/mrdox
//

#include <mrdox/Dom/DomBase.hpp>
#include <mrdox/Dom/DomSymbol.hpp>
#include <mrdox/Dom/DomType.hpp>

namespace clang {
namespace mrdox {

DomBase::
DomBase(
    RecordInfo const& I,
    BaseInfo const& B,
    Corpus const& corpus) noexcept
    : DomSymbol<RecordInfo>(I, corpus)
    , B_(&B)
{
}

dom::Value
DomBase::
get(std::string_view key) const
{
    if(key == "type")
        return dom::makePointer<DomType>(B_->Type, corpus_);
    if(key == "base-access")
        return toString(B_->Access);
    if(key == "is-virtual")
        return B_->IsVirtual;

    return DomSymbol<RecordInfo>::get(key);
}

auto
DomBase::
props() const ->
    std::vector<std::string_view>
{
    std::vector<std::string_view> v =
        DomSymbol<RecordInfo>::props();
    v.insert(v.end(), {
        "type",
        "base-access",
        "is-virtual"
        });
    return v;
}

} // mrdox
} // clang