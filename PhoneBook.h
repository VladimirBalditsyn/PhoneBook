#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class PhoneBook {
public:
  // Для упрощения предположим, что номера телефонов уникальны, 11-значны,
  // начинаются с 8. В случае, если данная фамилия уже встречалась, к
  // ней добавится некоторе случайное число, и новая фамилия будет сообщена,
  // в противном случае вернётся "Ok". Время работы - в среднем О(1)
  // (полагая, что большинство фамилий различны)
  std::string AddNumber(std::string person, std::string number);

  // Получаем номер телефона по фамилии (которая в книге). В случае отсутсвия
  // вернётся "Not found". Время работы - О(1)
  std::string GetNumber(std::string person);

  // Получаем фамилию (или изменённую) по номеру. В случае отсутствия
  // вернётся "Not found". Время работы - О(1)
  std::string GetPerson(std::string number);

  // Возвращает вектор фамилий по первым цифрам номера
  std::vector<std::string> GetFromFirstFigures(std::string first_fig);

  // Возвращает вектор фамилий подходящих под паттерн со '*'
  std::vector<std::string> GetFromPattern(const std::string& pattern);

private:
  std::vector<uint32_t> find_patterns_occurances(std::string_view pattern);
  void update_num_str_();

private:
  // В классе в жертву принесена память (ассимптотически все равно O(кол-ва
  // номеров) в угоду отностительной быстроте
  std::unordered_map<std::string, std::string> phone_base_person_num_;
  std::unordered_map<std::string, std::string> phone_base_num_person_;

  bool was_addition_;
  size_t last_add_;
  std::vector<std::string> persons_order_;
  std::string big_numbers_string_;
};

