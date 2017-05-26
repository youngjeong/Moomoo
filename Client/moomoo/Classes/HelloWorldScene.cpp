#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "../moomoo/proj.win32/RingBuffer.h"
#include "../moomoo/proj.win32/TestScene.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
	// Test RingBuffer Code //

	auto ring = RingBuffer(10);

	ring.push((char *)"hello", 5);
	char res[10] = { 0, };
	ring.pop((char*)res, 5);
	

	// Test RingBuffer Code End //


    auto label = Label::createWithTTF("ESCAPE", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("escape.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

	auto textBox = CCTextFieldTTF::textFieldWithPlaceHolder("ID", CCSize(480, 40), kCCTextAlignmentCenter, "Arial", 30);
	textBox->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3 * 2));
	this->addChild(textBox);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	auto testScene = TestScene::createScene();
	Director::getInstance()->pushScene(testScene);
    
}
