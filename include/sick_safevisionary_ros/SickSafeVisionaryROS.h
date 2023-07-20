// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------

// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Marvin Große Besselmann <grosse@fzi.de>
 * \date    2023-06-06
 */
//----------------------------------------------------------------------

#ifndef SICK_SAFEVISIONARY_ROS_SICK_SAFE_VISIONARY_H_INCLUDED
#define SICK_SAFEVISIONARY_ROS_SICK_SAFE_VISIONARY_H_INCLUDED

#include "image_transport/publisher.h"
#include "sick_safevisionary_base/SafeVisionaryData.h"
#include "sick_safevisionary_base/SafeVisionaryDataStream.h"
#include "sick_safevisionary_base/PointXYZ.h"
#include <mutex>
#include <thread>

#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/CameraInfo.h>

#include <pcl_conversions/pcl_conversions.h>
#include <pcl_ros/point_cloud.h>
#include "sensor_msgs/PointCloud2.h"
#include <ros/ros.h>

class SickSafeVisionaryROS
{
public:
  SickSafeVisionaryROS();
  virtual ~SickSafeVisionaryROS(){};
  void run();
  void stop();

private:
  void receiveThread();
  void publishThread();
  void processFrame();

  void publishCameraInfo();
  void publishPointCloud();
  void publishDepthImage();
  void publishIntensityImage();
  void publishStateMap();


  sensor_msgs::ImagePtr Vec16ToImage(std::vector<uint16_t> vec);
  sensor_msgs::ImagePtr Vec8ToImage(std::vector<uint8_t> vec);

  std::shared_ptr<visionary::SafeVisionaryData> m_data_handle;
  std::shared_ptr<visionary::SafeVisionaryDataStream> m_data_stream;

  ros::Publisher m_camera_info_pub;
  ros::Publisher m_pointcloud_pub;

  image_transport::Publisher m_depth_pub;
  image_transport::Publisher m_intensity_pub;
  image_transport::Publisher m_state_pub;


  ros::NodeHandle m_nh;
  ros::NodeHandle m_priv_nh;
  std_msgs::Header m_header;
  std::string m_frame_id;

  std::string m_connection_type;
  std::string m_ip;
  int32_t m_udp_port;
  // TODO add tcp param
  std::unique_ptr<std::thread> m_udp_client_thread_ptr;
  std::mutex m_data_mutex;
};

#endif /* SICK_SAFEVISIONARY_ROS_SICK_SAFE_VISIONARY_H_INCLUDED */
