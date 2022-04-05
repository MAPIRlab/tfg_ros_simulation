cmake_minimum_required(VERSION 2.8.3)
project(keyboard_control)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  geometry_msgs
  )

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES turtle_test
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

include_directories(
  ${catkin_INCLUDE_DIRS}
)


## Declare a cpp executable
add_executable(keyboard_control src/keyboard_control.cpp)

target_link_libraries(keyboard_control 
   ${catkin_LIBRARIES}
)
