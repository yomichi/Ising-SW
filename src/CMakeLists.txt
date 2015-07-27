cmake_minimum_required(VERSION 2.8.0 FATAL_ERROR)
project(scheduler)

# find ALPS Library
find_package(ALPS REQUIRED PATHS ${ALPS_ROOT_DIR} $ENV{ALPS_HOME} NO_SYSTEM_ENVIRONMENT_PATH)
message(STATUS "Found ALPS: ${ALPS_ROOT_DIR} (revision: ${ALPS_VERSION})")
include(${ALPS_USE_FILE})

add_executable(ising ising.cpp SW.cpp)
target_link_libraries(ising ${ALPS_LIBRARIES})
