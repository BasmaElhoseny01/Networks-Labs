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

#include "Node.h"

Define_Module(Node);

void Node::initialize()
{
    // TODO - Generated method body
    if(strcmp(this->getName(),"Tic")==0){
        // Init for Tic to send Tic_0
        cMessage *msg=new cMessage("Tic_0");
        send(msg,"out");
        EV<<"Sending"<<*msg<<" ..."<<endl;
    }
}

void Node::handleMessage(cMessage *msg){
    // TODO - Generated method body
    char i=msg->getName()[4];
    int index=  i - '0';
    EV<<"Index"<<index<<endl;
    if(index!=9){
        //Tic
        if(strcmp(this->getName(),"Tic")==0){
            std::string messageName = "Tic_" + std::to_string(index+1);
            cMessage *send_msg=new cMessage(messageName.c_str());
            send(send_msg,"out");
            EV<<"Sending"<<*send_msg<<" ..."<<endl;
        }
        //Toc
        else if(strcmp(this->getName(),"Toc")==0){
            std::string messageName = "Toc_" + std::to_string(index+1);
            cMessage *send_msg=new cMessage(messageName.c_str());
            send(send_msg,"out");
            EV<<"Sending"<<*send_msg<<" ..."<<endl;
        }
    }
    // End message has been reached
    else{
       EV<<"End of sending ..."<<endl;
    }
}

void Node::finish()
{
  EV<<"End of Simulation"<<endl;
}
