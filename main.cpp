#include <iostream>

#include "bulk_reader.h"
#include "bulk_processor.h"
#include "bulk_logger.h"

namespace {

size_t parseArg(int argc, char* argv[])
{
  try
  {
    if (argc < 2)
      throw std::logic_error("command line argument expected; usage: bulk N (N - bulk size)");

    return std::stoul(argv[1]);
  }
  catch(const std::invalid_argument&)
  {
    throw std::logic_error("invalid argument passed to command line");
  }
  catch(const std::out_of_range&)
  {
    throw std::logic_error("didn't convert argument to number");
  }
}

}

int main(int argc, char* argv[])
{
  try
  {
    hw10::BulkReader reader{parseArg(argc, argv)};

    auto processor = std::make_shared<hw10::BulkProcessor>();
    auto logger = std::make_shared<hw10::BulkLogger>();

    reader.subscribe(processor);
    reader.subscribe(logger);

    reader.read();

    std::cout << reader.stats() << reader.lineCount() << " lines" << std::endl;
    std::cout << processor->stats();
    std::cout << logger->file1Stats();
    std::cout << logger->file2Stats();
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
