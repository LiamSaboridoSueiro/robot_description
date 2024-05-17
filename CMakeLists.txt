cmake_minimum_required(VERSION 3.5)
project(robot_description)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(speed_controller src/speed_controller.cpp)
ament_target_dependencies(speed_controller rclcpp geometry_msgs)

install(
  TARGETS speed_controller
  DESTINATION lib/${PROJECT_NAME}
)

install(
  DIRECTORY launch meshes urdf rviz config src
  DESTINATION share/${PROJECT_NAME}
)

ament_export_dependencies(${THIS_PACKAGE_INCLUDE_DEPENDS})

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)
endif()

ament_package()
