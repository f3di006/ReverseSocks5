// testReverseSocksClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"Globals.h"
#include"net.h"
#include<string>

using namespace std;


void _stdcall newserver(connexion_details* det) {
    char data[8000];
    SOCKADDR_IN infc;
    memset(&infc, 0, sizeof(infc));

    memcpy(&infc.sin_addr.s_addr, det->d, 4);
    //unsigned short port;
    memcpy(&infc.sin_port, &det->d[4], 2);
    //inf.sin_port = htons(port);
    infc.sin_family = AF_INET;
    socket_details* sd = new socket_details;
    SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(server, (sockaddr*)&infc, sizeof(infc)) == SOCKET_ERROR) {
        delete det; closesocket(server); delete(sd); return;
    }

    sd->id = det->id;
    sd->sc = server;
    mc.lock();
    clients.push_front(sd);
    mc.unlock();



    if (send_data(granted, 10, det->id) == SOCKET_ERROR) { goto cleanup; }



    int r;
    while (1) {

        r = recv(server, data, 8000, 0);
        if (r <= 0) { send_data(data, 0, det->id); break; }
        else { send_data(data, r, det->id); }


    }

cleanup:
    clean_connection(sd);
    delete det;
    return;
}

void new_connection(char* buff, long long int id) {

    connexion_details* o = new connexion_details;
    o->id = id;
    memcpy(&o->d, buff, 6);

    std::future<void> h = std::async(std::launch::async, newserver, o);
    fu.push_back(std::move(h));



    return;
}


void usage() {

    cout << bnr;
    cout << "\n\n\nusage : ReverseSocksClient.exe ip_server port_server";
    exit(0);

}
int main(int argc,char *argv[])
{

    if (argc < 2) { usage(); }
    cout << bnr;
    string ip = argv[1];
    string port_s = argv[2];
    unsigned short port = (unsigned short)std::stoi(port_s);

    WSAData d;
    if (WSAStartup(MAKEWORD(2, 0), &d)) { return -1; }
    connectback((char*)"192.168.1.16",5000);
    cout << "Connected!\n";
    char packet[8000];
    while (1) {
        if (recvp(packet, 8000) == SOCKET_ERROR) { return -1; }


    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
