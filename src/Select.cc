// 三つの待ち行列の準備が出来たらジョブを行う

#include "Select.h"
Define_Module(Select);
#include "BlockingQueue.h"

void Select::initialize()
{
    // 変数初期化
    onLoading1 = false;
    onLoading2 = false;

    // BlockingQueueノードのポインタを取得
    cModule *mod1 = gate("in1")->getPreviousGate()->getOwnerModule();
    cModule *mod2 = gate("in2")->getPreviousGate()->getOwnerModule();
    cModule *mod3 = gate("in3")->getPreviousGate()->getOwnerModule();
    before1 = check_and_cast<BlockingQueue *>(mod1);
    before2 = check_and_cast<BlockingQueue *>(mod2);
    before3 = check_and_cast<BlockingQueue *>(mod3);
}

// 積込アクティビティの終了
void Select::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        if (strcmp(msg->getName(), "loading1") == 0) {
            onLoading1 = false;     // 積込機1の利用終了
            loader1 = simTime();    // 利用終了時刻
            stats1.collect(simTime() - msg->getCreationTime()); // 稼働時間を記録
        }
        else {
            onLoading2 = false;     // 積込機2の利用終了
            loader2 = simTime();    // 利用終了時刻
            stats2.collect(simTime() - msg->getCreationTime()); // 稼働時間を記録
        }
        send(msg, "out");
    }
}

// 全ての待ち行列の準備が出来ていれば，積込作業を行う
void Select::request()
{
    Enter_Method("request");

    // シミュレーション終了時刻を記録
    lastTime = simTime();

    // 全ての待ち行列の準備が出来ていることを確認
    if ( !before1->check() )  return;
    if ( !before2->check() )  return;
    if ( !before3->check() )  return;

    // 待ち行列の在庫を減らす
    before1->dispatch(lastTime);
    before2->dispatch(lastTime);
    before3->dispatch(lastTime);

    // 待ち時間が長い方の積込機を利用して積込作業を行う
    if (!onLoading1 && loader1 < loader2) {     // 積込機1の待ち時間が長い
        onLoading1 = true;
        cMessage *msg = new cMessage("loading1");   // メッセージを生成
        scheduleAt(simTime() + par("productionTime1"), msg);
    }
    else if (!onLoading2) {         // もし積込機2が未使用ならば
        onLoading2 = true;
        cMessage *msg = new cMessage("loading2");   // メッセージを生成
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
