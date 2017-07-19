#include "flea3/header_trigger_node.h"

int main(int argc, char** argv) {
  ros::init(argc, argv, "flea3_single");
  ros::NodeHandle pnh("~");

  try {
    flea3::HeaderTriggerNode header_trigger_node(pnh);
    header_trigger_node.Run();
    ros::spin();
    header_trigger_node.End();
  } catch (const std::exception& e) {
    ROS_ERROR("%s: %s", pnh.getNamespace().c_str(), e.what());
  }
}
