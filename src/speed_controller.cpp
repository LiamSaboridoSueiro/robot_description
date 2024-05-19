#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

class Controller : public rclcpp::Node
{
public:
    Controller()
        : Node("controller"), state_(State::ACCELERATE), start_time_(this->now())
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/rover_base_control/cmd_vel_unstamped", 10);
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(50),
            std::bind(&Controller::publish_message, this));
    }

private:
    enum class State
    {
        ACCELERATE,
        CRUISE,
        DECELERATE,
        STOP
    };

    void publish_message()
    {
        auto message = geometry_msgs::msg::Twist();
        rclcpp::Time current_time = this->now();
        double elapsed_time = (current_time - start_time_).seconds();

        switch (state_)
        {
        case State::ACCELERATE:
            message.linear.x = calculate_acceleration(elapsed_time);
            if (elapsed_time >= 5.0)
            {
                state_ = State::CRUISE;
                start_time_ = current_time;
            }
            break;
        case State::CRUISE:
            message.linear.x = 5.0;
            if (elapsed_time >= 5.0)
            {
                state_ = State::DECELERATE;
                start_time_ = current_time;
            }
            break;
        case State::DECELERATE:
            message.linear.x = calculate_deceleration(elapsed_time);
            if (elapsed_time >= 5.0)
            {
                state_ = State::STOP;
                start_time_ = current_time;
            }
            break;
        case State::STOP:
            message.linear.x = 0.0;
            rclcpp::shutdown();
            break;
        }

        message.angular.z = 0.0;
        publisher_->publish(message);
    }

    float calculate_acceleration(double elapsed_time)
    {
        // Linearly increase speed from 0 to 5 over the first 5 seconds
        return (elapsed_time / 5.0) * 5.0;
    }

    float calculate_deceleration(double elapsed_time)
    {
        // Linearly decrease speed from 5 to 0 over the last 5 seconds
        return 5.0 - ((elapsed_time / 5.0) * 5.0);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    State state_;
    rclcpp::Time start_time_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Controller>();

    rclcpp::spin(node);
    return 0;
}
