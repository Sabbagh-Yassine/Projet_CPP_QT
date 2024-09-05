#ifndef GESTIONNAIREOFFRES_H
#define GESTIONNAIREOFFRES_H

#include <vector>
#include "offreemploi.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include "connection.h"


class GestionnaireOffres {
public:
    void ajouterOffre(const OffreEmploi& offre);
    bool supprimerOffreEmploi(int id);
    void updateEtatPosteIfNeeded(const QString& poste);


    std::vector<OffreEmploi>& getListeOffres();

private:
    std::vector<OffreEmploi> listeOffres;;
};

#endif // GESTIONNAIREOFFRES_H
