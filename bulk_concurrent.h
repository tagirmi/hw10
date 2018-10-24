#pragma once

#include <array>
#include <atomic>
#include <mutex>
#include <queue>
#include <thread>

#include "bulk.h"

namespace hw10 {

template<size_t ThreadCount>
class BulkConcurrentObserver : public hw7::BulkObserver
{
public:
  BulkConcurrentObserver()
  {
    for (auto& t : m_threads)
      t = std::thread{&BulkConcurrentObserver::worker, this};
  }

  ~BulkConcurrentObserver()
  {
    m_stop = true;

    for (auto& t : m_threads)
      t.join();
  }

  void update(const hw7::BulkTime& time, const hw7::Bulk& bulk) final override
  {
    std::lock_guard<std::mutex> lock{m_mutex};
    m_queue.emplace(time, bulk);
  }

private:
  virtual void handle(const hw7::BulkTime&, const hw7::Bulk&) = 0;

  void worker()
  {
    while(!m_stop) {
      hw7::BulkTime time;
      hw7::Bulk bulk;

      {
        std::lock_guard<std::mutex> lock{m_mutex};

        if (m_queue.empty())
          continue;

        std::tie(time, bulk) = m_queue.front();
        m_queue.pop();
      }

      handle(time, bulk);
    }
  }

  std::array<std::thread, ThreadCount> m_threads;
  std::queue<std::tuple<hw7::BulkTime, hw7::Bulk>> m_queue;
  std::mutex m_mutex;
  std::atomic<bool> m_stop{false};
};

} // hw10
