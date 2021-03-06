#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/point_cloud_conversion.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <iostream>
#include <nav_msgs/Odometry.h>




nav_msgs::Odometry::Ptr nav;

void cloud_cb(const nav_msgs::Odometry::ConstPtr& msg){
    nav->pose.pose.position.x = msg->pose.pose.position.x;
    nav->pose.pose.position.y = msg->pose.pose.position.y;
    nav->pose.pose.position.z = msg->pose.pose.position.z;
    nav->pose.pose.orientation.x = msg->pose.pose.orientation.x;
    nav->pose.pose.orientation.y = msg->pose.pose.orientation.y;
    nav->pose.pose.orientation.z = msg->pose.pose.orientation.z;
}
int main (int argc, char** argv){


  ros::init (argc, argv, "my_pcl_tutorial");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("/laser_odom_to_init", 1, cloud_cb);

  nav = nav_msgs::Odometry::Ptr (new nav_msgs::Odometry);
  std::string home_env;
  home_env = getenv("HOME");

  std::string fileName;
  fileName = home_env + "/Desktop/loam_front.csv";

  FILE* logFp_;
  logFp_ = fopen(fileName.c_str(), "wb");

  ros::Rate rate(20.0f);

    while (ros::ok()) {

        fprintf(logFp_, "%f, %f, %f, %f,%f,%f",nav->pose.pose.position.x, nav->pose.pose.position.y, nav->pose.pose.position.z,
                nav->pose.pose.orientation.x,nav->pose.pose.orientation.y,nav->pose.pose.orientation.z);

        fprintf(logFp_, "\n");
        float a = nav->pose.pose.position.x;
        std::cout << nav->pose.pose.orientation.x << std::endl;
        ros::spinOnce();
        rate.sleep();
    }

}

