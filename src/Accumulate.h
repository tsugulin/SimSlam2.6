#ifndef ACCUMULATE_H_
#define ACCUMULATE_H_

#include <omnetpp.h>
using namespace omnetpp;

class Accumulate : public cSimpleModule {
private:
    int workUnit;
    int counter;
    cMessage *grpMsg;
    cStdDev stats;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

#endif /* ACCUMULATE_H_ */
