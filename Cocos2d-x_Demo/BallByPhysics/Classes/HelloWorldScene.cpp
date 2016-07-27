#include "HelloWorldScene.h"
USING_NS_CC;
Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	auto* background = LayerColor::create(Color4B(255, 255, 255, 255));
	addChild(background);
	ball = Sprite::create("ball.png");
	ball->setPosition(320, 300);
	addChild(ball);
	b2Vec2 gravity;					// ��������
	gravity.Set(0.0f, -2.0f);	// ������������
	world = new b2World(gravity);		// �����������
	world->SetAllowSleeping(true);			//��������
	world->SetContinuousPhysics(true);		//���ü��������ײ
	b2BodyDef groundBodyDef;		// �������
	groundBodyDef.position.Set(0, 0);	// �������½�Ϊ����ԭ��
	//���ݸ�������������������
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	groundBody->SetType(b2_staticBody);
	b2EdgeShape groundBox;		//����������״
	//2����ȷ��һ���ߣ����·ֱ���������Ļ��4����
	groundBox.Set(b2Vec2(0, 0), b2Vec2(640, 0));
	groundBody->CreateFixture(&groundBox, 0);
	groundBox.Set(b2Vec2(0, 360), b2Vec2(640, 360));
	groundBody->CreateFixture(&groundBox, 0);
	groundBox.Set(b2Vec2(0,360), b2Vec2(0, 0));
	groundBody->CreateFixture(&groundBox, 0);
	groundBox.Set(b2Vec2(640, 360), b2Vec2(640, 0));
	groundBody->CreateFixture(&groundBox, 0);
	b2BodyDef bodyDef;				// ���嶯̬����
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(320, 300);
	b2Body *ballbody = world->CreateBody(&bodyDef);
	ballbody->SetUserData(ball);
	ballbody->SetActive(true);
	//�������̬���崴��������״
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.5f, 0.5f);
	b2FixtureDef fixtureDef;			//Ϊ�ø��嶨��о�
	fixtureDef.shape = &dynamicBox;		//���������״
	fixtureDef.density = 0.2f;			//�ܶ�
	fixtureDef.restitution = 0.9f;		//����ϵ��
	fixtureDef.friction = 0.1f;			//Ħ����
	ballbody->CreateFixture(&fixtureDef);	//�ڸ���ļо߹����д����о�
	this->scheduleUpdate();
    return true;
}
void HelloWorld::update(float dt)
{
	int velocityIterations = 8;
	int positionIterations = 1;
	//ʱ�䶨��ɹ̶��ģ������dt�Ļ���������֡�ʵı仯���仯
	world->Step(0.2f, velocityIterations, positionIterations);
	//ö�������е��������壬�ҳ���userdata�����壬ǿ��ת��Ϊ����
	for (b2Body *b = world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL)
		{
			Sprite *sprite = (CCSprite *)b->GetUserData();
			if (sprite != NULL)
			{
				b2Vec2 bodyPos = b->GetPosition();	// ��ȡС�����
				Point pos = ccp(bodyPos.x, bodyPos.y);	// ��С�������ת��Ϊbox2d������
				float32 rotation = -1 * CC_RADIANS_TO_DEGREES(b->GetAngle());		//ת���Ƕ�
				sprite->setPosition(pos);		//���þ�������
				sprite->setRotation(rotation);	//���þ���Ƕ�
			}
		}
	}
}
