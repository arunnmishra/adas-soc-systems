cmake_minimum_required(VERSION 3.20)
project(SomeIpFramework CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define include directories
set(SOMEIP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/core/include)
set(SOMEIP_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/core/src)
set(SOMEIP_SERVICE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/service)
set(SOMEIP_TRANSPORT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/transport)

# Include directories
include_directories(${SOMEIP_INCLUDE_DIR})
include_directories(${SOMEIP_SERVICE_DIR})
include_directories(${SOMEIP_TRANSPORT_DIR})

# Core library sources
set(SOMEIP_CORE_SOURCES
    ${SOMEIP_SRC_DIR}/deserializer.cpp
    ${SOMEIP_SRC_DIR}/dispatcher.cpp
    ${SOMEIP_SRC_DIR}/endpoint_udp.cpp
    ${SOMEIP_SRC_DIR}/message.cpp
    ${SOMEIP_SERVICE_DIR}/service.cpp
)

# Core library headers
set(SOMEIP_CORE_HEADERS
    ${SOMEIP_INCLUDE_DIR}/header.hpp
    ${SOMEIP_INCLUDE_DIR}/MemPool.hpp
    ${SOMEIP_INCLUDE_DIR}/message.hpp
    ${SOMEIP_INCLUDE_DIR}/owned_msg.hpp
    ${SOMEIP_INCLUDE_DIR}/queue.hpp
    ${SOMEIP_INCLUDE_DIR}/ResponseWriter.hpp
    ${SOMEIP_INCLUDE_DIR}/serializer.hpp
    ${SOMEIP_INCLUDE_DIR}/ServiceRegistry.hpp
    ${SOMEIP_INCLUDE_DIR}/SomeIpService.hpp
    ${SOMEIP_INCLUDE_DIR}/types.hpp
)

# Create core library
add_library(someip_core STATIC
    ${SOMEIP_CORE_SOURCES}
    ${SOMEIP_CORE_HEADERS}
)

# Set include directories for the library
target_include_directories(someip_core PUBLIC ${SOMEIP_INCLUDE_DIR})
target_include_directories(someip_core PUBLIC ${SOMEIP_SERVICE_DIR})
target_include_directories(someip_core PUBLIC ${SOMEIP_TRANSPORT_DIR})

# Example executable
add_executable(someip_example
    examples/main.cpp
)

# Link the core library to the example
target_link_libraries(someip_example PRIVATE someip_core)

# Set output directories
set_target_properties(someip_example PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

set_target_properties(someip_core PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# Enable all warnings
if(MSVC)
    target_compile_options(someip_core PRIVATE /W4)
    target_compile_options(someip_example PRIVATE /W4)
else()
    target_compile_options(someip_core PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(someip_example PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Print configuration info
message(STATUS "SOME/IP Framework Configuration:")
message(STATUS "  Include Dir: ${SOMEIP_INCLUDE_DIR}")
message(STATUS "  Source Dir: ${SOMEIP_SRC_DIR}")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
