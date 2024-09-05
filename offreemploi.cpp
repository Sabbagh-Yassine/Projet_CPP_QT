#include "offreemploi.h"

OffreEmploi::OffreEmploi(int id, const QString& poste, int salaire, int heuresParSemaine, const QString& branche)
    : id(id), poste(poste), salaire(salaire), heuresParSemaine(heuresParSemaine), branche(branche), nombreCandidats(0), etatPoste(EtatPoste::Disponible) {}

int OffreEmploi::getId() const {
    return id;
}

QString OffreEmploi::getPoste() const {
    return poste;
}

int OffreEmploi::getSalaire() const {
    return salaire;
}

int OffreEmploi::getHeuresParSemaine() const {
    return heuresParSemaine;
}

QString OffreEmploi::getBranche() const {
    return branche;
}

int OffreEmploi::getNombreCandidats() const {
    return nombreCandidats;
}

OffreEmploi::EtatPoste OffreEmploi::getEtatPoste() const {
    return etatPoste;
}


void OffreEmploi::setEtatPoste(EtatPoste etat) {
    etatPoste = etat;
}


void OffreEmploi::incrementerNombreCandidats() {
    nombreCandidats++;
}
