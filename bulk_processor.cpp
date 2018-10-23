#include <iostream>

#include "bulk_processor.h"

void hw10::BulkProcessor::update(const hw7::BulkTime&, const hw7::Bulk& bulk)
{
  //TODO log thread
  std::cout << bulk << std::endl;

  m_stats.takeCountOf(bulk);
}

hw10::BulkStats hw10::BulkProcessor::stats() const
{
  return m_stats;
}
