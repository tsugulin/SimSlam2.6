// ���b�Z�[�W���w����󂯎������C���Ƀ��b�Z�\�s�𑗂�

#include "Accumulate.h"
Define_Module(Accumulate);

void Accumulate::initialize()
{
    workUnit = par("workUnit");     // �܂Ƃ߂��
    counter = 0;                    // �J�E���^�[��������
}

void Accumulate::handleMessage(cMessage *msg)
{
    // �͂������b�Z�[�W�𐔂��č폜����
    delete msg;

    // �W�񃁃b�Z�[�W���쐬
    if (counter++ == 0) {
        grpMsg = new cMessage("accumlater");
        grpMsg->setTimestamp(simTime());
    }

    // �O���[�v���������玟�H���ɑ���
    if (counter >= workUnit) {
        send(grpMsg, "out");
        stats.collect( simTime() - grpMsg->getTimestamp() );   // �o�ߎ��Ԃ��L�^
        counter = 0;    // �J�E���^�[��������
    }
}

void Accumulate::finish()
{
    EV << "Loading jobs Count:        " << stats.getCount() << endl;
    EV << "Loading jobs Min leadtime: " << stats.getMin() << endl;
    EV << "Loading jobs Avg leadtime: " << stats.getMean() << endl;
    EV << "Loading jobs Max leadtime: " << stats.getMax() << endl;
    EV << "Loading jobs SD:           " << stats.getStddev() << endl;
}
