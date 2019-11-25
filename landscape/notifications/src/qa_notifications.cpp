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
#include <qa_notifications.h>
#include <lumin/node/RootNode.h>
#include <lumin/ui/Cursor.h>
#include <ml_logging.h>
#include <lumin/notifications/Notification.h>
#include <notificationController.h>
#include <lumin/Consts.h>
#include <lumin/event/GestureInputEventData.h>
using namespace lumin;
using namespace lumin::ui;

qa_notifications::qa_notifications() {
  ML_LOG(Debug, "qa_notifications Constructor.");

}

qa_notifications::~qa_notifications() {
  ML_LOG(Debug, "qa_notifications Destructor.");
}

int qa_notifications::init() {
  ML_LOG(Debug, "qa_notifications Initializing.");

  // Create a new prism.
  glm::vec3 size(2.0f, 2.0f, 2.0f);
  prism_ = requestNewPrism(size);
  if (!prism_) {
    ML_LOG(Error, "qa_notifications Error creating default prism.");
    return 1;
  }
  Cursor::SetScale(prism_, .03f);
   
  auto CurrentPrism = std::make_shared<notificationController>();  

  prism_->setPrismController(CurrentPrism);
   
  CurrentPrism->Button1->onActivateSub([this,CurrentPrism](const UiEventData&) {
	 
	  postNotification(&CurrentPrism->m_Notification1);
  });

  CurrentPrism->Button2->onActivateSub([this, CurrentPrism](const UiEventData&) {

	  postNotification(&CurrentPrism->m_Notification2);
  });

  CurrentPrism->Button3->onActivateSub([this, CurrentPrism](const UiEventData&) {

	  postNotification(&CurrentPrism->m_Notification3);
  });
  CurrentPrism->Button4->onActivateSub([this, CurrentPrism](const UiEventData&) {

	  postNotification(&CurrentPrism->m_Notification4);
  });
  CurrentPrism->Button5->onActivateSub([this, CurrentPrism](const UiEventData&) {

	  postNotification(&CurrentPrism->m_Notification5);
  });
  CurrentPrism->Button6->onActivateSub([this, CurrentPrism](const UiEventData&) {

	  postNotification(&CurrentPrism->m_Notification6);
  });
  CurrentPrism->Button7->onActivateSub([this, CurrentPrism](const UiEventData&) {

	  postNotification(&CurrentPrism->m_Notification7);
  });

  CurrentPrism->DissMissNotificationButton->onActivateSub([this, CurrentPrism](const UiEventData&) {

	  dismissNotification(CurrentPrism->m_Notification1);
  });

  CurrentPrism->DissMissAllNotificationButton->onActivateSub([this, CurrentPrism](const UiEventData&) {

	  dismissAllNotifications();
  });

  return 0;
}

int qa_notifications::deInit() {
  ML_LOG(Debug, "qa_notifications Deinitializing.");


  if (prism_) {
    ML_LOG(Debug, "Error deleting prism.");
    return 1;
  }
  return 0;
}

bool qa_notifications::updateLoop(float fDelta) {
		

  return true;  
}

bool qa_notifications::eventListener(ServerEvent* event)
{
	
  return false;  
}
