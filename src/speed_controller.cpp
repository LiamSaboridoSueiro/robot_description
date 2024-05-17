#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

class Controller : public rclcpp::Node
{
public:
    Controller()
        : Node("controller"), step_counter_(0)
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/rover_base_control/cmd_vel_unstamped", 10);
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(50),
            std::bind(&Controller::publish_message, this));
    }

private:
    void publish_message()
    {
        auto message = geometry_msgs::msg::Twist();

        // Calculate the current second based on the step counter
        int current_second = step_counter_ / 20;

        if (current_second < 5) {
            // Increase speed by 1 each second for the first 5 seconds
            message.linear.x = current_second + 1;
        } else if (current_second < 10) {
            // Maintain speed at 5 for the next 5 seconds
            message.linear.x = 5;
        } else if (current_second < 15) {
            // Decrease speed by 1 each second for the last 5 seconds
            message.linear.x = 15 - current_second;
        } else {
            // After 15 seconds, stop the node
            rclcpp::shutdown();
        }

        message.angular.z = 0;
        publisher_->publish(message);

        step_counter_++;
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    int step_counter_;
};

void stop_node(const std::shared_ptr<rclcpp::Node> & node)
{
    RCLCPP_INFO(node->get_logger(), "Shutting down...");
    rclcpp::shutdown();
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Controller>();

    // Create a separate timer to stop the node after 15 seconds
    auto stop_timer = node->create_wall_timer(
        std::chrono::seconds(15),
        [node]() { stop_node(node); }
    );

    rclcpp::spin(node);
    return 0;
}