#include <fcntl.h>

#include <cstdlib>
#include <iostream>

#include "micro_docker/error.hpp"

int main() {
  try {
    std::string file_path = "/tmp/test_file";
    std::cout << "hello world\n";
    if (open(file_path.c_str(), O_RDONLY) < 0) {
      micro_docker::throw_system_error(file_path);
    }
  } catch (const std::system_error& e) {
    std::cerr << "Error (" << e.code().value() << "): " << e.what() << "\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
