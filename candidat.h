#ifndef CANDIDAT_H
#define CANDIDAT_H

#include <QString>
#include <QDate>
#include <QRegularExpressionValidator>
#include <QMessageBox>

class Candidat {
public:
    enum class Status {
        Accepte,
        Refuse,
        EnAttente
    };

    Candidat(int cin, const QString& nom, const QString& prenom, const QDate& datePostulation, const QString& poste, const QString& cv, const QString& e_mail);

    int getCin() const;
    QString getNom() const;
    QString getPrenom() const;
    QDate getDatePostulation() const;
    QString getPoste() const;
    QString getCv() const;
    Status getStatus() const;
    QString getEmail() const;

    void setStatus(Status newStatus);

private:
    int cin;
    QString nom;
    QString prenom;
    QDate datePostulation;
    QString poste;
    QString cv;
    Status status;
    QString e_mail;
};
QString statusToString(Candidat::Status status);
Candidat::Status stringToStatus(const QString& statusStr);

#endif // CANDIDAT_H
