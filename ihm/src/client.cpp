#include "./../include/client.h"
#include <iostream>

/**
 * CONSTRUCTOR
 *
 * @brief ClientTcp::ClientTcp : TODO
 * @param ip
 * @param port
 */
ClientTcp::ClientTcp(QString ip, quint16 port, int id) {
    // Set the port and the IP
    serverPort = port; // choix arbitraire (>1024)
    serverIp   = ip;

    // Create a new socket
    soc = new QTcpSocket(this);

    my_id  = id;
    known_ids.push_back(id);

    soc->abort(); // On désactive les connexions précédentes s'il y en a
    soc->connectToHost(serverIp, serverPort); // On se connecte au serveur demandé

    // Create connectors
    connect(soc, SIGNAL(readyRead()),                         this, SLOT(readDataFromTCPIP()));
    connect(soc, SIGNAL(connected()),                         this, SLOT(connecte()));
    connect(soc, SIGNAL(disconnected()),                      this, SLOT(deconnecte()));
    connect(soc, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));

    // Set the length of the message to 0
    tailleMessage = 0;
}

/**
 * DESTRUCTOR
 *
 * @brief ClientTcp::~ClientTcp : TODO
 */
ClientTcp::~ClientTcp() {
    soc->close();
    delete soc;
}

bool ClientTcp::is_known(int _id){
    for (unsigned int i=0; i<known_ids.size(); i++){
        if(known_ids.at(i)==_id)
            return true;
    }
    return false;
}
/**
 * METHOD
 *
 * @brief ClientTcp::init_msg : TODO
 * @param msg
 */
void ClientTcp::init_msg(Message& msg){
    msg.setType(new string(msg_type));
    msg.setIdSender(new int(my_id));
    msg.setIdDest(new int(id_dest));
    msg.setIdConcern(new int(my_id));
    return;
}

/**
 * METHOD
 *
 * @brief ClientTcp::set_barre : TODO
 * @param b
 */
void ClientTcp::set_barre(float * b) {
    Message msg;
    init_msg(msg);
    msg.setBarre(b);
    send(msg.encodeData());
}

/**
 * METHOD
 *
 * @brief ClientTcp::set_voile : TODO
 * @param v
 */
void ClientTcp::set_voile(float * v) {
    Message msg;
    init_msg(msg);
    msg.setEcoute(v);
    send(msg.encodeData());
}

/*--------------------------*
 *                          *
 *          SLOTS           *
 *                          *
 *--------------------------*/
/**
 * SLOT -> TODO
 *
 * @brief ClientTcp::send : on envoie un message au serveur
 * @param msg
 */
void ClientTcp::send(QString msg) {
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << quint16(0);
    out << msg;
    out.device()->seek(0);
    out << quint16(paquet.size() - int(sizeof(quint16)));
    soc->write(paquet); // On envoie le paquet
}

/**
 * SLOT -> TODO
 *
 * @brief ClientTcp::readDataFromTCPIP : On a reçu un paquet (ou un sous-paquet)
 */
void ClientTcp::readDataFromTCPIP() {
    // On reçoit un paquet (ou un sous-paquet) d'un des clients
    // On détermine quel client envoie le message (recherche du QTcpSocket du client)
    QDataStream in(soc);

    if (tailleMessage == 0) { // Si on ne connaît pas encore la taille du message, on essaye de la récupérer
        if (soc->bytesAvailable() < int(sizeof(quint16))) // On n'a pas reçu la taille du message en entier
            return;

        in >> tailleMessage; // Si on a reçu la taille du message en entier, on la récupère
    }

     // Si on connaît la taille du message, on vérifie si on a reçu le message en entier
    if (soc->bytesAvailable() < tailleMessage)
        return; // Si on n'a pas encore tout reçu, on arrête la méthode

    // Si on arrive jusqu'à cette ligne, on peut récupérer le message entier
    QString messageRecu;
    in >> messageRecu;
    //messageRecu += "\r\n"; // To fit to the message trame
    received_data(messageRecu);

    // On affiche le message sur la zone de Chat

    // On remet la taille du message à 0 pour pouvoir recevoir de futurs messages
    tailleMessage = 0;
}

/**
 * SLOT -> TODO
 *
 * @brief ClientTcp::connecte : Ce slot est appelé lorsque la connexion au serveur a réussi
 */
void ClientTcp::connecte() {
    emit connexion_status(true);

    // Give to the server our id
    Message msg;
    // Change the type of the message (PC for Post Connection)
    msg_type = "PC";
    // Init the trame
    init_msg(msg);
    // Send it to the server
    send(msg.encodeData());
    // Reset the type to P
    msg_type = "P";

    cout << "\nConnexion réussie !" << endl;
}

/**
 * SLOT -> TODO
 *
 * @brief ClientTcp::deconnecte : Ce slot est appelé lorsqu'on est déconnecté du serveur
 */
void ClientTcp::deconnecte() {
    emit connexion_status(false);
    cout << "\nDéconnecté du serveur" << endl;
}

/**
 * SLOT -> TODO
 *
 * @brief ClientTcp::erreurSocket : Ce slot est appelé lorsqu'il y a une erreur
 * @param erreur
 */
void ClientTcp::erreurSocket(QAbstractSocket::SocketError erreur) {
    switch(erreur) { // On affiche un message différent selon l'erreur qu'on nous indique
        case QAbstractSocket::HostNotFoundError:
            //emit connexion_status(false);
            cout << "\nERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port." << endl;
            break;
        case QAbstractSocket::ConnectionRefusedError:
            emit connexion_status(false);
            cout << "\nERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port." << endl;
            break;
        case QAbstractSocket::RemoteHostClosedError:
            cout << "\nERREUR : le serveur a coupé la connexion." << endl;
            break;
        default:
            //emit connexion_status(false);
            cout << "\nERREUR : " << soc->errorString().toStdString() << endl;
    }
}

/**
 * SLOT -> TODO
 *
 * @brief ClientTcp::received_data : TODO
 * @param data
 */
void ClientTcp::received_data(QString data){
    Message msg;
    msg.decodeData(data);
    cout << data.toStdString() <<endl;
    // Apres decodage du message : verification de la validite puis emission de signals pour l'IHM
    if (!msg.getError() && *msg.getIdSender()==0 && *msg.getIdDest()==my_id) { // Le message vient du serveur et m'est destine
        if((!is_known(*msg.getIdConcern()))){
            if (*msg.getIdConcern()>0) {
                emit add_new_boat(*msg.getIdConcern());
                known_ids.push_back(*msg.getIdConcern());
            } else
                return;
        }
        else {
            if (msg.getLongitude()) {
                emit send_longitude(*msg.getLongitude(),*msg.getIdConcern());
            }
            if (msg.getLatitude()){
                emit send_latitude(*msg.getLatitude(),*msg.getIdConcern());
            }
            if (msg.getCap()){
                emit send_cap(*msg.getCap(),*msg.getIdConcern());
            }
            if (msg.getVitesse()){
                emit send_vitesse(*msg.getVitesse(),*msg.getIdConcern());
            }
            if (msg.getGite()){
                emit send_gite(*msg.getGite(),*msg.getIdConcern());
            }
            if (msg.getTangage()){
                emit send_tangage(*msg.getTangage(),*msg.getIdConcern());
            }
            if (msg.getBarre()){
                emit send_barre(*msg.getBarre(),*msg.getIdConcern());
            }
            if (msg.getEcoute()){
                emit send_voile(*msg.getEcoute(),*msg.getIdConcern());
            }
        }
    }
}
