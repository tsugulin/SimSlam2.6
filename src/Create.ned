simple Create
{
    parameters:
        double timeLimit @unit(s) = default(0);
        volatile double intervalTime @unit(s) = default(0);
    gates:
        output out;
}