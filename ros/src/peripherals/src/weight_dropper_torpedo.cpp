#include <ros/ros.h>

#include "monitor/GetSerialDevice.h"
// #include "peripherals/weight_dropper_torpedo.h"

int main(int argc, char **argv) {

    ros::init(argc, argv, "weight_dropper_torpedo");
    ros::NodeHandle nh("~");

    monitor::GetSerialDevice srv;
    nh.getParam("/device_id", srv.request.device_id);

    int loop_rate;
    nh.getParam("loop_rate", loop_rate);

    ros::ServiceClient client = nh.serviceClient<monitor::GetSerialDevice>("/serial_manager/GetDevicePort");
    if(!client.call(srv)) {
        ROS_ERROR("Couldn't get \"%s\" file descripter. Shutting down.\n", srv.request.device_id.c_str());
        return 1;
    }

    std::cout << "FOUND ARDUINO BOARD!!" << std::endl;

    ROS_ERROR("Using Weight Dropper Torpedo on fd %s\n", srv.response.device_fd.c_str());
    
    
    
    ros::spin();
    return 0;
}