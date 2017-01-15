#include "MenuGameScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
USING_NS_CC;
using namespace std;
Scene* MenuGame::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuGame::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuGame::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("graphics/menu-background.png");
	bg->setPosition(Vec2(visibleSize.width/2+origin.x, visibleSize.height/2+origin.y));
	bg->setScaleX((float)visibleSize.width / bg->getContentSize().width);
	bg->setScaleY((float)visibleSize.height / bg->getContentSize().height);
    Play = MenuItemImage::create("graphics/play-button.png", "graphics/play-button(selected).png", CC_CALLBACK_1(MenuGame::PlayGame, this));
	Play->setScale((float)visibleSize.width*0.4 / Play->getContentSize().width);
	Play->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.25));
	auto menu = Menu::create(Play, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
	this->addChild(bg, -1);
	auto Rate = ui::Button::create("graphics/Rate.png");
	Rate->setScale(visibleSize.height*0.3 / Rate->getContentSize().height);
	Rate->setPosition(Vec2(visibleSize.width / 2 + Rate->getBoundingBox().size.width*2, Play->getPositionY()));
	Rate->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
												  std::string link = std::string("https://play.google.com/store/apps/details?id=com.KNVN.Tornadoer");
												  Application::getInstance()->openURL(link);
												  break;
		}
		}
	});
	this->addChild(Rate, 4);
	load = ui::LoadingBar::create("graphics/loading-bar.png");
	load->setScaleX(visibleSize.width*0.5 / load->getContentSize().width);
	load->setScaleY(visibleSize.height*0.1 / load->getContentSize().height);
	load->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.02 + load->getBoundingBox().size.height / 2));
	load->setDirection(ui::LoadingBar::Direction::LEFT);
	load->setOpacity(0);
	this->addChild(load, 1);
		return true;
}
void MenuGame::ExitGame(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/select.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/select.wav");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	return;
#endif

	Director::getInstance()->end();

}
void MenuGame::PlayGame(Ref* pSender)
{
	load->setOpacity(255);
	Play->setEnabled(false);
	LoadingStep = 0;
	this->scheduleUpdate();
}
void MenuGame::update(float dt)
{
	switch (LoadingStep)
	{
	case 0:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("graphics/Canon&Bomb sprites/bomb-sprites.plist", "graphics/Canon&Bomb sprites/bomb-sprites.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("graphics/Canon&Bomb sprites/canon-sprites.plist", "graphics/Canon&Bomb sprites/canon-sprites.png");
		load->setPercent(6);
		break;
	case 1:
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/bomb beep.mp3");
		break;
	case 2:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("graphics/Destroyed_House/Type_3/destroyed-house-type 3-sprites.plist", "graphics/Destroyed_House/Type_3/destroyed-house-type 3-sprites.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("graphics/Trees falling/tree-falling-sprites.plist", "graphics/Trees falling/tree-falling-sprites.png");
		load->setPercent(18);
		break;
	case 3:
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/destroyed houses.mp3");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("graphics/Wall sprites/wall-sprites.plist", "graphics/Wall sprites/sprites.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("graphics/wind-fans/wind-fan-sprites-1.plist", "graphics/wind-fans/wind-fan-sprites-1.png");
		load->setPercent(24);
		break;
	case 4:
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/destroyed tree.mp3");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("graphics/wind-fans/wind-fan-sprites-2.plist", "graphics/wind-fans/wind-fan-sprites-2.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("graphics/items sprites/heart/heart-sprites.plist", "graphics/items sprites/heart/heart-sprites.png");
		load->setPercent(30);
		break;
	case 5:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("graphics/items sprites/speed/speed-sprites.plist", "graphics/items sprites/speed/speed-sprites.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("graphics/items sprites/storm/storm-sprites.plist", "graphics/items sprites/storm/storm-sprites.png");
		load->setPercent(36);
		break;
	case 6:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("graphics/Tornado/Begin/tornado-begin-sprites.plist", "graphics/Tornado/Begin/tornado-begin-sprites.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("graphics/Tornado/Normal/tornado-normal-sprites.plist", "graphics/Tornado/Normal/tornado-normal-sprites.png");
		load->setPercent(42);
		break;
	case 7:
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sounds/tornado(heart).mp3");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("graphics/Tornado/Heart/tornado-heart-sprites-1.plist", "graphics/Tornado/Heart/tornado-heart-sprites-1.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("graphics/Tornado/Heart/tornado-heart-sprites-2.plist", "graphics/Tornado/Heart/tornado-heart-sprites-2.png");
		load->setPercent(48);
		break;
	case 8:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("graphics/Tornado/Heart/tornado-heart-sprites-3.plist", "graphics/Tornado/Heart/tornado-heart-sprites-3.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("graphics/Tornado/Heart/tornado-heart-sprites-4.plist", "graphics/Tornado/Heart/tornado-heart-sprites-4.png");
		load->setPercent(54);
		break;
	case 9:
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sounds/tornado(normal).mp3");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("graphics/Tornado/Heart/tornado-heart-sprites-5.plist", "graphics/Tornado/Heart/tornado-heart-sprites-5.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("graphics/Tornado/Storm/tornado-storm-sprites.plist", "graphics/Tornado/Storm/tornado-storm-sprites.png");
		load->setPercent(60);
		break;
	case 10:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("graphics/Destroyed_House/Type_1/destroyed-house-type 1-sprites.plist", "graphics/Destroyed_House/Type_1/destroyed-house-type 1-sprites.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("graphics/Destroyed_House/Type_2/destroyed-house-type 2-sprites.plist", "graphics/Destroyed_House/Type_2/destroyed-house-type 2-sprites.png");
		load->setPercent(66);
		break;
	case 11:
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/point.wav");
		load->setPercent(72);
		break;
	case 12:
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/wind.mp3");
		load->setPercent(78);
		break;
	case 13:
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/bomb explosion.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/canon.mp3");
		load->setPercent(84);
		break;
	case 14:
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/tornado begin.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/tornado end.mp3");
		load->setPercent(90);
		break;
	case 15:
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/item.wav");
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/pushing door.mp3");
		break;
	case 16:
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sounds/tornado(speed).mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sounds/tornado(storm).mp3");
		load->setPercent(96);
		break;
	case 17:
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/select.wav");
		load->setPercent(100);
		break;
	case 18:
		auto GameScene = GAME::createScene();
		Director::getInstance()->replaceScene(GameScene);
		break;
	}
	LoadingStep++;
}
