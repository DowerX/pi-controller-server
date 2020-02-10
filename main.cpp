#include <wiringPi.h>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <bitset>

using namespace std;
using namespace boost::asio;

struct Button
{
    bool state;
    int pin;
};

Button buttons[6] = {
    {false, 0},
    {false, 2},
    {false, 3},
    {false, 12},
    {false, 13},
    {false, 14}
};

string remoteIP = "192.168.11.128";
int remotePort = 6969;

int main(){
    int change = 0;
    wiringPiSetup();
    for (int i = 0; i < sizeof(buttons)/sizeof(buttons[0]); i++){
        pinMode(buttons[i].pin, INPUT);
    }

    io_service io_serv;
    ip::udp::socket socket(io_serv);
    auto remote = ip::udp::endpoint(ip::address::from_string(remoteIP), remotePort);
    socket.open(boost::asio::ip::udp::v4());

    while (true){
	bitset<6> current;
        for (int i = 0; i < sizeof(buttons)/sizeof(buttons[0]); i++){
            if (buttons[i].state != digitalRead(buttons[i].pin)){
                buttons[i].state = !buttons[i].state;
		change += 1;
                current[i] = 1;
            }
            current[i] = (int)buttons[i].state;
        }
	if(change > 0){
            socket.send_to(buffer(current.to_string()), remote);
            change = 0;
        }
        delay(1);
    }

    return 0;
}
