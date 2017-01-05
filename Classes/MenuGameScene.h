#ifndef __MENUGAME_SCENE_H__
#define __MENUGAME_SCENE_H__
#include "ui/CocosGUI.h"
#include "cocos2d.h"
USING_NS_CC;
class MenuGame : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void ExitGame(Ref* pSender);
	void update(float dt);
	void PlayGame(Ref* pSender);
	cocos2d::ui::LoadingBar* load;
	cocos2d::MenuItemImage* Play;
    // implement the "static create()" method manually
    CREATE_FUNC(MenuGame);
	
private:
	int LoadingStep;
};

#endif // __MENUGAME_SCENE_H__
