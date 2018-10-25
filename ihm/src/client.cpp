#include "./../include/client.h"
#include <iostream>

ClientTcp::ClientTcp(QString ip, quint16 port) {
/**
 * @brief ClientTcp::ClientTcp
 * @param ip
 * @param port
 */
    serverPort = port; // choix arbitraire (>1024)
    serverIp   = ip;

    soc = new QTcpSocket(this);

    msg_my_id  = new int(1);

    soc->abort(); // On désactive les connexions précédentes s'il y en a
    soc->connectToHost(serverIp, serverPort); // On se connecte au serveur demandé

    connect(soc, SIGNAL(readyRead()), this, SLOT(readDataFromTCPIP()));
    connect(soc, SIGNAL(connected()), this, SLOT(connecte()));
    connect(soc, SIGNAL(disconnected()), this, SLOT(deconnecte()));
    connect(soc, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));

    tailleMessage = 0;
}

/**
 * @brief ClientTcp::~ClientTcp
 */
ClientTcp::~ClientTcp() {
    delete soc;
}

/**
 * @brief ClientTcp::send : on envoie un message au serveur
 * @param msg
 */
void ClientTcp::send(QString msg) {
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (quint16) 0;
    out << msg;
    out.device()->seek(0);
    out << (quint16) (paquet.size() - (int)sizeof(quint16));

    soc->write(paquet); // On envoie le paquet
}

/**
 * @brief ClientTcp::readDataFromTCPIP : On a reçu un paquet (ou un sous-paquet)
 */
void ClientTcp::readDataFromTCPIP() {
    // On reçoit un paquet (ou un sous-paquet) d'un des clients
    // On détermine quel client envoie le message (recherche du QTcpSocket du client)
    QDataStream in(soc);

    if (tailleMessage == 0) { // Si on ne connaît pas encore la taille du message, on essaye de la récupérer
        if (soc->bytesAvailable() < (int)sizeof(quint16)) // On n'a pas reçu la taille du message en entier
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
 * @brief ClientTcp::connecte : Ce slot est appelé lorsque la connexion au serveur a réussi
 */
void ClientTcp::connecte() {
    emit connexion_status(true);
    cout << "\nConnexion réussie !" << endl;
}

/**
 * @brief ClientTcp::deconnecte : Ce slot est appelé lorsqu'on est déconnecté du serveur
 */
void ClientTcp::deconnecte() {
    emit connexion_status(false);
    cout << "\nDéconnecté du serveur" << endl;
}

/**
 * @brief ClientTcp::erreurSocket : Ce slot est appelé lorsqu'il y a une erreur
 * @param erreur
 */
void ClientTcp::erreurSocket(QAbstractSocket::SocketError erreur) {
    emit connexion_status(false);
    switch(erreur) { // On affiche un message différent selon l'erreur qu'on nous indique
        case QAbstractSocket::HostNotFoundError:
            cout << "\nERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port." << endl;
            break;
        case QAbstractSocket::ConnectionRefusedError:
            cout << "\nERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port." << endl;
            break;
        case QAbstractSocket::RemoteHostClosedError:
            cout << "\nERREUR : le serveur a coupé la connexion." << endl;
            break;
        default:
            cout << "\nERREUR : " << soc->errorString().toStdString() << endl;
    }
}

void ClientTcp::init_msg(Message* msg){
    msg->setType(msg_type);
    msg->setIdSender(msg_my_id);
    msg->setIdDest(msg_id_dest);
    msg->setIdConcern(msg_my_id);
    return;
}

void ClientTcp::set_barre(float * b) {
    Message* msg = new Message();
    init_msg(msg);
    msg->setBarre(b);
    send(msg->encodeData());
}

void ClientTcp::set_voile(float * v) {
    Message* msg = new Message();
    init_msg(msg);
    msg->setEcoute(v);
    send(msg->encodeData());
}

void ClientTcp::received_data(QString data){
    Message* msg = new Message();
    msg->decodeData(data);
    //Apres decodage du message : verification de la validite puis emission de signals pour l'IHM
    if (*msg->getIdSender()==0 && *msg->getIdDest()==*msg_my_id){ //Le message vient du serveur et m'est destine
        if (msg->getLongitude()) {
            emit send_longitude(*msg->getLongitude(),*msg->getIdConcern());
        }
        if (msg->getLatitude()){
            emit send_latitude(*msg->getLatitude(),*msg->getIdConcern());
        }
        if (msg->getCap()){
            emit send_cap(*msg->getCap(),*msg->getIdConcern());
        }
        if (msg->getVitesse()){
            emit send_vitesse(*msg->getVitesse(),*msg->getIdConcern());
        }
        if (msg->getGite()){
            emit send_gite(*msg->getGite(),*msg->getIdConcern());
        }
        if (msg->getTangage()){
            emit send_tangage(*msg->getTangage(),*msg->getIdConcern());
        }
        if (msg->getBarre()){
            emit send_barre(*msg->getBarre(),*msg->getIdConcern());
        }
        if (msg->getEcoute()){
            emit send_voile(*msg->getEcoute(),*msg->getIdConcern());
        }
    }
}
