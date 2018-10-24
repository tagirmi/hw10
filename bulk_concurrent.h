#pragma once

#include "bulk.h"

namespace hw10 {

class BulkConcurrentObserver : public hw7::BulkObserver
{
  public:
    void update(const hw7::BulkTime&, const hw7::Bulk&) final override;

  private:
    virtual void handle(const hw7::BulkTime&, const hw7::Bulk&) = 0;
};

} // hw10
