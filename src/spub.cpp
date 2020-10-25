#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <fstream>
#include <iostream>

pcl::PointCloud<pcl::PointXYZ>::Ptr temp_cloud;

void cloud_cb (const sensor_msgs::PointCloud2::ConstPtr& input){
    pcl::PCLPointCloud2 pcl_pc2;
    pcl_conversions::toPCL(*input,pcl_pc2);
    pcl::fromPCLPointCloud2(pcl_pc2,*temp_cloud);

}

int main (int argc, char** argv){
  ros::init (argc, argv, "my_pcl_tutorial2");
  ros::NodeHandle nh;

  temp_cloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>); //주소에 어던떤 공간할당
  ros::Subscriber sub2 = nh.subscribe("fuck", 1, cloud_cb);


  //time_t timer = time(NULL);
  //struct tm* ltime = localtime(&timer);
  //char fn_date[13];
  //sprintf(fn_date, "%02d%02d%02d_%02d%02d%02d", (ltime->tm_year) - 100, (ltime->tm_mon) + 1, ltime->tm_mday,
  //          ltime->tm_hour, ltime->tm_min, ltime->tm_sec);
  //std::string fnDate(fn_date);

  std::string home_env;
  home_env = getenv("HOME");

  std::string fileName;
  fileName = home_env + "/rosLog/bag2csv2.csv";

  FILE* logFp_;
  logFp_ = fopen(fileName.c_str(), "wb");

  ros::Rate rate(20.0f);

    while (ros::ok()) {
        if (temp_cloud->points.size() != 0) {
            ros::Time t = ros::Time::now();

            std::string temp_frame_id;
            temp_frame_id = temp_cloud->header.frame_id;
            //char c_temp_frame_id;
            //          strcpy(c_temp_frame_id,temp_frame_id.c_str());

            fprintf(logFp_, "%d.%d,%s,%d,", t.sec, t.nsec,temp_frame_id.c_str(),temp_cloud->header.seq);


            for (int i = 0; i < temp_cloud->points.size(); i++) {
                fprintf(logFp_, "%f, %f, %f,",temp_cloud->points[i].x, temp_cloud->points[i].y, temp_cloud->points[i].z);
//                  fprintf(logFp_, "%f," ,temp_cloud->points[i].x);

            }
            fprintf(logFp_, "\n");
            //           std::cout<< temp_cloud->header<<std::endl;;
        }
        ros::spinOnce();
        rate.sleep();
    }
}