// ���b�Z�[�W���w����C�w��Ԋu�ɂĐ�������

#include "Create.h"
Define_Module(Create);

void Create::initialize()
{
    timeLimit = (simtime_t)par("timeLimit");     // ���b�Z�[�W�̑��M���������ݒ�
    beatMsg = new cMessage("beat"); // �J��Ԃ��������郁�b�Z�[�W���P��������
    scheduleAt(simTime(), beatMsg); // �ŏ��̃��b�Z�[�W�����g�ɑ��M
}

void Create::handleMessage(cMessage *msg)
{
    // ���̃��W���[����data���b�Z�[�W�𑗐M�D���������M���̐�������
    if (simTime() < timeLimit) {
        send(new cMessage("data"), "out");

        //�@intervalTime�̃s�b�`�ɂ�heartbeat���b�Z�[�W�����g�ɑ��M����
        double d = par("intervalTime");
        stats.collect(d);
        scheduleAt(simTime() + d, msg);
    }
}

//�@�m�[�h�̓��v����\��
void Create::finish()
{
    EV << "Create Jobs Count:    " << stats.getCount() << endl;
    EV << "Create Jobs Min Time: " << stats.getMin() << endl;
    EV << "Create Jobs Avg Time: " << stats.getMean() << endl;
    EV << "Create Jobs Max Time: " << stats.getMax() << endl;
    EV << "Create Jobs SD:       " << stats.getStddev() << endl;
}
