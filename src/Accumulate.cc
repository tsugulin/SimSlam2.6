// メッセージを指定個数受け取ったら，次にメッセ―市を送る

#include "Accumulate.h"
Define_Module(Accumulate);

void Accumulate::initialize()
{
    workUnit = par("workUnit");     // まとめる個数
    counter = 0;                    // カウンターを初期化
}

void Accumulate::handleMessage(cMessage *msg)
{
    // 届いたメッセージを数えて削除する
    delete msg;

    // 集約メッセージを作成
    if (counter++ == 0) {
        grpMsg = new cMessage("accumlater");
        grpMsg->setTimestamp(simTime());
    }

    // グループが揃ったら次工程に送る
    if (counter >= workUnit) {
        send(grpMsg, "out");
        stats.collect( simTime() - grpMsg->getTimestamp() );   // 経過時間を記録
        counter = 0;    // カウンターを初期化
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
