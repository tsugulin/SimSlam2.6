#ifndef PROCESS_H_
#define PROCESS_H_

#include <omnetpp.h>
using namespace omnetpp;

class Process : public cSimpleModule {
private:
    const char *workName;
    const char *subworkName;
    cStdDev stats1;
    cStdDev stats2;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

#endif /* PROCESS_H_ */
