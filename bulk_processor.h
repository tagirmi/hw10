#pragma once

#include <future>
#include <thread>

#include "bulk.h"
#include "bulk_stats.h"

namespace hw10 {

class BulkProcessor : public hw7::BulkObserver
{
public:
  BulkProcessor();
  ~BulkProcessor();

  void update(const hw7::BulkTime&, const hw7::Bulk&) override;

  BulkStats stats() const;

private:
  std::promise<hw7::Bulk> m_promise;
  std::future<hw7::Bulk> m_future;
  std::thread m_thread;
  BulkStats m_stats{"log"};
};

} // hw7
