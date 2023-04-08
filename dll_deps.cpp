#include "tools/cpp/runfiles/runfiles.h"

#include <fstream>

int main(int argc, const char* argv[])
{
    using bazel::tools::cpp::runfiles::Runfiles;

    std::string error;
    // For tests it should be CreateforTest
    const auto runfiles{ Runfiles::Create(argv[0], BAZEL_CURRENT_REPOSITORY, &error) };
    if (runfiles == nullptr) {
        fprintf(stderr, "ERROR(%s): %s\n", argv[0], error.c_str());
        return 1;
    }
    const auto input_filename{ runfiles->Rlocation(DEPS_FILE) };
    const auto output_filename{ std::string( argv[1] ) };

    fprintf(stderr, "Input: [%s]\n", input_filename.c_str() );
    fprintf(stderr, "Output: [%s]\n", output_filename.c_str() );

    std::fstream input_file; 
    input_file.open(input_filename, std::ios::in);
    if( !input_file.is_open() ) {
        fprintf(stderr, "ERROR(%s): Can't open input file %s\n", argv[0], input_filename.c_str() );
        return 1;
    }

    std::fstream output_file; 
    output_file.open(output_filename, std::ios::out | std::ios::binary);
    if( !output_file.is_open() ) {
        fprintf(stderr, "ERROR(%s): Can't open output file %s\n", argv[0], output_filename.c_str() );
        return 1;
    }

    std::string line;
    output_file
        << "# This file has been generated by dll_deps" << '\n'
        << "DLL_DEPS = {" << '\n';
    while( std::getline(input_file, line) )
        output_file << "  Label(\"@" << line << "\"): None," << '\n';
    output_file << "}" << '\n';
    return 0;
}
