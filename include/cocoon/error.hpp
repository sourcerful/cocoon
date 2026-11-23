#ifndef COCOON_ERROR_HPP
#define COCOON_ERROR_HPP

#include <cerrno>
#include <string>
#include <string_view>
#include <system_error>

namespace cocoon {
[[noreturn]] inline void throw_system_error(const std::string_view what) {
  int err_code = errno;
  throw std::system_error(err_code, std::system_category(), std::string(what));
}

}  // namespace cocoon

#endif  // COCOON_ERROR_HPP
