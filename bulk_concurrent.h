#pragma once

#include <array>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

#include "bulk.h"
#include "bulk_stats.h"

namespace hw10 {

template<size_t ThreadCount>
class BulkConcurrentObserver : public hw7::BulkObserver
{
public:
  BulkConcurrentObserver(std::array<std::string, ThreadCount> names)
  {
    for (size_t i = 0; i < ThreadCount; ++i) {
      m_threads[i] = std::thread{&BulkConcurrentObserver::worker, this, i};
      m_stats[i] = BulkStats{names[i]};
    }
  }

  ~BulkConcurrentObserver()
  {
    stop();
  }

  void stop()
  {
    m_stop = true;

    for (auto& t : m_threads)
      if (t.joinable())
        t.join();
  }

  void update(const hw7::BulkTime& time, const hw7::Bulk& bulk) final override
  {
    std::unique_lock<std::mutex> lock{m_queueMutex};
    m_queue.emplace(time, bulk);
    m_ready.notify_all();
  }

  auto stats() const
  {
    std::lock_guard<std::mutex> lock{m_statsMutex};
    return m_stats;
  }

private:
  virtual void handle(const hw7::BulkTime&, const hw7::Bulk&) = 0;

  void worker(int statIndex)
  {
    while(!m_stop) {
      hw7::BulkTime time;
      hw7::Bulk bulk;

      {
        std::unique_lock<std::mutex> lock{m_queueMutex};

        while (m_queue.empty() && !m_stop)
          m_ready.wait(lock);
//        m_ready.wait(lock, [this]() { return !m_queue.empty() && !m_stop; });
        if (m_stop)
          break;

        std::tie(time, bulk) = m_queue.front();
        m_queue.pop();
      }

      handle(time, bulk);

      {
        std::lock_guard<std::mutex> lock{m_statsMutex};
        m_stats[statIndex].takeCountOf(bulk);
      }
    }
  }

  std::array<std::thread, ThreadCount> m_threads;
  std::queue<std::tuple<hw7::BulkTime, hw7::Bulk>> m_queue;
  std::mutex m_queueMutex;
  std::atomic<bool> m_stop{false};
  std::condition_variable m_ready;

  std::array<BulkStats, ThreadCount> m_stats;
  mutable std::mutex m_statsMutex;
};

} // hw10
