
#include <notificationController.h>
#include <lumin/Prism.h>
#include <lumin/event/GestureInputEventData.h>
#include <lumin/node/TransformNode.h>
#include <lumin/ui/node/UiImage.h>
#include <lumin/ui/node/UiText.h>
#include <lumin/event/ServerEvent.h>
#include <lumin/event/SelectionEventData.h>
#include <ml_logging.h>
#include <lumin/ui/node/UiTextEdit.h>
#include <lumin/notifications/Notification.h>
#include <lumin/ui/node/UiGridLayout.h>


using namespace lumin;
using namespace lumin::input;


notificationController::notificationController()
	: PrismController("NotificationController") {

}

notificationController::~notificationController()
{

}

void notificationController::onAttachPrism(lumin::Prism * prism)
{
	prism_ = prism;
	auto UiTextNode = lumin::ui::UiText::Create(prism, "Notifications with sounds Glphy model");
	UiTextNode->setLocalPosition(glm::vec3(-.35f, .8f, 0));
	UiTextNode->setLocalScale(glm::vec3(5.1f, 5.1f, 5.1f));
	getRoot()->addChild(UiTextNode);
	CreateButtons();
	CreateNotificationsActions();	
}

bool notificationController::onEvent(ServerEvent* event)
{
	return true;
}


void notificationController::CreateNotificationsActions()
{
	auto DismissPtr = [&](const Notification & in)
	{
		CreateDissmissButton(in.getTitle());
	};

	auto ActPtr = [&](const Notification & in)
	{
		CreateActivateButton(in.getTitle());
	};

	m_Notification1.setTitle("ActGlyph Check  ");
	m_Notification1.setActivateButtonGlyph(lumin::Notification::NotificationActivateGlyph::kCheck);
	m_Notification1.setDismissButtonGlyph(lumin::Notification::NotificationDismissGlyph::kClose);
	m_Notification1.setDismissButtonText("Dismiss Glyph Close");
	m_Notification1.setActivateButtonText(" Activate Glyph Check");
	m_Notification1.setDismissAction(DismissPtr);
	m_Notification1.setActivateAction(ActPtr);

	
	m_Notification2.setTitle("ActGlyph Person");
	m_Notification2.setActivateButtonGlyph(lumin::Notification::NotificationActivateGlyph::kPerson);
	m_Notification2.setDismissButtonGlyph(lumin::Notification::NotificationDismissGlyph::kThumbsDown);
	m_Notification2.setDismissButtonText("Dismiss Glyph Thumbs Down");
	m_Notification2.setActivateButtonText(" Activate Glyph Person");
	m_Notification2.setDismissAction(DismissPtr);
	m_Notification2.setActivateAction(ActPtr);
		
	m_Notification3.setTitle("ActGlyph PersonFollow");
	m_Notification3.setActivateButtonGlyph(lumin::Notification::NotificationActivateGlyph::kPersonFollow);
	m_Notification3.setDismissButtonGlyph(lumin::Notification::NotificationDismissGlyph::kThumbsDownLeft);
	m_Notification3.setDismissButtonText("Dismiss Glyph Thumbs Down Left");
	m_Notification3.setActivateButtonText(" Activate Glyph Person Follow");
	m_Notification3.setDismissAction(DismissPtr);
	m_Notification3.setActivateAction(ActPtr);
	
	m_Notification4.setTitle("ActGlyph PersonThree G");
	m_Notification4.setActivateButtonGlyph(lumin::Notification::NotificationActivateGlyph::kPersonThree);
	m_Notification4.setDismissButtonGlyph(lumin::Notification::NotificationDismissGlyph::kThumbsDownLeft);
	m_Notification4.setDismissButtonText("Dismiss Glyph Thumbs Down Left");
	m_Notification4.setActivateButtonText(" Activate Glyph Person Follow");
	m_Notification4.setDismissAction(DismissPtr);
	m_Notification4.setActivateAction(ActPtr);
		
	m_Notification5.setTitle("ActGlyph PhoneIncoming G");
	m_Notification5.setActivateButtonGlyph(lumin::Notification::NotificationActivateGlyph::kPhoneIncomingCall);
	m_Notification5.setDismissButtonGlyph(lumin::Notification::NotificationDismissGlyph::kPhoneEndCall);
	m_Notification5.setDismissButtonText("Dismiss Glyph Phone End Call");
	m_Notification5.setActivateButtonText(" Activate Glyph Phone Incoming Call");
	m_Notification5.setDismissAction(DismissPtr);
	m_Notification5.setActivateAction(ActPtr);
	
	m_Notification6.setTitle("ActGlyph Stream ");
	m_Notification6.setActivateButtonGlyph(lumin::Notification::NotificationActivateGlyph::kStream);
	m_Notification6.setDismissButtonGlyph(lumin::Notification::NotificationDismissGlyph::kThumbsDownRight);
	m_Notification6.setDismissButtonText("Dismiss Glyph Phone Down Right");
	m_Notification6.setActivateButtonText(" Activate Glyph Stream");
	m_Notification6.setDismissAction(DismissPtr);
	m_Notification6.setActivateAction(ActPtr);
	
	m_Notification7.setTitle("ActGlyph UndoReply G D20 Model");
	m_Notification7.setActivateButtonGlyph(lumin::Notification::NotificationActivateGlyph::kUndoReply);
	m_Notification7.setIconTexturePath("res/Green_gradient.png");
	m_Notification7.setIconModelPath("res/D20_spin.fbx");
	m_Notification7.setDismissButtonGlyph(lumin::Notification::NotificationDismissGlyph::kClose);
	m_Notification7.setDismissButtonText("Dismiss Glyph Close");
	m_Notification7.setActivateButtonText(" Activate Glyph Undo");
	m_Notification7.setDismissAction(DismissPtr);
	m_Notification7.setActivateAction(ActPtr);

	auto m_TextGetStatus = lumin::ui::UiText::Create(prism_, "");
	m_TextGetStatus->setLocalPosition(glm::vec3(-.5f, 0.0f, 0));
	m_TextGetStatus->setTextSize(0.09f);
	getRoot()->addChild(m_TextGetStatus);

	GettersButton->onActivateSub([=](const UiEventData&) {
		
		bool n1 = (m_Notification1.getActivateButtonGlyph() == lumin::Notification::NotificationActivateGlyph::kCheck);
		bool n2 = (m_Notification2.getActivateButtonGlyph() == lumin::Notification::NotificationActivateGlyph::kPerson);
		bool n3 = (m_Notification3.getActivateButtonGlyph() == lumin::Notification::NotificationActivateGlyph::kPersonFollow);
		bool n4 = (m_Notification4.getActivateButtonGlyph() == lumin::Notification::NotificationActivateGlyph::kPersonThree);
		bool n5 = (m_Notification5.getActivateButtonGlyph() == lumin::Notification::NotificationActivateGlyph::kPhoneIncomingCall);
		bool n6 = (m_Notification6.getActivateButtonGlyph() == lumin::Notification::NotificationActivateGlyph::kStream);
		bool n7 = ((m_Notification7.getIconModelPath() == "res/D20_spin.fbx") && (m_Notification7.getIconTexturePath() == "res/Green_gradient.png") &&
			(m_Notification7.getActivateButtonGlyph() == lumin::Notification::NotificationActivateGlyph::kUndoReply));

		bool finalCheck = (n1 & n2 & n3 &n4 & n5 & n6 & n7);
		m_TextGetStatus->setText(finalCheck== 1 ? "True":"False");

	});

}
void notificationController::CreateButtons()
{
	UiGridLayout *layout = UiGridLayout::Create(prism_);
	layout->setColumns(2);
	glm::vec3 size = prism_->getSize();
	layout->setLocalPosition(glm::vec3(-size.x/2, size.y/2-0.3, 0));
	getRoot()->addChild(layout);

	Button1 = lumin::ui::UiButton::CreateEclipseButton(prism_, EclipseButtonParams(EclipseButtonType::kText, "Check Close", .05f));
	Button1->setTextColor(glm::vec4(.1f,1,.1f,1));
	layout->addItem(Button1);

	Button2 = lumin::ui::UiButton::CreateEclipseButton(prism_, EclipseButtonParams(EclipseButtonType::kText, "Person ThumbsDown", .05f));
	Button2->setTextColor(glm::vec4(.1f, 1, .1f, 1));
	layout->addItem(Button2);

	Button3 = lumin::ui::UiButton::CreateEclipseButton(prism_, EclipseButtonParams(EclipseButtonType::kText, "PersonFollow ThumbsDownLeft", .05f));
	Button3->setTextColor(glm::vec4(.1f, 1, .1f, 1));
	layout->addItem(Button3);

	Button4 = lumin::ui::UiButton::CreateEclipseButton(prism_, EclipseButtonParams(EclipseButtonType::kText, "PersonThree ThumbsDownLeft", .05f));
	Button4->setTextColor(glm::vec4(.1f, 1, .1f, 1));
	layout->addItem(Button4);

	Button5 = lumin::ui::UiButton::CreateEclipseButton(prism_, EclipseButtonParams(EclipseButtonType::kText, "PhoneIncomingCall PhoneEndCall", .05f));
	Button5->setTextColor(glm::vec4(.1f, 1, .1f, 1));
	layout->addItem(Button5);

	Button6 = lumin::ui::UiButton::CreateEclipseButton(prism_, EclipseButtonParams(EclipseButtonType::kText, "Stream ThumbsDownRight", .05f));
	Button6->setTextColor(glm::vec4(.1f, 1, .1f, 1));
	layout->addItem(Button6);

	Button7 = lumin::ui::UiButton::CreateEclipseButton(prism_, EclipseButtonParams(EclipseButtonType::kText, "UndoReply D20Model Close ", .05f));
	Button7->setTextColor(glm::vec4(.1f, 1, .1f, 1));
	layout->addItem(Button7);


	GettersButton = lumin::ui::UiButton::CreateEclipseButton(prism_, EclipseButtonParams(EclipseButtonType::kText, "Show all notification  text", .05f));
	GettersButton->setTextColor(glm::vec4(.1f, 1, .1f, 1));
	layout->addItem(GettersButton);

	DissMissNotificationButton = lumin::ui::UiButton::CreateEclipseButton(prism_, EclipseButtonParams(EclipseButtonType::kText, "Dissmiss Notification Check Close", .05f));
	DissMissNotificationButton->setTextColor(glm::vec4(.1f, 1, .1f, 1));
	layout->addItem(DissMissNotificationButton);


	DissMissAllNotificationButton = lumin::ui::UiButton::CreateEclipseButton(prism_, EclipseButtonParams(EclipseButtonType::kText, "DissMiss all notification", .05f));
	DissMissAllNotificationButton->setTextColor(glm::vec4(.1f, 1, .1f, 1));
	layout->addItem(DissMissAllNotificationButton);
	   	   
	m_DismissNotificationText = lumin::ui::UiText::Create(prism_, "");
	m_DismissNotificationText->setLocalPosition(glm::vec3(-.5f, -0.2f, 0));
	m_DismissNotificationText->setTextSize(0.09f);
	getRoot()->addChild(m_DismissNotificationText);

	m_ActivateNotificationText = lumin::ui::UiText::Create(prism_, "");
	m_ActivateNotificationText->setLocalPosition(glm::vec3(-.5f, -0.4f, 0));
	m_ActivateNotificationText->setTextSize(0.09f);
	getRoot()->addChild(m_ActivateNotificationText);

}

void notificationController::CreateDissmissButton(std::string in)
{
	m_DismissNotificationText->setText(in + "Dismiss");
}

void notificationController::CreateActivateButton(std::string in)
{
	m_ActivateNotificationText->setText(in + "Activate");
}