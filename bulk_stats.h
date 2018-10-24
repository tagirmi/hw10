#pragma once

#include <string>
#include <iostream>

#include "bulk.h"

namespace hw10 {

class BulkStats
{
public:
  explicit BulkStats(const std::string& name);

  BulkStats() = default;
  BulkStats(const BulkStats&) = default;
  BulkStats& operator=(const BulkStats&) = default;

  void takeCountOf(const hw7::Bulk&);

  std::string name() const;
  size_t bulkCount() const;
  size_t totalCommandCount() const;

private:
  std::string m_name;
  size_t m_bulkCount;
  size_t m_totalCommandCount;
};

} // hw10

std::ostream& operator<<(std::ostream&, const hw10::BulkStats&);
