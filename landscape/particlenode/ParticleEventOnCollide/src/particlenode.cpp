// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
//
// Copyright (c) 2018 Magic Leap, Inc. All Rights Reserved.
// Use of this file is governed by the Creator Agreement, located
// here: https://id.magicleap.com/creator-terms
//
// %COPYRIGHT_END%
// ---------------------------------------------------------------------
// %BANNER_END%
#include <particlenode.h>
#include <lumin/node/RootNode.h>
#include <lumin/ui/Cursor.h>
#include <lumin/ui/node/UiText.h>
#include <ml_logging.h>

using namespace lumin;

particlenode::particlenode() {
  ML_LOG(Debug, "ParticleEventOnCollide Constructor.");  
}

particlenode::~particlenode() {
  ML_LOG(Debug, "ParticleEventOnCollide Destructor.");

}

int particlenode::init() {
  ML_LOG(Debug, "ParticleEventOnCollide Initializing.");  

  return 0;
}

void particlenode::onAppStart(const InitArg&) {
  ML_LOG(Debug, "ParticleEventOnCollide creating instance");
  // Create a prism
  glm::vec3 size(2.0f, 2.0f, 2.0f);
  Prism* prism = requestNewPrism(size);
  if (!prism) {
    ML_LOG(Error, "ParticleEventOnCollide Error creating default prism.");
  }
  // Cursor size is determined from prism size. Set the scale to ignore the default size.
  ui::Cursor::SetScale(prism, 0.03f);

  auto CurrentPrism = std::make_shared<ParticleEventOnCollide>();
  prism->setPrismController(CurrentPrism);
}

int particlenode::deInit() {
  ML_LOG(Debug, "ParticleEventOnCollide Deinitializing.");

  return 0;
}

bool particlenode::updateLoop(float fDelta) {

   return true;  
}

bool particlenode::eventListener(ServerEvent* event) {
	
  return false;  
}

