#include <iostream>
#include <Resource.h>


int main(int argc, char ** argv)
{
    const auto & factory = CppResource::ResourceFactory::instance();

    auto string = factory.getAsString("f1");
    std::cerr << string << std::endl;
    std::cerr << factory.getAsString("f2") << std::endl;
    std::cerr << factory.getAsStringView("f3") << std::endl;
    std::cerr << factory.getAsStringView("f4") << std::endl;

    std::cerr << "Contains f4:" << std::boolalpha << factory.has("f4") << std::endl;
    std::cerr << "Contains f5:" << std::boolalpha << factory.has("f5") << std::endl;

    return 0;
}
