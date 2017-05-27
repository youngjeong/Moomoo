#include "LoginEditBox.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "cocos-ext.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace extension;
using namespace std;

size_t func(void* ptr, size_t size, size_t nmemb, void* stream)
{
	strncat((char*)stream, (char*)ptr, size*nmemb);

	return size*nmemb;
}


CCScene* Login::scene()
{
	CCScene *scene = CCScene::create();
	Login *layer = Login::create();
	scene->addChild(layer);

	return scene;
}

bool Login::init()
{
	if (!CCLayer::init()) {
		return false;
	}

	Appd->soundPlay();

	winSize = CCDirector::sharedDirector()->getWinSize();
	this->setTouchEnabled(true);

	CCPoint visibleOrigin = CCEGLView::sharedOpenGLView()->getVisibleOrigin();
	CCSize visibleSize = CCEGLView::sharedOpenGLView()->getVisibleSize();

	CCSize editBoxSize = CCSizeMake(visibleSize.width - winSize.width / 2, 60);


	//editbox
	{
		m_pEditName = CCEditBox::create(editBoxSize, CCScale9Sprite::create("orange_edit.png"));
		m_pEditName->setPosition(ccp(visibleOrigin.x + visibleSize.width / 2 - 30, visibleOrigin.y + visibleSize.height / 2 + 50));
		m_pEditName->setFontName("Arial");
		m_pEditName->setFontSize(40);
		m_pEditName->setFontColor(ccGREEN);
		m_pEditName->setPlaceHolder("아이디:");
		m_pEditName->setPlaceholderFontColor(ccGREEN);
		m_pEditName->setMaxLength(8);
		m_pEditName->setReturnType(kKeyboardReturnTypeDone);
		//        m_pEditPassword->setInputFlag(kEditBoxInputFlagSensitive);
		//        m_pEditPassword->setInputMode(kEditBoxInputModeAny);
		m_pEditName->setDelegate(this);

		addChild(m_pEditName, 2);

		// middle
		m_pEditPassword = CCEditBox::create(editBoxSize, CCScale9Sprite::create("orange_edit.png"));
		m_pEditPassword->setPosition(ccp(visibleOrigin.x + visibleSize.width / 2 - 30, visibleOrigin.y + visibleSize.height / 2 - 50));
		m_pEditPassword->setFont("Arial", 40);
		m_pEditPassword->setFontColor(ccGREEN);
		m_pEditPassword->setPlaceholderFontColor(ccGREEN);
		m_pEditPassword->setPlaceHolder("Password:");
		m_pEditPassword->setMaxLength(13);
		m_pEditPassword->setInputFlag(kEditBoxInputFlagPassword);
		m_pEditPassword->setInputMode(kEditBoxInputModeSingleLine);
		m_pEditPassword->setDelegate(this);
		addChild(m_pEditPassword);
	}

	{
		CCSprite *login_btn = CCSprite::create("login_btn.png");
		login_btn->setPosition(ccp(winSize.width / 2 + 400, winSize.height / 2));
		login_btn->setScale(winSize.width / 11 / login_btn->getContentSize().width);
		login_btn->setTag(001);
		this->addChild(login_btn, 3);
	}

	{
		CCSprite *join_btn = CCSprite::create("Member_Join.png");
		join_btn->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 150));
		join_btn->setTag(002);
		this->addChild(join_btn, 3);
	}


	return true;
}

void Login::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox) {
	//    CCLog("editBox %p DidBegin !", editBox);
}
void Login::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox) {
	//    CCLog("editBox %p DidEnd !", editBox);
}
void Login::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text) {
	//    CCLog("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}
void Login::editBoxReturn(CCEditBox* editBox) {
	//    CCLog("editBox %p was returned !");

	if (m_pEditName == editBox)
	{
		//        m_pTTFShowEditReturn->setString("Name EditBox return !");
	}
	//    else if (m_pEditPassword == editBox)
	//    {
	//        m_pTTFShowEditReturn->setString("Password EditBox return !");
	//    }
}


void Login::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint point = pTouch->getLocationInView();
	point = CCDirector::sharedDirector()->convertToGL(point);

	string a = "123";

	CCSprite *login_btn = (CCSprite*)this->getChildByTag(001);
	CCRect login_rect = login_btn->boundingBox();
	if (login_rect.containsPoint(point)) {
		CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.2, select::scene(), ccc3(255, 255, 255)));
	}

	cout << id_R << endl;
	cout << password_R << endl;
}

void Login::keyBackClicked() {
	CCDirector::sharedDirector()->end();

}

