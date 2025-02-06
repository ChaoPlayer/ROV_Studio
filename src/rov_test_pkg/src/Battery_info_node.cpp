#include<ros/ros.h>
#include<mavros_msgs/BatteryStatus.h>

void battery_status(const mavros_msgs::BatteryStatus::ConstPtr& msg)
{
    if(msg->battery_status==1)
    {
    switch (msg->charge_state)
    {
    case 1:
        ROS_INFO("充电中...");
        break;
    case 2:
        ROS_INFO("充电完成");
        break;
    case 3:
        ROS_ERROR("充电时出现错误");
        break;
    default:
        break;
    }
    ROS_INFO("当前电量为：%.2f",msg->charge,"A·h");
    ROS_INFO("当前电池电压为：%.2f",msg->voltage,"V");
    ROS_INFO("当前电池电流为：%.2f",msg->current,"A");
    ROS_INFO("当前电池温度为：%.2f",msg->temperature,"度");
    }
    else
    ROS_ERROR("电池状态异常，当前电池状态为 %d\n",msg->battery_state,"0:未知状态\n2:电池临界\n3:电池故障\n")
}
int main(int argc,char** argv)
{
    ros::init(argc,argv,"Battery_info_node");
    ros::NodeHandle nh;

    ros::Subscriber battery_situation=nh.subscribe("mavros/battery",10,battery_status);
    ros::spin();
    return 0;
}