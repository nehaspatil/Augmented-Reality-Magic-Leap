#include <ml_logging.h>
#include <ParticleEventOnDeath.h>
#include <lumin/ui/UiKit.h>
#include <lumin/node/ParticleNode.h>
#include <lumin/event/ServerEvent.h>
#include <lumin/event/ParticleEventData.h>
#include <glm/ext.hpp>
#include <ml_logging.h>
#include <string.h>
#include <lumin/node/ModelNode.h>
#include <lumin/utils/RendererInterface.h>

using namespace lumin;
using namespace lumin::ui;
using namespace lumin::utils;
using namespace glm;

void ParticleEventOnDeath::onAttachPrism(lumin::Prism* prism)
{
	 m_currentPrism = prism;	
	 auto packageRes = prism->createParticlePackageResourceId("res/particle_onDeath");
	 auto m_ParticleNode1 = prism->createParticleNode(packageRes);
	 m_ParticleNode1->setEffectName("Particles/Warfare/Spark_ExternEvents.pkfx");	
	 m_ParticleNode1->setLocalScale(glm::vec3(.01f, .01f, .01f));
	 m_ParticleNode1->setLocalPosition(glm::vec3(-.25f, 0.25f, 0));
	 getRoot()->addChild(m_ParticleNode1);
	 	 
	 CreateTextandButtonNodes();
	 	 
	 m_playButton->onActivateSub([m_ParticleNode1](const UiEventData&) {
		 m_ParticleNode1->play();
	 });	
}

bool ParticleEventOnDeath::onEvent(lumin::ServerEvent* a_pEvent)
{	
	lumin::ServerEventTypeValue serverEventType = a_pEvent->getServerEventTypeValue();
	Prism* prism = getPrism();

	std::string s;
	s.append("Particle Event :");

	if (ParticleEventData::GetServerEventTypeValue() == serverEventType)
	{
		ParticleEventData* ParticleEvent = static_cast<lumin::ParticleEventData*>(a_pEvent);
		ML_LOG(Info, "Particle Node Event Data Detected.");
				
		s.append(ParticleEvent->getEventName()); // detects the OnDeath event 
		m_titleNode->setText(s);
		return true;
	}
	
	return false;
}

void ParticleEventOnDeath::CreateTextandButtonNodes()
{
	m_titleNode = lumin::ui::UiText::Create(m_currentPrism, "OnDeath Play and Stop ");
	m_titleNode->setLocalPosition(glm::vec3(-.8f, 0, 0));
	m_titleNode->setLocalScale(glm::vec3(5.1f, 5.1f, 5.1f));
	m_titleNode->setAllCaps(true);
	getRoot()->addChild(m_titleNode);

	m_playButton = lumin::ui::UiButton::CreateEclipseButton(m_currentPrism, EclipseButtonParams(EclipseButtonType::kText, "Play Particle", .05f));
	m_playButton->setLocalPosition(glm::vec3(-.7f, .4f, 0));
	m_playButton->setLocalScale(glm::vec3(2.1f, 2.1f, 2.1f));
	m_playButton->setTextColor(glm::vec4(.1f, 1, .1f, 1));
	getRoot()->addChild(m_playButton);
}
