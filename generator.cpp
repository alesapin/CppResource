#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

/// Simple tool which transforms files
/// into binary arrays in .cpp files

static constexpr size_t BUFFER_LENGTH = 4096;

/// Write preamle of special generated resource file
void writePrefix(std::ofstream & ofs, const std::string & rand_name)
{
    ofs << "#include <cstdlib>" << std::endl;
    ofs << "#include \"Resource.h\"" << std::endl;
    ofs << "const unsigned char " << rand_name << "[] = {" << std::endl;
}

/// Write file data in form of hex unsigned char array
void writeData(std::ofstream & ofs, std::ifstream & ifs)
{
    char buffer[BUFFER_LENGTH];

    size_t line_length = 0;
    ifs.read(buffer, BUFFER_LENGTH);
    size_t real_lenth;
    while ((real_lenth = ifs.gcount()))
    {
        for (size_t i = 0; i < real_lenth; ++i)
        {
            int repr = (unsigned char)(buffer[i]);
            ofs << "0x" <<  std::hex << std::setw(2) << std::setfill('0') << repr << ", ";
            if (line_length == 20)
            {
                ofs << "\n";
                line_length = 0;
            }
            else
                line_length++;
        }
        ifs.read(buffer, BUFFER_LENGTH);
    }
}

/// Write suffix of special generated resource file
void writeSuffix(std::ofstream & ofs, const std::string & key, const std::string & name)
{
    ofs << "\n};\n";
    ofs << "size_t " << name << "_len = sizeof(" << name << ");\n";
    ofs << "static CppResource::detail::Resource " << name << "_resource(" << name << ", " << name << "_len);\n\n";
    ofs << "static CppResource::detail::ResourceWrapper " << name << "_resource_wrapper(\"" << key << "\", " << name << "_resource);\n\n";
}

int main(int argc, char ** argv)
{
    if (argc != 4)
    {
        std::cerr << "USAGE: " << argv[0] << " key_name path_to_file\n\n"
                  << "Creates (random_name).cpp from the contents of path_to_file\n";
    }
    std::string key_name(argv[1]);
    std::string path(argv[2]);
    std::string output_path(argv[3]);
    std::string result_name = key_name;
    std::ifstream ifs(path, std::ios::binary);
    std::ofstream ofs(output_path + "/" + result_name + ".cpp",  std::ios::binary);
    writePrefix(ofs, result_name);
    writeData(ofs, ifs);
    writeSuffix(ofs, key_name, result_name);
    ofs.flush();
    return 0;
};
