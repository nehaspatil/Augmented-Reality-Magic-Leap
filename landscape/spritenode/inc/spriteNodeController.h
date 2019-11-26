#pragma once
#include <lumin/Prism.h>
#include <lumin/PrismController.h>
#include <lumin/node/VideoNode.h>
#include <lumin/node/SpriteNode.h>
#include <lumin/ui/node/UiText.h>
class spriteNodeController :public lumin::PrismController {
public:
	spriteNodeController();

	virtual ~spriteNodeController();

	void onAttachPrism(lumin::Prism* prism) override;
	void onDetachPrism(lumin::Prism* prism) override;
	virtual void onUpdate(float a_fDelta) override;
	bool onEvent(lumin:: ServerEvent* a_pEvent) override;
	
private:
	lumin::Prism* m_prism;
	lumin::SpriteNode * bearSpriteNode;
	void CreateButtons();
	lumin::ui::UiText *UiTextCurrentEvent;

};