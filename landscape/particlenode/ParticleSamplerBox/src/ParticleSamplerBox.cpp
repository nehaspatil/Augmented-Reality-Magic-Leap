#include <ml_logging.h>
#include <ParticleSamplerBox.h>
#include <lumin/ui/UiKit.h>
#include <lumin/node/ParticleNode.h>
#include <lumin/event/ServerEvent.h>
#include <lumin/event/ParticleEventData.h>
#include <glm/ext.hpp>
#include <ml_logging.h>
#include <string.h>
#include <lumin/node/ModelNode.h>
#include <lumin/utils/RendererInterface.h>
#include <lumin/utils/ParticleSamplers.h>


using namespace lumin;
using namespace lumin::ui;
using namespace lumin::utils;
using namespace glm;
using namespace particles;

void ParticleSamplerBox::onAttachPrism(lumin::Prism* prism)
{
	m_currentPrism = prism;
		
	auto packageRes = prism->createParticlePackageResourceId("res/particle_box");
	auto m_ParticleNode1 = prism->createParticleNode(packageRes);
	m_ParticleNode1->setEffectName("Particles/sparks_box.pkfx", true);
	m_ParticleNode1->setLocalScale(glm::vec3(.01f, .01f, .01f));
	m_ParticleNode1->setLocalPosition(glm::vec3(-.25f, 0.0f, 0));
	getRoot()->addChild(m_ParticleNode1);

	
	m_ParticleNode1->play();
	// create a button to set X, Y Z properties for samplers 
	CreateTextandButtonNodes();
	auto currentStatusText = m_titleNode;
	// .1 , .1 , .1 = silver
	m_PropertiesXButton->onActivateSub([m_ParticleNode1, currentStatusText](const UiEventData&) {


		BoxShapeSampler *m_CurrentSampler = new BoxShapeSampler();
		glm::vec3 size;
		size.x = .9f; size.y = .1f; size.z = .1f;
		m_CurrentSampler->setSize(size);

		auto box_sampler = static_cast<ShapeSampler*>(m_CurrentSampler);
		if (m_ParticleNode1->setSampler("Shape_1", *box_sampler))
			currentStatusText->setText("Setting X Success");
		else
			currentStatusText->setText("Setting X Fail");

		std::string s;
		s.append("Properties size X,Y,Z = .1 ");
		s.append(" \n Current Size ");
		s.append(glm::to_string(m_CurrentSampler->getSize()));
		currentStatusText->setText(s);

	});

	m_PropertiesYButton->onActivateSub([m_ParticleNode1, currentStatusText](const UiEventData&) {

		BoxShapeSampler *m_CurrentSampler = new BoxShapeSampler();
		glm::vec3 size;
		size.x = .1f; size.y = .9f; size.z = .1f;
		m_CurrentSampler->setSize(size);
		auto box_sampler = static_cast<ShapeSampler*>(m_CurrentSampler);
		if (m_ParticleNode1->setSampler("Shape_1", *box_sampler))
			currentStatusText->setText("Setting Y Success");
		else
			currentStatusText->setText("Setting Y Fail");

		std::string s;
		s.append("Properties size X,Y,Z = .1 ");
		s.append(" \n Current Size ");
		s.append(glm::to_string(m_CurrentSampler->getSize()));
		currentStatusText->setText(s);

	});

	m_PropertiesZButton->onActivateSub([m_ParticleNode1, currentStatusText](const UiEventData&) {

		BoxShapeSampler *m_CurrentSampler = new BoxShapeSampler();
		glm::vec3 size;
		size.x = .1f; size.y = .1f; size.z = .9f;
		m_CurrentSampler->setSize(size);
		auto box_sampler = static_cast<ShapeSampler*>(m_CurrentSampler);
		if (m_ParticleNode1->setSampler("Shape_1", *box_sampler))
			currentStatusText->setText("Setting Z Success");
		else
			currentStatusText->setText("Setting Z Fail");


		std::string s;
		s.append("Properties size X,Y,Z = .1 ");
		s.append(" \n Current Size ");
		s.append(glm::to_string(m_CurrentSampler->getSize()));
		currentStatusText->setText(s);

	});
}
void ParticleSamplerBox::CreateTextandButtonNodes()
{

	m_titleNode = lumin::ui::UiText::Create(m_currentPrism, "");
	m_titleNode->setLocalPosition(glm::vec3(-.8f, 0, 0));
	m_titleNode->setLocalScale(glm::vec3(5.1f, 5.1f, 5.1f));
	m_titleNode->setAllCaps(true);
	getRoot()->addChild(m_titleNode);

	m_PropertiesXButton = lumin::ui::UiButton::CreateEclipseButton(m_currentPrism, EclipseButtonParams(EclipseButtonType::kText, "Box X \n Output Color : Red", .07f));
	m_PropertiesXButton->setLocalPosition(glm::vec3(.3f, -.3f, 0));
	m_PropertiesXButton->setTextColor(glm::vec4(.1f, 1, .1f, 1));
	getRoot()->addChild(m_PropertiesXButton);

	m_PropertiesYButton = lumin::ui::UiButton::CreateEclipseButton(m_currentPrism, EclipseButtonParams(EclipseButtonType::kText, "Box Y \n Output Color : Green", .07f));
	m_PropertiesYButton->setLocalPosition(glm::vec3(.5f, -.5f, 0));
	m_PropertiesYButton->setTextColor(glm::vec4(.1f, 1, .1f, 1));
	getRoot()->addChild(m_PropertiesYButton);


	m_PropertiesZButton = lumin::ui::UiButton::CreateEclipseButton(m_currentPrism, EclipseButtonParams(EclipseButtonType::kText, "Box Z \n Output Color : Blue", .07f));
	m_PropertiesZButton->setLocalPosition(glm::vec3(.5f, -.7f, 0));
	m_PropertiesZButton->setTextColor(glm::vec4(.1f, 1, .1f, 1));
	getRoot()->addChild(m_PropertiesZButton);

}

