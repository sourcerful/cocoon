#ifndef MICRO_DOCKER_ERROR_HPP
#define MICRO_DOCKER_ERROR_HPP

#include <cerrno>
#include <string>
#include <string_view>
#include <system_error>

namespace micro_docker {
[[noreturn]] inline void throw_system_error(const std::string_view what) {
  int err_code = errno;
  throw std::system_error(err_code, std::system_category(), std::string(what));
}

}  // namespace micro_docker

#endif  // MICRO_DOCKER_ERROR_HPP
