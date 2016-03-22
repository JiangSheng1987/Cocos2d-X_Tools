#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class TiXmlElement;
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
    CREATE_FUNC(HelloWorld);

private:
    void loadXmlTest1(const char* sPath);           // XML��ȡ����1��Hello TinyXML
    void loadXmlEle(TiXmlElement* rootElement);     //��ȡ��ͨ��XML�����ļ�

    
    void loadXmlTest2(const char* sPath);           // XML��ȡ����2����ȡMM�ؼ���XML
    void loadXmlEleMMWin(TiXmlElement* rootElement);//��ȡMM�ؼ���XML�����ļ�
};

#endif // __HELLOWORLD_SCENE_H__
