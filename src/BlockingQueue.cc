// �����l�̂���҂��s��

#include "BlockingQueue.h"
Define_Module(BlockingQueue);
#include "Select.h"

void BlockingQueue::initialize()
{
    // �L���[�̏������D�w�肳�ꂽ���O�̃��b�Z�[�W���w��������L���[�ɓ����
    queue.setName("queue");             // GUI�ɑ҂��s�񒷂���\�����邽�߂̖��O
    qName = par("qName");               // �҂��s��̖��O
    int imax = par("initialQnum");
    for (int i = 0;  i < imax;  i++)
        queue.insert(new cMessage(qName));

    // �҂��s��̕��ϒ������v�Z����N���X��������
    qlen.init(simTime(), maxQnum);

    // Select�m�[�h�̃|�C���^���擾
    cModule *mod = gate("out")->getNextGate()->getOwnerModule();
    next = check_and_cast<Select *>(mod);
}

void BlockingQueue::handleMessage(cMessage *msg)
{
    msg->setTimestamp(simTime());           // ���[�h�^�C���̊J�n���Ԃ��Z�b�g
    qlen.set(simTime(), queue.getLength()); // �҂��s�񒷂����W�v
    queue.insert(msg);                      // �҂��s��Ƀ��b�Z�[�W��ۊ�
    next->request();                        // ���H�����Ăяo��
}

// �҂��s�񂪂���Ȃ��True��Ԃ�
bool BlockingQueue::check()
{
    Enter_Method("check");
    return (queue.getLength() > 0) ? true: false;
}

// �҂��s�񂪂���Ȃ�Γ��v�����Ƃ��č폜����
void BlockingQueue::dispatch(simtime_t t)
{
    Enter_Method("dispatch");

    // �ŏI���s�����̋L�^
    lastTime = t;

    if (queue.getLength() > 0) {    // �݌ɂ��݂��
        qlen.set(simTime(), queue.getLength());                     // �҂��s�񒷂��̉��d���ϒl�̌v�Z
        cMessage *msg = check_and_cast<cMessage *>(queue.pop());    // �҂��s��擪�̃��b�Z�[�W�����o��
        stats.collect(simTime() - msg->getTimestamp());             // �ؗ����Ԃ̓��v����ۊ�
        delete msg;                 // ���b�Z�[�W�͍폜
    }
}

//�@�m�[�h�̓��v����\��
void BlockingQueue::finish()
{
    EV << qName << " AVG Length: " << qlen.get(lastTime) << endl;
    EV << qName << " Jobs Count: " << stats.getCount() << endl;
    EV << qName << " Min Time:   " << stats.getMin() << endl;
    EV << qName << " Avg Time:   " << stats.getMean() << endl;
    EV << qName << " Max Time:   " << stats.getMax() << endl;
    EV << qName << " SD:         " << stats.getStddev() << endl;
    EV << qName << " Utilization " << stats.getSum() / lastTime << endl;
}
