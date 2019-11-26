
#include <spriteNodePrism.h>
#include <spriteNodeController.h>
#include <lumin/node/RootNode.h>
#include <ml_logging.h>
#include <lumin/ui/UiKit.h>
#include <lumin/ui/UiKitConsts.h>

using namespace lumin;
using namespace lumin::ui;

spriteNodePrism::spriteNodePrism() {
	ML_LOG(Debug, "spriteNodePrism Constructor.");
}
 

spriteNodePrism::~spriteNodePrism() {
  ML_LOG(Debug, "spriteNodePrism Destructor.");  
}

int spriteNodePrism::init() {
  ML_LOG(Debug, "spriteNodePrism Initializing.");

  // Create a new prism.
  glm::vec3 vVolExtents(2.0f, 2.0f, 2.0f);
  prism_ = requestNewPrism(vVolExtents);
  
   if (!prism_) {
    ML_LOG(Error, "spriteNodePrism Error creating default prism.");
    return 1;
  }
  Cursor::SetScale(prism_, .03f);
  prism_->setPrismController(std::make_shared<spriteNodeController>());

  
  return 0;
}

int spriteNodePrism::deInit() {
  ML_LOG(Debug, "spriteNodePrism Deinitializing.");
   
  if (prism_) {
    ML_LOG(Debug, "Error deleting prism.");
    return 1;
  }
  
  return 0;
}

bool spriteNodePrism::updateLoop(float fDelta) {

  return true;  
}

bool spriteNodePrism::eventListener(ServerEvent* event) {
	 

  return false; 
}
