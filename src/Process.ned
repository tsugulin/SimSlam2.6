simple Process
{
    parameters:
        string workName;
        string subworkName;
        volatile double productionTime1 @unit(s) = default(0);
        volatile double productionTime2 @unit(s) = default(0);
    	gates:
        input in;
        output out @loose;
        output res @loose;
}
