#include <iostream>
#include "PhoneBook.h"
#include "PhoneBook.cpp"

int main() {
  auto pers1 = std::make_pair("Иванов", "89239426237");
  auto pers2 = std::make_pair("Петров", "89235426237");
  auto pers3 = std::make_pair("Сидоров", "89239426223");
  auto pers4 = std::make_pair("Крахмалёв", "89999999999");
  auto pers5 = std::make_pair("Старичков", "87777777777");

  PhoneBook book;

  std::cout << book.AddNumber(pers1.first, pers1.second) << '\n'; //Ok
  std::cout << book.AddNumber(pers2.first, pers2.second) << '\n'; //Ok
  std::cout << book.AddNumber(pers3.first, pers3.second) << '\n'; //Ok
  std::cout << book.AddNumber(pers4.first, pers4.second) << '\n'; //Ok
  std::cout << book.AddNumber(pers5.first, pers5.second) << '\n'; //Ok

  std::cout<<book.GetNumber(pers4.first) << '\n'; // 89999999999
  std::cout<<book.GetNumber("Иванова") << '\n'; // No found

  std::cout<<book.GetPerson(pers5.second) << '\n'; // Старичков
  std::cout<<book.GetPerson("89376547754") << '\n'; // Not found

  auto r1 = book.GetFromFirstFigures("89239");
  for (const auto& s : r1) {
    std::cout<<s <<' '; // Иванов Сидоров
  }
  std::cout <<'\n';

  auto r2 = book.GetFromPattern("89**9******");
  for (const auto& s : r2) {
    std::cout<<s <<' '; // Иванов Сидоров Крахмалёв
  }
  std::cout <<'\n';
  return 0;
}