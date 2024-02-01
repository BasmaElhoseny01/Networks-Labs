package assigment_2;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    @display("bgb=257,206");
    submodules:
        player1: Player1 {
            @display("p=45,79");
        }
        player2: Player2 {
            @display("p=203,79");
        }
    connections:
        player1.out --> player2.in;
        player2.out --> player1.in;
}

