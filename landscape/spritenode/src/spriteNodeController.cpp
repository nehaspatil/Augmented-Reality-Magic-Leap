#include <lumin/ui/UiKit.h>
#include <spriteNodeController.h>
#include <ml_logging.h>
#include <lumin/resource/TexturePackResource.h>
#include <lumin/resource/TextureMultiPack.h>
#include <lumin/node/ModelNode.h>
#include <lumin/node/TransformNode.h>
#include <lumin/node/SpriteNode.h>
#include <lumin/event/ServerEvent.h>
#include <lumin/event/SpriteAnimationEventData.h>

using namespace lumin;
using namespace lumin::ui;
using namespace lumin::utils;

spriteNodeController::spriteNodeController() :PrismController(" Texture Sprite ")
{
}

spriteNodeController::~spriteNodeController()
{
}

void spriteNodeController::onAttachPrism(lumin::Prism* prism)
{
	m_prism = prism;
	ML_LOG(Info, "spriteNodeController::onAttachPrism() ");
	
	auto titleNode = lumin::ui::UiText::Create(prism, "Bear Walking");
	titleNode->setLocalPosition(glm::vec3(-.8f, .7f, 0));
	titleNode->setLocalScale(glm::vec3(10.1f, 10.1f, 10.1f));
	getRoot()->addChild(titleNode);

	// Load sprite json files 
	std::vector<std::string> bearTexPackFiles = { "res/bear/Walking-1.json", "res/bear/Walking-2.json" };
	ResourceIDType bearTexPackResID = prism->createTexturePackResourceId(bearTexPackFiles, multipack::Params::DEFAULT);
	
	// create a sprite node
	bearSpriteNode = prism->createSpriteNode(bearTexPackResID);
	bearSpriteNode->setLocalPosition(glm::vec3(-0.4f, .3f, 0));
	bearSpriteNode->setLocalScale(bearSpriteNode->getLocalScale() * glm::vec3(0.41, 0.45, 1.0));
	// set sprite properties 
	bearSpriteNode->setRepeatCount(10);
	bearSpriteNode->setSpeedFactor(0.66f);
	bearSpriteNode->setPlaybackOrder(animation::PlaybackOrder::kForward);
	bearSpriteNode->setIsOpaque(false);
	getRoot()->addChild(bearSpriteNode);

	// create button to control
	CreateButtons();
}

void spriteNodeController::CreateButtons()
{	        
	auto BearSpritePlay = lumin::ui::UiToggle::CreateEclipseToggle(m_prism, EclipseToggleParams(EclipseToggleType::kSwitchWithIcon, SystemIcon::kPlay,"Stop/Start"));
	BearSpritePlay->setText("Stop/Start");
	BearSpritePlay->setLocalPosition(glm::vec3(-0.6f, 0.2f, 0));
	BearSpritePlay->setLocalScale(glm::vec3(2.1f, 2.1f, 2.1f));
	getRoot()->addChild(BearSpritePlay);

	BearSpritePlay->onActivateSub([this](const UiEventData& toggle) {

		if (UiToggle::CastFrom(toggle.getUiNode())->getOn()) {
			bearSpriteNode->start();
		}
		else {
			bearSpriteNode->stop();
		}
	});


	auto BearSpriteResume = lumin::ui::UiToggle::CreateEclipseToggle(m_prism, EclipseToggleParams(EclipseToggleType::kSwitchWithIcon, SystemIcon::kPlay, "Resume/Pause"));
	BearSpriteResume->setText("Resume/Pause");
	BearSpriteResume->setLocalPosition(glm::vec3(-0.1f, 0.2f, 0));
	BearSpriteResume->setLocalScale(glm::vec3(2.1f, 2.1f, 2.1f));
	getRoot()->addChild(BearSpriteResume);
	BearSpriteResume->onActivateSub([this](const UiEventData& toggle) {

		if (UiToggle::CastFrom(toggle.getUiNode())->getOn()) {
			bearSpriteNode->pause();
		}
		else {
			bearSpriteNode->resume();
		}
	});

	auto BearSpriteCount = lumin::ui::UiToggle::CreateEclipseToggle(m_prism, EclipseToggleParams(EclipseToggleType::kSwitchWithIcon, SystemIcon::kPlay, "Repeat 1 or 10"));
	BearSpriteCount->setText("Repeat 1/10");
	BearSpriteCount->setLocalPosition(glm::vec3(0.4f, 0.2f, 0));
	BearSpriteCount->setLocalScale(glm::vec3(2.1f, 2.1f, 2.1f));
	getRoot()->addChild(BearSpriteCount);

	BearSpriteCount->onActivateSub([this](const UiEventData& toggle) {

		if (UiToggle::CastFrom(toggle.getUiNode())->getOn()) {
			bearSpriteNode->setRepeatCount(1);
		}
		else {
			bearSpriteNode->setRepeatCount(10);
		}
	});

	auto BearSpriteRepeat = lumin::ui::UiToggle::CreateEclipseToggle(m_prism, EclipseToggleParams(EclipseToggleType::kSwitchWithIcon, SystemIcon::kPlay, "Repeat forever on /off "));
	BearSpriteRepeat->setText("Repeat forever");
	BearSpriteRepeat->setLocalPosition(glm::vec3(0.5f, 0.0f, 0));
	BearSpriteRepeat->setLocalScale(glm::vec3(2.1f, 2.1f, 2.1f));
	getRoot()->addChild(BearSpriteRepeat);

	BearSpriteRepeat->onActivateSub([this](const UiEventData& toggle) {

		if (UiToggle::CastFrom(toggle.getUiNode())->getOn()) {
			bearSpriteNode->setRepeatForever();
		}
		
	});

	auto BearSpriteStatus = lumin::ui::UiButton::CreateEclipseButton(m_prism, EclipseButtonParams(EclipseButtonType::kText, " Current States", .05f));
	BearSpriteStatus->setLocalPosition(glm::vec3(-0.05f, -0.3f, 0));
	BearSpriteStatus->setLocalScale(glm::vec3(2.1f, 2.1f, 2.1f));
	getRoot()->addChild(BearSpriteStatus);


	auto UiTextSpriteStatus = lumin::ui::UiText::Create(m_prism, "");
	UiTextSpriteStatus->setLocalPosition(glm::vec3(-.45f, -0.1f, 0));
	UiTextSpriteStatus->setLocalScale(glm::vec3(2.1f, 2.1f, 2.1f));
	BearSpriteStatus->addChild(UiTextSpriteStatus);	


	BearSpriteStatus->onActivateSub([this, UiTextSpriteStatus](const UiEventData& toggle) {

		std::string s;
		UiTextSpriteStatus->setAllCaps(true);		

			s.append("RepeatCount = "); s.append(std::to_string(bearSpriteNode->getRepeatCount()));
			s.append("\n SpeedFactor = "); s.append(std::to_string(bearSpriteNode->getSpeedFactor()));

			if (bearSpriteNode->isPaused())
				s.append("\n Pause = True");
			else
				s.append("\n Pause = false");

			if (bearSpriteNode->isPlaying ())
				s.append("\n Playing = True");
			else
				s.append("\n Playing = false");

			if ( bearSpriteNode->getPlaybackOrder() == animation::PlaybackOrder::kReverse)
			s.append("\n GetPlaybackOrder = Reverse  \n Set is Reverse");
			

			if (bearSpriteNode->getPlaybackOrder() == animation::PlaybackOrder::kForward)
				s.append("\n GetPlaybackOrder = Forward \n Set is kForward");

			UiTextSpriteStatus->setText(s);
				

	});


	UiTextCurrentEvent = lumin::ui::UiText::Create(m_prism, "");
	UiTextCurrentEvent->setLocalPosition(glm::vec3(-.5f, -.1f, 0));
	UiTextCurrentEvent->setLocalScale(glm::vec3(7.1f, 7.1f, 7.1f));
	UiTextCurrentEvent->setTextColor(glm::vec4(.2f, .2f, .9f, .9f));
	getRoot()->addChild(UiTextCurrentEvent);
	
}

void spriteNodeController::onDetachPrism(lumin::Prism*)
{
	ML_LOG(Info, "TextureController::onDetachPrism() Done");
	deleteSceneGraph();
}

bool spriteNodeController:: onEvent(lumin::ServerEvent* a_pEvent)
{	
	lumin::ServerEventTypeValue serverEventType = a_pEvent->getServerEventTypeValue();
	Prism* prism = getPrism();

	if (SpriteAnimationEventData::GetServerEventTypeValue() == serverEventType)
	{
		SpriteAnimationEventData* spriteEventData = static_cast<lumin::SpriteAnimationEventData*>(a_pEvent);
		std::string s;
		switch (spriteEventData->getSpriteAnimationEventType()) 
		{
			case SpriteAnimationEventType::kStarted: {
				s+="Event Started";
				ML_LOG(Info, "Sprite node Started event.");
				break;
			}
			case SpriteAnimationEventType::kPaused: {
				s+="Event Pause";
				ML_LOG(Info, "Sprite node paused event.");
				break;
			}
			case SpriteAnimationEventType::kResumed: {
				s+="Event Resume";
				ML_LOG(Info, "Sprite node Resumed event.");
				break;
			}
			case SpriteAnimationEventType::kStopped: {
				s+="Event Stop";
				ML_LOG(Info, "Sprite node stopped event.");
				break;
			}
			case SpriteAnimationEventType::kLooped: {
				s+="Event Looped";
				ML_LOG(Info, "Sprite node Looped event.");
				break;
			}
			default: {
				ML_LOG(Info, "Event Sprite node unknown event.");
				break;
				}
		}
		s += "\n Current FrameIndex = ";
		s += std::to_string(spriteEventData->getCurrentFrameIndex());
		UiTextCurrentEvent->setText(s);
		return true;
	}

	return false;

}
void spriteNodeController::onUpdate(float a_fDelta)
{	
}