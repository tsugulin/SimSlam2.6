simple BlockingQueue
{
    parameters:
        string qName;
        int initialQnum = default(0);
    gates:
        input in;
        output out;
}
