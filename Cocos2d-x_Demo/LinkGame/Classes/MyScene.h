#ifndef __MYWORLD_SCENE_H__
#define __MYWORLD_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"
class MyWorld :public cocos2d::Layer
{
public:
	int iniX;
	int id;
	static cocos2d::Scene* createScene();	// ��̬�������û���ȡ��������
	virtual bool init();					// ��ʼ������
	void menu(cocos2d::Ref* pSender);
	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual void onTouchMoved(Touch *touch, Event *event);
	virtual void onTouchEnded(Touch *touch, Event *event);
	CREATE_FUNC(MyWorld);					// ����ʹ����һ����
};
#endif

