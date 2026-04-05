#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

using namespace std::placeholders;

class SmartPhoneNode : public rclcpp::Node {
public:
  SmartPhoneNode() : Node("smartphone") {
    subscription_ = this->create_subscription<example_interfaces::msg::String>(
      "news", 10, std::bind(&SmartPhoneNode::callbackRobotNews, this, _1));
    RCLCPP_INFO(this->get_logger(), "Smartphone Node has been started and is listening to news.");
  }

private:
  void callbackRobotNews(const example_interfaces::msg::String::SharedPtr msg) 
  {
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
  } 
  rclcpp::Subscription<example_interfaces::msg::String>::SharedPtr subscription_;
};

int main(int argc, char **argv) 
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SmartPhoneNode>());
  rclcpp::shutdown();
  return 0;
}