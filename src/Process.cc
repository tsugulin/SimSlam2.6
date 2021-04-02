//

#include "Process.h"
Define_Module(Process);
#include "BlockingQueue.h"

void Process::initialize()
{
    workName = par("workName");
    subworkName = par("subworkName");
}

void Process::handleMessage(cMessage *msg)
{
    if ( msg->isSelfMessage() ) {
        // �A�N�e�B�r�e�B�̏I��
        if ( strcmp(msg->getName(), workName) == 0 ) {
            // ���i�����H���ɑ���ꍇ
            send(msg, "out");
            stats1.collect( simTime() - msg->getCreationTime() );
        }
        else {
            // ���\�[�X��߂��ꍇ
            send(msg, "res");
            stats2.collect( simTime() - msg->getCreationTime() );
        }
    }
    else {
        // �͂������b�Z�[�W���폜
        delete msg;

        // �����̃A�N�e�B�r�e�B�̊J�n
        double d1 = par("productionTime1");             // �A�N�e�B�r�e�B����
        if (d1 > 0) {
            cMessage *msg = new cMessage(workName);     // ���b�Z�[�W���쐬
            scheduleAt(simTime() + d1, msg);
        }

        // ���\�[�X�̃A�N�e�B�r�e�B�̏���
        double d2 = par("productionTime2");             // �A�N�e�B�r�e�B����
        if (d2 > 0) {
            cMessage *msg = new cMessage(subworkName);  // ���\�[�X�p���b�Z�[�W���쐬
            scheduleAt(simTime() + d2, msg);
        }
    }
}

void Process::finish()
{
    EV << workName << " jobs Count:        " << stats1.getCount() << endl;
    EV << workName << " jobs Min leadtime: " << stats1.getMin() << endl;
    EV << workName << " jobs Avg leadtime: " << stats1.getMean() << endl;
    EV << workName << " jobs Max leadtime: " << stats1.getMax() << endl;
    EV << workName << " jobs SD:           " << stats1.getStddev() << endl;
    EV << subworkName << " jobs Count:        " << stats2.getCount() << endl;
    EV << subworkName << " jobs Min leadtime: " << stats2.getMin() << endl;
    EV << subworkName << " jobs Avg leadtime: " << stats2.getMean() << endl;
    EV << subworkName << " jobs Max leadtime: " << stats2.getMax() << endl;
    EV << subworkName << " jobs SD:           " << stats2.getStddev() << endl;
}
