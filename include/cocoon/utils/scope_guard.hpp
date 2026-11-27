#ifndef COCOON_UTILS_SCOPE_GUARD_HPP
#define COCOON_UTILS_SCOPE_GUARD_HPP

#include <utility>

namespace cocoon {

// Runs a cleanup callback when the guard goes out of scope, unless disarm() was called.
// Typical use: undo a half-finished setup if anything after it throws.
//
//   ScopeGuard guard([&] { kill(child, SIGKILL); });
//   setup_cgroup(child);  // throws -> guard runs the cleanup
//   guard.disarm();       // success -> cleanup is skipped
//
// The callback must not throw: it runs from a destructor.
template <typename F>
class ScopeGuard {
 public:
  explicit ScopeGuard(F cleanup) : cleanup_(std::move(cleanup)) {}

  // A guard is tied to the scope it was created in: no copies, no moves.
  ScopeGuard(const ScopeGuard&) = delete;
  ScopeGuard& operator=(const ScopeGuard&) = delete;
  ScopeGuard(ScopeGuard&&) = delete;
  ScopeGuard& operator=(ScopeGuard&&) = delete;

  ~ScopeGuard() {
    if (active_) {
      cleanup_();
    }
  }

  void disarm() noexcept { active_ = false; }

 private:
  F cleanup_;
  bool active_ = true;
};

}  // namespace cocoon

#endif  // COCOON_UTILS_SCOPE_GUARD_HPP
