/*!
 * This is a template code to demonstrate how to measure runtime of part of your
 * code. I'm using the chrono C++ library.
 * @date September 8th, 2020.
 * @author Selan
 */

#include <chrono>
#include <iostream>

int main() {

  std::cout
      << ">>> STARTING computation that needs timing, please WAIT.... <<<\n";
  auto start = std::chrono::steady_clock::now();
  //================================================================================

  // >>>>>>>>  Put the code that needs timing here  <<<<<<<<<<<< //
  typedef int test_t; // The testing type for increment.
  int a{1};
  for (test_t i = std::numeric_limits<test_t>::min();
       i < std::numeric_limits<test_t>::max(); ++i)
    // for ( unsigned long long j{0} ; j < std::numeric_limits<unsigned long
    // long>::max() ; ++j ) for ( unsigned long long j{0} ; j <
    // std::numeric_limits<unsigned long long>::max() ; ++j )
    a *= 2;

  //================================================================================
  std::chrono::time_point<std::chrono::steady_clock> end =
      std::chrono::steady_clock::now();
  std::cout << ">>> ENDING computation that needs timing <<<\n";

  // Store the time difference between start and end
  //  auto diff = end - start;
  std::chrono::duration<double> diff = end - start;

  // Milliseconds (10^-3)
  std::cout << "\t\t>>> "
            << std::chrono::duration<double, std::milli>(diff).count() << " ms"
            << std::endl;

  // Nanoseconds (10^-9)
  std::cout << "\t\t>>> "
            << std::chrono::duration<double, std::nano>(diff).count() << " ns"
            << std::endl;

  // Seconds
  auto diff_sec = std::chrono::duration_cast<std::chrono::seconds>(diff);
  std::cout << "\t\t>>> " << diff_sec.count() << " s" << std::endl;

  return EXIT_SUCCESS;
}
