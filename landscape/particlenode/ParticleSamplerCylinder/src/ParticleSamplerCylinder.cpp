#include <ml_logging.h>
#include <ParticleSamplerCylinder.h>
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
using namespace lumin::particles;
using namespace glm;

void ParticleSamplerCylinder::onAttachPrism(lumin::Prism* prism)
{
	m_currentPrism = prism;
	
	auto packageRes = prism->createParticlePackageResourceId("res/particle_cylinder");
	auto m_ParticleNode1 = prism->createParticleNode(packageRes);
	m_ParticleNode1->setEffectName("Particles/sparks_cylinder.pkfx", true);
	m_ParticleNode1->setLocalScale(glm::vec3(.01f, .01f, .01f));
	m_ParticleNode1->setLocalPosition(glm::vec3(-.25f, 0.25f, 0));
	getRoot()->addChild(m_ParticleNode1);		

	m_ParticleNode1->play();

	// create a button to set cyclinder dimensions in the effect , outer radius , inner radius , height
	CreateTextandButtonNodes();
	auto currentStatusText = m_titleNode;
	// radius 1  inner .3 and  height 1.5
	m_PropertiesButtonOuterRadius->onActivateSub([m_ParticleNode1, currentStatusText](const UiEventData&) {

		CylinderShapeSampler *m_CurrentCylinderSampler = new CylinderShapeSampler();
		m_CurrentCylinderSampler->setOuterRadius(2);
		m_CurrentCylinderSampler->setInnerRadius(.3f);
		m_CurrentCylinderSampler->setHeight(1.5f);
		auto cylinder_sampler = static_cast<ShapeSampler*>(m_CurrentCylinderSampler);
		m_ParticleNode1->setSampler("Shape_1", *cylinder_sampler);

		std::string s;
		s.append("Properties default outerR =1 innerR=.3 height = 1.5 ");
		s.append(" \n Current Outer Radius ");
		s.append(std::to_string(m_CurrentCylinderSampler->getOuterRadius()));
		s.append(" Inner Radius ");
		s.append(std::to_string(m_CurrentCylinderSampler->getInnerRadius()));
		s.append(" Height ");
		s.append(std::to_string(m_CurrentCylinderSampler->getHeight()));
		currentStatusText->setText(s);


	});

	m_PropertiesButtonInnerRadius->onActivateSub([m_ParticleNode1, currentStatusText](const UiEventData&) {


		CylinderShapeSampler *m_CurrentCylinderSampler = new CylinderShapeSampler();
		m_CurrentCylinderSampler->setOuterRadius(1);
		m_CurrentCylinderSampler->setInnerRadius(.7f);
		m_CurrentCylinderSampler->setHeight(1.5f);
		auto cylinder_sampler = static_cast<ShapeSampler*>(m_CurrentCylinderSampler);
		m_ParticleNode1->setSampler("Shape_1", *cylinder_sampler);

		std::string s;
		s.append("Properties default outerR =1 innerR=.3 height = 1.5 ");
		s.append(" \n Current Outer Radius ");
		s.append(std::to_string(m_CurrentCylinderSampler->getOuterRadius()));
		s.append(" Inner Radius ");
		s.append(std::to_string(m_CurrentCylinderSampler->getInnerRadius()));
		s.append(" Height ");
		s.append(std::to_string(m_CurrentCylinderSampler->getHeight()));
		currentStatusText->setText(s);
	});

	m_PropertiesButtonHeight->onActivateSub([m_ParticleNode1, currentStatusText](const UiEventData&) {

		CylinderShapeSampler *m_CurrentCylinderSampler = new CylinderShapeSampler();
		m_CurrentCylinderSampler->setOuterRadius(1);
		m_CurrentCylinderSampler->setInnerRadius(.3f);
		m_CurrentCylinderSampler->setHeight(2.5f);

		auto cylinder_sampler = static_cast<ShapeSampler*>(m_CurrentCylinderSampler);
		m_ParticleNode1->setSampler("Shape_1", *cylinder_sampler);

		std::string s;
		s.append("Properties default outerR =1 innerR=.3 height = 1.5 ");
		s.append(" \n Current Outer Radius ");
		s.append(std::to_string(m_CurrentCylinderSampler->getOuterRadius()));
		s.append(" Inner Radius ");
		s.append(std::to_string(m_CurrentCylinderSampler->getInnerRadius()));
		s.append(" Height ");
		s.append(std::to_string(m_CurrentCylinderSampler->getHeight()));
		currentStatusText->setText(s);
	});

}
void ParticleSamplerCylinder::CreateTextandButtonNodes()
{
	m_titleNode = lumin::ui::UiText::Create(m_currentPrism, "");
	m_titleNode->setLocalPosition(glm::vec3(-.8f, 0, 0));
	m_titleNode->setLocalScale(glm::vec3(5.1f, 5.1f, 5.1f));
	m_titleNode->setAllCaps(true);
	getRoot()->addChild(m_titleNode);

	m_PropertiesButtonOuterRadius = lumin::ui::UiButton::CreateEclipseButton(m_currentPrism, EclipseButtonParams(EclipseButtonType::kText, "Cylinder OuterRadius \n Output Color : Yellow", .07f));
	m_PropertiesButtonOuterRadius->setLocalPosition(glm::vec3(.5f, -.3f, 0));
	m_PropertiesButtonOuterRadius->setTextColor(glm::vec4(.1f, 1, .1f, 1));
	getRoot()->addChild(m_PropertiesButtonOuterRadius);

	m_PropertiesButtonInnerRadius = lumin::ui::UiButton::CreateEclipseButton(m_currentPrism, EclipseButtonParams(EclipseButtonType::kText, "Cylinder Inner Radius \n Output Color : Same More Intensity", .07f));
	m_PropertiesButtonInnerRadius->setLocalPosition(glm::vec3(.5f, -.5f, 0));
	m_PropertiesButtonInnerRadius->setTextColor(glm::vec4(.1f, 1, .1f, 1));
	getRoot()->addChild(m_PropertiesButtonInnerRadius);

	m_PropertiesButtonHeight = lumin::ui::UiButton::CreateEclipseButton(m_currentPrism, EclipseButtonParams(EclipseButtonType::kText, "Cylinder Height \n Output Color : Green", .07f));
	m_PropertiesButtonHeight->setLocalPosition(glm::vec3(.5f, -.7f, 0));
	m_PropertiesButtonHeight->setTextColor(glm::vec4(.1f, 1, .1f, 1));
	getRoot()->addChild(m_PropertiesButtonHeight);
}
