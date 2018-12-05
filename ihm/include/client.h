#ifndef CLIENT_H
#define CLIENT_H 1


#include <QObject>
#include <QtNetwork>
#include <QString>
#include <iostream>
#include <unistd.h>

#include "message.h"

using namespace std;

/**
 * @brief The ClientTcp class
 */
class ClientTcp : public QObject {
    Q_OBJECT
    public:
        ClientTcp(QString ip, quint16 port, int id);
        ~ClientTcp();
        void set_barre(float * b);
        void set_voile(float * v);
        void init_msg(Message& msg);

    public slots:
        void readDataFromTCPIP();
        void connecte();
        void deconnecte();
        void erreurSocket(QAbstractSocket::SocketError erreur);

    signals:
        void connexion_status(bool);
        //Envoi a l'IHM du contenu des messages
        void send_longitude(float, int);
        void send_latitude(float, int);
        void send_cap(float, int);
        void send_vitesse(float, int);
        void send_gite(float, int);
        void send_tangage(float, int);
        void send_barre(float, int);
        void send_voile(float, int);
        void add_new_boat(int);

    private:
        // Ip du serveur
        QString serverIp;
        // Port utilisé par le serveur
        quint16 serverPort;
        // Socket
        QTcpSocket* soc;
        // Taille du message
        quint16 tailleMessage;

        // Donnes relatives au client pour la creation de messages
        string msg_type = "P";
        int my_id;
        vector<int> known_ids;
        int id_dest = 0;

        // Method to send a message to the server
        void send(QString msg);
        void received_data(QString data);
        bool is_known(int _id);
};


#endif // !CLIENT_H
