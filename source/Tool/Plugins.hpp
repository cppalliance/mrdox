//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// Copyright (c) 2023 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Official repository: https://github.com/cppalliance/mrdox
//

#ifndef MRDOX_TOOL_PLUGINS_HPP
#define MRDOX_TOOL_PLUGINS_HPP

#include <mrdox/Support/Error.hpp>

namespace clang {
namespace mrdox {

class Config;
class Generators;

Error
loadPlugins(
        std::string_view addonsDir
        );

}
}

#endif //MRDOX_TOOL_PLUGINS_HPP
