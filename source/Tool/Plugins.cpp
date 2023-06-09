//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// Copyright (c) 2023 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Official repository: https://github.com/cppalliance/mrdox
//

#include "Plugins.hpp"


#include <mrdox/Config.hpp>
#include <mrdox/Generators.hpp>
#include <mrdox/Support/Path.hpp>
#include <mrdox/Support/Report.hpp>
#include <mrdox/Version.hpp>

#include "ToolWorld.hpp"
#include "Support/Path.hpp"
#include "Support/Debug.hpp"

#include <llvm/Support/FileSystem.h>
#include <llvm/Support/DynamicLibrary.h>
#include <llvm/Support/Path.h>

namespace clang {
namespace mrdox {

Error
loadPlugins(
        std::string_view addonsDir
        )
{

    std::string err_;

    SmallPathString pluginPath{addonsDir};
    llvm::sys::path::append(pluginPath, "plugins");

    namespace fs = llvm::sys::fs;

    std::error_code ec;
    for (auto itr = fs::directory_iterator(pluginPath, ec);
         itr != fs::directory_iterator() && !ec;
         itr.increment(ec))
    {
        if (!itr->path().ends_with(".dll")
         && !itr->path().ends_with(".so"))
            continue;

        auto lib = llvm::sys::DynamicLibrary::getLibrary(itr->path().c_str(), &err_);
        toolWorld().plugins.push_back(lib);
        if (!lib.isValid())
            return formatError("getPermanentLibrary({}) failed with error {}", itr->path(), err_);
        auto mkgen = lib.getAddressOfSymbol("MrDoxPluginMain");

        if (!mkgen)
            return formatError("the plugin entry point MrDoxPluginMain was not found in {}",
                                itr->path());


        reportInfo("Loaded plugin {}, initializing.", itr->path());
        using MrDoxPluginMainSignature = void(int, int);
        (*reinterpret_cast<MrDoxPluginMainSignature*>(mkgen))(projectVersionMajor, projectVersionMinor);
        reportInfo("Initialized {}.", itr->path());
    }
    if (ec)
        return formatError("Loading from the plugins directory failed {}", ec);
    return {};
}

}
}
