// �O�̑҂��s��̏������o������W���u���s��

#include "Select.h"
Define_Module(Select);
#include "BlockingQueue.h"

void Select::initialize()
{
    // �ϐ�������
    onLoading1 = false;
    onLoading2 = false;

    // BlockingQueue�m�[�h�̃|�C���^���擾
    cModule *mod1 = gate("in1")->getPreviousGate()->getOwnerModule();
    cModule *mod2 = gate("in2")->getPreviousGate()->getOwnerModule();
    cModule *mod3 = gate("in3")->getPreviousGate()->getOwnerModule();
    before1 = check_and_cast<BlockingQueue *>(mod1);
    before2 = check_and_cast<BlockingQueue *>(mod2);
    before3 = check_and_cast<BlockingQueue *>(mod3);
}

// �ύ��A�N�e�B�r�e�B�̏I��
void Select::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        if (strcmp(msg->getName(), "loading1") == 0) {
            onLoading1 = false;     // �ύ��@1�̗��p�I��
            loader1 = simTime();    // ���p�I������
            stats1.collect(simTime() - msg->getCreationTime()); // �ғ����Ԃ��L�^
        }
        else {
            onLoading2 = false;     // �ύ��@2�̗��p�I��
            loader2 = simTime();    // ���p�I������
            stats2.collect(simTime() - msg->getCreationTime()); // �ғ����Ԃ��L�^
        }
        send(msg, "out");
    }
}

// �S�Ă̑҂��s��̏������o���Ă���΁C�ύ���Ƃ��s��
void Select::request()
{
    Enter_Method("request");

    // �V�~�����[�V�����I���������L�^
    lastTime = simTime();

    // �S�Ă̑҂��s��̏������o���Ă��邱�Ƃ��m�F
    if ( !before1->check() )  return;
    if ( !before2->check() )  return;
    if ( !before3->check() )  return;

    // �҂��s��̍݌ɂ����炷
    before1->dispatch(lastTime);
    before2->dispatch(lastTime);
    before3->dispatch(lastTime);

    // �҂����Ԃ��������̐ύ��@�𗘗p���Đύ���Ƃ��s��
    if (!onLoading1 && loader1 < loader2) {     // �ύ��@1�̑҂����Ԃ�����
        onLoading1 = true;
        cMessage *msg = new cMessage("loading1");   // ���b�Z�[�W�𐶐�
        scheduleAt(simTime() + par("productionTime1"), msg);
    }
    else if (!onLoading2) {         // �����ύ��@2�����g�p�Ȃ��
        onLoading2 = true;
        cMessage *msg = new cMessage("loading2");   // ���b�Z�[�W�𐶐�
        scheduleAt(simTime() + par("productionTime2"), msg);
    }
}

void Select::finish()
{
    EV << "Loader1 jobs Count:        " << stats1.getCount() << endl;
    EV << "Loader1 jobs Min leadtime: " << stats1.getMin() << endl;
    EV << "Loader1 jobs Avg leadtime: " << stats1.getMean() << endl;
    EV << "Loader1 jobs Max leadtime: " << stats1.getMax() << endl;
    EV << "Loader1 jobs SD:           " << stats1.getStddev() << endl;
    EV << "Loader1 Utilization:       " << stats1.getSum() / lastTime << endl;
    EV << "Loader2 jobs Count:        " << stats2.getCount() << endl;
    EV << "Loader2 jobs Min leadtime: " << stats2.getMin() << endl;
    EV << "Loader2 jobs Avg leadtime: " << stats2.getMean() << endl;
    EV << "Loader2 jobs Max leadtime: " << stats2.getMax() << endl;
    EV << "Loader2 jobs SD:           " << stats2.getStddev() << endl;
    EV << "Loader2 Utilization:       " << stats2.getSum() / lastTime << endl;
}
