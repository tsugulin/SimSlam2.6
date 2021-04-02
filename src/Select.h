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
    bool onLoading1;        // 1号機を利用中
    bool onLoading2;        // 2号機を利用中
    simtime_t loader1;      // 1号機の利用終了時刻
    simtime_t loader2;      // 2号機の利用終了時刻
    cStdDev stats1;
    cStdDev stats2;
    simtime_t lastTime;     // 最終シミュレーション時間の記録用

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

public:
  virtual void request();
};

#endif /* SELECT_H_ */
