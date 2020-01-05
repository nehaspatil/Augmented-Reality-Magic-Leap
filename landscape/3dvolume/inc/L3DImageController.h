#pragma once
#include <lumin/Prism.h>
#include <lumin/PrismController.h>
#include <lumin/LandscapeApp.h>
#include <lumin/Prism.h>
#include <lumin/event/ServerEvent.h>

using namespace lumin;


class L3DImageController final :public lumin::PrismController {
public:

	L3DImageController() {};
		
protected:
	void onAttachPrism(lumin::Prism* prism) override;
	
private:
	lumin::Prism* CurrentPrism = nullptr;  // represents the bounded space where the Scene Graph renders.	

};
