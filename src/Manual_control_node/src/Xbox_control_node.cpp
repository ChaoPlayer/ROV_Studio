#include<ros/ros.h>
#include<sensor_msgs/Joy.h>
#include<mavros_msgs/SetMode.h>
#include<mavros_msgs/CommandBool.h>//用于控制飞行器的武装状态
#include<mavros_msgs/RCIn.h>//用于获取遥控器的输入信号
#include<mavros_msgs/RCOut.h>//发布遥控信号，控制飞行器的动作用

ros::Publisher rc_out_pub;
ros::ServiceClient set_mode_client;
ros::ServiceClient arm_client;

float th