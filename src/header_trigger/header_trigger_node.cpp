#include "flea3/header_trigger_node.h"

namespace flea3 {

HeaderTriggerNode::HeaderTriggerNode(const ros::NodeHandle &pnh)
    : CameraNodeBase(pnh), flea3_ros_(pnh) ,mpnh_(pnh){
      trigger_sub_ = mpnh_.subscribe("trigger",1, &HeaderTriggerNode::HeaderCB,this);
    }

void HeaderTriggerNode::Acquire() {
  while (is_acquire() && ros::ok()) {
    if(next_.size()==0) {
      Sleep();
    } else {
      // sleep until next requested fram
      ros::Time next = next_.front();
      next_.pop_front();
      ros::Time::sleepUntil(next);

      if (flea3_ros_.RequestSingle()) {
        const auto expose_duration =
            ros::Duration(flea3_ros_.camera().GetShutterTimeSec() / 2);
        const auto time = ros::Time::now() + expose_duration;
        flea3_ros_.PublishCamera(time);
        //      flea3_ros_.PublishImageMetadata(time);
      }
    }
      

  }
}

void HeaderTriggerNode::HeaderCB(const std_msgs::Header &head){
  next_.push_back(head.stamp + delay_);
}
void HeaderTriggerNode::Setup(Config &config) {
  flea3_ros_.Stop();
  config.trigger_source = 7;//set to software trigger
  flea3_ros_.camera().Configure(config);
  flea3_ros_.set_fps(config.fps);
  delay_ = ros::Duration(config.header_trigger_delay);
  flea3_ros_.Start();
}

}  // namespace flea3
