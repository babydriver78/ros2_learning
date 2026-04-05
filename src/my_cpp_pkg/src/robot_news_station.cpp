#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

using namespace std::chrono_literals;
 
class RobotStationNode : public rclcpp::Node 
{
public:
    RobotStationNode() : Node("robot_news_station"), robot_name_("RobotReporter")
    {
            publisher_ = this->create_publisher<example_interfaces::msg::String>("news", 10);
            timer_ = this->create_wall_timer(2s, std::bind(&RobotStationNode::publish_news, this));
            RCLCPP_INFO(this->get_logger(), "Robot News Station Node has been started.");
    }
 
private:

    void publish_news()
    {
        auto message = example_interfaces::msg::String();
        message.data = "Breaking news: ROS2 is awesome! published by " + robot_name_;
        publisher_->publish(message);
    }

    std::string robot_name_;
    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

};
 
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotStationNode>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}