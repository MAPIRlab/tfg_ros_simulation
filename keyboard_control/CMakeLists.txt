cmake_minimum_required(VERSION 3.5)
project(keyboard_control)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

# Add Executables
add_executable(keyboard_control src/keyboard_control.cpp)
ament_target_dependencies(keyboard_control rclcpp std_msgs geometry_msgs)

# Declare and install executables
install(TARGETS
  keyboard_control
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
