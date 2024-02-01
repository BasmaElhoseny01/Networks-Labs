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
#include "Player1.h"

Define_Module(Player1);

void Player1::initialize()
{
    // TODO - Generated method body
    //Hello Message
    EV<<"Player (1): Hello I am Player 1"<<endl;

    //Player 1 chooses a random number
    EV<<"Player(1): The Number is "<<par("number").intValue()<<endl;

    //Send Hello Message to Player 2 so that he starts guessing
    cMessage *msg=new cMessage("Guess My Number :D");
    send(msg,"out");
    EV<<"Player(1): "<<msg->getName()<<endl;
}

void Player1::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
//    Check Player 2 Guess
    if(atoi(msg->getName())!=par("number").intValue()){
        //Wrong Guess
        EV<<"Player(1): Wrong guess :("<<endl;
        msg->setName("wrong guess");
    }
    else {
        //right guess
        EV<<"Player(1): Right guess :)"<<endl;
        msg->setName("correct guess");
    }
    send(msg,"out");

}
