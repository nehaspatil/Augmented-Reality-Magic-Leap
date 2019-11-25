#pragma once
#include <lumin/Prism.h>
#include <lumin/PrismController.h>
#include <lumin/ui/UiKit.h>
#include <lumin/ui/UiKitConsts.h>
#include <lumin/Consts.h>
#include <lumin/LandscapeApp.h>

using namespace lumin;
using namespace lumin::ui;
using namespace lumin::utils;

class ParticleSamplerBox final: public lumin::PrismController {

protected:
	void onAttachPrism(lumin::Prism* prism) override;	

private:
	
	lumin::Prism* m_currentPrism;
	UiText* m_titleNode;
	UiButton *m_playButton, *m_PropertiesZButton, *m_PropertiesXButton, *m_PropertiesYButton;
	void CreateTextandButtonNodes();

};