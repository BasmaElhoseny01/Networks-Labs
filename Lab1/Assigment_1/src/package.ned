package assigment_1;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    @display("bgb=417,130");
    submodules:
        Tic: Node {
            @display("p=84,50");
        }
        Toc: Node {
            @display("p=255,50");
        }
    connections:
        Tic.out --> Toc.in;
        Toc.out --> Tic.in;
}

