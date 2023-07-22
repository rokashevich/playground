#include <chrono>   // chrono::system_clock
#include <ctime>    // localtime
#include <iomanip>  // put_time
#include <iostream>
#include <sstream>  // stringstream
#include <string>   // string
std::string timestamp() {
  const auto now = std::chrono::system_clock::now();
  const auto in_time_t = std::chrono::system_clock::to_time_t(now);
  const auto milliseconds =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          now.time_since_epoch())
          .count();
  const auto seconds =
      std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch())
          .count();
  const auto ms = milliseconds - seconds * 1000;
  std::cout << ms << std::endl;

  std::stringstream ss;
  ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H%M%S");
  return ss.str();
}
int main() {
  auto time = std::chrono::system_clock::now();
  std::cout << timestamp() << std::endl;
  return 0;
}