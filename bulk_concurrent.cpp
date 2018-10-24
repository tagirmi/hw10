#include "bulk_concurrent.h"

void hw10::BulkConcurrentObserver::update(const hw7::BulkTime& time, const hw7::Bulk& bulk)
{
  //TODO make concurrent handle
  handle(time, bulk);
}
