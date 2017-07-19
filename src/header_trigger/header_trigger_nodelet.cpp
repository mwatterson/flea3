#include "flea3/header_trigger_node.h"

#include <nodelet/nodelet.h>
#include <pluginlib/class_list_macros.h>

namespace flea3 {

class HeaderTriggerNodelet : public nodelet::Nodelet {
 public:
  HeaderTriggerNodelet() = default;
  ~HeaderTriggerNodelet() {
    if (header_trigger_node_) {
      header_trigger_node_->End();
    }
  }

  virtual void onInit() {
    try {
      header_trigger_node_.reset(new HeaderTriggerNode(getPrivateNodeHandle()));
      header_trigger_node_->Run();
    } catch (const std::exception &e) {
      NODELET_ERROR("%s: %s", getPrivateNodeHandle().getNamespace().c_str(),
                    e.what());
    }
  }

 private:
  std::unique_ptr<HeaderTriggerNode> header_trigger_node_;
};

PLUGINLIB_EXPORT_CLASS(flea3::HeaderTriggerNodelet, nodelet::Nodelet)

}  // namespace flea3
