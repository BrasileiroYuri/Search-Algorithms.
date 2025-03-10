/*!
 * This is a template code to demonstrate how to measure runtime of part of your
 * code. I'm using the chrono C++ library.
 * @date September 8th, 2020.
 * @author Selan
 */

#include <chrono>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <map>
#include <numeric>
#include <unordered_map>
#include <vector>

#include "searching.h"

using sa::value_type;

using TestFunction = value_type *(*)(value_type *first, value_type *last,
                                     value_type value);

std::unordered_map<TestFunction, std::string> func_names = {
    {sa::lsearch, "LSearch"},         {sa::bsearch, "BSearch"},
    {sa::bsearch_rec, "BSearch_Rec"}, {sa::tsearch, "TSearch"},
    {sa::lbound, "LBound"},           {sa::ubound, "UBound"},
    {sa::isearch, "ISearch"},         {sa::esearch, "ESearch"}};

struct RunningOptions {
  static constexpr value_type TAM{10000000};
  static constexpr value_type QTD_AMOSTRAS{1000};
  static constexpr value_type INCREMENT{TAM / QTD_AMOSTRAS};
  static constexpr value_type QTD_POR_AMOSTRA{100};
  static constexpr const char *FILENAME{"data/data_1000.txt"};
};

std::map<value_type, std::vector<std::chrono::duration<double, std::micro>>>
get_time() {

  std::vector<int> vec(RunningOptions::TAM);
  std::iota(vec.begin(), vec.end(), 1);

  TestFunction funcs[]{sa::lsearch, sa::bsearch, sa::bsearch_rec, sa::tsearch,
                       sa::lbound,  sa::ubound,  sa::isearch,     sa::esearch};

  std::map<value_type, std::vector<std::chrono::duration<double, std::micro>>>
      times;

  std::cout
      << ">>> STARTING computation that needs timing, please WAIT... <<<\n\n";

  for (TestFunction const &func : funcs) {

    std::cout << ">>> Function: " << func_names[func] << " <<<\n";

    for (value_type i{0}; i < RunningOptions::TAM;
         i += RunningOptions::INCREMENT) {

      std::chrono::duration<double, std::micro> sum{0};

      for (value_type j{0}; j < RunningOptions::QTD_POR_AMOSTRA; j++) {

        std::chrono::time_point<std::chrono::steady_clock> start =
            std::chrono::steady_clock::now();
        func(vec.data(), vec.data() + i, 0);

        std::chrono::time_point<std::chrono::steady_clock> end =
            std::chrono::steady_clock::now();

        sum += (end - start);
      }

      times[i].push_back(sum / RunningOptions::QTD_POR_AMOSTRA);
    }
  }
  std::cout << "\n>>> ENDING computation that needs timing. <<<\n";
  return times;
}

void write_data(
    const std::map<value_type,
                   std::vector<std::chrono::duration<double, std::micro>>>
        &m_times) {

  std::ofstream file(RunningOptions::FILENAME);

  if (not file.is_open()) {
    std::cerr << "Erro ao abrir arquivo " << RunningOptions::FILENAME << "\n";
  }

  std::cout << "\n>>> STARTING writing of data... <<<\n";

  file << "# Mediçao de tempo de algoritmos de busca (WORST CASE): \n";

  file << "#" << std::setw(14) << std::left << "Tamanho";

  for (const auto &func_name : func_names) {
    file << std::setw(15) << std::left << func_name.second;
  }
  file << "\n";

  for (const auto &key : m_times) {
    file << std::setw(15) << std::left
         << key.first; // Tamanho, alinhado à esquerda

    for (const auto &time : key.second) {
      file << std::setw(15) << std::left << std::fixed << std::setprecision(2)
           << time.count() * 100;
    }

    file << "\n";
  }

  file.close();
  std::cout << ">>> ENDING writing of data. <<<\n";
}

int main() {

  auto times = get_time();
  write_data(times);

  return EXIT_SUCCESS;
}
