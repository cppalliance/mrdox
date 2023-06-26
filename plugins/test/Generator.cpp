//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// Copyright (c) 2023 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Official repository: https://github.com/cppalliance/mrdox
//

#include <mrdox/Generator.hpp>
#include <mrdox/Generators.hpp>
#include "mrdox/Version.hpp"
#include "mrdox/Support/Report.hpp"

struct myGen final : public clang::mrdox::Generator
{
    std::string_view
    id() const noexcept override {
        return "test";
    }

    std::string_view
    displayName() const noexcept override {
        return "test generator";
    }

    std::string_view
    fileExtension() const noexcept override {
        return "test";
    }

    clang::mrdox::Error
    buildOne(
            std::ostream &os,
            clang::mrdox::Corpus const &corpus) const override
            {
        os << "It works!";
        return {};
    }
};


extern "C"
MRDOX_SYMBOL_EXPORT
void
MrDoxPluginMain(
        int versionMajor,
        int versionMinor )
{
    using namespace clang::mrdox;
    if (versionMajor != projectVersionMajor)
        return reportError("invalid version for test plugin {}", projectVersionMajor);

    auto err = getGenerators().insert(std::make_unique<myGen>());

    if (err)
        reportError("can't add generator, because {} ", err);
}
