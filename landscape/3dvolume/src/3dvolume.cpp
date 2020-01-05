#include <3dvolume.h>
#include <lumin/node/RootNode.h>
#include <lumin/ui/Cursor.h>
#include <lumin/ui/node/UiText.h>
#include <ml_logging.h>

using namespace lumin;

L3Dvolume::L3Dvolume() {
  ML_LOG(Debug, "3dvolume Constructor.");

}

L3Dvolume::~L3Dvolume() {
  ML_LOG(Debug, "3dvolume Destructor.");
}

int L3Dvolume::init() {
  ML_LOG(Debug, "3dvolume Initializing.");
  return 0;
}

void L3Dvolume::onAppStart(const InitArg&) {
  ML_LOG(Debug, "3dvolume creating instance");
  // Create a prism
  glm::vec3 size(2.0f, 2.0f, 2.0f);
  Prism* prism = requestNewPrism(size);
  if (!prism) {
    ML_LOG(Error, "3dvolume Error creating default prism.");
  } 

  ui::Cursor::SetScale(prism, 0.03f);

  // render 3d volume prism controller
  prism->setPrismController(std::make_shared<L3DImageController>());
}

int L3Dvolume::deInit() {
  ML_LOG(Debug, "3dvolume Deinitializing.");

  return 0;
}



