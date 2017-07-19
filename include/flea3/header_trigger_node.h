#ifndef FLEA3_HEADER_TRIGGER_NODE_H_
#define FLEA3_HEADER_TRIGGER_NODE_H_

#include "flea3/flea3_ros.h"
#include "flea3/Flea3DynConfig.h"
#include <camera_base/camera_node_base.h>
#include <boost/circular_buffer.hpp>

namespace flea3 {

using Config = ::flea3::Flea3DynConfig;

class HeaderTriggerNode : public camera_base::CameraNodeBase<Config> {
 public:
  explicit HeaderTriggerNode(const ros::NodeHandle &pnh);

  void Acquire() override;
  void Setup(Config &config) override;

 private:

  void HeaderCB(const std_msgs::Header &head);
  Flea3Ros flea3_ros_;
  ros::Subscriber trigger_sub_;
  ros::Duration delay_;
  boost::circular_buffer<ros::Time> next_{20}; // this number is abitrary
  ros::NodeHandle mpnh_; 
};

}  // namespace flea3

#endif  // FLEA3_HEADER_TRIGGER_NODE_H_
