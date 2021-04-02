#ifndef SELECT_H_
#define SELECT_H_

#include <omnetpp.h>
using namespace omnetpp;

class BlockingQueue;

class Select : public cSimpleModule {
private:
    BlockingQueue *before1;
    BlockingQueue *before2;
    BlockingQueue *before3;
    bool onLoading1;        // 1���@�𗘗p��
    bool onLoading2;        // 2���@�𗘗p��
    simtime_t loader1;      // 1���@�̗��p�I������
    simtime_t loader2;      // 2���@�̗��p�I������
    cStdDev stats1;
    cStdDev stats2;
    simtime_t lastTime;     // �ŏI�V�~�����[�V�������Ԃ̋L�^�p

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

public:
  virtual void request();
};

#endif /* SELECT_H_ */
