#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "MenuGameScene.h"
#define PTM_RATIO 32.0
USING_NS_CC;
using namespace std;
using namespace CocosDenshion;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "pluginadmob/PluginAdMob.h"
#include "pluginfacebook/PluginFacebook.h"
using namespace sdkbox;
#endif
Scene* GAME::createScene()
{
    // 'scene' is an autorelease object
    auto Scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GAME::create();

    // add layer as a child to scene
    Scene->addChild(layer);

    // return the scene
    return Scene;
}
// on "init" you need to initialize your instance
auto audio = SimpleAudioEngine::getInstance();
bool GAME::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	 begin_bg = Sprite::create("graphics/background-begin.png");//Begin_background
	begin_bg->setScaleX(visibleSize.width*2 / begin_bg->getContentSize().width);
	begin_bg->setScaleY(visibleSize.height / begin_bg->getContentSize().height);
	begin_bg->setPosition(Vec2(visibleSize.width , visibleSize.height / 2));
	this->addChild(begin_bg, -2);
	begin_bg->setTag(16);

	pause_button = ui::CheckBox::create("graphics/pause-button.png", "graphics/pause-button(selected).png");//pause_button
	pause_button->setScale(visibleSize.height*0.12 / pause_button->getContentSize().height);
	pause_button->setPosition(Vec2(visibleSize.width  - pause_button->getBoundingBox().size.width / 2, visibleSize.height - pause_button->getBoundingBox().size.height / 2));
	GAME::PauseButton();
	pause_button->addEventListener([&](Ref* sender, ui::CheckBox::EventType type)
	{
		switch (type)
		{
		case ui::CheckBox::EventType::SELECTED:
		{
			audio->pauseAllEffects();
			audio->pauseBackgroundMusic();
			paus_table->setOpacity(255);
			restart_bt->setOpacity(255);
			restart_bt->setTouchEnabled(true);
			continue_bt->setOpacity(255);
			continue_bt->setTouchEnabled(true);
			back_bt->setOpacity(255);
			back_bt->setTouchEnabled(true);
			this->pauseSchedulerAndActions();
			auto node = this->getChildren();
			for (int i = 0; i < node.size(); i++)
			{
				if (node.at(i)->getTag() == -3)
					continue;
				node.at(i)->pauseSchedulerAndActions();
			}
		}
		break;
		case ui::CheckBox::EventType::UNSELECTED:
		{
			paus_table->setOpacity(0);
			restart_bt->setOpacity(0);
			restart_bt->setTouchEnabled(false);
			continue_bt->setOpacity(0);
			continue_bt->setTouchEnabled(false);
			back_bt->setOpacity(0);
			back_bt->setTouchEnabled(false);
		}
		break;
		default:
			break;
		}
	});
	pause_button->setTag(-3);
	this->addChild(pause_button, 3);
	st_button = ui::CheckBox::create("graphics/setting-button.png", "graphics/setting-button(selected).png");//setting_button
	st_button->setScale(visibleSize.height*0.12 / st_button->getContentSize().height);
	st_button->setPosition(Vec2(visibleSize.width - pause_button->getBoundingBox().size.width - visibleSize.width*0.05 - st_button->getBoundingBox().size.width / 2, visibleSize.height - st_button->getBoundingBox().size.height / 2));
	GAME::SettingButton();
	st_button->addEventListener([&](Ref* sender, ui::CheckBox::EventType type)
	{
		switch (type)
		{
		case ui::CheckBox::EventType::SELECTED:
		{
			st_table->setOpacity(255);
			sfx->setOpacity(255);
			sfx->setTouchEnabled(true);
			music_bt->setOpacity(255);
			music_bt->setTouchEnabled(true);
			exit_bt->setOpacity(255);
			exit_bt->setTouchEnabled(true);
		}
			break;
		case ui::CheckBox::EventType::UNSELECTED:
		{
			st_table->setOpacity(0);
			sfx->setOpacity(0);
			sfx->setTouchEnabled(false);
			music_bt->setOpacity(0);
			music_bt->setTouchEnabled(false);
			exit_bt->setOpacity(0);
			exit_bt->setTouchEnabled(false);
		}
			break;
		default:
			break;
		}
	});
	st_button->setTag(-3);
	this->addChild(st_button, 3);
		//
	power = ui::LoadingBar::create("graphics/power bar.png");//power_bar
	power->setScaleX(visibleSize.width*0.35 / power->getContentSize().width);
	power->setScaleY(visibleSize.height*0.06 / power->getContentSize().height);
	power->setPosition(Vec2(power->getBoundingBox().size.width / 2, visibleSize.height - visibleSize.height*0.01 - power->getBoundingBox().size.height / 2));
	power->setDirection(ui::LoadingBar::Direction::LEFT);
	this->addChild(power, 3);
	up_bt = ui::Button::create("graphics/up-button.png");//up button
	up_bt->setScale(visibleSize.height*0.2 / up_bt->getContentSize().height);
	up_bt->setPosition(Vec2(visibleSize.width*0.03 + up_bt->getBoundingBox().size.width / 2, up_bt->getBoundingBox().size.height / 2));
	up_bt->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			isDown = false;
			isUp = true;
		}
		break;
		case ui::Widget::TouchEventType::ENDED:
		{
			isUp = false;
		}
		break;
		default:
			break;
		}
	});
	this->addChild(up_bt, 1);
	down_bt = ui::Button::create("graphics/down-button.png");//down button
	down_bt->setScale(visibleSize.height*0.2 / down_bt->getContentSize().height);
	down_bt->setPosition(Vec2(visibleSize.width-visibleSize.width*0.03 - up_bt->getBoundingBox().size.width / 2, down_bt->getBoundingBox().size.height / 2));
	down_bt->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			isUp = false;
			isDown = true;
		}
		break;
		case ui::Widget::TouchEventType::ENDED:
		{
			isDown = false;
		}
		break;
		default:
			break;
		}
	});
	this->addChild(down_bt, 1);
	auto scoretemp = String::createWithFormat("%i", score);//score
	 label = Label::createWithTTF(scoretemp->getCString(), "fonts/Marker Felt.ttf", visibleSize.height*0.1);//score label
	label->setColor(Color3B::GRAY);
	label->setPosition(Vec2(visibleSize.width /2, visibleSize.height-visibleSize.height*0.02-label->getContentSize().height/2));
	label->enableGlow(Color4B::WHITE);
	this->addChild(label, 3);
	
	heart = ui::Button::create("graphics/items sprites/heart/heart-sprite-1.png");//heart button
	heart->setScale(visibleSize.width*0.1 / heart->getContentSize().width);
	heart->setPosition(Vec2(visibleSize.width / 2, heart->getBoundingBox().size.height / 2));
	heart->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		break;
		case ui::Widget::TouchEventType::ENDED:
		{
			if (HeartScore>0)
			{
				TYPE = TornadoType::HEART;
				tor->setOpacity(0);
				tor_body->DestroyFixture(tor_fixture);
				audio->stopBackgroundMusic();
				torheart->setOpacity(255);
				torheart->runAction(Sequence::create(GAME::CreateAnimate("tornado-heart-", 22, 0.3f, 1), GAME::CreateAnimate("tornado-heart-", 1, 7.5f, 23), GAME::CreateAnimate("tornado-heart-", 3, 0.3f, 24), CallFunc::create(CC_CALLBACK_0(GAME::SetTorNormalPosition, this)), CallFunc::create(CC_CALLBACK_0(GAME::NormalTorCall, this)), NULL));
				audio->playBackgroundMusic("sounds/tornado(heart).mp3", false);
				//...
				heart->setTouchEnabled(false);
				storm->setTouchEnabled(false);
				speed->setTouchEnabled(false);
				heart->setOpacity(0);
				heart_spr->setOpacity(255);
				heart_spr->runAction(Sequence::create(GAME::CreateAnimate("heart-sprite-", 6, 4.5f, 2), CallFunc::create([&] {heart_spr->setOpacity(0); heart->setTouchEnabled(true); heart->setOpacity(255); storm->setTouchEnabled(true); speed->setTouchEnabled(true); }), NULL));
				HeartScore--;
			}
		}
		break;
		default:
			break;
		}
	});
	this->addChild(heart, 1);
	speed = ui::Button::create("graphics/items sprites/speed/speed-sprite-1.png");//speed button
	speed->setScale(visibleSize.width*0.1 / speed->getContentSize().width);
	speed->setPosition(Vec2(visibleSize.width / 2-visibleSize.width*0.05-heart->getBoundingBox().size.width/2-speed->getBoundingBox().size.width/2, speed->getBoundingBox().size.height / 2));
	speed->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		break;
		case ui::Widget::TouchEventType::ENDED:
		{
			if (SpeedScore > 0)
			{
				TYPE = TornadoType::SPEED;
				isBeginTorUpdate = true;
				SpeedVelocity = 1.5;
				CheckSpeedUpdate = true;
				tor->runAction(Sequence::create(DelayTime::create(8.0), CallFunc::create(CC_CALLBACK_0(GAME::NormalTorCall, this)), CallFunc::create([&]{SpeedVelocity = 1.0; CheckSpeedUpdate = true; }), NULL));
				storm->setTouchEnabled(false);
				heart->setTouchEnabled(false);
				speed->setTouchEnabled(false);
				speed->setOpacity(0);
				speed_spr->setOpacity(255);
				speed_spr->runAction(Sequence::create(GAME::CreateAnimate("speed-sprite-", 6, 3.0f, 2), CallFunc::create([&] {speed_spr->setOpacity(0); storm->setTouchEnabled(true); speed->setOpacity(255); heart->setTouchEnabled(true); speed->setTouchEnabled(true); }), NULL));
				SpeedScore--;
			}
		}
		break;
		default:
			break;
		}
	});
	this->addChild(speed, 1);
	storm = ui::Button::create("graphics/items sprites/storm/storm-sprite-1.png");//storm button
	storm->setScale(visibleSize.width*0.1 / storm->getContentSize().width);
	storm->setPosition(Vec2(visibleSize.width / 2 +heart->getBoundingBox().size.width/2+ visibleSize.width*0.05 + speed->getBoundingBox().size.width / 2, storm->getBoundingBox().size.height / 2));
	storm->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		break;
		case ui::Widget::TouchEventType::ENDED:
		{
			if (StormScore > 0)
			{
				TYPE = TornadoType::STORM;
				isBeginTorUpdate = true;
				tor->runAction(Sequence::create(DelayTime::create(20.0), CallFunc::create(CC_CALLBACK_0(GAME::NormalTorCall, this)), NULL));
				storm->setTouchEnabled(false);
				heart->setTouchEnabled(false);
				speed->setTouchEnabled(false);
				storm->setOpacity(0);
				storm_spr->setOpacity(255);
				storm_spr->runAction(Sequence::create(GAME::CreateAnimate("storm-sprite-", 6, 5.5f, 2), CallFunc::create([&] {storm_spr->setOpacity(0); storm->setTouchEnabled(true); storm->setOpacity(255); heart->setTouchEnabled(true); speed->setTouchEnabled(true); }), NULL));
				StormScore--;
			}

		}
		break;
		default:
			break;
		}
	});
	this->addChild(storm, 1);
	auto heartscoretemp = String::createWithFormat("%i", HeartScore);
    heartlabel = Label::createWithTTF(heartscoretemp->getCString(), "fonts/Marker Felt.ttf", visibleSize.height*0.03);//heart score label
	heartlabel->setColor(Color3B::WHITE);
	heartlabel->setPosition(Vec2(visibleSize.width / 2, heart->getBoundingBox().size.height + visibleSize.height*0.01 + heartlabel->getContentSize().height / 2));
	heartlabel->enableShadow();
	this->addChild(heartlabel, 1);
	heart_spr = Sprite::createWithSpriteFrameName("heart-sprite-2.png");
	heart_spr->setScale(visibleSize.width*0.1 / heart_spr->getContentSize().width);
	heart_spr->setPosition(Vec2(visibleSize.width / 2, heart_spr->getBoundingBox().size.height / 2));
	heart_spr->setOpacity(0);
	this->addChild(heart_spr, 1);
	auto speedscoretemp = String::createWithFormat("%i", SpeedScore);
    speedlabel = Label::createWithTTF(speedscoretemp->getCString(), "fonts/Marker Felt.ttf", visibleSize.height*0.03);//speed score label
	speedlabel->setColor(Color3B::WHITE);
	speedlabel->setPosition(Vec2(speed->getPositionX(), heart->getBoundingBox().size.height + visibleSize.height*0.01 + heartlabel->getContentSize().height / 2));
	speedlabel->enableShadow();
	this->addChild(speedlabel, 1);
	speed_spr = Sprite::createWithSpriteFrameName("speed-sprite-2.png");
	speed_spr->setScale(visibleSize.width*0.1 / speed_spr->getContentSize().width);
	speed_spr->setPosition(Vec2(visibleSize.width / 2 - visibleSize.width*0.05 - heart_spr->getBoundingBox().size.width / 2 - speed_spr->getBoundingBox().size.width / 2, speed_spr->getBoundingBox().size.height / 2));
	speed_spr->setOpacity(0);
	this->addChild(speed_spr, 1);
	auto stormscoretemp = String::createWithFormat("%i", StormScore);
     stormlabel = Label::createWithTTF(stormscoretemp->getCString(), "fonts/Marker Felt.ttf", visibleSize.height*0.03);//storm score label
	stormlabel->setColor(Color3B::WHITE);
	stormlabel->setPosition(Vec2(storm->getPositionX(), heart->getBoundingBox().size.height + visibleSize.height*0.01 + heartlabel->getContentSize().height / 2));
	stormlabel->enableShadow();
	this->addChild(stormlabel, 1);
	storm_spr = Sprite::createWithSpriteFrameName("storm-sprite-2.png");
	storm_spr->setScale(visibleSize.width*0.1 / storm_spr->getContentSize().width);
	storm_spr->setPosition(Vec2(visibleSize.width / 2 + heart_spr->getBoundingBox().size.width / 2 + visibleSize.width*0.05 + storm_spr->getBoundingBox().size.width / 2, storm_spr->getBoundingBox().size.height / 2));
	storm_spr->setOpacity(0);
	this->addChild(storm_spr, 1);
	//End
	EndTable = Sprite::create("graphics/gameover-table.png");
	EndTable->setScale(visibleSize.width*0.7 / EndTable->getContentSize().width);
	EndTable->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - EndTable->getBoundingBox().size.height / 2));
	EndTable->setOpacity(0);
	this->addChild(EndTable, 4);
	Return_bt = ui::Button::create("graphics/try-again-button.png", "graphics/try-again-selected.png");
	Return_bt->setScale(EndTable->getBoundingBox().size.width/4 / Return_bt->getContentSize().width);
	Return_bt->setPosition(Vec2(visibleSize.width / 2 , EndTable->getPositionY()));
	Return_bt->setOpacity(0);
	Return_bt->setTouchEnabled(false);
	Return_bt->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			audio->playEffect("sounds/select.wav");
			auto ReplaceScene = GAME::createScene();
			Director::getInstance()->replaceScene(ReplaceScene);
			break;
		}
	});
	Return_bt->setTag(-3);
	this->addChild(Return_bt, 4);
	Share_bt = ui::Button::create("graphics/share-button.png", "graphics/share-button(selected).png");
	Share_bt->setScale(EndTable->getBoundingBox().size.width / 4 / Share_bt->getContentSize().width);
	Share_bt->setPosition(Vec2(visibleSize.width / 2, EndTable->getPositionY()-Share_bt->boundingBox().size.height*2.5));
	Share_bt->setOpacity(0);
	Share_bt->setTouchEnabled(false);
	Share_bt->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
												  audio->playEffect("sounds/select.wav");
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
												  if(isShowBigAd){
													  isShowBigAd = false;
													  PluginAdMob::show("gameover");}
													  else{
												  PluginFacebook::login(); 
												  sdkbox::PluginFacebook::requestReadPermissions({ FB_PERM_READ_PUBLIC_PROFILE, FB_PERM_READ_USER_FRIENDS });
												  sdkbox::PluginFacebook::requestPublishPermissions({ FB_PERM_PUBLISH_POST });
												  FBShareInfo info;
												  info.type = FB_LINK;
												  info.link = "https://play.google.com/store/apps/details?id=com.KNVN.Tornadoer";
												  info.title = "Tornader";
												  auto tempText = CCString::createWithFormat("Best Score :%i. Let's join the game with me!", HighScore);
												  info.text = tempText->getCString();
												  info.image = "http://i.imgur.com/NyaTudE.png";
												  PluginFacebook::dialog(info);
													  isShowBigAd = true;}
#endif
		}
			break;
		default:
			break;
		}
	});
	Share_bt->setTag(-3);
	this->addChild(Share_bt, 4);
	FaceIcon = Sprite::create("graphics/facebook-icon.png");
	FaceIcon->setScale(visibleSize.height*0.1 / FaceIcon->getContentSize().height);
	FaceIcon->setPosition(Vec2(visibleSize.width / 2, Share_bt->getPositionY() - Share_bt->getBoundingBox().size.height / 2 - FaceIcon->getBoundingBox().size.height / 2));
	FaceIcon->setOpacity(0);
	this->addChild(FaceIcon, 4);
	EndScoreLB = Label::createWithTTF(scoretemp->getCString(), "fonts/Marker Felt.ttf", visibleSize.height*0.1);
	EndScoreLB->setOpacity(0);
	this->addChild(EndScoreLB, 4);
	HighScoreLB = Label::createWithTTF(scoretemp->getCString(), "fonts/Marker Felt.ttf", visibleSize.height*0.1);
	HighScoreLB->setOpacity(0);
	this->addChild(HighScoreLB, 4);
	TextScoreLB = Label::createWithTTF(text->getCString(), "fonts/Marker Felt.ttf", visibleSize.height*0.05);
	TextScoreLB->setOpacity(0);
	TextScoreLB->setColor(Color3B::BLACK);
	TextScoreLB->enableItalics();
	TextScoreLB->enableGlow(Color4B::YELLOW);
	TextScoreLB->setOpacity(0);
	this->addChild(TextScoreLB, 4);
	//
	tor = Sprite::createWithSpriteFrameName("tornado begin-1.png");
	tor->setScale(visibleSize.height*0.35 / tor->getContentSize().height);
	tor->setPosition(Vec2(visibleSize.width*0.35, visibleSize.height / 2));
	tor->setTag(15);
	this->addChild(tor, 1);
	torheart = Sprite::createWithSpriteFrameName("tornado-heart-1.png");
	torheart->setScaleX(visibleSize.width*0.4 / tor->getContentSize().width);
	torheart->setScaleY(visibleSize.height*0.35 / tor->getContentSize().height);
	torheart->setPosition(Vec2(visibleSize.width*0.35, visibleSize.height / 2));
	torheart->setOpacity(0);
	this->addChild(torheart, 1);
	tor->setOpacity(0);  
	b2Vec2 gravity(0.0f, 0.0f);
	world = new b2World(gravity);
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(tor->getPositionX() / PTM_RATIO, tor->getPositionY() / PTM_RATIO);
	bodyDef.userData = tor;
	tor_body = world->CreateBody(&bodyDef);
	world->SetAllowSleeping(false);
	world->SetContactListener(this);
	CallFunc *begin_action = CallFunc::create([&] {
		tor->setOpacity(255);
		tor->runAction(Sequence::create(GAME::CreateAnimate("tornado begin-", 4, 0.5f, 1), CallFunc::create(CC_CALLBACK_0(GAME::SetTorNormalPosition, this)), CallFunc::create(CC_CALLBACK_0(GAME::NormalTorCall, this)),CallFunc::create(CC_CALLBACK_0(GAME::HideBanner, this)),CallFunc::create(CC_CALLBACK_0(GAME::MoveBackGroundBegin, this)), NULL));
		audio->playEffect("sounds/tornado begin.mp3", false);
	});
	this->runAction(Sequence::create(DelayTime::create(5.0), begin_action, NULL));//delay 5 seconds before first animation
	_house1 = new Vector<Sprite*>(numberSpritesMax);
	_house2 = new Vector<Sprite*>(numberSpritesMax);
	_house3 = new Vector<Sprite*>(numberSpritesMax);
	_tree = new Vector<Sprite*>(numberSpritesMax);
	_windfan = new Vector<Sprite*>(numberSpritesMax);
	_windfanAnims = new Vector<Sprite*>(numberSpritesMax);
	_wind = new Vector<Sprite*>(numberSpritesMax);
	_bomb = new Vector<Sprite*>(numberSpritesMax);
	_bombExplosion = new Vector<Sprite*>(numberSpritesMax);
		for (int i = 0; i < numberSpritesMax; ++i) {
			Sprite *house1 = Sprite::createWithSpriteFrameName("destroyed house-type 1-0.png");
			Sprite *house2 = Sprite::createWithSpriteFrameName("destroyed house-type 2-0.png");
			Sprite *house3 = Sprite::createWithSpriteFrameName("destroyed house-type 3-0.png");
			Sprite *tree = Sprite::createWithSpriteFrameName("tree-falling-sprite-0.png");
		Sprite *windfan = Sprite::create("graphics/wind-fan.png");
		Sprite *windfanAnims = Sprite::createWithSpriteFrameName("wind-fan-1.png");
		Sprite *wind = Sprite::create("graphics/wind.png");//
		Sprite *bomb = Sprite::createWithSpriteFrameName("bomb-1.png");
		Sprite *bombExplosion = Sprite::create("graphics/Canon&Bomb sprites/bomb-explosion.png");
		house1->setOpacity(0); 
		house2->setOpacity(0);
		house3->setOpacity(0);
		tree->setOpacity(0);
		windfan->setOpacity(0);
		windfanAnims->setOpacity(0);
		wind->setOpacity(0);
		bomb->setOpacity(0);
		bombExplosion->setOpacity(0);
		//
		house1->setTag(13); 
		house2->setTag(1);
		house3->setTag(2);
		tree->setTag(3);
		windfan->setTag(4);
		windfanAnims->setTag(5);
		wind->setTag(10);
		bombExplosion->setTag(11);//
		this->addChild(house1,0); 
		this->addChild(house2, 0);
		this->addChild(house3, 0);
		this->addChild(tree, 0);
		this->addChild(windfan, 0);
		this->addChild(windfanAnims, 0);
		this->addChild(wind, 3);
		this->addChild(bomb, 0);
		this->addChild(bombExplosion, 0);//
		_house1->pushBack(house1);
		_house2->pushBack(house2);
		_house3->pushBack(house3);
		_tree->pushBack(tree);
		_windfan->pushBack(windfan);
		_windfanAnims->pushBack(windfanAnims);
		_wind->pushBack(wind);
		_bomb->pushBack(bomb);
		_bombExplosion->pushBack(bombExplosion);
	}
	_heartItem = new Vector<Sprite*>(2);
	_stormyItem = new Vector<Sprite*>(2);
	_canon = new Vector<Sprite*>(2);
	for (int i = 0; i < 2; ++i)
	{
		Sprite *heartItem = Sprite::create("graphics/heart item.png");
		Sprite *stormyItem = Sprite::create("graphics/stormy item.png");
		Sprite *canon = Sprite::createWithSpriteFrameName("phao-sprite-1.png");
		heartItem->setOpacity(0);
		stormyItem->setOpacity(0);
		canon->setOpacity(0);
		heartItem->setTag(6);
		stormyItem->setTag(7);
		this->addChild(heartItem, 0);
		this->addChild(stormyItem, 0);
		this->addChild(canon, 3);
		_heartItem->pushBack(heartItem);
		_stormyItem->pushBack(stormyItem);
		_canon->pushBack(canon);
	}
	background2 = Sprite::create("graphics/Background.png");
	background2->setOpacity(0);
	this->addChild(background2, -2);
	background1 = Sprite::create("graphics/Background.png");
	background1->setOpacity(0);
	this->addChild(background1, -2);
	bridge_bg = Sprite::create("graphics/bridge-background.png");
	bridge_bg->setScaleX(visibleSize.width*1.1 / bridge_bg->getContentSize().width);
	bridge_bg->setScaleY(visibleSize.height / bridge_bg->getContentSize().height);
	bridge_bg->setOpacity(0);
	bridge_bg->setTag(8);
	this->addChild(bridge_bg, -1);
	bridge = Sprite::create("graphics/bridge.png");
	bridge->setOpacity(0);
	bridge->setTag(9);
	this->addChild(bridge, 0);
	Wall = Sprite::createWithSpriteFrameName("wall-sprite-1.png");
	Wall->setScale(visibleSize.height*0.68 / Wall->getContentSize().height);
	Wall->setOpacity(0);
    Wall->setTag(12);
	this->addChild(Wall, 2);
	b2BodyDef bodyBox1Def;
	bodyBox1Def.type = b2_staticBody;
	bodyBox1Def.position.Set(visibleSize.width/2/PTM_RATIO, visibleSize.height*0.94 / PTM_RATIO);
	bodyBox1Def.userData = begin_bg;
	auto TopBox = world->CreateBody(&bodyBox1Def);
	b2PolygonShape TopBoxShape;
	TopBoxShape.SetAsBox(visibleSize.width/2 / PTM_RATIO, visibleSize.height*0.06 / PTM_RATIO);
	b2FixtureDef FixtureTopBox;
	FixtureTopBox.shape = &TopBoxShape;
	TopBox->CreateFixture(&FixtureTopBox);
	//
	b2BodyDef bodyBox2Def;
	bodyBox2Def.type = b2_staticBody;
	bodyBox2Def.position.Set(visibleSize.width / 2 / PTM_RATIO, visibleSize.height*0.1 / PTM_RATIO);
	bodyBox2Def.userData = begin_bg;
	auto UnderBox = world->CreateBody(&bodyBox2Def);
	b2PolygonShape UnderBoxShape;
	UnderBoxShape.SetAsBox(visibleSize.width / 2 / PTM_RATIO, visibleSize.height*0.1 / PTM_RATIO);
	b2FixtureDef FixtureUnderBox;
	FixtureUnderBox.shape = &UnderBoxShape;
	UnderBox->CreateFixture(&FixtureUnderBox);
	this->scheduleUpdate();

	return true;
}
void GAME::SettingButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	st_table = Sprite::create("graphics/setting-table.png");
	st_table->setScaleX(st_button->getBoundingBox().size.width / st_table->getContentSize().width);
	st_table->setScaleY(visibleSize.height*0.4 / st_table->getContentSize().height);
	st_table->setPosition(Vec2(st_button->getPositionX(), visibleSize.height - st_table->getBoundingBox().size.height / 2));
	st_table->setOpacity(0);
	this->addChild(st_table, 2);
	
	sfx = ui::CheckBox::create("graphics/sound-button.png", "graphics/sound(mute).png");
	sfx->setScale(visibleSize.height*0.07 / sfx->getContentSize().height);
	sfx->setPosition(Vec2(st_button->getPositionX(), st_button->getPositionY() - st_button->getBoundingBox().size.height / 2 - visibleSize.height*0.02 - sfx->getBoundingBox().size.height / 2));
	sfx->setOpacity(0);
	sfx->setTouchEnabled(false);
	sfx->addEventListener([&](Ref* sender, ui::CheckBox::EventType type)
	{
		switch (type)
		{
		case ui::CheckBox::EventType::SELECTED:
			audio->setEffectsVolume(0.0f);
			break;
		case ui::CheckBox::EventType::UNSELECTED:
			audio->setEffectsVolume(0.5f);
			break;
		default:
			break;
		}
	});
	sfx->setTag(-3);
	this->addChild(sfx, 3);
	music_bt = ui::CheckBox::create("graphics/music.png", "graphics/music-mute.png");
	music_bt->setScale(visibleSize.height*0.07 / music_bt->getContentSize().height);
	music_bt->setPosition(Vec2(st_button->getPositionX(), sfx->getPositionY() - sfx->getBoundingBox().size.height / 2 - visibleSize.height*0.02 - music_bt->getBoundingBox().size.height / 2));
	music_bt->setOpacity(0);
	music_bt->setTouchEnabled(false);
	music_bt->addEventListener([&](Ref* sender, ui::CheckBox::EventType type)
	{
		switch (type)
		{
		case ui::CheckBox::EventType::SELECTED:
			audio->setBackgroundMusicVolume(0.0f);
			break;
		case ui::CheckBox::EventType::UNSELECTED:
			audio->setBackgroundMusicVolume(0.5f);
			break;
		default:
			break;
		}
	});
	music_bt->setTag(-3);
	this->addChild(music_bt, 3);
	exit_bt = ui::Button::create("graphics/exit-button.png");
	exit_bt->setScale(visibleSize.height*0.07 / exit_bt->getContentSize().height);
	exit_bt->setPosition(Vec2(st_button->getPositionX(), music_bt->getPositionY() - music_bt->getBoundingBox().size.height / 2 - visibleSize.height*0.02 - exit_bt->getBoundingBox().size.height / 2));
	exit_bt->setOpacity(0);
	exit_bt->setTouchEnabled(false);
	GAME::st_ExitGame();
	exit_bt->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
												  this->ShowBanner();
			audio->playEffect("sounds/select.wav");
			exit_table->setOpacity(255);
			yes->setOpacity(255);
			yes->setTouchEnabled(true);
			no->setOpacity(255);
			no->setTouchEnabled(true);
			pause_button->setTouchEnabled(false);
			pause_button->setSelected(false);
			paus_table->setOpacity(0);
			restart_bt->setOpacity(0);
			restart_bt->setTouchEnabled(false);
			continue_bt->setOpacity(0);
			continue_bt->setTouchEnabled(false);
			back_bt->setOpacity(0);
			back_bt->setTouchEnabled(false);
		}
			break;
		default:
			break;
		}
	});
	exit_bt->setTag(-3);
	this->addChild(exit_bt, 3);
}
void GAME::exit()
{
	audio->playEffect("sounds/select.wav");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
void GAME::st_ExitGame()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	exit_table = Sprite::create("graphics/exit-table.png");
	exit_table->setScaleX(visibleSize.width*0.8 / exit_table->getContentSize().width);
	exit_table->setScaleY(visibleSize.height*0.7 / exit_table->getContentSize().height);
	exit_table->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	exit_table->setOpacity(0);
	this->addChild(exit_table, 6);
	yes = ui::Button::create("graphics/yes-button(exit).png", "graphics/yes-button selected (exit).png");
	yes->setScale(exit_table->getBoundingBox().size.width / 2 * 0.7 / yes->getContentSize().width);
	yes->setPosition(Vec2(visibleSize.width / 2 - exit_table->getBoundingBox().size.width / 4, exit_table->getPositionY() - exit_table->getBoundingBox().size.height / 2 * 0.2));
	yes->setOpacity(0);
	yes->setTouchEnabled(false);
	yes->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			GAME::exit();
			break;
		default:
			break;
		}
	});
	yes->setTag(-3);
	this->addChild(yes, 7);
    no = ui::Button::create("graphics/no-button(exit).png", "graphics/no-button selected (exit).png");
	no->setScale(exit_table->getBoundingBox().size.width / 2 * 0.7 / no->getContentSize().width);
	no->setPosition(Vec2(visibleSize.width / 2 + exit_table->getBoundingBox().size.width / 4, exit_table->getPositionY() - exit_table->getBoundingBox().size.height / 2 * 0.2));
	no->setOpacity(0);
	no->setTouchEnabled(false);
	no->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
												  this->HideBanner();
			audio->playEffect("sounds/select.wav");
			exit_table->setOpacity(0);
			yes->setOpacity(0);
			yes->setTouchEnabled(false);
			no->setOpacity(0);
			no->setTouchEnabled(false);
			pause_button->setTouchEnabled(true);
		}
			break;
		default:
			break;
		}
	});
	no->setTag(-3);
	this->addChild(no, 7);
}
void GAME::PauseButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	paus_table = Sprite::create("graphics/pause-table.png");
	paus_table->setScaleX(visibleSize.width*0.6 / paus_table->getContentSize().width);
	paus_table->setScaleY(visibleSize.height*0.7 / paus_table->getContentSize().height);
	paus_table->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	paus_table->setOpacity(0);
	this->addChild(paus_table, 4);
	restart_bt = ui::Button::create("graphics/restart-button.png","graphics/restart-button(selected).png");
	restart_bt->setScaleX(paus_table->getBoundingBox().size.width*0.8 / restart_bt->getContentSize().width);
	restart_bt->setScaleY(paus_table->getBoundingBox().size.height*0.2 / restart_bt->getContentSize().height);
	restart_bt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	restart_bt->setOpacity(0);
	restart_bt->setTouchEnabled(false);
	restart_bt->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
			audio->playEffect("sounds/select.wav");
			auto ReplaceScene = GAME::createScene();
			Director::getInstance()->replaceScene(ReplaceScene);
		}
		break;
		default:
			break;
		}
	});
	restart_bt->setTag(-3);
	this->addChild(restart_bt, 5);
	continue_bt = ui::Button::create("graphics/continue-button.png", "graphics/continue-button(selected).png");
	continue_bt->setScaleX(paus_table->getBoundingBox().size.width*0.8 / continue_bt->getContentSize().width);
	continue_bt->setScaleY(paus_table->getBoundingBox().size.height*0.2 / continue_bt->getContentSize().height);
	continue_bt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + paus_table->getBoundingBox().size.height*0.3));
	continue_bt->setOpacity(0);
	continue_bt->setTouchEnabled(false);
	continue_bt->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
			audio->resumeAllEffects();
			audio->resumeBackgroundMusic();
			audio->playEffect("sounds/select.wav");
			paus_table->setOpacity(0);
			restart_bt->setOpacity(0);
			restart_bt->setTouchEnabled(false);
			continue_bt->setOpacity(0);
			continue_bt->setTouchEnabled(false);
			back_bt->setOpacity(0);
			back_bt->setTouchEnabled(false);
			pause_button->setSelected(false);
			this->resumeSchedulerAndActions();
			auto node = this->getChildren();
			for (int i = 0; i < node.size(); i++)
			{
				if (node.at(i)->getTag() == -3)
					continue;
				node.at(i)->resumeSchedulerAndActions();
			}
		}
		break;
		default:
			break;
		}
	});
	continue_bt->setTag(-3);
	this->addChild(continue_bt, 5);
	back_bt = ui::Button::create("graphics/back-button.png", "graphics/back-button(selected).png");
	back_bt->setScaleX(paus_table->getBoundingBox().size.width*0.8 / back_bt->getContentSize().width);
	back_bt->setScaleY(paus_table->getBoundingBox().size.height*0.2 / back_bt->getContentSize().height);
	back_bt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - paus_table->getBoundingBox().size.height*0.3));
	back_bt->setOpacity(0);
	back_bt->setTouchEnabled(false);
	back_bt->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
		{
			audio->playEffect("sounds/select.wav");
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			PluginAdMob::show("gameover");
#endif
			
			auto BackScene = MenuGame::createScene();
			Director::getInstance()->replaceScene(BackScene);
		}
		break;
		default:
			break;
		}
	});
	back_bt->setTag(-3);
	this->addChild(back_bt, 5);
}
Animate* GAME::CreateAnimate(std::string prefixName, int numberFrames, float delay, int FirstNumber)
{
	char number[40] = { 0 };
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numberFrames);

	for (int i = FirstNumber; i < numberFrames+FirstNumber; i++)
	{
		sprintf(number, "%d.png", i);
		std::string SpriteFrameName = prefixName + number;

		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName);
		animFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animFrames, delay);
	auto animate = Animate::create(animation);
	return animate;
}
void GAME::update(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	float timeStep = 1 / 20.0f;     
	int velocityIterations = 24;  
	int positionIterations = 12;  
	world->Step(timeStep, velocityIterations, positionIterations);
	if (isBeginTorUpdate==true)
	{
		if (TYPE == TornadoType::SPEED)
		{
			auto repeat = RepeatForever::create(GAME::CreateAnimate("tornado-normal-", 6, 0.125f, 1));
			repeat->setTag(3);
			tor->stopActionByTag(3);
			tor->runAction(repeat);
			this->CreateB2TorFittedBody(0.2f);
			audio->stopBackgroundMusic();
			audio->playBackgroundMusic("sounds/tornado(speed).mp3", true);
		}
		if (TYPE == TornadoType::NORMAL)
		{
			auto repeat = RepeatForever::create(GAME::CreateAnimate("tornado-normal-", 6, 0.25f, 1));
			if (tor->getActionByTag(3) != NULL){ tor->stopActionByTag(3); }
			repeat->setTag(3);
			tor->runAction(repeat);
			this->CreateB2TorFittedBody(0.2f);
			audio->stopBackgroundMusic();
			audio->playBackgroundMusic("sounds/tornado(normal).mp3", true);
		}
		if (TYPE == TornadoType::STORM)
		{
			auto repeat = RepeatForever::create(GAME::CreateAnimate("tornado-storm-", 6, 0.3f, 1));
			repeat->setTag(3);
			tor->stopActionByTag(3);
			tor->runAction(repeat);
			this->CreateB2TorFittedBody(0.2f);
			audio->stopBackgroundMusic();
			audio->playBackgroundMusic("sounds/tornado(storm).mp3", true);
		}
		tor->setOpacity(255);
		isBeginTorUpdate = false;
	}
	//
	power->setPercent(power->getPercent()+0.04);
	if (power->getPercent() >= 100)
	{
		if (SpeedScore < 1)
			SpeedScore++;
		power->setPercent(0);
	}

	//
	if (isUp){ tor->setPositionY(tor->getPositionY() + visibleSize.height*0.006); }
	if (isDown){ tor->setPositionY(tor->getPositionY() - visibleSize.height*0.006); }
	//
	if (CheckSpeedUpdate == true)
	{
			for (auto b = world->GetBodyList(); b; b = b->GetNext())
			{
				if (b->GetUserData() != NULL)
				{
					Sprite *sprite = (Sprite *)b->GetUserData();
					if (sprite->getTag() == 15||sprite->getTag() == -2){}
					else{
						b->SetLinearVelocity(b2Vec2(-visibleSize.width / 10 * SpeedVelocity / PTM_RATIO, 0));
					}
				}
			}
		CheckSpeedUpdate = false;
	}
	if (ClearWhenSpawnBridge == true)
	{
		SpawnObjectUpdate = false;
	}
	//
	if (SpawnObjectUpdate == true)
	{
		SpawnObjectUpdate = false;
		ObjectSpawnNumber = (rand() % 3) + 1;
		SpawnObjectTime = (CCRANDOM_0_1()*2) + 0.5;
		 
		 if (isSpawnBombUpdate == true)
		 {
			 if (SpawnScore >= 20)
			 {
				 if (SpawnScore <= (int)WallSpawnScore - 10){
					 isSpawnBombUpdate = false;
					 float SpawnBombTime = (CCRANDOM_0_1()*(4.0 - 0.5)) + 0.5;
					 this->scheduleOnce(SEL_SCHEDULE(&GAME::SpawnBomb), SpawnBombTime);
					 this->runAction(Sequence::create(DelayTime::create(SpawnBombTime), CallFunc::create([&]{isSpawnBombUpdate = true; }), NULL));
				 }
			 }
		 }//Spawn Bomb
		if (SpawnScore >= WallSpawnScore)
		{
			this->scheduleOnce(SEL_SCHEDULE(&GAME::SpawnWall), 1.0f);
			ObjectSpawnNumber = 1;
			SpawnObjectTime =(float)2.5f;
		}//Spawn Wall
		 if (ObjectSpawnNumber == 1)
		{
			this->scheduleOnce(SEL_SCHEDULE(&GAME::SpawnObject), SpawnObjectTime);//1
		}
		else if (ObjectSpawnNumber == 2)
		{
			this->runAction(Spawn::createWithTwoActions(CallFunc::create(CC_CALLBACK_0(GAME::ScheduleObject, this)), CallFunc::create(CC_CALLBACK_0(GAME::ScheduleObject, this))));//2
		}
		else{
			this->runAction(Spawn::create(CallFunc::create(CC_CALLBACK_0(GAME::ScheduleObject, this)), CallFunc::create(CC_CALLBACK_0(GAME::ScheduleObject, this)), CallFunc::create(CC_CALLBACK_0(GAME::ScheduleObject, this)), NULL));//3
		}
		this->runAction(Sequence::create(DelayTime::create(SpawnObjectTime), CallFunc::create([&]{SpawnObjectUpdate = true;}), NULL));
	}
	//
	if (isSpawnBridge == true)
	{
		isSpawnBridge = false;
		float SpawnTime = (CCRANDOM_0_1()*(100.0 - 32.0)) + 32.0;
		this->runAction(Sequence::create(DelayTime::create((float)SpawnTime-6.0), CallFunc::create([&]{ClearWhenSpawnBridge = true; }), NULL));
		this->runAction(Sequence::create(DelayTime::create(SpawnTime), CallFunc::create(CC_CALLBACK_0(GAME::BridgeSpawn, this)), CallFunc::create([&]{isSpawnBridge = true; }), NULL));
	}
	if (isSpawnWind == true)
	{
		isSpawnWind = false;
		float SpawnTime = (CCRANDOM_0_1()*(100.0 - 0.5)) + 0.5;
		this->runAction(Sequence::create(DelayTime::create(SpawnTime), CallFunc::create(CC_CALLBACK_0(GAME::SpawnWind, this)), CallFunc::create([&]{isSpawnWind = true; }), NULL));
	}
	//
	for (auto b = world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData()!= NULL)
		{
			Sprite *sprite = (Sprite *)b->GetUserData();
			if (sprite->getTag() == 16){}
			else if (sprite->getTag() == 15){ b->SetTransform(b2Vec2(tor->getPositionX() / PTM_RATIO, tor->getPositionY() / PTM_RATIO), 0); 
			}
			else{
				sprite->setPositionX(b->GetPosition().x *PTM_RATIO);
			}
			if (sprite->getTag() == 12)
			{
				if ((float)sprite->getPositionX() <= (float)visibleSize.width*0.36 && (float)sprite->getPositionX() >= visibleSize.width*0.33)
					{
						if (isWinScore == false){
							sprite->runAction(GAME::CreateAnimate("wall-sprite-", 7, 0.2f, 1));
							audio->playEffect("sounds/pushing door.mp3");
							score++;
							audio->playEffect("sounds/point.wav");
							isWinScore = true;
						}
					}
					else{ isWinScore = false; }
			}
		}
	}
	for (auto b = world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL)
		{
			
			Sprite *sprite = (Sprite *)b->GetUserData();
			if ((float)sprite->getPositionX() <= (float)-visibleSize.width)
			{
				world->DestroyBody(b);
				sprite->stopAllActions();
				sprite->setOpacity(0);
				break;
			}
		}
	}
	if (background2->getPositionX() <= visibleSize.width / 2 && background2->getPositionX() > visibleSize.width*0.45){
		if (isDestroyBg2body)
		{
			world->DestroyBody(Bg2Box);
			background2->setPositionX(visibleSize.width / 2);
			isDestroyBg2body = false;
		}
	}
	if (NeedtoDestroyWind)
	{
		world->DestroyBody(DestroyWindBody);
		NeedtoDestroyWind = false;
	}
	world->ClearForces();
	//
	auto scoretemp = String::createWithFormat("%i", score);
	label->setString(scoretemp->getCString());
	auto heartscoretemp = String::createWithFormat("%i", HeartScore);
	heartlabel->setString(heartscoretemp->getCString());
	auto stormscoretemp = String::createWithFormat("%i", StormScore);
	stormlabel->setString(stormscoretemp->getCString());
	auto speedscoretemp = String::createWithFormat("%i", SpeedScore);
	speedlabel->setString(speedscoretemp->getCString());
}
void GAME::CreateB2TorFittedBody(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.userData = tor;

	if (TYPE == TornadoType::NORMAL || TYPE == TornadoType::SPEED)
	{
		world->DestroyBody(tor_body);
		b2Vec2 vertices[3];
		vertices[0].Set(-tor->getBoundingBox().size.width*0.01 / PTM_RATIO, -visibleSize.height*0.04/PTM_RATIO);
		vertices[1].Set(tor->getBoundingBox().size.width*0.075/PTM_RATIO, -visibleSize.height*0.105 / PTM_RATIO);//0.065
		vertices[2].Set(tor->getBoundingBox().size.width*0.18 / PTM_RATIO, -visibleSize.height*0.04/PTM_RATIO);
		b2PolygonShape polygonShape;
		polygonShape.Set(vertices, 3);
		b2FixtureDef FixtureDef;
		FixtureDef.shape = &polygonShape;
		FixtureDef.filter.groupIndex = 1;
		bodyDef.position.Set(tor->getPositionX() / PTM_RATIO, tor->getPositionY() / PTM_RATIO);
		tor_body = world->CreateBody(&bodyDef);
		tor_fixture = tor_body->CreateFixture(&FixtureDef);
	}
	if (TYPE == TornadoType::STORM)
	{
		world->DestroyBody(tor_body);
		b2Vec2 vertices[3];
		vertices[0].Set(-tor->getBoundingBox().size.width*0.065/PTM_RATIO, -visibleSize.height*0.062/PTM_RATIO);
		vertices[1].Set(tor->getBoundingBox().size.width*0.05/PTM_RATIO, -visibleSize.height*0.12 / PTM_RATIO);//0.058
		vertices[2].Set(tor->getBoundingBox().size.width*0.15 / PTM_RATIO, -visibleSize.height*0.062 / PTM_RATIO);
		b2PolygonShape polygonShape;
		polygonShape.Set(vertices, 3);
		b2FixtureDef FixtureDef;
		FixtureDef.shape = &polygonShape;
		bodyDef.position.Set(tor->getPositionX() / PTM_RATIO, tor->getPositionY()-tor->getBoundingBox().size.height*0.25-visibleSize.height*0.029 / PTM_RATIO);
		tor_body = world->CreateBody(&bodyDef);
		tor_fixture = tor_body->CreateFixture(&FixtureDef);
	}

}
void GAME::NormalTorCall()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	tor->setOpacity(0);
	TYPE = TornadoType::NORMAL;
	isBeginTorUpdate = true;
}
void GAME::SetTorNormalPosition()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	if (TYPE == TornadoType::HEART)
	{
		torheart->setOpacity(0);
	}
	else{
		tor->setOpacity(0);
		tor->setPosition(Vec2(visibleSize.width*0.35, visibleSize.height / 2));
	}
}
void GAME::MoveBackGroundBegin()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	
	begin_bg->runAction(Sequence::create(MoveBy::create(4.0, Vec2(-visibleSize.width, 0)), CallFunc::create([&] { SpawnObjectUpdate = true; isSpawnWind = true; }),NULL));
}
void GAME::SpawnObject(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	 float ObjectPositionY = (CCRANDOM_0_1()*(0.9 - 0.45)) + 0.45;
	int ObjectType = rand() % 6;
	//Type  0.House1   1.House2  2.House3  3.Tree.  4.Wind-fan  5.Wind-fan animation
	if (ObjectType == 0)
	{
		Sprite *house1 = (Sprite*)_house1->at(At_House1Next);
		At_House1Next++;
		if (At_House1Next >= _house1->size())
			At_House1Next = 0;
		house1->stopAllActions();
		house1->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("destroyed house-type 1-0.png"));
		float Scale = (CCRANDOM_0_1()*(0.27 - 0.24)) + 0.24;
		house1->setScale(visibleSize.height*Scale / house1->getContentSize().height);
		house1->setPosition(Vec2(visibleSize.width*1.5, visibleSize.height*ObjectPositionY - house1->getBoundingBox().size.height*0.25));
		b2BodyDef bodyDef;
		bodyDef.type = b2_kinematicBody;
		bodyDef.position.Set(house1->getPositionX() / PTM_RATIO, (house1->getPositionY() - house1->getBoundingBox().size.height / 4) / PTM_RATIO);
		bodyDef.userData = house1;
		auto house1_body = world->CreateBody(&bodyDef);
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(house1->getBoundingBox().size.width / 2 / PTM_RATIO, house1->getBoundingBox().size.height*0.25 / PTM_RATIO);
		b2FixtureDef FixtureDef;
		FixtureDef.shape = &polygonShape;
		FixtureDef.filter.groupIndex = 2;
		house1_body->CreateFixture(&FixtureDef);
		house1->setOpacity(255);
		house1_body->SetLinearVelocity(b2Vec2(-visibleSize.width / 10*SpeedVelocity / PTM_RATIO, 0));
		SpawnScore++;
		ItemPoint++;
	}
	if (ObjectType == 1){
		Sprite * house2= (Sprite*)_house2->at(At_House2Next);
		At_House2Next++;
		if (At_House2Next >= _house2->size())
			At_House2Next = 0;
		house2->stopAllActions();
		house2->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("destroyed house-type 2-0.png"));
		float Scale = (CCRANDOM_0_1()*(0.25-0.22)) +0.22;
		house2->setScale(visibleSize.height*Scale / house2->getContentSize().height);
		house2->setPosition(Vec2(visibleSize.width*1.5, visibleSize.height*ObjectPositionY - house2->getBoundingBox().size.height*0.25));
		b2BodyDef bodyDef;
		bodyDef.type = b2_kinematicBody;
		bodyDef.position.Set(house2->getPositionX() / PTM_RATIO, (house2->getPositionY() - house2->getBoundingBox().size.height / 4)/PTM_RATIO);
		bodyDef.userData = house2;
		auto house2_body = world->CreateBody(&bodyDef);
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(house2->getBoundingBox().size.width / 2 / PTM_RATIO, house2->getBoundingBox().size.height*0.25 / PTM_RATIO);
		b2FixtureDef FixtureDef;
		FixtureDef.shape = &polygonShape;
		FixtureDef.filter.groupIndex = 1;
		house2_body->CreateFixture(&FixtureDef);
		house2->setOpacity(255);
		house2_body->SetLinearVelocity(b2Vec2(-visibleSize.width / 10 * SpeedVelocity / PTM_RATIO, 0));
		SpawnScore++;
		ItemPoint++;
	}
	if (ObjectType == 2){
		Sprite *house3 = (Sprite*)_house3->at(At_House3Next);
		At_House3Next++;
		if (At_House3Next >= _house3->size())
			At_House3Next = 0;
		house3->stopAllActions();
		house3->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("destroyed house-type 3-0.png"));
		float Scale = (CCRANDOM_0_1()*(0.33-0.30)) + 0.30;
		house3->setScale(visibleSize.height*Scale / house3->getContentSize().height);
		house3->setPosition(Vec2(visibleSize.width*1.5, visibleSize.height*ObjectPositionY - house3->getBoundingBox().size.height*0.25));
		b2BodyDef bodyDef;
		bodyDef.type = b2_kinematicBody;
		bodyDef.position.Set(house3->getPositionX() / PTM_RATIO, (house3->getPositionY()-house3->getBoundingBox().size.height/4) / PTM_RATIO);
		bodyDef.userData = house3;
		auto house3_body = world->CreateBody(&bodyDef);
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(house3->getBoundingBox().size.width / 2 / PTM_RATIO, house3->getBoundingBox().size.height/4 / PTM_RATIO);
		b2FixtureDef FixtureDef;
		FixtureDef.shape = &polygonShape;
		FixtureDef.filter.groupIndex = 3;
		house3_body->CreateFixture(&FixtureDef);
		house3->setOpacity(255);
		house3_body->SetLinearVelocity(b2Vec2(-visibleSize.width / 10 * SpeedVelocity / PTM_RATIO, 0));
		SpawnScore++;
		ItemPoint++;
	}
	if (ObjectType == 3){
		Sprite *tree= (Sprite*)_tree->at(At_treeNext);
		At_treeNext++;
		if (At_treeNext >= _tree->size())
			At_treeNext = 0;
		tree->stopAllActions();
		tree->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tree-falling-sprite-0.png"));
		float Scale = (CCRANDOM_0_1()*(0.15-0.1)) + 0.1;
		tree->setScale(visibleSize.height*Scale / tree->getContentSize().height);
		tree->setPosition(Vec2(visibleSize.width*1.5, visibleSize.height*ObjectPositionY - tree->getBoundingBox().size.height*0.25));
		b2BodyDef bodyDef;
		bodyDef.type = b2_kinematicBody;
		bodyDef.position.Set(tree->getPositionX() / PTM_RATIO, tree->getPositionY() / PTM_RATIO);
		bodyDef.userData = tree;
		auto tree_body = world->CreateBody(&bodyDef);
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(tree->getBoundingBox().size.width / 2 / PTM_RATIO, tree->getBoundingBox().size.height/ 2 / PTM_RATIO);
		b2FixtureDef FixtureDef;
		FixtureDef.shape = &polygonShape;
		FixtureDef.filter.groupIndex = 0;
		tree_body->CreateFixture(&FixtureDef);
		tree->setOpacity(255);
		tree_body->SetLinearVelocity(b2Vec2(-visibleSize.width / 10 * SpeedVelocity / PTM_RATIO, 0));
		SpawnScore++;
		ItemPoint++;
	}
	if (ObjectType == 4){
		Sprite *windfan = (Sprite*)_windfan->at(At_WindfanNext);
		At_WindfanNext++;
		if (At_WindfanNext >= _windfan->size())
			At_WindfanNext = 0;
		windfan->stopAllActions();
		float Scale = (CCRANDOM_0_1()*(0.25-0.2)) + 0.2;
		windfan->setScale(visibleSize.height*Scale / windfan->getContentSize().height);
		windfan->setPosition(Vec2(visibleSize.width*1.5, visibleSize.height*ObjectPositionY - windfan->getBoundingBox().size.height*0.25));
		b2BodyDef bodyDef;
		bodyDef.type = b2_kinematicBody;
		bodyDef.position.Set(windfan->getPositionX() / PTM_RATIO, windfan->getPositionY() / PTM_RATIO);
		bodyDef.userData = windfan;
		auto windfan_body = world->CreateBody(&bodyDef);
		b2CircleShape circleShape;
		circleShape.m_radius = (windfan->getBoundingBox().size.height/4)/PTM_RATIO;
		b2FixtureDef FixtureDef;
		FixtureDef.shape = &circleShape;
		windfan_body->CreateFixture(&FixtureDef);
		windfan->setOpacity(255);
		windfan_body->SetLinearVelocity(b2Vec2(-visibleSize.width / 10 * SpeedVelocity / PTM_RATIO, 0));
		SpawnScore++;
		ItemPoint++;
	}
	if (ObjectType == 5)
	{
		Sprite *windfan = (Sprite*)_windfan->at(At_WindfanNext);
		At_WindfanNext++;
		if (At_WindfanNext >= _windfan->size())
			At_WindfanNext = 0;
		windfan->stopAllActions();
		float Scale = (CCRANDOM_0_1()*(0.25 - 0.2)) + 0.2;
		windfan->setScale(visibleSize.height*Scale / windfan->getContentSize().height);
		windfan->setPosition(Vec2(visibleSize.width*1.5, visibleSize.height*ObjectPositionY - windfan->getBoundingBox().size.height*0.25));
		b2BodyDef bodyDef;
		bodyDef.type = b2_kinematicBody;
		bodyDef.position.Set(windfan->getPositionX() / PTM_RATIO, windfan->getPositionY() / PTM_RATIO);
		bodyDef.userData = windfan;
		auto windfan_body = world->CreateBody(&bodyDef);
		b2CircleShape circleShape;
		circleShape.m_radius = (windfan->getBoundingBox().size.height / 4) / PTM_RATIO;
		b2FixtureDef FixtureDef;
		FixtureDef.shape = &circleShape;
		windfan_body->CreateFixture(&FixtureDef);
		windfan->setOpacity(255);
		windfan_body->SetLinearVelocity(b2Vec2(-visibleSize.width / 10 * SpeedVelocity / PTM_RATIO, 0));
		windfan->runAction(Sequence::create(DelayTime::create(3.0),CallFunc::create(CC_CALLBACK_0(GAME::WindfanAnims,this,windfan)), NULL));
		SpawnScore++;
		ItemPoint++;
	}
	int ItemScoreSpawn = (rand() % (20 - 10)) + 10;
	if (ItemPoint > ItemScoreSpawn)
	{
		ItemPoint = 0;
		int ItemType = rand() % 2 + 1;//1.Heart(Tag 6) 2.Storm(Tag 7)
		float ItemPositionY = (CCRANDOM_0_1()*(0.9 - 0.45)) + 0.45;
		if (ItemType == 1)
		{
			Sprite *heartItem = (Sprite*)_heartItem->at(At_heartItemNext);
			At_heartItemNext++;
			if (At_heartItemNext >= _heartItem->size())
				At_heartItemNext = 0;
			heartItem->stopAllActions();
			float ItemScale = (CCRANDOM_0_1()*(0.15 - 0.1)) + 0.1;
			heartItem->setScale(visibleSize.height*ItemScale / heartItem->getContentSize().height);
			heartItem->setPosition(Vec2(visibleSize.width*1.5, visibleSize.height*ItemPositionY - heartItem->getBoundingBox().size.height*0.25));
			b2BodyDef bodyDef;
			bodyDef.type = b2_kinematicBody;
			bodyDef.position.Set(heartItem->getPositionX() / PTM_RATIO, heartItem->getPositionY() / PTM_RATIO);
			bodyDef.userData = heartItem;
			auto heartItem_body = world->CreateBody(&bodyDef);
			b2PolygonShape polygonShape;
			polygonShape.SetAsBox(heartItem->getBoundingBox().size.width / 2 / PTM_RATIO, heartItem->getBoundingBox().size.height*0.5 / PTM_RATIO);
			b2FixtureDef FixtureDef;
			FixtureDef.shape = &polygonShape;
			heartItem_body->CreateFixture(&FixtureDef);
			heartItem->setOpacity(255);
			heartItem_body->SetLinearVelocity(b2Vec2(-visibleSize.width / 10 * SpeedVelocity / PTM_RATIO, 0));
			SpawnScore++;
		}
		else
		{
			Sprite *stormyItem = (Sprite*)_stormyItem->at(At_stormyItemNext);
			At_stormyItemNext++;
			if (At_stormyItemNext >= _stormyItem->size())
				At_stormyItemNext = 0;
			stormyItem->stopAllActions();
			float ItemScale = (CCRANDOM_0_1()*(0.15 - 0.1)) + 0.1;
			stormyItem->setScale(visibleSize.height*ItemScale / stormyItem->getContentSize().height);
			stormyItem->setPosition(Vec2(visibleSize.width*1.5, visibleSize.height*ItemPositionY - stormyItem->getBoundingBox().size.height*0.25));
			b2BodyDef bodyDef;
			bodyDef.type = b2_kinematicBody;
			bodyDef.position.Set(stormyItem->getPositionX() / PTM_RATIO, stormyItem->getPositionY() / PTM_RATIO);
			bodyDef.userData = stormyItem;
			auto stormyItem_body = world->CreateBody(&bodyDef);
			b2PolygonShape polygonShape;
			polygonShape.SetAsBox(stormyItem->getBoundingBox().size.width / 2 / PTM_RATIO, stormyItem->getBoundingBox().size.height*0.5 / PTM_RATIO);
			b2FixtureDef FixtureDef;
			FixtureDef.shape = &polygonShape;
			stormyItem_body->CreateFixture(&FixtureDef);
			stormyItem->setOpacity(255);
			stormyItem_body->SetLinearVelocity(b2Vec2(-visibleSize.width / 10 * SpeedVelocity / PTM_RATIO, 0));
		}
	}
}
void GAME::ScheduleObject()
{
	this->scheduleOnce(SEL_SCHEDULE(&GAME::SpawnObject), SpawnObjectTime);
}
void GAME::WindfanAnims(Node* sender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto windfan = (Sprite*)sender;
	windfan->setOpacity(0);
	Sprite *windfanAnims = (Sprite*)_windfanAnims->at(At_WindfanAnimsNext);
	At_WindfanAnimsNext++;
	if (At_WindfanAnimsNext >= _windfanAnims->size())
		At_WindfanAnimsNext = 0;
	windfanAnims->stopAllActions();
	float Scale = (CCRANDOM_0_1()*(0.25 - 0.16)) + 0.16;
	windfanAnims->setScale(visibleSize.height*Scale / windfanAnims->getContentSize().height);
	windfanAnims->setPosition(Vec2(windfan->getPositionX(), windfan->getPositionY()));
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(windfanAnims->getPositionX() / PTM_RATIO, windfanAnims->getPositionY() / PTM_RATIO);
	bodyDef.userData = windfanAnims;
	auto windfanAnims_body = world->CreateBody(&bodyDef);
	b2Vec2 vertices[5];
	vertices[0].Set(-windfanAnims->getBoundingBox().size.width*0.4/ PTM_RATIO, -windfanAnims->getBoundingBox().size.height*0.03 / PTM_RATIO);
	vertices[4].Set(-windfanAnims->getBoundingBox().size.width*0.18 / PTM_RATIO, windfanAnims->getBoundingBox().size.height*0.2 / PTM_RATIO);
	vertices[3].Set(windfanAnims->getBoundingBox().size.width*0.24 / PTM_RATIO, windfanAnims->getBoundingBox().size.height*0.2 / PTM_RATIO);
	vertices[2].Set(windfanAnims->getBoundingBox().size.width*0.6 / PTM_RATIO, windfanAnims->getBoundingBox().size.height*0.145 / PTM_RATIO);
	vertices[1].Set(windfanAnims->getBoundingBox().size.width*0.12/PTM_RATIO, -windfanAnims->getBoundingBox().size.height*0.4 / PTM_RATIO);
	b2PolygonShape polygonShape;
	polygonShape.Set(vertices, 5);
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &polygonShape;
	windfanAnims_body->CreateFixture(&FixtureDef);
	windfanAnims->setOpacity(255);
	windfanAnims->runAction(RepeatForever::create(GAME::CreateAnimate("wind-fan-", 5, 0.2f, 1)));
	windfanAnims_body->SetLinearVelocity(b2Vec2(-visibleSize.width / 10 * SpeedVelocity / PTM_RATIO, 0));
}
void GAME::BridgeSpawn()
{
	this->schedule(SEL_SCHEDULE(&GAME::CreateB2TorFittedBody),0.1f);
	isBeginBodyUpdate = true;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	background1->stopAllActions();
	background1->setScaleX(visibleSize.width / background1->getContentSize().width);
	background1->setScaleY(visibleSize.height / background1->getContentSize().height);
	background1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 ));
	b2BodyDef bodyBg1Def;
	bodyBg1Def.type = b2_kinematicBody;
	bodyBg1Def.position.Set(background1->getPositionX()/ PTM_RATIO, visibleSize.height*0.94 / PTM_RATIO);
	bodyBg1Def.userData = background1;
	BgBox = world->CreateBody(&bodyBg1Def);
	b2PolygonShape TopBoxShape;
	TopBoxShape.SetAsBox(visibleSize.width / 2 / PTM_RATIO, visibleSize.height*0.06 / PTM_RATIO);
	b2FixtureDef FixtureTopBox;
	FixtureTopBox.shape = &TopBoxShape;
	BgBox->CreateFixture(&FixtureTopBox);
	background1->setOpacity(255);
	//
	bridge_bg->setPosition(Vec2(visibleSize.width*1.5, visibleSize.height / 2));
	b2BodyDef bodyBridBgDef;
	bodyBridBgDef.type = b2_kinematicBody;
	bodyBridBgDef.position.Set(bridge_bg->getPositionX() / PTM_RATIO, visibleSize.height*0.54 / PTM_RATIO);
	bodyBridBgDef.userData = bridge_bg;
	auto bridge_bg_body = world->CreateBody(&bodyBridBgDef);
	bridge_bg->setOpacity(255);
	b2PolygonShape BridBgShape;
	BridBgShape.SetAsBox(visibleSize.width*0.3 / PTM_RATIO, visibleSize.height*0.32 / PTM_RATIO);
	b2FixtureDef FixtureBridBg;
	FixtureBridBg.shape = &BridBgShape;
	bridge_bg_body->CreateFixture(&FixtureBridBg);
	//
	float ObjectPositionY = (CCRANDOM_0_1()*(0.6 - 0.45)) + 0.45;

	bridge->setScale(visibleSize.width*0.61 / bridge->getContentSize().width);
	bridge->setPosition(Vec2(visibleSize.width*1.5, visibleSize.height*ObjectPositionY));
	b2Body* bridge_body[7];
	for (int i = 0; i <= 6; i++)
	{
		b2BodyDef bodyBridDef;
		bodyBridDef.type = b2_kinematicBody;
		bodyBridDef.position.Set(bridge->getPositionX() / PTM_RATIO, bridge->getPositionY() / PTM_RATIO);
		bodyBridDef.userData = bridge;
		bridge_body[i] = world->CreateBody(&bodyBridDef);
		b2Vec2 vertices[4];
		switch (i)
		{
		case 0:
			vertices[0].Set(-bridge->getBoundingBox().size.width*0.5 / PTM_RATIO, -bridge->getBoundingBox().size.height*0.23 / PTM_RATIO);
			vertices[1].Set(-bridge->getBoundingBox().size.width*0.405 / PTM_RATIO, -bridge->getBoundingBox().size.height*0.32 / PTM_RATIO);
			vertices[2].Set(-bridge->getBoundingBox().size.width*0.405 / PTM_RATIO, bridge->getBoundingBox().size.height*0.14 / PTM_RATIO);
			vertices[3].Set(-bridge->getBoundingBox().size.width*0.5 / PTM_RATIO, bridge->getBoundingBox().size.height*0.234 / PTM_RATIO);
			break;
		case 1:
			vertices[0].Set(-bridge->getBoundingBox().size.width*0.405 / PTM_RATIO, -bridge->getBoundingBox().size.height*0.32 / PTM_RATIO);
			vertices[1].Set(-bridge->getBoundingBox().size.width*0.234 / PTM_RATIO, -bridge->getBoundingBox().size.height*0.12 / PTM_RATIO);
			vertices[2].Set(-bridge->getBoundingBox().size.width*0.234 / PTM_RATIO, bridge->getBoundingBox().size.height*0.34 / PTM_RATIO);
			vertices[3].Set(-bridge->getBoundingBox().size.width*0.405 / PTM_RATIO, bridge->getBoundingBox().size.height*0.14 / PTM_RATIO);
			break;
		case 2:
			vertices[0].Set(-bridge->getBoundingBox().size.width*0.234 / PTM_RATIO, -bridge->getBoundingBox().size.height*0.12 / PTM_RATIO);
			vertices[1].Set(-bridge->getBoundingBox().size.width*0.1022 / PTM_RATIO, -bridge->getBoundingBox().size.height*0.29 / PTM_RATIO);
			vertices[2].Set(-bridge->getBoundingBox().size.width*0.1022 / PTM_RATIO, bridge->getBoundingBox().size.height*0.174 / PTM_RATIO);
			vertices[3].Set(-bridge->getBoundingBox().size.width*0.234 / PTM_RATIO, bridge->getBoundingBox().size.height*0.34 / PTM_RATIO);
			break;
		case 3:
			vertices[0].Set(-bridge->getBoundingBox().size.width*0.1022 / PTM_RATIO, -bridge->getBoundingBox().size.height*0.29 / PTM_RATIO);
			vertices[1].Set(bridge->getBoundingBox().size.width*0.1 / PTM_RATIO, bridge->getBoundingBox().size.height*0.03 / PTM_RATIO);
			vertices[2].Set(bridge->getBoundingBox().size.width*0.1 / PTM_RATIO, bridge->getBoundingBox().size.height*0.5 / PTM_RATIO);
			vertices[3].Set(-bridge->getBoundingBox().size.width*0.1022 / PTM_RATIO, bridge->getBoundingBox().size.height*0.174 / PTM_RATIO);
			break;
		case 4:
			vertices[0].Set(bridge->getBoundingBox().size.width*0.1 / PTM_RATIO, bridge->getBoundingBox().size.height*0.03 / PTM_RATIO);
			vertices[1].Set(bridge->getBoundingBox().size.width*0.253 / PTM_RATIO, -bridge->getBoundingBox().size.height*0.43 / PTM_RATIO);
			vertices[2].Set(bridge->getBoundingBox().size.width*0.253 / PTM_RATIO, bridge->getBoundingBox().size.height*0.034 / PTM_RATIO);
			vertices[3].Set(bridge->getBoundingBox().size.width*0.1 / PTM_RATIO, bridge->getBoundingBox().size.height*0.5 / PTM_RATIO);
			break;
		case 5:
			vertices[0].Set(bridge->getBoundingBox().size.width*0.253 / PTM_RATIO, -bridge->getBoundingBox().size.height*0.43 / PTM_RATIO);
			vertices[1].Set(bridge->getBoundingBox().size.width*0.36 / PTM_RATIO, -bridge->getBoundingBox().size.height*0.275 / PTM_RATIO);
			vertices[2].Set(bridge->getBoundingBox().size.width*0.36 / PTM_RATIO, bridge->getBoundingBox().size.height*0.1894 / PTM_RATIO);
			vertices[3].Set(bridge->getBoundingBox().size.width*0.253 / PTM_RATIO, bridge->getBoundingBox().size.height*0.034 / PTM_RATIO);
			break;
		case 6:
			vertices[0].Set(bridge->getBoundingBox().size.width*0.36 / PTM_RATIO, -bridge->getBoundingBox().size.height*0.275 / PTM_RATIO);
			vertices[1].Set(bridge->getBoundingBox().size.width*0.5 / PTM_RATIO, -bridge->getBoundingBox().size.height*0.41 / PTM_RATIO);
			vertices[2].Set(bridge->getBoundingBox().size.width*0.5 / PTM_RATIO, bridge->getBoundingBox().size.height*0.03 / PTM_RATIO);
			vertices[3].Set(bridge->getBoundingBox().size.width*0.36 / PTM_RATIO, bridge->getBoundingBox().size.height*0.1894 / PTM_RATIO);
			break;

		default:
			break;
		}
		b2PolygonShape BridgeShape;
		BridgeShape.Set(vertices, 4);
		b2FixtureDef FixtureBridgeDef;
		FixtureBridgeDef.shape = &BridgeShape;
		bridge_body[i]->CreateFixture(&FixtureBridgeDef);
	}
	bridge->setOpacity(255);
	background2->stopAllActions();
	background2->setScaleX(visibleSize.width / background2->getContentSize().width);
	background2->setScaleY(visibleSize.height / background2->getContentSize().height);
	background2->setPosition(Vec2(visibleSize.width*2.5, visibleSize.height / 2));
	b2BodyDef bodyBg2Def;
	bodyBg2Def.type = b2_kinematicBody;
	bodyBg2Def.position.Set(visibleSize.width*2.5 / PTM_RATIO, visibleSize.height*0.94 / PTM_RATIO);
	bodyBg2Def.userData = background2;
	Bg2Box = world->CreateBody(&bodyBg2Def);
	b2PolygonShape TopBox2Shape;
	TopBox2Shape.SetAsBox(visibleSize.width / 2 / PTM_RATIO, visibleSize.height*0.06 / PTM_RATIO);
	b2FixtureDef FixtureTopBox2;
	FixtureTopBox2.shape = &TopBox2Shape;
	Bg2Box->CreateFixture(&FixtureTopBox2);
	isDestroyBg2body = true;
	background2->setOpacity(255);
	//
	BgBox->SetLinearVelocity(b2Vec2(-visibleSize.width / 10 * SpeedVelocity / PTM_RATIO, 0));
	bridge_bg_body->SetLinearVelocity(b2Vec2(-visibleSize.width / 10 * SpeedVelocity / PTM_RATIO, 0));
	Bg2Box->SetLinearVelocity(b2Vec2(-visibleSize.width / 10 * SpeedVelocity / PTM_RATIO, 0));
	for (int i = 0; i <= 6; i++)
	{
		bridge_body[i]->SetLinearVelocity(b2Vec2(-visibleSize.width / 10 * SpeedVelocity / PTM_RATIO, 0));
	}
	background2->runAction(Sequence::create(DelayTime::create(8.0), CallFunc::create([&]{ClearWhenSpawnBridge = false; SpawnObjectUpdate = true; this->unschedule(SEL_SCHEDULE(&GAME::CreateB2TorFittedBody)); isBeginBodyUpdate = false; }), NULL));
	//
}
void GAME::SpawnWind()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Sprite *wind = (Sprite*)_wind->at(At_windNext);
	At_windNext++;
	if (At_windNext >= _wind->size())
		At_windNext = 0;
	wind->stopAllActions();
	float Scale = (CCRANDOM_0_1()*(0.45 - 0.2)) + 0.2;
	float PositionY = (CCRANDOM_0_1()*(0.9 - 0.45)) + 0.45;
	wind->setScale(visibleSize.height*Scale / wind->getContentSize().height);
	wind->setPosition(Vec2(visibleSize.width *1.5 - wind->getBoundingBox().size.width / 2, visibleSize.height*PositionY - wind->getBoundingBox().size.height*0.75));
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(wind->getPositionX() / PTM_RATIO, wind->getPositionY() / PTM_RATIO);
	bodyDef.userData = wind;
	auto wind_body = world->CreateBody(&bodyDef);
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(wind->getBoundingBox().size.width / 2 / PTM_RATIO, wind->getBoundingBox().size.height*0.5 / PTM_RATIO);
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &polygonShape;
	wind_body->CreateFixture(&FixtureDef);
	wind->setOpacity(255);
	wind_body->SetLinearVelocity(b2Vec2(-visibleSize.width/7 *SpeedVelocity / PTM_RATIO, 0));
	audio->playEffect("sounds/wind.mp3");
}
void GAME::SpawnWall(float dt)
{
	SpawnScore = 0;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Wall->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("wall-sprite-1.png"));
	Wall->setPosition(Vec2(visibleSize.width*1.5, visibleSize.height*0.56));
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(Wall->getPositionX() / PTM_RATIO, (Wall->getPositionY() + Wall->getBoundingBox().size.height*0.2465) / PTM_RATIO);
	bodyDef.userData = Wall;
	auto Wall1_body = world->CreateBody(&bodyDef);
	b2BodyDef body2Def;
	body2Def.type = b2_kinematicBody;
	body2Def.position.Set(Wall->getPositionX() / PTM_RATIO, (Wall->getPositionY() - Wall->getBoundingBox().size.height*0.35) / PTM_RATIO);
	body2Def.userData = Wall;
	auto Wall2_body = world->CreateBody(&body2Def);
	b2PolygonShape Wall1Shape;
	Wall1Shape.SetAsBox(Wall->getBoundingBox().size.width*0.5 / PTM_RATIO, Wall->getBoundingBox().size.height*0.2535 / PTM_RATIO);
	b2PolygonShape Wall2Shape;
	Wall2Shape.SetAsBox(Wall->getBoundingBox().size.width*0.5 / PTM_RATIO, Wall->getBoundingBox().size.height*0.15 / PTM_RATIO);
	b2FixtureDef FixtureWall1Def;
	FixtureWall1Def.shape = &Wall1Shape;
	Wall1_body->CreateFixture(&FixtureWall1Def);
	b2FixtureDef FixtureWall2Def;
	FixtureWall2Def.shape = &Wall2Shape;
	Wall2_body->CreateFixture(&FixtureWall2Def);
	Wall->setOpacity(255);
	//
	//
	Sprite* canon1 = (Sprite*)_canon->at(0);
	canon1->stopAllActions();
	Sprite* canon2 = (Sprite*)_canon->at(1);
	canon2->stopAllActions();
	canon1->setScale(visibleSize.height*0.12 / canon1->getContentSize().height);
	canon2->setScale(visibleSize.height*0.12 / canon2->getContentSize().height);
	canon1->setPosition(Vec2(visibleSize.width*1.5-canon1->getBoundingBox().size.width*0.25, visibleSize.height*0.9 - canon1->getBoundingBox().size.height*0.75));
	b2BodyDef bodyCan1Def;
	bodyCan1Def.type = b2_kinematicBody;
	bodyCan1Def.position.Set(canon1->getPositionX() / PTM_RATIO, canon1->getPositionY() / PTM_RATIO);
	bodyCan1Def.userData = canon1;
	auto can1_body = world->CreateBody(&bodyCan1Def);
	b2CircleShape circle1Shape;
	circle1Shape.m_radius = (canon1->getBoundingBox().size.height / 4) / PTM_RATIO;
	b2FixtureDef Fixture1Def;
	Fixture1Def.shape = &circle1Shape;
	can1_body->CreateFixture(&Fixture1Def);
	canon1->setOpacity(255);//
	canon2->setPosition(Vec2(visibleSize.width*1.5-canon2->getBoundingBox().size.width/4, Wall->getPositionY()-Wall->getBoundingBox().size.height/2 + canon2->getBoundingBox().size.height*2.5));
	b2BodyDef bodyCan2Def;
	bodyCan2Def.type = b2_kinematicBody;
	bodyCan2Def.position.Set(canon2->getPositionX() / PTM_RATIO, canon2->getPositionY() / PTM_RATIO);
	bodyCan2Def.userData = canon2;
	auto can2_body = world->CreateBody(&bodyCan2Def);
	b2CircleShape circle2Shape;
	circle2Shape.m_radius = (canon2->getBoundingBox().size.height / 4) / PTM_RATIO;
	b2FixtureDef Fixture2Def;
	Fixture2Def.shape = &circle2Shape;
	can2_body->CreateFixture(&Fixture2Def);
	canon2->setOpacity(255);//

	canon1->runAction(RepeatForever::create(GAME::CreateAnimate("phao-sprite-", 3, 0.5f, 1)));
	canon2->runAction(RepeatForever::create(GAME::CreateAnimate("phao-sprite-", 3, 0.5f, 1)));
	can = audio->playEffect("sounds/canon.mp3", true);
	this->runAction(Sequence::create(DelayTime::create(8.0), CallFunc::create([&]{audio->stopEffect(can); }), NULL));
	can1_body->SetLinearVelocity(b2Vec2(-visibleSize.width / 10 * SpeedVelocity / PTM_RATIO, 0));
	can2_body->SetLinearVelocity(b2Vec2(-visibleSize.width / 10 * SpeedVelocity / PTM_RATIO, 0));
	Wall1_body->SetLinearVelocity(b2Vec2(-visibleSize.width / 10 * SpeedVelocity / PTM_RATIO, 0));
	Wall2_body->SetLinearVelocity(b2Vec2(-visibleSize.width / 10 * SpeedVelocity / PTM_RATIO, 0));
	WallSpawnScore = (rand() % (40 - 30)) + 30;
}
void GAME::SpawnBomb(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Sprite *bomb = (Sprite*)_bomb->at(At_BombNext);
	At_BombNext++;
	if (At_BombNext >= _bomb->size())
		At_BombNext = 0;
	bomb->stopAllActions();
	float Scale = (CCRANDOM_0_1()*(0.12 - 0.08)) + 0.08;
	float PositionY = (CCRANDOM_0_1()*(0.9 - 0.45)) + 0.45;
	bomb->setScale(visibleSize.height*Scale / bomb->getContentSize().height);
	bomb->setPosition(Vec2(visibleSize.width*1.5, visibleSize.height*PositionY-bomb->getBoundingBox().size.height*0.25));
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(bomb->getPositionX() / PTM_RATIO, bomb->getPositionY() / PTM_RATIO);
	bodyDef.userData = bomb;
	auto bomb_body = world->CreateBody(&bodyDef);
	b2CircleShape circleShape;
	circleShape.m_radius = (bomb->getBoundingBox().size.height / 2) / PTM_RATIO;
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &circleShape;
	bomb_body->CreateFixture(&FixtureDef);
	bomb->setOpacity(255);
	bomb_body->SetLinearVelocity(b2Vec2(-visibleSize.width / 10 * SpeedVelocity / PTM_RATIO, 0));
	bomb->runAction(Sequence::create(DelayTime::create(0.6), Spawn::create(Repeat::create(GAME::CreateAnimate("bomb-", 2, 0.5f, 1), 2), CallFunc::create([&]{audio->playEffect("sounds/bomb beep.mp3", false); }), NULL), CallFunc::create(CC_CALLBACK_0(GAME::SpawnBombExplosion, this, bomb)), NULL));
}
void GAME::SpawnBombExplosion(Node* sender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//
	Sprite *bomb = (Sprite*)sender;
	bomb->setOpacity(0);
	Sprite *bombExplosion = (Sprite*)_bombExplosion->at(At_BombExplosionNext);
	At_BombExplosionNext++;
	if (At_BombExplosionNext >= _bombExplosion->size())
		At_BombExplosionNext = 0;
	bombExplosion->stopAllActions();
	float Scale = (CCRANDOM_0_1()*(0.3 - 0.2)) + 0.2;
	bombExplosion->setScale(visibleSize.height*Scale / bombExplosion->getContentSize().height);
	bombExplosion->setPosition(Vec2(bomb->getPositionX() , bomb->getPositionY()));
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(bombExplosion->getPositionX() / PTM_RATIO, bombExplosion->getPositionY() / PTM_RATIO);
	bodyDef.userData = bombExplosion;
	auto bombExplosion_body = world->CreateBody(&bodyDef);
	b2Vec2 vertices[5];
	vertices[0].Set(-bombExplosion->getBoundingBox().size.width / 2 / PTM_RATIO, -bombExplosion->getBoundingBox().size.height*0.26 / PTM_RATIO);
	vertices[1].Set(0, -bombExplosion->getBoundingBox().size.height / 2 / PTM_RATIO);
	vertices[2].Set(bombExplosion->getBoundingBox().size.width / 2 / PTM_RATIO, -bombExplosion->getBoundingBox().size.height*0.26 / PTM_RATIO);
	vertices[3].Set(bombExplosion->getBoundingBox().size.width*0.27 / PTM_RATIO, bombExplosion->getBoundingBox().size.height*0.108 / PTM_RATIO);
	vertices[4].Set(-bombExplosion->getBoundingBox().size.width*0.27 / PTM_RATIO, bombExplosion->getBoundingBox().size.height*0.108 / PTM_RATIO);
	b2PolygonShape polygonShape;
	polygonShape.Set(vertices, 5);
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &polygonShape;
	bombExplosion_body->CreateFixture(&FixtureDef);
	bombExplosion->setOpacity(255);
	audio->playEffect("sounds/bomb explosion.mp3");
	bombExplosion_body->SetLinearVelocity(b2Vec2(-visibleSize.width / 10 * SpeedVelocity / PTM_RATIO, 0));
}
void GAME::Contact(Sprite* otherObject,b2Body* otherBody)
{
	CCLOG("Crashes");
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	int Tag = (int)otherObject->getTag();
	//16.Begin_bg   15.Tornado  13.house1  1.house2  2.house3  3.tree   4.windfan  5.windfanAnims  6.heart  7.storm  8.bg,bridge_bg 9.bridge
	//10.wind 11.bomb  12.wall
	if (Tag != NULL){
		if (Tag == 8){
			for (b2ContactEdge* edge = tor_body->GetContactList(); edge; edge = edge->next)
			{
				Sprite* other = (Sprite*)edge->other->GetUserData();
		 	if (other!=NULL && other->getTag() == 9)
					break;
			else if (edge->next == NULL){ this->EndGame(); }
				else{}
			}
		}
			if (TYPE == GAME::TornadoType::NORMAL || TYPE == GAME::TornadoType::SPEED)
			{
				if (Tag == 6)
				{
					HeartScore++;
					audio->playEffect("sounds/item.wav");
					otherObject->setOpacity(0);
				}
				else if (Tag == 7)
				{
					StormScore++;
					audio->playEffect("sounds/item.wav");
					otherObject->setOpacity(0);
				}
				else if (Tag == 10)
				{
					TYPE = TornadoType::SPEED;
					auto repeat = RepeatForever::create(GAME::CreateAnimate("tornado-normal-", 6, 0.125f, 1));
					repeat->setTag(3);
					tor->stopActionByTag(3);
					tor->runAction(repeat);
					audio->stopBackgroundMusic();
					audio->playBackgroundMusic("sounds/tornado(speed).mp3", true);
					SpeedVelocity = 1.5;
					CheckSpeedUpdate = true;
					speed->setTouchEnabled(false);
					heart->setTouchEnabled(false);
					storm->setTouchEnabled(false);
					this->runAction(Sequence::create(DelayTime::create(6.0), CallFunc::create(CC_CALLBACK_0(GAME::NormalTorCall, this)), DelayTime::create(0.5), CallFunc::create([&]{SpeedVelocity = 1.0; CheckSpeedUpdate = true; speed->setTouchEnabled(true); heart->setTouchEnabled(true); storm->setTouchEnabled(true); }), NULL));
					if (isBeginBodyUpdate)
					{
						otherObject->setOpacity(0);
						DestroyWindBody =(b2Body*)otherBody;
						NeedtoDestroyWind = true;
					}
				}
				else if (Tag == 3)
				{
					if (TYPE == TornadoType::SPEED)
					{
						otherObject->runAction(GAME::CreateAnimate("tree-falling-sprite-", 8, 0.15f, 1));
						audio->playEffect("sounds/destroyed tree.mp3");
					}
					else{ this->EndGame(); }
				}
				else if (Tag == 13 || Tag == 1 || Tag == 2 || Tag == 4 || Tag == 5 || Tag == 11 || Tag == 12){ this->EndGame(); }
				else if (Tag == 16){
					if (tor_body->GetPosition().y*PTM_RATIO >=visibleSize.height*0.92 || tor_body->GetPosition().y*PTM_RATIO <= visibleSize.height*0.31)
					{
						this->EndGame();
					}
				}
				else{}
			}
			if (TYPE == TornadoType::STORM)
			{
				if (Tag == 13)
				{
					otherObject->runAction(GAME::CreateAnimate("destroyed house-type 1-", 12, 0.2f, 1));
					audio->playEffect("sounds/destroyed houses.mp3");
				}
				else if (Tag == 1)
				{
					otherObject->runAction(GAME::CreateAnimate("destroyed house-type 2-", 10, 0.2f, 1));
					audio->playEffect("sounds/destroyed houses.mp3");
				}
				else if (Tag == 2)
				{
					otherObject->runAction(GAME::CreateAnimate("destroyed house-type 3-", 9, 0.2f, 1));
					audio->playEffect("sounds/destroyed houses.mp3");
				}
				else if (Tag == 3)
				{
					otherObject->runAction(GAME::CreateAnimate("tree-falling-sprite-", 8, 0.15f, 1));
					audio->playEffect("sounds/destroyed tree.mp3");
				}
				else if (Tag == 4)
				{

					otherObject->setOpacity(0);

				}
				else if (Tag == 6)
				{
					HeartScore++;
					audio->playEffect("sounds/item.wav");
					otherObject->setOpacity(0);
				}
				else if (Tag == 7)
				{
					StormScore++;
					audio->playEffect("sounds/destroyed houses.mp3");
					otherObject->setOpacity(0);
				}
				else if (Tag == 5 || Tag == 11 || Tag == 12){ this->EndGame(); }
				else if (Tag == 16){
					if (tor_body->GetPosition().y*PTM_RATIO >= visibleSize.height*0.94 || tor_body->GetPosition().y*PTM_RATIO <= visibleSize.height*0.33)
					{
						this->EndGame();
					}
				}
				else{}
		}
	}
}
void GAME::EndGame()
{
	st_button->setTouchEnabled(false);
	pause_button->setTouchEnabled(false);
	this->pauseSchedulerAndActions();
	auto node = this->getChildren();
	for (int i = 0; i < node.size(); i++)
	{
		if (node.at(i)->getTag() == -3 || node.at(i)->getTag() == 15)
			continue;
		node.at(i)->pauseSchedulerAndActions();
	}
	audio->stopAllEffects();
	audio->stopBackgroundMusic();
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(3);
	for (int i = 3; i >= 1; i--)
	{
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("tornado begin-%d.png",i)->getCString());
		animFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
	auto EndAnimate = Animate::create(animation);
	EndAnimate->retain();
	tor->stopActionByTag(3);
	tor->runAction(Sequence::create(EndAnimate, CallFunc::create([&]{tor->setOpacity(0); }),DelayTime::create(0.5),CallFunc::create(CC_CALLBACK_0(GAME::EnableEndTable, this)), NULL));
	audio->playEffect("sounds/tornado end.mp3", false);

}
void GAME::BeginContact(b2Contact* contact)
{
	CCLOG("shit");
	void* Object1 = contact->GetFixtureA()->GetBody()->GetUserData();
	void* Object2 = contact->GetFixtureB()->GetBody()->GetUserData();
	if (Object1 != NULL && Object2 != NULL){
		auto A = static_cast<Sprite*>(Object1);
		auto B = static_cast<Sprite*>(Object2);
		if (A->getTag() == 15)
		{
			b2Body* body = contact->GetFixtureB()->GetBody();
			this->Contact(B, body);
		}
		if (B->getTag() == 15){
			b2Body* body = contact->GetFixtureA()->GetBody();
			this->Contact(A ,body);
		}
	}
}
void GAME::EnableEndTable()
{
	this->ShowBanner();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	tor->schedule(SEL_SCHEDULE(&GAME::UpdateBanner), 1.0f);
	EndTable->setOpacity(255);
	Return_bt->setOpacity(255);
	Return_bt->setTouchEnabled(true);
	Share_bt->setOpacity(255);
	Share_bt->setTouchEnabled(true);
	FaceIcon->setOpacity(255);
	EndScoreLB->setOpacity(255);
	auto scoretemp = String::createWithFormat("%i", score);
	EndScoreLB->setColor(Color3B::GRAY);
	EndScoreLB->enableShadow();
	EndScoreLB->setPosition(Vec2(EndTable->getPositionX() - EndTable->getBoundingBox().size.width*0.3, EndTable->getPositionY() - EndTable->getBoundingBox().size.height / 5));
	EndScoreLB->setString(scoretemp->getCString());

	HighScoreLB->setOpacity(255);
	HighScoreLB->setColor(Color3B::RED);
	HighScoreLB->enableShadow();
	HighScoreLB->setPosition(Vec2(EndTable->getPositionX() + EndTable->getBoundingBox().size.width*0.3, EndTable->getPositionY() - EndTable->getBoundingBox().size.height / 5));
	auto userScore = UserDefault::sharedUserDefault();
	const char *HIGH_SCORE_KEY = "key";
	HighScore = userScore->getIntegerForKey(HIGH_SCORE_KEY);
	if (score > HighScore)
	{
		HighScore = score;
	}
	userScore->setIntegerForKey(HIGH_SCORE_KEY, HighScore);
	userScore->flush();
	auto HighScoretemp = String::createWithFormat("%i", HighScore);
	HighScoreLB->setString(HighScoretemp->getCString());
	if (score <= 5){ text = String::createWithFormat("Do better!"); }
	else if (score > 5 && score < 10)
	{
		text = String::createWithFormat("Good!");
	}
	else if (score < 20)
	{
		text = String::createWithFormat("Great!");
	}
	else if (score < 30)
	{
		text = String::createWithFormat("Amazing!");
	}
	else if (score < 40)
	{
		text = String::createWithFormat("Incredible!");
	}
	else if (score < 50)
	{
		text = String::createWithFormat("A real destroyer!");
	}
	else{ text = String::createWithFormat("Fu***** awesome, bro!"); }
	TextScoreLB->setString(text->getCString());
	TextScoreLB->setPosition(Vec2(HighScoreLB->getPositionX(), HighScoreLB->getPositionY() - TextScoreLB->getBoundingBox().size.height*2));
	TextScoreLB->setOpacity(255);
}
void GAME::EndContact(b2Contact* contact){}
void GAME::PreSolve(b2Contact* contact, const b2Manifold* oldManifold){}
void GAME::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){}
void GAME::ShowBanner()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)	

		PluginAdMob::show("home");
#endif
}
void GAME::HideBanner()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)	
	if(PluginAdMob::isAvailable("home"))
	{
		PluginAdMob::hide("home");
	}
#endif
}
void GAME::UpdateBanner(float dt)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)	
	CountToShowBanner++;

	if (isShowBanner && CountToShowBanner == 30)
	{
		PluginAdMob::hide("home");
		CountToShowBanner = 0;
		isShowBanner = false;
	}
	else if (!isShowBanner && CountToShowBanner == 5)
	{
		PluginAdMob::show("home");
		CountToShowBanner = 0;
		isShowBanner = true;
	}
#endif
}