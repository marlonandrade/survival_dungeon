#include "AppDelegate.h"
#include "IntroScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs() {
  //set OpenGL context attributions,now can only set six attributions:
  //red,green,blue,alpha,depth,stencil
  GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

  GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
  // initialize director
  auto director = Director::getInstance();
  auto glview = director->getOpenGLView();
  if(!glview) {
    glview = GLViewImpl::create("My Game");
    director->setOpenGLView(glview);
  }

  // turn on display FPS
  director->setDisplayStats(true);

  // set FPS. the default value is 1.0/60 if you don't call this
  director->setAnimationInterval(1.0 / 60);
  
  this->_adjustResolution();

  // create a scene. it's an autorelease object
  auto scene = IntroScene::create();

  // run
  director->runWithScene(scene);

  return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
  Director::getInstance()->stopAnimation();

  // if you use SimpleAudioEngine, it must be pause
  // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
  Director::getInstance()->startAnimation();

  // if you use SimpleAudioEngine, it must resume here
  // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

#pragma mark - Private Interface

#define DESIGN_SIZE       Size(480, 320)
#define LOW_RESOLUTION    Size(480, 320)
#define MEDIUM_RESOLUTION Size(1024, 768)
#define HIGH_RESOLUTION   Size(2048, 1536)

void AppDelegate::_adjustResolution() {
  auto glView = Director::getInstance()->getOpenGLView();
  auto deviceSize = glView->getFrameSize();
  
  auto designAspectRatio = DESIGN_SIZE.width / DESIGN_SIZE.height;
  auto deviceAspectRatio = deviceSize.width / deviceSize.height;
  
  glView->setDesignResolutionSize(DESIGN_SIZE.width, DESIGN_SIZE.height, ResolutionPolicy::NO_BORDER);
  
  std::vector<std::string> resourceSearchPaths;
  
  struct Resource {
    Size size;
    char directory[100];
  };
  
  Resource smallResource  = { Size(480, 320),   "sd" };
  Resource mediumResource = { Size(960, 640),   "md" };
  Resource highResource   = { Size(1440, 960),  "hd" };
  Resource ultraResource  = { Size(2400, 1600), "ud" };
  
  Resource currentResource;
  
  if (deviceAspectRatio >= designAspectRatio) {
    if (deviceSize.height > highResource.size.height) {
      currentResource = ultraResource;
    } else if (deviceSize.height > mediumResource.size.height) {
      currentResource = highResource;
    } else if (deviceSize.height > smallResource.size.height) {
      currentResource = mediumResource;
    } else {
      currentResource = smallResource;
    }
  } else {
    if (deviceSize.width > highResource.size.width) {
      currentResource = ultraResource;
    } else if (deviceSize.width > mediumResource.size.width) {
      currentResource = highResource;
    } else if (deviceSize.width > smallResource.size.width) {
      currentResource = mediumResource;
    } else {
      currentResource = smallResource;
    }
  }
  
  log("(%f, %f), %s", currentResource.size.width, currentResource.size.height, currentResource.directory);
  
  resourceSearchPaths.push_back(currentResource.directory);
  FileUtils::getInstance()->setSearchPaths(resourceSearchPaths);
  
  Director::getInstance()->setContentScaleFactor(currentResource.size.width / DESIGN_SIZE.width);
}