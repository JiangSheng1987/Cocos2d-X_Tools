#include "Player.h"
USING_NS_CC;
Player::Player(int type)
{
	count = 0;
	t_count = 0;
	this->status = 0;		// 0ΪĬ��״̬
	this->type = type;
	for (int i = 0; i < 14; i++)
	{
		m_pocker[i] = -1;	// -1��ʶΪ��
	}
	for (int i = 0; i < 4; i++)
	{
		t_pocker[i] = -1;
	}
	if (type == 0)
	{
		m_pos = Vec2(35, 45);
	}
	else
	{
		m_pos = Vec2(35, 315);
	}         
}
void Player::addPocker(int id)
{
	if (count <= 14)
	{
		// ��ҳ���ֽ�Ƶ��������Ϊ14
		m_pocker[count] = id;
		count++;
	}
}
void Player::removePocker(int id)
{
	// ������������ҵ���id��ֵ
	for (int i = 0; i < 14; i++)
	{
		if (m_pocker[i] == id)
		{
			m_pocker[i] = -1;
		}
	}
}
void Player::updatePocker()
{
	for (int i = 1; i < 14; i++)
	{
		// ��m_pocker����ĵ�2��Ԫ�ؿ�ʼ����
		if (m_pocker[i] >= 0)
		{
			for (int j = 0; j < i; j++)
			{
				if (m_pocker[j] == -1)
				{
					// ����ҵ��հ׵�ֽ��λ
					m_pocker[j] = m_pocker[i];
					m_pocker[i] = -1;
				}
			}
		}
	}
}
void Player::addToHand(int id)
{
	// �ж�����t_pocker�Ƿ�������
	if (t_count >= 0 && t_count < 4)
	{
		t_pocker[t_count] = id;
	}
	t_count++;
}
void Player::cleanHand()
{
	// ѵ���������t_pocker�е�ֽ��
	for (int i = 0; i < t_count; i++)
	{
		t_pocker[i] = -1;
	}
	t_count = 0;
}
