cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
  set(BUILD $ENV{TRAVIS_BUILD_NUMBER})
else()
  set(BUILD 0)
endif()

project(bulkmt VERSION 0.0.${BUILD})

add_executable(${PROJECT_NAME} main.cpp bulk_reader.cpp bulk_processor.cpp bulk_logger.cpp bulk_collector.cpp bulk_stats.cpp)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT tagirmi@gmail.com)

include (CPack)