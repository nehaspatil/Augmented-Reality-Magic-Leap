#pragma once
#include <lumin/Prism.h>
#include <lumin/PrismController.h>
#include <BaseExample.h>

using namespace lumin;
using namespace lumin::ui;
using namespace lumin::utils;

class Quad3DTexture final : public BaseExample {
public:

	Quad3DTexture() : BaseExample("Quad3D") {}
	void onAttachPrism(lumin::Prism* prism) override;
	bool onEvent(ServerEvent* a_pEvent) override;
	void onUpdate(float a_fDelta) override;

private:
	
	lumin::Prism* CurrentPrism;
	UiText* UiTextNode1;
	void GetQuad3DProperties();
	Quad3dNode* m_Quad3DNode;
	bool shouldAnimate = true;
	float scale = 1;
	

};
