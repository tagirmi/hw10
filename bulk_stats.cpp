#include "bulk_stats.h"

hw10::BulkStats::BulkStats(const std::string& name)
  : m_name{name}
  , m_bulkCount{}
  , m_totalCommandCount{}
{
}

void hw10::BulkStats::takeCountOf(const hw7::Bulk& bulk)
{
  ++m_bulkCount;
  m_totalCommandCount += bulk.size();
}

std::string hw10::BulkStats::name() const
{
  return m_name;
}

size_t hw10::BulkStats::bulkCount() const
{
  return m_bulkCount;
}

size_t hw10::BulkStats::totalCommandCount() const
{
  return m_totalCommandCount;
}

std::ostream& operator<<(std::ostream& os, const hw10::BulkStats& stats)
{
  os << stats.name() << ": "
     << stats.bulkCount() << " bulks; "
     << stats.totalCommandCount() << " commands"
     << std::endl;

  return os;
}
