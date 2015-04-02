#ifndef preney_benchmark_hxx_
#define preney_benchmark_hxx_

#include <chrono>

template <typename Clock = std::chrono::high_resolution_clock>
class benchmark
{
public:
  using time_point_type = typename Clock::time_point;

private:
  bool was_started_;
  time_point_type start_;
  time_point_type stop_;

public:
  benchmark() : was_started_{false} { }
  benchmark(bool autostart) : was_started_{autostart} 
  { 
    if (was_started_) 
      start(); 
  }

  bool started() const { return was_started_; }

  void start() { start_ = Clock::now(); was_started_ = true; }
  void stop() { stop_ = Clock::now(); }

  auto duration_ms() const ->
    decltype(std::chrono::duration_cast<std::chrono::milliseconds>(
      stop_ - start_).count())
  {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
      stop_ - start_).count();
  }

  auto duration_us() const ->
    decltype(std::chrono::duration_cast<std::chrono::microseconds>(
      stop_ - start_).count())
  {
    return std::chrono::duration_cast<std::chrono::microseconds>(
      stop_ - start_).count();
  }
  
  auto duration_ns() const ->
    decltype(std::chrono::duration_cast<std::chrono::nanoseconds>(
      stop_ - start_).count())
  {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
      stop_ - start_).count();
  }

  long double resolution() const
  {
    using period = typename Clock::period;
    return double(period::num)/period::den;
  }
};

#endif // #ifndef preney_benchmark_hxx_
