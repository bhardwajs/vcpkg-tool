#include <vcpkg/base/hash.h>
#include <vcpkg/base/system.print.h>
#include <vcpkg/base/util.h>

#include <vcpkg/commands.hash.h>
#include <vcpkg/vcpkgcmdarguments.h>
#include <vcpkg/vcpkgpaths.h>

namespace vcpkg::Commands::Hash
{
    const CommandStructure COMMAND_STRUCTURE = {
        Strings::format("The argument should be a file path\n%s", create_example_string("hash boost_1_62_0.tar.bz2")),
        1,
        2,
        {},
        nullptr,
    };

    void HashCommand::perform_and_exit(const VcpkgCmdArguments& args, Filesystem& fs) const
    {
        (void)args.parse_arguments(COMMAND_STRUCTURE);

        const auto file_to_hash = (fs.current_path(VCPKG_LINE_INFO) / args.command_arguments[0]).lexically_normal();

        auto algorithm = vcpkg::Hash::Algorithm::Sha512;
        if (args.command_arguments.size() == 2)
        {
            algorithm = vcpkg::Hash::algorithm_from_string(args.command_arguments[1]).value_or_exit(VCPKG_LINE_INFO);
        }

        const std::string hash = vcpkg::Hash::get_file_hash(VCPKG_LINE_INFO, fs, file_to_hash, algorithm);
        print2(hash, '\n');
        Checks::exit_success(VCPKG_LINE_INFO);
    }
}
