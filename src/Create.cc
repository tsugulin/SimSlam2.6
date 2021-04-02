// メッセージを指定個数，指定間隔にて生成する

#include "Create.h"
Define_Module(Create);

void Create::initialize()
{
    timeLimit = (simtime_t)par("timeLimit");     // メッセージの送信個数を初期設定
    beatMsg = new cMessage("beat"); // 繰り返し生成するメッセージを１つだけ生成
    scheduleAt(simTime(), beatMsg); // 最初のメッセージを自身に送信
}

void Create::handleMessage(cMessage *msg)
{
    // 次のモジュールにdataメッセージを送信．ただし送信個数の制限あり
    if (simTime() < timeLimit) {
        send(new cMessage("data"), "out");

        //　intervalTimeのピッチにてheartbeatメッセージを自身に送信する
        double d = par("intervalTime");
        stats.collect(d);
        scheduleAt(simTime() + d, msg);
    }
}

//　ノードの統計情報を表示
void Create::finish()
{
    EV << "Create Jobs Count:    " << stats.getCount() << endl;
    EV << "Create Jobs Min Time: " << stats.getMin() << endl;
    EV << "Create Jobs Avg Time: " << stats.getMean() << endl;
    EV << "Create Jobs Max Time: " << stats.getMax() << endl;
    EV << "Create Jobs SD:       " << stats.getStddev() << endl;
}
