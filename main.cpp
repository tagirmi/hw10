#include <iostream>

#include "bulk_reader.h"
#include "bulk_processor.h"
#include "bulk_logger.h"

namespace {

size_t parseArg(int argc, char* argv[], size_t& parsed)
{
  if (argc < 2) {
    std::cerr << "command line argument expected; usage: bulk N (N - bulk size)";
    return false;
  }

  try
  {
    parsed = std::stoul(argv[1]);
  }
  catch(const std::invalid_argument&)
  {
    std::cerr << "invalid argument passed to command line";
    return false;
  }
  catch(const std::out_of_range&)
  {
    std::cerr << "didn't convert argument to number";
    return false;
  }

  return true;
}

}

int main(int argc, char* argv[])
{
  try
  {
    size_t bulkSize;
    if (!parseArg(argc, argv, bulkSize))
      return EXIT_FAILURE;

    hw10::BulkReader reader{bulkSize};

    auto processor = std::make_shared<hw10::BulkProcessor>();
    auto logger = std::make_shared<hw10::BulkLogger>();

    reader.subscribe(processor);
    reader.subscribe(logger);

    reader.read();

    std::cout << reader.stats();
    for (const auto& s : processor->stats())
      std::cout << s;
    for (const auto& s : logger->stats())
      std::cout << s;
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
