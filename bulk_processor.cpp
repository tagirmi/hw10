#include <iostream>

#include "bulk_processor.h"

hw10::BulkProcessor::BulkProcessor()
  : m_promise{}
  , m_future{m_promise.get_future()}
  , m_thread{}
  , m_stats{"log"}
{
  auto worker = [](std::future<hw7::Bulk>& future) {
    while(true) {
      //TODO проверка на выход
      //TODO не работает
      future.wait();
      std::cout << future.get() << std::endl;
    }
  };
  m_thread = std::thread(worker, std::ref(m_future));
}

hw10::BulkProcessor::~BulkProcessor()
{
  if (m_thread.joinable())
    m_thread.join();
}

void hw10::BulkProcessor::update(const hw7::BulkTime&, const hw7::Bulk& bulk)
{
  m_promise.set_value(bulk);
  m_stats.takeCountOf(bulk);
}

hw10::BulkStats hw10::BulkProcessor::stats() const
{
  return m_stats;
}
