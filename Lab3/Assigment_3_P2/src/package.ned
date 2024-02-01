package lab03_p2;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    //    @display("bgb=474,328");            
    parameters:
        int N = default(5);
        @display("bgb=432,284");
    submodules:
        nodes[N]: Node;
    connections:
        for i=0..N-1 {
            nodes[i].out[0] --> nodes[(i+1)%N].in[0];
            nodes[(i+1)%N].out[1] --> nodes[i].in[1];
        }
}

