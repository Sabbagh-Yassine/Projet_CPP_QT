#ifndef GESTIONNAIRECANDIDATS_H
#define GESTIONNAIRECANDIDATS_H

#include <vector>
#include "candidat.h"
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QSqlDatabase>
#include "connection.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QObject>
#include <QProcess>




#include <QJsonArray>
#include <QUrl>




class GestionnaireCandidats {
public:

    void ajouterCandidat(const Candidat& candidat);
    bool supprimerCandidat(int cin);
    void sendEmail(const QString& recipient, const QString& subject, const QString& body);

    std::vector<Candidat>& getListeCandidats();

private:
    std::vector<Candidat> listeCandidats;
};

#endif // GESTIONNAIRECANDIDATS_H
