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

#include "Receiver.h"

Define_Module(Receiver);

void Receiver::initialize()
{
    // TODO - Generated method body
    EV<<"Hello from Receiver Node"<<endl;
}

void Receiver::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    /*====================================================================================================*/
    //Step(1) Decompose Message
    std::string packet=msg->getName();
    //    int packet_size=packet.size();


     //Char_count
      std::bitset<8> char_count_header=std::bitset<8>(packet[0]-48);
      int char_count= packet[0]-48;

     //Pay_load
     std::vector<std::bitset<8> > payload(char_count-2); //each char is 1 byte
     std::string message="";
     for(int i=1;i<char_count-1;i++){
            //Add to pay load
            payload[i-1]=std::bitset<8>(packet[i]);
            message+=packet[i];
     }
     //Tailer
     std::bitset<8> parity_check=std::bitset<8>(packet[char_count-1]-48);

     /*====================================================================================================*/
     //Step(2) Check Errors
     std::bitset<8> parity_check_xor=parity_check;
     parity_check_xor^=char_count_header;
     for(int i=0;i<payload.size();i++){
         parity_check_xor^=std::bitset<8>(payload[i]);
     }

     bool error=parity_check_xor.to_ulong();
     if(!error){
         //no Error
         std::cout<<"I have Received Correct Message :) :"<<message<<endl;
     }
     else{
         std::cout<<"I have Received Wrong Message :("<<endl;
     }

     /*====================================================================================================*/
     //Step(3) Logging
     std::cout<<"Final Receiver parity_check:"<<parity_check_xor.to_string()<<endl;
//     if(!error){
//         std::cout<<"Header (Ch_Count):"<<char_count_header.to_string()<<endl;
//         std::cout<<"PayLoad:"<<endl;
//         for(int i=0;i<payload.size();i++){
//             std::cout<<"                  "<<payload[i].to_string()<<endl;
//         }
//         std::cout<<endl<<"Tailer (Parity):  "<<parity_check.to_string()<<endl<<endl;
//     }
     /*====================================================================================================*/
     //Step(4) Send A dummy Message to the receiver that you have received the message
     send(new cMessage (""),"out");
}
