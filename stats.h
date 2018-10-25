#pragma once

#include <string>
#include <iostream>
#include <map>

namespace hw10 {

class Stats
{
public:
  explicit Stats(const std::string& name);

  Stats() = default;
  Stats(const Stats&) = default;
  Stats& operator=(const Stats&) = default;

  void takeCountOf(const std::string&, size_t count);
  std::string name() const;

  auto begin();
  auto begin() const;
  auto end();
  auto end() const;

private:
  std::string m_name;
  std::map<std::string, size_t> m_metrics;
};

} // hw10

std::ostream& operator<<(std::ostream&, const hw10::Stats&);
