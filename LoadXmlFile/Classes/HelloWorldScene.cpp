#include "HelloWorldScene.h"
#include "tinyxml\tinyxml.h"

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
    //loadXmlTest1("test1.xml");
    loadXmlTest2("test2.xml");
    return true;
}

void HelloWorld::loadXmlTest1(const char* sPath) {
    TiXmlDocument* xmlDoc = new TiXmlDocument();

    /* ��ȡXML�ļ� */
    Data fileData = FileUtils::getInstance()->getDataFromFile(sPath);

    /* ��ʼ����XML */
    xmlDoc->Parse((const char*)fileData.getBytes());

    /* ��ȡXML���ڵ� */
    TiXmlElement* rootElement = xmlDoc->RootElement();

    /* ��ʼ��ȡXML������ǩ */
    loadXmlEle(rootElement);

    /* ɾ������ */
    delete xmlDoc;
}

void HelloWorld::loadXmlEle(TiXmlElement* rootElement) {
    /* ȡ�ø��ڵ�ĵ�һ���ӱ�ǩ���� */
    TiXmlElement* cldElement = rootElement->FirstChildElement();

    /* ��ӡ��ǩ�����ֺͱ�ǩ��id���� */
    log("%s id=%s", cldElement->Value(), cldElement->Attribute("id"));

    /* ��ȡ�ñ�ǩ�ĵ�һ���Ӷ��� */
    cldElement = cldElement->FirstChildElement();

    /* ��ӡ��ǩ�����ֺͱ�ǩ��ֵ */
    log("%s:%s", cldElement->Value(), cldElement->GetText());
}

void HelloWorld::loadXmlTest2(const char* sPath) {
    TiXmlDocument* xmlDoc = new TiXmlDocument();

    /* ��ȡXML�ļ� */
    Data fileData = FileUtils::getInstance()->getDataFromFile(sPath);

    /* ��ʼ����XML */
    xmlDoc->Parse((const char*)fileData.getBytes());

    /* ��ȡXML���ڵ� */
    TiXmlElement* rootElement = xmlDoc->RootElement();

    /* ��ʼ��ȡXML������ǩ */
    loadXmlEleMMWin(rootElement);

    /* ɾ������ */
    delete xmlDoc;
}

void HelloWorld::loadXmlEleMMWin(TiXmlElement* rootElement) {
    TiXmlElement* cldElement = rootElement->FirstChildElement();

    while (cldElement != NULL) {
        /* ĳЩ�ڵ������Ϊ�գ����Բ���ȡ�������ݣ����ǿ������ӽڵ㣩 */
        if (cldElement->GetText() != NULL) {
            log("%s:%s", cldElement->Value(), cldElement->GetText());
        }
        /* ������ӽڵ㣬�����������������ӵ���ǰ�ڵ���ӽڵ��б� */
        else if (cldElement->FirstChildElement() != NULL) {
            loadXmlEleMMWin(cldElement);
        }

        /* ��һ��ͬ���ڵ� */
        cldElement = cldElement->NextSiblingElement();
    }
}