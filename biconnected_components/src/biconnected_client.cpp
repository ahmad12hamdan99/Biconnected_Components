#include "rclcpp/rclcpp.hpp"

#include "biconnected_interface/srv/find_biconnected_components.hpp" 
#include "biconnected.h" 

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;


int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  if (argc != 2) { 
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: add edges of graph please");  
      return 1;
  }

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("biconnected_client"); 
  rclcpp::Client<biconnected_interface::srv::FindBiconnectedComponents>::SharedPtr client = node->create_client<biconnected_interface::srv::FindBiconnectedComponents>("FindBiconnectedComponents");   

  auto request = std::make_shared<biconnected_interface::srv::FindBiconnectedComponents::Request>();     

  request->edges = argv[1];

  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }

  auto result = client->async_send_request(request);

  if (rclcpp::spin_until_future_complete(node, result) ==
    rclcpp::executor::FutureReturnCode::SUCCESS)
  {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Biconnected components : %s", result.get()->cycles.c_str());
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Number of biconnected components : %d", result.get()->n);
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service ");   
  }

  rclcpp::shutdown();
  return 0;
}