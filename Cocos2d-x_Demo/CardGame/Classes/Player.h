#ifndef _PLAYER_OBJECT_H_
#define _PLAYER_OBJECT_H_
#include "cocos2d.h"
#include "Pocker.h"
USING_NS_CC;
class Player :public Object
{
public:
	int count;								// ������е�ֽ����Ŀ
	int t_count;
	Point m_pos;							// ֽ�Ƴ�ʼλ��
	Player(int type);						// ʹ�ù��췽����ʼ�������
	void updatePocker();					// ����������е�ֽ��
	int m_pocker[14];						// ����������е�ֽ��
	int t_pocker[4];						// ������ҳ�����Щ��
	int type;								// ����������ͣ�0Ϊ���1Ϊ����
	int status;								// ��ʶ��ҵ�ǰ״̬
	void addPocker(int id);					// ����һ��ֽ��
	void removePocker(int id);		 		// �Ƴ�һ��ֽ��
	void addToHand(int id);					// ��һ��ֽ����������
	void cleanHand();						// ������е�ֽ��
};
#endif