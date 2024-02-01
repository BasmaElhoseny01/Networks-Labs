//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Hub.h"

Define_Module(Hub);

void Hub::initialize()
{
    // TODO - Generated method body
    //Send [now] Self Message to send the first message to the first random node node_n
    scheduleAt(simTime(),new cMessage(""));
}

void Hub::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(msg->isSelfMessage()){
        // Handle Self Messaging
        //1. Set Content of the message
        msg->setName("Hello from Hub");
        //2. Choose new Random Node
        int new_node=par("node_n");
        //3. Send message to the Node
        send(msg,"out",new_node);
        EV<<"Hub: Sending to Node ("<<int(par("node_n"))<<") ..."<<endl;
    }
    else{
        //Handle Message from the previous Node
        //Schedule [after the interval set by the network] next Message
        scheduleAt(simTime()+ getParentModule()->par("interval"),new cMessage(""));
    }
}
