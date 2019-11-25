#include <ml_logging.h>
#include <ParticleOnCollide.h>
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

void ParticleEventOnCollide::onAttachPrism(lumin::Prism* prism)
{
	 m_currentPrism = prism;
	 // create a plane aganist which the particles collide with and event is generated
	 ResourceIDType pFBXResource = prism->createModelResourceId("res/Plane.FBX", .5f);
	 ModelNode* pModelStaticFBXNode = prism->createModelNode(pFBXResource);
	 pModelStaticFBXNode->setLocalPosition(glm::vec3(0, -.7f, 0));
	 pModelStaticFBXNode->setLocalScale(glm::vec3(0.007f, 0.7f, .7f));
	 pModelStaticFBXNode->setShader(lumin::utils::ShaderType::kUnlitTextured);
	 getRoot()->addChild(pModelStaticFBXNode);

	auto packageRes = prism->createParticlePackageResourceId("res/particle_sphere_event");
	auto m_ParticleNode1 = prism->createParticleNode(packageRes);
	m_ParticleNode1->setEffectName("Particles/ParentFields2.pkfx");

	m_ParticleNode1->setLocalScale(glm::vec3(.01f, .01f, .01f));
	m_ParticleNode1->setLocalPosition(glm::vec3(-.25f, 0.25f, 0));
	getRoot()->addChild(m_ParticleNode1);

   // Create a button to play the particle
	auto Button1 = lumin::ui::UiButton::CreateEclipseButton(prism, EclipseButtonParams(EclipseButtonType::kText, "Play Particle", .05f));
	Button1->setLocalPosition(glm::vec3(-.7f, .3f, 0));
	Button1->setLocalScale(glm::vec3(2.1f, 2.1f, 2.1f));
	Button1->setTextColor(glm::vec4(.1f, 1, .1f, 1));
	getRoot()->addChild(Button1);

	Button1->onActivateSub([m_ParticleNode1](const UiEventData&) {

		m_ParticleNode1->play();
	});

	CreateTextandButtonNodes();
}



bool ParticleEventOnCollide::onEvent(lumin::ServerEvent* a_pEvent)
{

	lumin::ServerEventTypeValue serverEventType = a_pEvent->getServerEventTypeValue();
	Prism* prism = getPrism();

	std::string s;
	s.append("Particle Event :");

	if (ParticleEventData::GetServerEventTypeValue() == serverEventType)
	{
		ParticleEventData* ParticleEvent = static_cast<lumin::ParticleEventData*>(a_pEvent);
		ML_LOG(Info, "Particle Node Event Data Detected.");

		s.append(ParticleEvent->getEventName()); // detects the OnCollide event
		m_textNode1->setText(s);
		return true;
	}

	return false;
}

void ParticleEventOnCollide::CreateTextandButtonNodes()
{
	m_textNode1 = lumin::ui::UiText::Create(m_currentPrism, "");
	m_textNode1->setLocalPosition(glm::vec3(-.8f, 0, 0));
	m_textNode1->setLocalScale(glm::vec3(5.1f, 5.1f, 5.1f));
	m_textNode1->setAllCaps(true);
	getRoot()->addChild(m_textNode1);
}
