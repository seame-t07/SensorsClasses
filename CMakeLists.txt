cmake_minimum_required(VERSION 3.10)

# Project name and version
project(SpeedSensorExample VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add submodule for CANBus
add_subdirectory(CANBus)

# Include directories for the CANBus library
include_directories(CANBus/includes)  # Include Controller's headers

# Include directories for your headers
include_directories(${PROJECT_SOURCE_DIR}/includes)

# Add sources for the main library
set(SOURCES
    sources/SpeedSensor.cpp
)

# Create the library (Static or Shared)
add_library(SpeedSensorLib STATIC ${SOURCES})

# Link the CANBus library
target_link_libraries(SpeedSensorLib PRIVATE CANBus)

# Add tests using Google Test (optional)
enable_testing()
add_subdirectory(tests)

# Optional: Installation
install(TARGETS SpeedSensorLib DESTINATION lib)
