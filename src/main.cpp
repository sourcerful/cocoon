#include <fcntl.h>

#include <cerrno>
#include <cstdlib>
#include <iostream>

#include "cocoon/error.hpp"
#include "cocoon/utils/fd.hpp"

namespace {
bool isOpen(int fd) { return fcntl(fd, F_GETFD) != -1 || errno != EBADF; }
}  // namespace

int main() {
  try {
    std::string file_path = "/tmp/test_file";
    int fd = 0;
    {
      int raw_fd = open(file_path.c_str(), O_RDONLY);
      if (raw_fd < 0) {
        cocoon::throw_system_error("open " + file_path);
      }
      cocoon::UniqueFd ufile_descriptor(raw_fd);
      fd = ufile_descriptor.get();

      std::cout << "fd " << ufile_descriptor.get() << ": " << isOpen(ufile_descriptor.get());
    }
    std::cout << "\n";
    std::cout << "fd " << fd << ": " << isOpen(fd) << "\n";

  } catch (const std::system_error& e) {
    std::cerr << "Error (" << e.code().value() << "): " << e.what() << "\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
