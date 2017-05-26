
#include "cocos2d.h"
#include "cocos-ext.h"

class KeyboardNotificationLayer;

using namespace cocos2d;
using namespace extension;
using namespace std;

class LoginEditBox : public CCLayer, public cocos2d::extension::CCEditBoxDelegate
{
public:
	virtual bool init();
	static CCScene* scene();

	CCSize winSize;

	//멀티레이어를 위한 objc

	CREATE_FUNC(Login);

	CCTextFieldTTF *ID_Field;

	string id_R;
	string password_R;

	void ccTouchesBegan(cocos2d::CCSet* pTouch, cocos2d::CCEvent* pEvent);

	void keyBackClicked();

	void Login_request(CCObject* pSender);
	void onHttpRequestCompleted(CCNode *sender, void *data);

	virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
private:
	cocos2d::CCLabelTTF* m_pTTFShowEditReturn;
	cocos2d::extension::CCEditBox* m_pEditName;
	cocos2d::extension::CCEditBox* m_pEditPassword;


};