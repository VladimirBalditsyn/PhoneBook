#pragma once

#include "PhoneBook.h"
#include <cstdlib>

#include "Trie_with_A-K.cpp"

static const uint32_t seed = 13;
static const size_t num_len = 11;

std::string PhoneBook::AddNumber(std::string person, std::string number) {
  if (!was_addition_) {
    last_add_ = persons_order_.size();
  }
  was_addition_ = true;

  if (phone_base_person_num_.find(person) == phone_base_person_num_.end()) {
    phone_base_person_num_.insert(std::make_pair(person, number));
    phone_base_num_person_.insert(std::make_pair(number, person));
    persons_order_.push_back(person);
    return "Ok";
  }

  uint32_t random_addition = 0;
  for (;;) {
    random_addition = std::rand();
    if (phone_base_person_num_.find(person + std::to_string(random_addition)) !=
        phone_base_person_num_.end()) {
      break;
    }
  }

  std::string new_person =  person + std::to_string(random_addition);
  phone_base_person_num_.insert(std::make_pair(new_person, number));
  phone_base_num_person_.insert(std::make_pair(number, new_person));
  persons_order_.push_back(new_person);

  return new_person;
}

std::string PhoneBook::GetNumber(std::string person) {
  auto iter_to_num = phone_base_person_num_.find(person);

  if (iter_to_num == phone_base_person_num_.end()) {
    return "Not found";
  }
  return iter_to_num->second;
}

std::string PhoneBook::GetPerson(std::string number) {
  auto iter_to_person = phone_base_num_person_.find(number);

  if (iter_to_person == phone_base_num_person_.end()) {
    return "Not found";
  }
  return iter_to_person->second;
}

std::string normalize (std::string& first) {
  std::string stars(num_len - first.length(), '*');
  return first + stars;
}

// предполагается, что в реальной ситуации книга заполняется и затем нечасто обновляется,
// чаще поступают запросы на совпадение паттернов.
void PhoneBook::update_num_str_() {
  if (!was_addition_) {
    return;
  }
  for (size_t i = last_add_; i < persons_order_.size(); ++ i) {
    const std::string& p = phone_base_person_num_[persons_order_[i]];
    for (auto ch : p) {
      big_numbers_string_.push_back(ch);
    }
  }
  was_addition_ = false;
}

std::vector<uint32_t> PhoneBook::find_patterns_occurances(std::string_view
pattern) {
  update_num_str_();
  std::vector<std::pair<std::string_view, size_t>> subpatterns =
      pattern_split(pattern, '*');
  std::vector<uint16_t> count_occurances(big_numbers_string_.length(), 0);
  std::vector<uint32_t> answer;

  Trie trie(subpatterns);
  Aho_Korasick aho_korasick(trie);

  for (size_t i = 0; i < big_numbers_string_.length(); ++i) {
    std::vector<uint32_t> subpattern_occurences_index =
        aho_korasick.next_state(big_numbers_string_[i]);
    for (auto v : subpattern_occurences_index) {
      if (i >= subpatterns[v].second)
        ++count_occurances[i - subpatterns[v].second];
    }
  }
  size_t text_iterate_size = (big_numbers_string_.length() > pattern.length() - 1 ? big_numbers_string_.length() - pattern.length() + 1 : 0);
  for (size_t i = 0; i < text_iterate_size; ++i) {
    if (count_occurances[i] == subpatterns.size())
      answer.push_back(i);
  }
  return answer;
}


std::vector<std::string> PhoneBook::GetFromFirstFigures(std::string
first_fig) {
  std::string norm_string = normalize(first_fig);

  return GetFromPattern(norm_string);
}

std::vector<std::string> PhoneBook::GetFromPattern(const std::string& pattern) {
  auto probably_persons = find_patterns_occurances(pattern);
  std::vector<std::string> result;

  for (auto i : probably_persons) {
    if (i % num_len != 0) {
      continue;
    }
    result.push_back(persons_order_[i / 11]);
  }

  return result;
}
