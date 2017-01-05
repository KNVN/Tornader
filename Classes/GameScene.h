#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Box2D/Box2D.h"
using namespace std;
USING_NS_CC;
class GAME : public cocos2d::Layer, public b2ContactListener
{
public:
    static cocos2d::Scene* createScene();

	virtual bool init();
	void update(float dt);
	void SettingButton();
	void PauseButton();
	void st_ExitGame();
	void exit();
	void RestartScene();
	void BeginTornado();
	cocos2d::Animate* CreateAnimate(std::string prefixName, int numberFrames,float delay,int FirstNumber);
	void CreateTorAnimationWithPhysic(float dt);
	void CreateB2TorFittedBody(float dt);
	void NormalTorCall();
	void SetTorNormalPosition();
	void SpawnObject(float dt);
	void ScheduleObject();
	void WindfanAnims(Node* sender);
	void BridgeSpawn();
	void MoveBackGroundBegin();
	void SpawnWind();
	void SpawnWall(float dt);
	void SpawnBomb(float dt);
	void SpawnBombExplosion(Node* sender);
	void Contact(cocos2d::Sprite* otherObject, b2Body* otherBody);
	void EndGame();
	void EnableEndTable();
	void ShowBanner();
	void HideBanner();
	void UpdateBanner(float dt);
	//
	//
	bool isBeginTorUpdate = false;
	bool SpawnObjectUpdate = false;
	bool isSpawnBridge = true;
	bool ClearWhenSpawnBridge = false;
	bool isSpawnWind = false;
	bool isSpawnBombUpdate = true;
	bool CheckSpeedUpdate = false;
	bool isGameOver = false;
	bool isUp = false;
	bool isDown = false;
	bool isWinScore = false;
	bool isDestroyBg2body = false;
	bool isBeginBodyUpdate = false;
	bool NeedtoDestroyWind = false;
	bool isUpdateBanner = false;
	bool isShowBigAd = true;
	bool isShowBanner = true;

	int score = 0;
	int HighScore;
	int HeartScore = 0;
	int StormScore = 0;
	int SpeedScore = 0;
	float SpawnObjectTime;
	int CountToShowBanner = 0;
	cocos2d::String* text = cocos2d::String::createWithFormat("Do better!");
	cocos2d::Label* TextScoreLB;
	//
	//
	cocos2d::ui::CheckBox* sfx;
	cocos2d::ui::CheckBox* music_bt;
	cocos2d::ui::Button* exit_bt;
	cocos2d::Sprite* exit_table;
	cocos2d::ui::Button* yes;
	cocos2d::ui::Button* no;
	cocos2d::ui::Button* restart_bt;
	cocos2d::ui::Button* continue_bt;
	cocos2d::ui::Button* back_bt;
	cocos2d::Sprite* paus_table;
	cocos2d::ui::LoadingBar* power;
	cocos2d::ui::Button* up_bt;
	cocos2d::ui::Button* down_bt;
	cocos2d::ui::Button* speed;
	cocos2d::Sprite* speed_spr;
	cocos2d::Label* speedlabel;
	cocos2d::ui::Button* heart;
	cocos2d::Sprite* heart_spr;
	cocos2d::Label* heartlabel;
	cocos2d::ui::Button* storm;
	cocos2d::Sprite* storm_spr;
	cocos2d::Label* stormlabel;
	cocos2d::Label* label;
	cocos2d::Sprite* st_table;
	cocos2d::ui::CheckBox* st_button;
	cocos2d::ui::CheckBox* pause_button;
	cocos2d::Sprite* EndTable;
	cocos2d::ui::Button* Share_bt;
	cocos2d::ui::Button* Return_bt;
	cocos2d::ui::Button* Rate;
	cocos2d::Label* EndScoreLB;
	cocos2d::Label* HighScoreLB;
	cocos2d::Sprite* FaceIcon;
	cocos2d::Sprite* begin_bg;
	cocos2d::Sprite* bridge_bg;
	cocos2d::Sprite* bridge;
	cocos2d::Sprite* Wall;
	cocos2d::Sprite* tor;//main character
	cocos2d::Sprite* torheart;
	cocos2d::Sprite* background1;
	cocos2d::Sprite* background2;
	b2Body* tor_body;
	b2Fixture* tor_fixture;
	b2Body* BgBox;
	b2Body* Bg2Box;
	b2Body* DestroyWindBody;
	cocos2d::Vector<cocos2d::Sprite*>*_house1;
	cocos2d::Vector<cocos2d::Sprite*>*_house2;
	cocos2d::Vector<cocos2d::Sprite*>*_house3;
	cocos2d::Vector<cocos2d::Sprite*>*_tree;
	cocos2d::Vector<cocos2d::Sprite*>*_windfan;
	cocos2d::Vector<cocos2d::Sprite*>*_windfanAnims;
	cocos2d::Vector<cocos2d::Sprite*>*_heartItem;
	cocos2d::Vector<cocos2d::Sprite*>*_stormyItem;
	cocos2d::Vector<cocos2d::Sprite*>*_wind;
	cocos2d::Vector<cocos2d::Sprite*>*_bomb;
	cocos2d::Vector<cocos2d::Sprite*>*_bombExplosion;
	cocos2d::Vector<cocos2d::Sprite*>*_canon;
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
	unsigned int can;
	int At_House1Next = 0;
	int At_House2Next = 0;
	int At_House3Next = 0;
	int At_treeNext = 0;
	int At_WindfanNext = 0;
	int At_WindfanAnimsNext = 0;
	int At_heartItemNext = 0;
	int At_stormyItemNext = 0;
	int At_windNext = 0;
	int At_BgNext = 0;
	int At_BombNext = 0;
	int At_BombExplosionNext = 0;
	int numberSpritesMax = 15;
	int SpawnScore = 0;
	int WallSpawnScore = 30;
	int ItemPoint = 0;
	int ObjectSpawnNumber;
	float SpeedVelocity = 1.0;
	//
	enum class TornadoType {
		NONE,
		NORMAL,
		SPEED,
		HEART,
		STORM
	}TYPE;
	// implement the "static create()" method manually
    CREATE_FUNC(GAME);
private:
	b2World *world;
	
};

#endif // __GAME_SCENE_H__
