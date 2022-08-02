cmake_minimum_required(VERSION 3.5)
project(biconnected_components)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(biconnected_interface REQUIRED)

add_executable(server src/biconnected_server.cpp)
ament_target_dependencies(server
  rclcpp biconnected_interface)

add_executable(client src/biconnected_client.cpp)
ament_target_dependencies(client
  rclcpp biconnected_interface)

install(TARGETS
  server
  client
  DESTINATION lib/${PROJECT_NAME})

ament_package()