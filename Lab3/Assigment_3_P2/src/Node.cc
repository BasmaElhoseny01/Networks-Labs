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
    int indx = getIndex();
    EV << "Starting Node " << indx << endl;

    if(indx == 0)
    {
        indx++;
        cMessage* msg = new cMessage(std::to_string(indx).c_str());
        send(msg, "out", 0);
    }
}

void Node::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    int indx = getIndex();
    if(indx == 0)
    {
        EV << "Number of nodes: " << msg->getName() << endl;
        return;
    }
    int i = std::stoi(msg->getName());
    i++;
    msg->setName(std::to_string(i).c_str());
    send(msg, "out", 0);
}
