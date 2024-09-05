#include "candidat.h"

Candidat::Candidat(int cin, const QString& nom, const QString& prenom, const QDate& datePostulation, const QString& poste, const QString& cv, const QString& e_mail)
    : cin(cin), nom(nom), prenom(prenom), datePostulation(datePostulation), poste(poste), cv(cv), status(Status::EnAttente), e_mail(e_mail) {}


int Candidat::getCin() const {
    return cin;
}

QString Candidat::getNom() const {
    return nom;
}

QString Candidat::getPrenom() const {
    return prenom;
}

QDate Candidat::getDatePostulation() const {
    return datePostulation;
}

QString Candidat::getPoste() const {
    return poste;
}

QString Candidat::getCv() const {
    return cv;
}

Candidat::Status Candidat::getStatus() const {
    return status;
}

QString Candidat::getEmail() const {
    return e_mail;
}

void Candidat::setStatus(Status newStatus) {
    status = newStatus;
}

QString statusToString(Candidat::Status status) {
    switch (status) {
        case Candidat::Status::Accepte:
            return "Accepte";
        case Candidat::Status::Refuse:
            return "Refuse";
        case Candidat::Status::EnAttente:
            return "EnAttente";
        default:
            return "";
    }
}

Candidat::Status stringToStatus(const QString& statusStr) {
    if (statusStr == "Accepte") {
        return Candidat::Status::Accepte;
    } else if (statusStr == "Refuse") {
        return Candidat::Status::Refuse;
    } else if (statusStr == "EnAttente") {
        return Candidat::Status::EnAttente;
    } else {
        return Candidat::Status::EnAttente; // Default to EnAttente for unrecognized strings
    }
}
