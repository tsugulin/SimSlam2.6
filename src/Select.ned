simple Select
{
    parameters:
        volatile double productionTime1 @unit(s) = default(0);
        volatile double productionTime2 @unit(s) = default(0);
	gates:
        input in1;
        input in2;
        input in3;
        output out;
}