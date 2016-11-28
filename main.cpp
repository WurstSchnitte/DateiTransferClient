/* 
 * File:   main.cpp
 * Author: debian
 *
 * Created on 23. November 2016, 14:50
 */

#include "DateiTransfer.h"
#include <cstdlib>
#include <fstream>
#include <thrift/transport/TTransport.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <boost/shared_ptr.hpp>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

using namespace std;

#include "Uebertragung.h"

//PROTOTYPES
vector<Uebertragung*> ladeUebertragungen();
void speicherUebertragungen(vector<Uebertragung*> idvec);
//

Uebertragung* initSendFile(DateiTransferClient& client, boost::shared_ptr<TTransport> transport, string dateiname, long filesize, vector<Uebertragung*>& liste) {
    try {
        Uebertragung * ue{nullptr};
        transport->open();
        initUploadReturn re{};
        client.initUpload(re, dateiname, filesize);
        if (re.neuePosition == 0) {
            ue = new Uebertragung(dateiname, "localhost", re.verbindungsId);
            liste.push_back(ue);
            cout << "Neue Uebertragung gestartet" << endl;
        } else if (re.neuePosition > 0) {
            ue = new Uebertragung(dateiname, "localhost", filesize, re.neuePosition, 1, re.verbindungsId);
            liste.push_back(ue);
            cout << "Uebertragung besteht bereits" << endl;
        } else {
            cout << "Fehler beim Starten der Uebertragung" << endl;
        }
        cout << endl;
        transport->close();
        return ue;
    } catch (TException& tx) {
        cout << "ERROR: " << tx.what() << endl;
        return nullptr;
    }
}

bool send(DateiTransferClient& client, boost::shared_ptr<TTransport> transport, Uebertragung* ue) {
    try {
        bool fertig = false;
        char * buffer;
        while (true) {
            sleep(rand() % 2);
            transport->open();
            cout << "Position: " << ue->getDateiposition() << "  Id: " << ue->getVerbindungsid() << endl;
            long pos = ue->ladePaket(buffer);
            vector<signed char> paket{};
            paket.resize(pos - ue->getDateiposition());

            for (int i = 0; i < paket.size(); ++i) {
                paket.at(i) = buffer[i];
            }
            cout << "Senden --> Groeße: " << paket.size() << "bytes" << endl;
            long neuePos = client.sendPacket(ue->getVerbindungsid(), paket, pos);
            if (neuePos == pos) {
                ue->setDateiposition(neuePos);
                cout << "Fortschritt: " << ue->getDateiposition() << "/" << ue->getDateigroese() << " bytes" << endl;
                cout << "Fertig" << endl;
            } else if (neuePos = -1) {
                cout << "Datei: " << ue->getDateiname() << " erfolgreich Uebertragen" << endl;
                fertig = true;
                break;
            } else {
                cout << "Fehler beim Uebertragen" << endl;
                break;
            }
            cout << endl;

            transport->close();

            if (ue->getDateiposition() >= ue->getDateigroese()) {
                cout << "Fehler beim Uebertragen" << endl;
                cout << endl;
                break;
            }
        }
        delete[] buffer;
        return fertig;
    } catch (TException& tx) {
        cout << "ERROR: " << tx.what() << endl;
        return false;
    }
}

void setPacketSize(DateiTransferClient& client, boost::shared_ptr<TTransport> transport, Uebertragung* ue, int packetsize) {
    try {
        int paketgroese = packetsize;
        transport->open();
        paketgroese = client.checkoutPacketSize(ue->getVerbindungsid(), paketgroese);
        ue->setPaketgroese(paketgroese);
        transport->close();
    } catch (TException& tx) {
        cout << "ERROR: " << tx.what() << endl;
    }
}

void sendFile(DateiTransferClient& client, boost::shared_ptr<TTransport> transport, string filen, vector<Uebertragung*>& liste) {
    int paketgroese = 1000;
    cout << filen << endl;
    string dateiname = filen;
    ifstream file{dateiname};

    file.seekg(0, file.end);
    int filesize = file.tellg();
    file.seekg(0, file.beg);
    file.close();

    cout << "Sende Datei '" << filen << "' Groeße: " << filesize << "bytes" << endl;

    Uebertragung* ue = initSendFile(client, transport, dateiname, filesize, liste);
    if (ue != nullptr) {
        setPacketSize(client, transport, ue, paketgroese);
        if(send(client, transport, ue)){
            for(int i = 0; i < liste.size(); ++i){
                if(liste.at(i) == ue){
                    delete ue;
                    liste.erase(liste.begin()+i);
                }
            }
        }
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
    vector<Uebertragung*> idliste = ladeUebertragungen();


    boost::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

    DateiTransferClient client = DateiTransferClient(protocol);
    string file = "main.cpp";
    if (argc == 2) {
        file = argv[1];
    }
    sendFile(client, transport, file, idliste);


    speicherUebertragungen(idliste);
    return 0;
}

vector<Uebertragung*> ladeUebertragungen() {
    vector<Uebertragung*> idvec{};
    ifstream stream{"log"};
    string dateiname{};
    string peername{};
    string peerip{};
    long dateigroese{};
    long dateiposition{};
    int type{};
    int verbindungsid{};
    while (stream >> dateiname && stream >> peername && stream >> peerip && stream >> dateigroese && stream >> dateiposition && stream >> type && stream >> verbindungsid) {
        idvec.push_back(new Uebertragung(dateiname, peerip, dateigroese, dateiposition, type, verbindungsid));
    }
    return idvec;
}

void speicherUebertragungen(vector<Uebertragung*> idvec) {
    ofstream stream{"log"};
    for (int i = 0; i < idvec.size(); ++i) {
        stream << idvec.at(i)->getDateiname() << " " << idvec.at(i)->getPeerip() << " "
                << idvec.at(i)->getDateigroese() << " " << idvec.at(i)->getDateiposition()
                << " " << idvec.at(i)->getSendet() << " " << idvec.at(i)->getVerbindungsid() << endl;
    }
}