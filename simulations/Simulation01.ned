network Simulation01
{
    submodules:
        create: Create {
            parameters:
                @display("p=50,150;i=block/source");
        }
        accumulate: Accumulate {
            parameters:
                @display("p=150,150;i=block/join");
        }
        track: BlockingQueue {
            parameters:
                @display("p=250,50;i=block/boundedqueue;q=queue");
        }
        load: BlockingQueue {
                parameters:
                @display("p=250,150;i=block/boundedqueue;q=queue");
        }
        worker: BlockingQueue {
                parameters:
                @display("p=250,250;i=block/boundedqueue;q=queue");
        }
        select: Select {
            parameters:
                @display("p=350,150;i=block/fork");
        }
        process1: Process {
            parameters:
                @display("p=450,150;i=block/process");
        }
        process2: Process {
            parameters:
                @display("p=550,150;i=block/process");
        }
        process3: Process {
            parameters:
                @display("p=650,150;i=block/process");
        }
	connections:
        create.out --> accumulate.in;
        accumulate.out --> load.in;
        track.out --> select.in1;
        load.out --> select.in2;
        worker.out --> select.in3;
        select.out --> process1.in;
        process1.out --> process2.in;
        process1.res --> worker.in;
        process2.out --> process3.in;
        process3.res --> track.in;
}
