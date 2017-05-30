#include "selene.h"
#include "utilities.h"
#include "isotp_socket.h"
#include "UDS_TESTER.h"

#include <lua.hpp>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <libgen.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <array>
#include <cstdint>
#include <iostream>
#include <cerrno>
#include <thread>

using namespace std;

int main(int argc, char **argv)
{
    constexpr array<uint8_t, 32> payload01 = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
    };

    // listen on this socket with `isotprecv -s 321 -d 123 -l vcan0`
    IsoTpSocket my_sender(0x123, 0x321, "vcan0");

    //IsoTpSocket my_receiver(0x123, 0x321,"vcan0");
    //std::thread t1(&IsoTpSocket::receiveData, &my_receiver); // run async in thread

    //usleep(2000); // wait some time to ensure the thread is set up and running
    my_sender.sendData(payload01.data(), payload01.size()); // finally send the data

    constexpr array<uint8_t, 11> payload02 = {
        0x59, 0x65, 0x73, 0x20, 0x77, 0x65, 0x20, 0x43, 0x41, 0x4E, 0x21
    };
    while (true)
    {
        my_sender.sendData(payload02.data(), payload02.size()); // send some more data
        sleep(2);
    }

    // exit program with [Ctrl + C]
    //t1.join();




	//printf("SocketCAN Tester started, creating connection...\n");
    //UDS_TESTER* tester = new UDS_TESTER();
    //printf("Connection established, sending message:0x20 \n");
    //unsigned char Message[] = {0x10,0x20,0x30,0x40,0x50};

       //while(true)
       //{
           //tester->sendUDSmessage(Message,sizeof(Message));
           //printf("Message 0x10 sended,waiting for reply...\n");
           //tester->receiveUDSmessage();
       //}


   	return 0;
}