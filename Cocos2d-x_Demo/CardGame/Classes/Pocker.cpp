#include "Pocker.h"
USING_NS_CC;
Pocker* Pocker::createPocker(int number, Point position, bool isFont)
{
	Pocker* pocker = Pocker::create();
	if (pocker)
	{
		pocker->initPocker(number, position, isFont);
		return pocker;
	}
	CC_SAFE_DELETE(pocker);
	return NULL;
}
void Pocker::initPocker(int number, Point position, bool isFont)
{
	this->isSelected = false;
	this->number = number;
	// ������������
	card = Sprite::create(String::createWithFormat("%d.jpg",number)->getCString());
	card->setScale(0.4f);
	card->setPosition(position);
	addChild(card);
	// ���Ʊ���
	back = Sprite::create("card.png");
	auto cardSize = card->getContentSize();
	back->setPosition(cardSize.width / 2, cardSize.height / 2);
	// ���ݲ���isFont���ж���ʾֽ�Ƶ����滹�Ǳ���
	if (!isFont)
	{
		isActive = false;
	}
	else
	{
		back->setOpacity(0);
		this->isActive = true;
	}
	card->addChild(back);

	// �����¼��İ�
	listener = EventListenerTouchOneByOne::create();//�������㴥���¼�������
	listener->onTouchBegan = CC_CALLBACK_2(Pocker::onTouchBegan, this);//������ʼ
	listener->setSwallowTouches(true);//�������̲�����
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
bool Pocker::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	auto point = pTouch->getLocation();
	auto position = this->card->getPosition();
	// �ж�����һ��ֽ�Ʊ����
	if (point.x > position.x - CARDX&&point.x<position.x + CARDX&&point.y>position.y - CARDY&&point.y < position.y + CARDY)
	{
		// ȷ����ǰֽ��Ϊ������ʾ
		if (this->isActive)
		{
			// �ж�ֽ�ƽ��������еĲ���
			if (this->isSelected)
			{
				this->card->setPositionY(position.y - 10);
				this->isSelected = false;
			}
			else
			{
				this->card->setPositionY(position.y + 10);
				this->isSelected = true;
			}
		}
	}
	return false;
}
void Pocker::setTouchPriority(int num){
	_eventDispatcher->setPriority(listener, num);
}
void Pocker::showLast()
{
	if (isActive)
	{
		back->setOpacity(255);
		this->isActive = false;
	}
}
void Pocker::showFont()
{
	if (!isActive)
	{
		back->setOpacity(0);
		this->isActive = true;
	}
}
void Pocker::moveTo(Point des, float time)
{
	auto* moveto = MoveTo::create(time,Vec3(des.x,des.y,card->getPositionZ()));
	card->runAction(moveto);
}