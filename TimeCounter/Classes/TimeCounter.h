#ifndef TimeCounter_H
#define TimeCounter_H

#include "cocos2d.h"
USING_NS_CC;

class TimeCounter : public Node
{
public:
    CREATE_FUNC(TimeCounter);
    virtual bool init();

    virtual void update(float dt);

    void start();           /* ��ʼ��ʱ */
    float getfCurTime();    /* ��ȡ��ǰʱ�� */

private:
    float m_fTime;
};

#endif