#ifndef CLIENT_H
#define CLIENT_H 1


#include <QObject>
#include <QtNetwork>
#include <QString>
#include <iostream>
#include <unistd.h>

#include "message.h"

using namespace std;

class ClientTcp : public QObject {
    Q_OBJECT
    public:
        ClientTcp(QString ip, quint16 port);
        ~ClientTcp();
        void set_barre(float * b);
        void set_voile(float * v);
        void init_msg(Message* msg);
    public slots:
        void donneesRecues();
        void connecte();
        void deconnecte();
        void erreurSocket(QAbstractSocket::SocketError erreur);

    signals:
        void received_data(QString);

    private:
        // Ip du serveur
        QString serverIp;
        // Port utilisé par le serveur
        quint16 serverPort;
        // Socket
        QTcpSocket* soc;
        // Taille du message
        quint16 tailleMessage;

        //Donnes relatives au client pour creation de messages
        string* msg_type= new string("B");
        int* msg_id_sender;
        int* msg_id_dest = new int(0);
        int* msg_id_concern;
    public:
        // Method to send a message to the server
        void send(QString msg);
};


#endif // !CLIENT_H
