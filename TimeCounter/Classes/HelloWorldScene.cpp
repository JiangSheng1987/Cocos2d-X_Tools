#include "HelloWorldScene.h"
#include "CallbackTimeCounter.h"

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
//     /* ������ʱ����Ҫ��ӵ����� */
//     m_timeCounter = TimeCounter::create();
//     this->addChild(m_timeCounter);
// 
//     /* ��ʼ��ʱ */
//     m_timeCounter->start();
// 
//     this->schedule(schedule_selector(HelloWorld::logic), 1.0f);
//     this->schedule(schedule_selector(HelloWorld::doSomething));

    /* ������ʱ�� */
    CallbackTimeCounter* cbTimeCounter = CallbackTimeCounter::create();
    this->addChild(cbTimeCounter);

    /* ��ʼ��ʱ��5���ص����� */
    cbTimeCounter->start(5.0f, [&](){
        auto sprite = Sprite::create("sprite.png");
        sprite->setPosition(Point(200, 180));
        this->addChild(sprite);
    });

    return true;
}

void HelloWorld::logic(float dt)
{
    log("%f", m_timeCounter->getfCurTime());
}

void HelloWorld::doSomething(float dt)
{
    for (int i = 0; i < 99999999; i++)
    {
        ;
    }
}