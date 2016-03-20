#include "HelloWorldScene.h"
#include "StringUtil.h"
#include "CsvUtil.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if (!Layer::init())
    {
        return false;
    }
//     /* ����ַ��� */
//     auto strsList = StringUtil::getInstance()->split("Mutou,Xiaoruo,Cocos2d-x,Csv", ",");
// 
//     /* ���������� */
//     for (auto value : strsList)
//     {
//         log("value=%s", value.asString().c_str());
//     }

    /* ���Զ�ȡCsv�ļ� */
    const char* sPath = "Monster.csv";

    /* �����ļ� */
    CsvUtil::getInstance()->loadFile(sPath);

    /* ��ȡ��һ����������� */
    Value firstMonsterName = CsvUtil::getInstance()->getValue(2, 1, sPath);

    /* ��ȡ�ڶ��������HPֵ */
    Value secMonsterHP = CsvUtil::getInstance()->getValue(3, 3, sPath);

    log("firstMonsterName = %s", firstMonsterName.asString().c_str());
    log("secMonsterHP = %s", secMonsterHP.asString().c_str());

    log("secMonsterHP = %s", CsvUtil::getInstance()->get(3, 3, sPath).c_str());
    return true;
}
