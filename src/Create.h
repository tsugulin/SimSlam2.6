#ifndef CREATE_H_
#define CREATE_H_

#include <omnetpp.h>
using namespace omnetpp;

class Create : public cSimpleModule {
private:
  simtime_t timeLimit;  // ��������
  cMessage *beatMsg;    // �J��Ԃ����p���郁�b�Z�[�W���P�����쐬
  cStdDev stats;        // ���M�s�b�`�̓��v���L�^

protected:
  virtual void initialize();
  virtual void handleMessage(cMessage *msg);
  virtual void finish();
};

#endif /* CREATE_H_ */
