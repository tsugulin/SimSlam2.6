// 初期値のある待ち行列

#include "BlockingQueue.h"
Define_Module(BlockingQueue);
#include "Select.h"

void BlockingQueue::initialize()
{
    // キューの初期化．指定された名前のメッセージを指定個数だけキューに入れる
    queue.setName("queue");             // GUIに待ち行列長さを表示するための名前
    qName = par("qName");               // 待ち行列の名前
    int imax = par("initialQnum");
    for (int i = 0;  i < imax;  i++)
        queue.insert(new cMessage(qName));

    // 待ち行列の平均長さを計算するクラスを初期化
    qlen.init(simTime(), maxQnum);

    // Selectノードのポインタを取得
    cModule *mod = gate("out")->getNextGate()->getOwnerModule();
    next = check_and_cast<Select *>(mod);
}

void BlockingQueue::handleMessage(cMessage *msg)
{
    msg->setTimestamp(simTime());           // リードタイムの開始時間をセット
    qlen.set(simTime(), queue.getLength()); // 待ち行列長さを集計
    queue.insert(msg);                      // 待ち行列にメッセージを保管
    next->request();                        // 次工程を呼び出し
}

// 待ち行列があるならばTrueを返す
bool BlockingQueue::check()
{
    Enter_Method("check");
    return (queue.getLength() > 0) ? true: false;
}

// 待ち行列があるならば統計情報をとって削除する
void BlockingQueue::dispatch(simtime_t t)
{
    Enter_Method("dispatch");

    // 最終実行時刻の記録
    lastTime = t;

    if (queue.getLength() > 0) {    // 在庫が在れば
        qlen.set(simTime(), queue.getLength());                     // 待ち行列長さの加重平均値の計算
        cMessage *msg = check_and_cast<cMessage *>(queue.pop());    // 待ち行列先頭のメッセージを取り出す
        stats.collect(simTime() - msg->getTimestamp());             // 滞留時間の統計情報を保管
        delete msg;                 // メッセージは削除
    }
}

//　ノードの統計情報を表示
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
