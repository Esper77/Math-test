#include "FuncsForServer.h"
#include <QString>
#include <QDebug>

FuncsForServer::FuncsForServer(QObject *parent) : QObject(parent){

}
FuncsForServer::~FuncsForServer(){

}
QByteArray FuncsForServer::auth(QString input){
    QString response;
    response.append("Authentification complete\n");
    return response.toUtf8();
}
QByteArray FuncsForServer::reg(QString input){
    QString response;
    response.append("Registration complete\n");
    return response.toUtf8();
}
QByteArray FuncsForServer::lookMyStat(QString input){
    QString response;
    response.append("Your stat\n");
    return response.toUtf8();
}
QByteArray FuncsForServer::lookAllStat(QString input){
    QString response;
    response.append("Stats changed\n");
    return response.toUtf8();
}
QByteArray FuncsForServer::changeNickname(QString input){
    QString response;
    response.append("Nickname changed\n");
    return response.toUtf8();
}
QByteArray FuncsForServer::viewLeaderboard(QString input){
    QString response;
    response.append("Leaderboard\n");
    return response.toUtf8();
}
QByteArray FuncsForServer::logOut(QString input){
    QString response;
    response.append("Logged out\n");
    return response.toUtf8();
}
QByteArray FuncsForServer::parsing(QString input){
    char ihatemylife = input[0].digitValue();
    int control = ihatemylife;

    switch (control) {
    case 1:
        return this->reg(input);
    case 2:
        return this->auth(input);
    case 3:
        return this->lookMyStat(input);
    case 4:
        return this->lookAllStat(input);
    case 5:
        return this->changeNickname(input);
    case 6:
        return this->viewLeaderboard(input);
    case 7:
        return this->logOut(input);
    default:
        QString response;
        response.append("Invalid input\n");
        return response.toUtf8();
    }
}
