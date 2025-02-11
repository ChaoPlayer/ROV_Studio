#include<ros/ros.h>
#include<mavros/SetMode.h>
#include<string>
#include<ros/service_client.h>
#include<mavros_msgs/State.h>

std::string current_custom_mode;

// uint8_t base_mode_get()
// {
//     //用于获取用户输入的控制基本类型
// }
void custom_mode_get(const mavros_msgs::State::ConstPtr& msg)
{
    //用于获得用户输入的控制具体模式
    current_custom_mode=msg->custom_mode;
}


int main(int argc,char **argv)
{
    ros::init(argc,argv,"Mode_client_node");
    ros::Nodehandle nh,ns;

    ros::ServiceClient client=nh.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");
    mavros_msgs::SetMode set_mode_srv;
    ros::Subscriber mode_sub=mode_sub.subscribe("mode_state",10,custom_mode_get)

    //set_mode_srv.base_mode=base_mode_get();
    set_mode_srv.custom_mode=current_custom_mode;
    ROS_INFO("Current custom_mode is %s",set_mode_srv.custom_mode);

    if(client.call(set_mode_srv))
    {
        if(set_mode_srv.response.success)
        {
            ROS_INFO("Mode change to %s successful!",set_mode_srv.request.custom_mode.c_str());
        }
        else
        {
            ROS_EEROR("Unable to change mode!");
        }
    }
    else
    {
        ROS_ERROR("Fail to call service set_mode");
    }
    return 0;
}