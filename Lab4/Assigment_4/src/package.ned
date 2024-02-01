package assigment_4;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    @display("bgb=447,323");
    submodules:
        sender: Sender {
            @display("p=105,77");
        }
        receiver: Receiver {
            @display("p=300,77");
        }
    connections:
        sender.out --> receiver.in;
        receiver.out --> sender.in;
}

