#pragma once

#include <vcpkg/base/cstringview.h>

#include <vcpkg/build.h>

#include <array>

namespace vcpkg::PostBuildLint
{
    struct BuildType
    {
        BuildType() = delete;

        constexpr BuildType(Build::ConfigurationType c, Build::LinkageType l) : config(c), linkage(l) { }

        bool has_crt_linker_option(StringView sv) const;
        StringLiteral to_string() const;

        Build::ConfigurationType config;
        Build::LinkageType linkage;

        friend bool operator==(const BuildType& lhs, const BuildType& rhs)
        {
            return lhs.config == rhs.config && lhs.linkage == rhs.linkage;
        }
        friend bool operator!=(const BuildType& lhs, const BuildType& rhs) { return !(lhs == rhs); }
    };
}
