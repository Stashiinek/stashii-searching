#include "CLI/App.hpp"
#include "CLI/Config.hpp"
#include "CLI/Formatter.hpp"
#include "libfts/summ.hpp"
#include <iostream>

int main(int argc, char **argv) {
  CLI::App app{"App description"};

  double a = 0;
  double b = 0;

  app.add_option("--first", a, "");
  app.add_option("--second", b, "");

  CLI11_PARSE(app, argc, argv);
  double c = summ(a, b);
  std::cout << "Result: " << c << std::endl;

  return 0;
}
