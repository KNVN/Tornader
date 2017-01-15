#include "AppDelegate.h"
#include "MenuGameScene.h"
#include "SimpleAudioEngine.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "pluginadmob/PluginAdMob.h"
#include "pluginfacebook/PluginFacebook.h"
using namespace sdkbox;
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "StartAppPlugin.h"
#endif
USING_NS_CC;

#define PORTRAIT 0
#define SCREEN_WIDTH_SD     627
#define SCREEN_HEIGHT_SD    396
#define SCREEN_WIDTH_HD     1254
#define SCREEN_HEIGHT_HD    792
#define SCREEN_WIDTH_RETINA 2508
#define SCREEN_HEIGHT_RETINA 1584

#define GAME_WIDTH_SD       528
#define GAME_HEIGHT_SD      360
#define GAME_WIDTH_HD       1056
#define GAME_HEIGHT_HD      704
#define GAME_WIDTH_RETINA   2112
#define GAME_HEIGHT_RETINA  1408

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	PluginAdMob::init();
    PluginFacebook::init();
	class IMListener : public sdkbox::AdMobListener {
public:
    virtual void adViewDidReceiveAd(const std::string &name) {
        log("admob adViewDidReceiveAd %s: ", name.c_str());
        PluginAdMob::show("home");
        //if (showText) showText(StringUtils::format("%s name=%s", __FUNCTION__, name.c_str()));
    }
    virtual void adViewDidFailToReceiveAdWithError(const std::string &name, const std::string &msg) {
        log("admob adViewDidFailToReceiveAdWithError %s: ", msg.c_str());
        //if (showText) showText(StringUtils::format("%s name=%s, msg=%s", __FUNCTION__, name.c_str(), msg.c_str()));
    }
    virtual void adViewWillPresentScreen(const std::string &name) {
        log("admob adViewWillPresentScreen %s: ", name.c_str());
        //if (showText) showText(StringUtils::format("%s name=%s", __FUNCTION__, name.c_str()));
    }
    virtual void adViewDidDismissScreen(const std::string &name) {
        log("admob adViewDidDismissScreen %s: ", name.c_str());
        //if (showText) showText(StringUtils::format("%s name=%s", __FUNCTION__, name.c_str()));
    }
    virtual void adViewWillDismissScreen(const std::string &name) {
        //if (showText) showText(StringUtils::format("%s name=%s", __FUNCTION__, name.c_str()));

        //if (name == "gameover") {
            //sdkbox::PluginAdMob::cache(kHomeBanner);
            //sdkbox::PluginAdMob::cache(kGameOverAd);
        //}
        log("admob adViewWillDismissScreen %s: ", name.c_str());
    }
    virtual void adViewWillLeaveApplication(const std::string &name) {
        //if (showText) showText(StringUtils::format("%s name=%s", __FUNCTION__, name.c_str()));
        log("admob adViewWillLeaveApplication %s: ", name.c_str());
    }
};
    PluginAdMob::setListener(new IMListener());
	PluginAdMob::cache("home");
	PluginAdMob::cache("gameover");
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
 startappiOS* startAppBridge = startappiOS().sharedInstance();
    startAppBridge->STAInit("", "");
    startAppBridge->loadAd();    
#endif
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLViewImpl::create("Tornader");
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
   //     glview = GLViewImpl::createWithRect("TheGame", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
//#else
 //       glview = GLViewImpl::create("TheGame");
//#endif
        director->setOpenGLView(glview);
    }
	auto screenSize = glview->getFrameSize();
	auto designSize = cocos2d::Size(SCREEN_WIDTH_RETINA, SCREEN_HEIGHT_RETINA);
	auto gameSize = cocos2d::Size(GAME_WIDTH_RETINA, GAME_HEIGHT_RETINA);

	std::vector<std::string> searchPaths;

	if (screenSize.width <= SCREEN_WIDTH_SD) {
		searchPaths.push_back("SD");
		if (PORTRAIT) director->setContentScaleFactor(SCREEN_WIDTH_SD / designSize.width);
		else director->setContentScaleFactor(SCREEN_HEIGHT_SD / designSize.height);
		cocos2d::log("Set SD Design Res");
	}
	else if (screenSize.width <= SCREEN_WIDTH_HD) {
		searchPaths.push_back("HD");
		if (PORTRAIT) director->setContentScaleFactor(SCREEN_WIDTH_HD / designSize.width);
		else director->setContentScaleFactor(SCREEN_HEIGHT_HD / designSize.height);
		cocos2d::log("Set HD Design Res");
	}
	else {
		searchPaths.push_back("RETINA");
		if (PORTRAIT) director->setContentScaleFactor(SCREEN_WIDTH_RETINA / designSize.width);
		else director->setContentScaleFactor(SCREEN_HEIGHT_RETINA / designSize.height);
		cocos2d::log("Set RETINA Design Res");
	}

	cocos2d::FileUtils::getInstance()->setSearchPaths(searchPaths);
	if (PORTRAIT) glview->setDesignResolutionSize(designSize.height, designSize.width, ResolutionPolicy::EXACT_FIT);
	else glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::EXACT_FIT);
    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // Set the design resolution
    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = MenuGame::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
     CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	 CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
     CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	 CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
}
