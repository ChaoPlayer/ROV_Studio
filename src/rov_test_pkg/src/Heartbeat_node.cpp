#include<ros/ros.h>
#include<mavros_msgs/Heartbeat.h>
#include<mavros_msgs/State.h>
#include<string>

int mode_rec;
string status_rec;

ros::Publisher heartbeat_pb;;
ros::Subsriber receiver;

void sendheartbeat(const mavros_msgs::State::ConstPtr& msg,int status)
{
    mavros_msgs::Heartbeat heartbeat_msg;

    heartbeat_msg.type=0;
    heartbeat_msg.autopilot=3;//PX4飞控
    heartbeat_msg.base_mode=msg->mode.c.str();
    heartbeat_msg.system_status=status;

    heartbeat_pb.pubish(heartbeat_msg);
}

void rec_func(const mavros_msgs::State::ConstPtr& msg)
{
    status_rec=msg->custom_mode;
    ROS_INFO("Current mode is %s",status_rec);
}

int main(int argc,char **argv)
{
    ros::init(argc,argv,"Heartbeat_node");
    ros::Nodehandle n_pub;
    heartbeat_pb=n_pub.advertise<mavros_msgs::Heartbeat>("mavros/heartbeat",10);
    ros::Rate loop_rate(1);

    ros::Nodehandle n_rec;
    receiver=n_rec.subsricbe("mode_state",1000,rec_func);

    while(ros::ok())
    {
        sendheartbeat()
    }
}