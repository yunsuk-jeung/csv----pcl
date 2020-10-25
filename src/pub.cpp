#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
//#include <sensor_msgs/PointCloud.h>
//#include <sensor_msgs/point_cloud_conversion.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
//#include <fstream>
//#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

int main (int argc, char** argv){
  ros::init (argc, argv, "my_pcl_tutorial1");
  ros::NodeHandle nh;

    sensor_msgs::PointCloud2 luck;
    pcl::PointCloud<pcl::PointXYZ>::Ptr suck;

    suck = pcl::PointCloud<pcl::PointXYZ>::Ptr (new pcl::PointCloud<pcl::PointXYZ>); //주소에 어던떤 공간할당
    ros::Publisher pub = nh.advertise<sensor_msgs::PointCloud2>("fuck", 1);

    std::string home_env;
    home_env = getenv("HOME");
    std::string fileName;

    fileName = home_env + "/rosLog/bag2csv.csv";
    std::ifstream file(fileName.c_str());

    std::vector<std::vector<std::string> > re_2d;
    std::vector<std::string> re;
    std::string line, val;

    pcl::PointXYZ temp;


//    int count;
//    count =1;

    ros::Rate rate(20.0f);
    rate.sleep();
    rate.sleep();
    rate.sleep();
    rate.sleep();


    while (ros::ok()) {

            std::getline(file,line);
            std::stringstream ss(line);

            std::getline(ss, val, ',');
            suck->header.stamp=atol(val.c_str());

            std::getline(ss, val, ',');
            suck->header.frame_id=val.c_str();

            std::getline(ss, val, ',');
            suck->header.seq=atol(val.c_str());

            while (std::getline(ss, val, ',')) {
                temp.x = atof(val.c_str());
                std::getline(ss, val, ',');
                temp.y = atof(val.c_str());
                std::getline(ss, val, ',');
                temp.z = atof(val.c_str());
                suck->push_back(temp);
            }

            suck->width = suck->size();
            suck->height = 1;
            pcl::toROSMsg(*suck, luck);
            suck->clear();

            pub.publish(luck);

        ros::spinOnce();
        rate.sleep();


    }
}
