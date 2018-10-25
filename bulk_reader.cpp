#include <cassert>
#include <functional>
#include <iostream>

#include "bulk_reader.h"
#include "bulk_collector.h"

hw10::BulkReader::BulkReader(size_t bulkSize)
  : m_observers{}
  , m_lineCount{}
  , m_stats{"main"}
{
  using namespace std::placeholders;
  m_bulkCollector = std::make_unique<hw7::details::BulkCollector>(bulkSize, std::bind(&BulkReader::notify, this, _1, _2));
}

hw10::BulkReader::~BulkReader()
{
}

void hw10::BulkReader::subscribe(const std::shared_ptr<hw7::BulkObserver>& observer)
{
  assert(observer);

  m_observers.emplace_back(observer);
}

void hw10::BulkReader::read()
{
  for (std::string cmd; std::getline(std::cin, cmd);) {
    m_bulkCollector->add(cmd);
    ++m_lineCount;
  }

  m_bulkCollector->endData();

  stop();
}

size_t hw10::BulkReader::lineCount() const
{
  return m_lineCount;
}

hw10::BulkStats hw10::BulkReader::stats() const
{
  return m_stats;
}

void hw10::BulkReader::notify(const hw7::BulkTime& bulkTime, const hw7::Bulk& bulk)
{
  for (auto& i : m_observers) {
    auto p = i.lock();
    if (p)
      p->update(bulkTime, bulk);
  }

  m_stats.takeCountOf(bulk);
}

void hw10::BulkReader::stop()
{
  for (auto& i : m_observers) {
    auto p = i.lock();
    if (p)
      p->stop();
  }
}
