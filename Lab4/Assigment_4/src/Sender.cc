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

#include "Sender.h"

Define_Module(Sender);

void Sender::initialize()
{
    // TODO - Generated method body
    //Hello
    EV<<"Hello from Sender Node"<<endl;

    //Self-Message
    scheduleAt(simTime(),new cMessage("")); // Send Now :D
}

void Sender::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(msg->isSelfMessage()){
        // Handle of Self Messaging

        /*====================================================================================================*/
        //Step (1):Takes Input From The user
        std::string message;
        std::cout<<"Enter Word"<<endl;
        std::cin>>message;
        std::cout<<"You entered "<<message<<std::endl;
        int char_count=message.size();
        if(message=="end_of_debug")return;

        /*====================================================================================================*/
        //Step(2): Processing Message
        std::cout<<"Sending..."<<endl;
        std::vector<std::bitset<8> > packet(char_count+2); //each char is 1 byte

        //Calculate character count
        packet[0]=std::bitset<8>(char_count+2);//No of chars+1 for count_header +1 for parity

        //Even Parity Check
        std::bitset<8> parity_check=packet[0];


       //Pay_load
        for(int i=0;i<char_count;i++){
            //Add to pay load
            packet[i+1]=std::bitset<8>(message[i]);

            //Add to Parity
            parity_check^=packet[i+1];
        }

        //Update Tailer
        packet[char_count+1]=parity_check;

        /*====================================================================================================*/
        //Step(3) Adding Noise
        double error = par("error");
        bool error_msg=false;
        int error_bit, byte_no,indx;
        if(error>0.5){
            //set error
            cPar& msg_len_par = par("msg_len"); //update with the current message length
            msg_len_par.setIntValue(char_count+2);
            //bit to toggle
            error_bit=par("error_bit");

            byte_no=error_bit/8;
            indx=error_bit-8*byte_no;
            //Negation
            packet[byte_no][indx]=~ packet[byte_no][indx];

            error_msg=true;
        }

        /*====================================================================================================*/
        //Step(4) Sending Message
        std::string packet_str="";
        std::string msg_str="";
        //Char_Count
        packet_str+=(char)(packet[0].to_ulong()+48);

        //Pay_load
        for(int i=0;i<char_count;i++){
            msg_str+= (char)packet[i+1].to_ulong();
        }
        packet_str+=msg_str;

        //Parity
        packet_str+=(char)(packet[char_count+1].to_ulong()+48);

        //Set Content of the message
        send(new cMessage (packet_str.c_str()),"out");

        /*====================================================================================================*/
        //Step(5) Logging
        if(!error_msg){
            std::cout<<"Sender:"<<"Message Sent without Error :D"<<endl;
        }
        else{
            std::cout<<"Sender:"<<"Message Sent with Error :D at bit("<<error_bit<<") [bit no("<<indx<<")in byte ("<<byte_no+1<<")]"<<endl;
        }
        std::cout<<"Message:"<<msg_str<<endl;
        std::cout<<"Header (Ch_Count):"<<packet[0].to_string()<<endl;
        std::cout<<"PayLoad:"<<endl;
        for(int i=0;i<char_count;i++){
            std::cout<<"                  "<<packet[i+1].to_string()<<endl;
        }
        std::cout<<endl<<"Tailer (Parity):  "<<packet[char_count+1].to_string()<<endl<<endl;

        /*====================================================================================================*/

        }
    else{
        //Reply From The Receiver he has received my previous message Either Correctly or Incorrectly
        //Self Message to wait (listen) for input from the user
        scheduleAt(simTime(),new cMessage(""));
    }
}
