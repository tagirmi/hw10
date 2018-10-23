#include <fstream>
#include <sstream>

#include "bulk_logger.h"

namespace {

std::string getBulkLogName(const hw7::BulkTime& time)
{
  std::stringstream ss;
  ss << "bulk" << time.time_since_epoch().count() << ".log";
  return ss.str();
}

}

void hw10::BulkLogger::update(const hw7::BulkTime& time, const hw7::Bulk& bulk)
{
  std::ofstream fs{getBulkLogName(time)};

  fs << bulk;

  fs.close();
}

hw10::BulkStats hw10::BulkLogger::file1Stats() const
{
  return m_stats1;
}

hw10::BulkStats hw10::BulkLogger::file2Stats() const
{
  return m_stats2;
}
