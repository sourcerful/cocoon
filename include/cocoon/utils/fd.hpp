#ifndef COCOON_UTILS_FD_HPP
#define COCOON_UTILS_FD_HPP

#include <unistd.h>

#include <utility>

namespace cocoon {

class UniqueFd {
  // wrapper RAII class of file descriptors, movable for ownership transfer,
  // non copyable (don't want two instances responsible for the same fd,
  // there should be a single owner).
 private:
  static constexpr int kInvalidFd = -1;
  int fd_ = kInvalidFd;

 public:
  UniqueFd() noexcept = default;
  explicit UniqueFd(int fd_num) noexcept : fd_(fd_num) {}
  // Take ownership of other's fd and leave other with kInvalidFd, so its destructor won't close it.
  UniqueFd(UniqueFd&& other) noexcept : fd_(std::exchange(other.fd_, kInvalidFd)) {}
  UniqueFd(const UniqueFd&) = delete;
  // Close the fd we currently own (if any), then take other's.
  // The self-check matters: without it, a = std::move(a) would close our own fd.
  UniqueFd& operator=(UniqueFd&& other) noexcept {
    if (this != &other) {
      reset();
      fd_ = std::exchange(other.fd_, kInvalidFd);
    }
    return *this;
  }
  UniqueFd& operator=(const UniqueFd&) = delete;

  ~UniqueFd() { reset(); }

  [[nodiscard]]
  int get() const {
    return fd_;
  }

  void reset() noexcept {
    if (fd_ >= 0) {
      // close() result is ignored on purpose: this runs from the destructor, which can't report
      // errors, and on Linux the fd is released even on EINTR, so a retry could close a reused fd.
      close(fd_);
      fd_ = kInvalidFd;
    }
  }
};

}  // namespace cocoon

#endif  // COCOON_UTILS_FD_HPP
