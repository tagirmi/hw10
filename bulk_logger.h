#pragma once

#include "bulk.h"
#include "bulk_stats.h"

namespace hw10 {

class BulkLogger : public hw7::BulkObserver
{
public:
  void update(const hw7::BulkTime&, const hw7::Bulk&) override;

  BulkStats file1Stats() const;
  BulkStats file2Stats() const;

private:
  BulkStats m_stats1{"file1"};
  BulkStats m_stats2{"file2"};
};

} // hw10
