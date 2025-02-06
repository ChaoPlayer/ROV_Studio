#include<ros/ros.h>
#include<service_client_pkg/ServiceClientExMsg.h>
#include<string>
#include<mavros_msgs/SetMode.h>
#include<mavros/command.h>
#include<mavros_msgs/State.h>
#include<mavros/mavlink_convert.h>

ros::ServiceServer set_mode_service;
ros::Publisher heartbeat_pub;
ros::Publisher mode_pub;
ros::Subscriber mode_sub;

bool mode_change(mavros_msgs::SetMode::Request &req,mavros_msgs::SetMode::Response &res)
{
    uint8_t base_mode=req.base_mode;
    std::string custom_mode=req.custom_mode;
    
    mavlink_message_t msg;
    mavlink_msg_set_mode_pack(1,0,base_mode,custom_mode,c_str());

    mavros::mavlink::send_message(msg);

    res.success=true;
    res.result=0;

    ROS_INFO("Successfully changed mode to %s",custom_mode.c_str());
    return true;
}

void mode_state(const mavros_msgs::State::ConstPtr& msg)
{
    mavros_msgs::State custom_mode_msg;
    custom_mode_msg.custom_mode=msg->custom_mode;
    mode_pub.publish(custom_mode_msg);
}

int main(int argc,char **argv)
{
    ros::init(argc,argv,"Mode_server_node");
    ros::Nodehandle n;
    ros::Nodehandle nh;
    mode_sub.subscribe("mavros/state",10,mode_state);
    mode_pub.advertise<mavros_msgs::State>("mode_state",10);//发布当前custom_mode

    set_mode_service=n.advertiseService("mavros/set_mode",mode_change);
    heartbeat_pub=n.advertise<mavros_msgs::Heartbeat>("/mavros/heartbeat",10);

    ROS_INFO("Set mode service is ready");
    ros::spin();
    return 0;
}