#include "rclcpp/rclcpp.hpp"
#include "biconnected_interface/srv/find_biconnected_components.hpp" 
#include "biconnected.h"

#include <memory>

void caller(const std::shared_ptr<biconnected_interface::srv::FindBiconnectedComponents::Request> request,
                std::shared_ptr<biconnected_interface::srv::FindBiconnectedComponents::Response> response)  
{
  
  pair<string, int> x = find_components(request->edges);
  response->cycles = x.first;
  response->n = x.second;
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Graph edges : %s", request->edges.c_str());  
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Responding with biconnected components: [%s]", response->cycles.c_str());
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Responding with number of biconnected components: [%d]", response->n);
  
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("biconnected_server"); 

  rclcpp::Service<biconnected_interface::srv::FindBiconnectedComponents>::SharedPtr service =  
    node->create_service<biconnected_interface::srv::FindBiconnectedComponents>("FindBiconnectedComponents",  &caller); 

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Waiting for requestes----------"); 

  rclcpp::spin(node);
  rclcpp::shutdown();
}