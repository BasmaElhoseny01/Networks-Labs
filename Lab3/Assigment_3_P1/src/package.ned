package assigment_3_p1;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    parameters:
        int N = default(4);
        double interval=exponential(2.0);
        @display("p=310,104");
    submodules:
        hub: Hub {
//            @display("p=237,65");
        }
        nodes[N]: Node {
//            @display("p=310,104");
        }
    connections:
        for i=0..N-1{
            hub.out++-->nodes[i].in;
            hub.in++<--nodes[i].out;
        }
}

