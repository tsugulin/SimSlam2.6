#ifndef CREATE_H_
#define CREATE_H_

#include <omnetpp.h>
using namespace omnetpp;

class Create : public cSimpleModule {
private:
  simtime_t timeLimit;  // 制限時間
  cMessage *beatMsg;    // 繰り返し利用するメッセージを１つだけ作成
  cStdDev stats;        // 送信ピッチの統計を記録

protected:
  virtual void initialize();
  virtual void handleMessage(cMessage *msg);
  virtual void finish();
};

#endif /* CREATE_H_ */
