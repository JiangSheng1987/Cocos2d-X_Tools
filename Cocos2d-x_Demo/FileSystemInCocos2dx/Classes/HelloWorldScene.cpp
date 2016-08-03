#include "HelloWorldScene.h"

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
    if ( !Layer::init() )
    {
        return false;
    }
	// ����һ���˵���ť�����ڶ�ȡ�ļ��е�����
	auto* background = LayerColor::create(Color4B(255, 255, 255, 255));
	addChild(background);
	auto* readLabel = Label::create("read", "Arial", 56);
	readLabel->setColor(Color3B(0, 0, 0));
	auto* pReadLabel = MenuItemLabel::create(readLabel, this, menu_selector(HelloWorld::readCallback));
	auto* buttonReadLabel = Menu::create(pReadLabel, NULL);
	buttonReadLabel->setPosition(320, 260);
	addChild(buttonReadLabel);
	auto* saveLabel = Label::create("save", "Arial", 56);
	saveLabel->setColor(Color3B(0, 0, 0));
	auto* pSaveLabel = MenuItemLabel::create(saveLabel, this, menu_selector(HelloWorld::saveCallback));
	auto* buttonSaveLabel = Menu::create(pSaveLabel, NULL);
	buttonSaveLabel->setPosition(320, 100);
	addChild(buttonSaveLabel);
    return true;
}
void HelloWorld::readCallback(Ref* pSender)
{
	CCLOG("============================================================");
	std::string path = FileUtils::sharedFileUtils()->getWritablePath()+"test.txt";
	// ����ļ�·��
	CCLOG("path = %s", path.c_str());
	// ����һ���ļ�ָ��
	FILE* file = fopen(path.c_str(), "r");
	if (file) {
		char* buf;  //Ҫ��ȡ���ַ���  
		int len;    //��ȡ�ĳ���  
		// ��ȡ�ļ����ȳ���
		fseek(file, 0, SEEK_END);   //�Ƶ�β��  
		len = ftell(file);          //��ȡ����  
		rewind(file);               //�ع�ԭλ  
		CCLOG("count the file content len = %d", len);
		//����buf�ռ�  
		buf = (char*)malloc(sizeof(char) * len + 1);
		if (!buf) 
		{
			CCLOG("malloc space is not enough.");
		} 
		//��ȡ����buf����λ��С�����ȣ��ļ�ָ��  
		int rLen = fread(buf, sizeof(char), len, file);
		buf[rLen] = '\0';
		CCLOG("has read Length = %d", rLen);
		CCLOG("has read content = %s", buf);
		fclose(file);
		free(buf);
	}
	else
	{
		CCLOG("open file error.");
	}
	CCLOG("============================================================");
}
void HelloWorld::saveCallback(Ref* pSender)
{
	CCLOG("============================================================");
	std::string path = CCFileUtils::sharedFileUtils()->getWritablePath() + "test.txt";
	FILE* file = fopen(path.c_str(), "w");
	if (file) 
	{
		char* pContent = "this is a word";
		fputs(pContent, file);
		CCLOG("save file succeed.");
		fclose(file);
	}
	else
	{
		CCLOG("save file error.");
	}
	CCLOG("============================================================");
}
