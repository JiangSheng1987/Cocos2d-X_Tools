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
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	rule = 0;
	id = 0;
	auto* background = Sprite::create("background.png");
	background->setPosition(320, 180);
	addChild(background);

	player[0] = new Player(0);
	player[1] = new Player(1);

	this->preporePocker(Vec2(30,180));
	startDeal();
    return true;
}
void HelloWorld::initPocker()
{
	// ��ֽ�����а�����˳����г�ʼ��
	for (int i = 0; i < 54; i++)
	{
		pockerNumber[i] = i;
	}
	// ����˳����ʼ �����ֽ�ƽ����Եõ�һ�������ֽ����������
	// ʹ�õ�ǰʱ���������������
	srand(unsigned(time(0)));
	for (int i = 0; i < 54; i++)
	{
		// ����һ����0��53�������
		int num = (rand()*rand()) % 54;
		// ������Ԫ�ػ��ཻ��
		int temp = pockerNumber[i];
		pockerNumber[i] = pockerNumber[num];
		pockerNumber[num] = temp;
		CCLOG("pock[%d]=%d", i, pockerNumber[i]);
		// ���¶�������
		srand(rand());
	}
	//pockerNumSort(0, 54);
}
void HelloWorld::pockerNumSort(int low, int high)
{
	for (int i = low; i < high; i++)
	{
		// ���ѭ��
		for (int j = low; j < high; j++)
		{
			if (pockerNumber[j] < 52 && pockerNumber[j + 1] < 52)
			{
				// �������������������бȽ�
				int num1 = pockerNumber[j] % 13;
				int num2 = pockerNumber[j + 1] % 13;
				// �ȱȽ��Ƶ���ֵ
				if (num1 > num2)
				{
					int t = pockerNumber[j];
					pockerNumber[j] = pockerNumber[j + 1];
					pockerNumber[j + 1] = t;
				}
				else if (num1 == num2)
				{
					// �����ֵ��ͬ�ٱȽϻ�ɫ
					int type1 = pockerNumber[j] / 13;
					int type2 = pockerNumber[j + 1] / 13;
					if (type1 > type2)
					{
						int t = pockerNumber[j];
						pockerNumber[j] = pockerNumber[j + 1];
						pockerNumber[j + 1] = t;
					}
				}
			}
			if (pockerNumber[j] > 51 && pockerNumber[j + 1] > 51)
			{
				// �����Ʒֱ��Ǵ�С������ֱ�Ӷ������ƽ��и�ֵ����
				pockerNumber[j] = 52;
				pockerNumber[j + 1] = 53;
			}
			else
			{
				// һ��������һ������ͨ��
				if (pockerNumber[j] > 51)
				{
					// ��ʱ��Ҫ����˳��
					int t = pockerNumber[j];
					pockerNumber[j] = pockerNumber[j + 1];
					pockerNumber[j + 1] = t;
				}
				// ��������ֽ�Ƶ���ֵһ���ȴ�С��ҪС���ʵ�pockerNumber[j+1]>51ʱ����Ҫ����˳��
			}
		}
	}
	testSort(0, 54);
}
void HelloWorld::testSort(int low, int high)
{
	for (int i = low; i < high; i++)
	{
		int pocker = pockerNumber[i];
		int num = pocker % 13;
		int type = pocker / 13;
		CCLOG("the pocker[%d] is %d, the number is %d and type is %d", i, pocker, num, type);
	}
}
void HelloWorld::preporePocker(Point position)
{
	initPocker();
	pockerNumSort(0, 13);
	pockerNumSort(14, 27);
	for (int i = 0; i < 28; i++)
	{
		pocker[i] = Pocker::createPocker(pockerNumber[i], Vec2(position.x + 12 * i, position.y), false);
		int tag = pocker[i]->number;
		pocker[i]->setTag(tag);
		addChild(pocker[i]);
	}
}
void HelloWorld::startDeal()
{
	// ������ʱ��
	schedule(schedule_selector(HelloWorld::dealUpdate), 0.2f);
}
void HelloWorld::dealUpdate(float dt)
{
	// idȡֵΪ0~13ʱ����ҷ���
	if (id < 14)
	{
		pocker[27 - id]->moveTo(Vec2(35 + 44 * id, 45), 0.2f);
		pocker[27 - id]->showFont();				// ��ʾ����
		player[0]->addPocker(27 - id);
		id++;
	}
	else if (id < 28)
	{	// �������ԡ�����
		pocker[27 - id]->moveTo(Vec2(35 + 44 * (id - 14), 315), 0.2f);
		player[1]->addPocker(27 - id);
		id++;
	}
	else
	{
		// ��idȡֵ���ڵ���28ʱ��˵�����������ȡ����ʱ��
		unschedule(schedule_selector(HelloWorld::dealUpdate));
		// ���������˵���ť
		auto* pButton1 = MenuItemImage::create("fangqi1.png",
			"fangqi2.png",
			this,
			menu_selector(HelloWorld::chupai));
		auto* button1 = Menu::create(pButton1, NULL);
		button1->setPosition(250, 120);
		addChild(button1);
		auto* pButton2 = MenuItemImage::create("chupai1.png",
			"chupai2.png",
			this,
			menu_selector(HelloWorld::chupai));
		auto* button2 = Menu::create(pButton2, NULL);
		button2->setPosition(390, 120);
		addChild(button2);

		delay = 30;
		scheduleUpdate();
		player[0]->status = 1;
	}
}
void HelloWorld::chupai(Object* pSender)
{
	/**
	//diannaoChupai();
	���ڶ�Player���еķ������в���
	for (int i = 0; i < 14; i++)
	{
		int id = player[0]->m_pocker[i];	// ��ȡֽ�Ƶ�����
		if (id != -1)
		{
			int number = pocker[id]->number;
			int value = number % 13;
			int type = number / 13;
			CCLOG("this is the %dth pocker,the value is %d and the type is %d...", i + 1, value, type);
		}
	}
	CCLOG("===================="); // ����һ�������ķָ���
	for (int i = 0; i < 14; i++)
	{
		int id = player[0]->m_pocker[i];	// ��ȡֽ�Ƶ�����
		if (pocker[id]->isSelected)
		{
			// ���ֽ�Ʊ�ѡ�У����Ƴ�
			player[0]->removePocker(id);
		}
		if (player[0]->m_pocker[i] != -1)
		{
			int number = pocker[id]->number;
			int value = number % 13;
			int type = number / 13;
			CCLOG("this is the %dth pocker,the value is %d and the type is %d...", i + 1, value, type);
		}
	}
	CCLOG("===================="); // ����һ�������ķָ���
	player[0]->updatePocker();
	for (int i = 0; i < 14; i++)
	{
		int id = player[0]->m_pocker[i];	// ��ȡֽ�Ƶ�����
		if (id != -1)
		{
			int number = pocker[id]->number;
			int value = number % 13;
			int type = number / 13;
			CCLOG("this is the %dth pocker,the value is %d and the type is %d...", i + 1, value, type);
		}
	}
	**/
	/**û�й����жϵ���ҳ���
	//��status��ֵΪ1ʱ����ʾ���Գ���
	if (player[0]->status == 1&& delay==0)
	{
		playerChupai(0);
		// �ֵ����Գ��ƣ���
		if (player[0]->status == 0)
		{
			// ���status���޸�Ϊ0��˵���������޸���˵�����Ի����Գ���
			player[1]->status = 1;
			delay = 200;
		}
	}
	**/
	bool isChupai = false;
	// ���ж��Ƿ�������ҳ���
	if (player[0]->status == 1 && delay == 0)
	{
		// ���жϵ�ǰ�Ĺ���rule�����rule=0���ʾ���Է�������
		if (rule==0)
		{
			// ���������
			isChupai = true;
		}
		else if (rule == 1)
		{
			// ��Ҫ���յ���֮ǰ���Ƶ�˳����ƣ�������ȷ���Գ��˼�����
			int count = player[1]->t_count;
			if (player[0]->t_count == count)
			{
				// ����ȷ����Ŀ����ͬ�ģ���ȷ��ֵ�Ƿ���ͬ
				if (count == 1)
				{
					// ֻ��һ����
					int number0 = pocker[player[1]->t_pocker[0]]->number;
					int number1 = pocker[player[0]->t_pocker[0]]->number;
					if (number0 % 13 < number1 % 13 || number1 > 51)
					{
						isChupai = true;
					}
				}
				else if (count == 2)
				{
					int number0 = pocker[player[1]->t_pocker[0]]->number;
					int number1 = pocker[player[0]->t_pocker[0]]->number;
					int number2 = pocker[player[0]->t_pocker[1]]->number;
					if (number1 % 13 == number2 % 13 && number1 % 13 > number0 % 13)
					{
						isChupai = true;
					}
				}
				else if (count == 3)
				{
					int number0 = pocker[player[1]->t_pocker[0]]->number;
					int number1 = pocker[player[0]->t_pocker[0]]->number;
					int number2 = pocker[player[0]->t_pocker[1]]->number;
					int number3 = pocker[player[0]->t_pocker[2]]->number;
					if (number1 % 13 == number2 % 13 && number3 % 13 == number2 % 13 && number1 % 13 > number0 % 13)
					{
						isChupai = true;
					}
				}
				else if (count == 4)
				{
					int number0 = pocker[player[1]->t_pocker[0]]->number;
					int number1 = pocker[player[0]->t_pocker[0]]->number;
					int number2 = pocker[player[0]->t_pocker[1]]->number;
					int number3 = pocker[player[0]->t_pocker[2]]->number;
					int number4 = pocker[player[0]->t_pocker[3]]->number;
					if (number1 % 13 == number2 % 13 && number3 % 13 == number2 % 13 && number3 % 13 == number4 % 13 && number1 % 13 > number0 % 13)
					{
						isChupai = true;
					}
				}
			}
		}
		// ��������жϿ��Գ���
		if (isChupai)
		{
			playerChupai(0);
			if (player[0]->status == 0)
			{
				// ���status���޸�Ϊ0��˵���������޸���˵�����Ի����Գ���
				player[1]->status = 1;
				delay = 200;
				rule = 0;
			}
		}
		else
		{
			for (int i = 0; i < 14; i++)
			{
				int id = player[0]->m_pocker[i];
				if (pocker[id]->isSelected)
				{
					pocker[id]->card->setPositionY(pocker[id]->card->getPositionY() - 10);
				}
			}
		}
	}
}
void HelloWorld::diannaoChupai()
{
	// Ĭ��ȡ��һ���ƣ�֮����ڴ˴����������жϳ���Щֽ�Ƶ��㷨
	if (player[1]->m_pocker[0] != -1)
	{
		// m_pocker[0] != -1˵�������������ֽ�ƣ�����ѡ��
		int id = player[1]->m_pocker[0];
		pocker[id]->isSelected = true;
	}
	playerChupai(1);
	/**
	bool isChupai = false;
	if (rule == 1)
	{
		// rule=1������һ����
		int id = rand() % (player[1]->count);
		if (id != -1)
		{
			pocker[id]->isSelected = true;
			isChupai = true;
		}
	}
	else if (rule == 0)
	{
		// ���ݳ����������з���
		if (player[0]->t_count == 1)
		{
			// ��������Ϊ1
			for (int i = 0; i < 14; i++)
			{
				int id0 = player[1]->m_pocker[27 - i];
				if (id0 != -1 && player[0]->t_pocker[0]!=-1)
				{
					int number0 = pocker[player[0]->t_pocker[0]]->number;
					int number1 = pocker[id0]->number;
					if (number1 % 13>number0 % 13)
					{
						pocker[id0]->isSelected = true;
						isChupai = true;
						break;
					}
				}
			}
		}
		else if (player[0]->t_count == 2)
		{
			// ��������Ϊ2
			for (int i = 0; i < 13; i++)
			{
				int id0 = player[1]->m_pocker[0];
				int number0 = pocker[id0]->number;
				int id1 = player[1]->m_pocker[27 - i];
				int number1 = pocker[id1]->number;
				int id2 = player[1]->m_pocker[27 - i - 1];
				int number2 = pocker[id2]->number;
				if (number2 % 13 == number1 % 13 && number0 % 13 < number2 % 13)
				{
					pocker[id1]->isSelected = true;
					pocker[id2]->isSelected = true;
					isChupai = true;
					break;
				}
			}
		}
		else if (player[0]->t_count == 3)
		{
			// ��������Ϊ3
			for (int i = 0; i < 12; i++)
			{
				int id0 = player[1]->m_pocker[0];
				int number0 = pocker[id0]->number;
				int id1 = player[1]->m_pocker[27 - i];
				int number1 = pocker[id1]->number;
				int id2 = player[1]->m_pocker[27 - i - 1];
				int number2 = pocker[id2]->number;
				int id3 = player[1]->m_pocker[27 - i - 2];
				int number3 = pocker[id3]->number;
				if (number2 % 13 == number1 % 13 && number2 % 13 == number3 % 13 && number0 % 13 < number2 % 13)
				{
					pocker[id1]->isSelected = true;
					pocker[id2]->isSelected = true;
					pocker[id3]->isSelected = true;
					isChupai = true;
					break;
				}
			}
		}
		else
		{
			// ��������Ϊ4
			for (int i = 0; i < 11; i++)
			{
				int id0 = player[1]->m_pocker[0];
				int number0 = pocker[id0]->number;
				int id1 = player[1]->m_pocker[27 - i];
				int number1 = pocker[id1]->number;
				int id2 = player[1]->m_pocker[27 - i - 1];
				int number2 = pocker[id2]->number;
				int id3 = player[1]->m_pocker[27 - i - 2];
				int number3 = pocker[id3]->number;
				int id4 = player[1]->m_pocker[27 - i - 3];
				int number4 = pocker[id4]->number;
				if (number2 % 13 == number1 % 13 && number2 % 13 == number3 % 13 && number4 % 13 == number3 % 13 && number0 % 13 < number2 % 13)
				{
					pocker[id1]->isSelected = true;
					pocker[id2]->isSelected = true;
					pocker[id3]->isSelected = true;
					pocker[id4]->isSelected = true;
					isChupai = true;
					break;
				}
			}
		}
	}
	if (isChupai)
	{
		playerChupai(1);
		if (player[1]->status == 0)
		{
			player[0]->status = 1;
			delay = 200;
			rule = 1;
		}
	}
	else
	{
		CCLOG("fangqi");
		player[1]->status = 0;
		player[0]->status = 1;
		rule = 0;
	}
	**/
}
void HelloWorld::playerChupai(int type)
{
	int d = 0;
	// �������ѡ�е�ֽ���Ƴ�
	for (int i = 0; i < 14; i++)
	{
		int id = player[type]->m_pocker[i];
		// ȷ��ֽ������Ч��
		if (id != -1)
		{
			CCLOG("%d:%d", i, id);
			if (pocker[id]->isSelected)
			{
				// ѭ�����е�����˵��ȷʵ�����˳��ƵĲ�����������Ϊ��������Ч�ģ���status��Ϊ0
				player[type]->status = 0;
				CCLOG("is chupai now........");
				if (type == 1)
				{
					// ���ڵ��Ե�ֽ����ʾ���Ǳ��棬��ͨ������showFont�����䷭����
					pocker[id]->showFont();
				}
				// ֽ���ƶ�
				pocker[id]->moveTo(Vec2(400 + 45 * d, 180), 1.2f);
				player[type]->removePocker(id);
				player[type]->addToHand(id);
				d++;			// ��������һ
			}
		}
	}
	// ����������е�ֽ��
	player[type]->updatePocker();
	for (int i = 0; i < 14; i++)
	{
		int id = player[type]->m_pocker[i];
		if (id != -1)
		{
			// ֽ������Ч�ģ���ʼλ��
			auto pos = Vec2(player[type]->m_pos.x + 44 * i, player[type]->m_pos.y);
			pocker[id]->moveTo(pos, 1.3f);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		int id0 = player[0]->t_pocker[i];
		int id1 = player[0]->t_pocker[i];
		if (id0 != -1)
		{
			pocker[id0]->card->setOpacity(0);
		}
		if (id1 != -1)
		{
			pocker[id1]->card->setOpacity(0);
		}
	}
	//player[(type + 1) % 2]->cleanHand();
}
void HelloWorld::update(float dt)
{
	if (delay > 0)
	{
		CCLOG("%fwaiting......", dt);
		delay--;
	}
	else
	{
		if (player[1]->status == 1)
		{
			// ����1����ʾ�Ѿ�Ϊ����״̬������
			diannaoChupai();
			// ����player[1]��status�����ж��Ƿ�ɹ����ƣ�������������ҳ���
			if (player[1]->status == 0)
			{
				player[0]->status = 1;
				delay = 200;
			}
		}
	}
}
void HelloWorld::wanjiaChupai()
{
	int d = 0;
	// �������ѡ�е�ֽ���Ƴ�
	for (int i = 0; i < 14; i++)
	{
		int id = player[0]->m_pocker[i];
		// ȷ��ֽ������Ч��
		if (id != -1)
		{
			CCLOG("%d:%d", i, id);
			if (pocker[id]->isSelected)
			{
				// ѭ�����е�����˵��ȷʵ�����˳��ƵĲ�����������Ϊ��������Ч�ģ���status��Ϊ0
				player[0]->status = 0;
				player[0]->addToHand(id);
				CCLOG("is chupai now........");
				// ֽ���ƶ�
				pocker[id]->moveTo(Vec2(400 + 45 * d, 180), 1.2f);
				player[0]->removePocker(id);
				d++;			// ��������һ
			}
		}
	}
	// ����������е�ֽ��
	player[0]->updatePocker();
	for (int i = 0; i < 14; i++)
	{
		int id = player[0]->m_pocker[i];
		if (id != -1)
		{
			// ֽ������Ч�ģ���ʼλ��
			auto pos = Vec2(player[0]->m_pos.x + 44 * i, player[0]->m_pos.y);
			pocker[id]->moveTo(pos, 1.3f);
		}
	}
}
