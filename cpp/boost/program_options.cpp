// g++ program_options.cpp -pedantic -lboost_program_options
#include <boost/program_options.hpp>
#include <iostream>
namespace po = boost::program_options;

int main(int argc, const char** argv) {
  // Добавление различных опций внутрь boost_program_options
  // string-opton превратится в "длинную" опцию --string-option,
  // в паре с ней можно задать "короткую" опцию -s.
  po::options_description desc("Options:");
  desc.add_options()("help", "Show this help.")(
      "string-option,s", po::value<std::string>(), "String value.");

  // Дальше буст парсит опции использую argc и argv и выводит
  // help в случае если ни одна опция не задана, задана сама
  // опция --help, либо неизвестная опция типа --gggbbbbzzzz
  po::variables_map vm;
  bool has_unknown_options = false;
  try {
    po::store(po::parse_command_line(argc, argv, desc), vm);
  } catch (po::error e) {
    has_unknown_options = true;
  }
  if (has_unknown_options || vm.count("help") || argc == 1) {
    std::cout << desc << std::endl;
    return 0;
  }

  // Получаем в строку s значение из опции.
  if (vm.count("string-option")) {
    const std::string& s = vm["string-option"].as<std::string>();
    std::cout << "string-option = " << s << std::endl;
  }

  po::notify(vm);

  return 0;
}