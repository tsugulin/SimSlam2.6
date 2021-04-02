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
        // アクティビティの終了
        if ( strcmp(msg->getName(), workName) == 0 ) {
            // 製品を次工程に送る場合
            send(msg, "out");
            stats1.collect( simTime() - msg->getCreationTime() );
        }
        else {
            // リソースを戻す場合
            send(msg, "res");
            stats2.collect( simTime() - msg->getCreationTime() );
        }
    }
    else {
        // 届いたメッセージを削除
        delete msg;

        // 物流のアクティビティの開始
        double d1 = par("productionTime1");             // アクティビティ時間
        if (d1 > 0) {
            cMessage *msg = new cMessage(workName);     // メッセージを作成
            scheduleAt(simTime() + d1, msg);
        }

        // リソースのアクティビティの処理
        double d2 = par("productionTime2");             // アクティビティ時間
        if (d2 > 0) {
            cMessage *msg = new cMessage(subworkName);  // リソース用メッセージを作成
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
