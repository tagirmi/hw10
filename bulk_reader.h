#pragma once

#include <list>
#include <memory>

#include "bulk.h"
#include "bulk_stats.h"

namespace hw7 {

namespace details {

class BulkCollector;

} // details

} // hw7

namespace hw10 {

class BulkReader
{
public:
  explicit BulkReader(size_t bulkSize);
  ~BulkReader();

  void subscribe(const std::shared_ptr<hw7::BulkObserver>&);
  void read();

  size_t lineCount() const;
  BulkStats stats() const;

private:
  void notify(const hw7::BulkTime&, const hw7::Bulk&);
  void stop();

  std::list<std::weak_ptr<hw7::BulkObserver>> m_observers;
  std::unique_ptr<hw7::details::BulkCollector> m_bulkCollector;

  size_t m_lineCount;
  BulkStats m_stats;
};

} // hw10
