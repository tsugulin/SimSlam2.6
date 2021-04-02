#ifndef BLOCKINGQUEUE_H_
#define BLOCKINGQUEUE_H_

#include <omnetpp.h>
using namespace omnetpp;
#include "Wavg.h"
#define maxQnum 100

class Select;

class BlockingQueue : public cSimpleModule
{
  private:
    const char *qName;
    cQueue queue;
    Select *next;
    simtime_t lastTime;     // 最終シミュレーション時間の記録用
    cStdDev stats;
    Wavg qlen;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

  public:
    virtual bool check();
    virtual void dispatch(simtime_t t);
};

#endif /* BLOCKINGQUEUE_H_ */
