#pragma once

#include "bulk.h"
#include "bulk_stats.h"

namespace hw10 {

class BulkProcessor : public hw7::BulkObserver
{
public:
  BulkProcessor() = default;
  ~BulkProcessor() = default;

  void update(const hw7::BulkTime&, const hw7::Bulk&) override;

  BulkStats stats() const;

private:
  BulkStats m_stats{"log"};
};

} // hw7
