#pragma once
#include <lumin/Prism.h>
#include <lumin/event/ServerEvent.h>
#include <map>
#include <functional>
#include <lumin/ui/node/UiText.h>
#include <lumin/PrismController.h>
#include <lumin/ui/UiKit.h>
#include <lumin/notifications/Notification.h>
using namespace lumin;
using namespace lumin::ui;

class notificationController:public lumin::PrismController {
public:

	notificationController();
	virtual ~notificationController();
	lumin::Notification m_Notification1;
	lumin::Notification m_Notification2;
	lumin::Notification m_Notification3;
	lumin::Notification m_Notification4;
	lumin::Notification m_Notification5;
	lumin::Notification m_Notification6;
	lumin::Notification m_Notification7;	

	lumin::ui::UiButton *Button1;
	lumin::ui::UiButton *Button2;
	lumin::ui::UiButton *Button3;
	lumin::ui::UiButton *Button4;
	lumin::ui::UiButton *Button5;
	lumin::ui::UiButton *Button6;
	lumin::ui::UiButton *Button7;
	lumin::ui::UiButton *DissMissNotificationButton;
	lumin::ui::UiButton *DissMissAllNotificationButton;

protected:
	void onAttachPrism(lumin::Prism* prism) override;
	bool onEvent(lumin::ServerEvent* event) override;

private:
	lumin::Prism* prism_ = nullptr;  // represents the bounded space where the Scene Graph renders.
	void CreateButtons();
	void CreateNotificationsActions();
	lumin::ui::UiButton *GettersButton;
	void CreateDissmissButton(std::string );
	void CreateActivateButton(std::string);
	lumin::ui::UiText *m_DismissNotificationText;
	lumin::ui::UiText *m_ActivateNotificationText;
	
};