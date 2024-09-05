#ifndef OFFREEMPLOI_H
#define OFFREEMPLOI_H

#include <QString>

class OffreEmploi {
public:
    // Define the enum type
    enum EtatPoste {
        Disponible,
        NonDisponible
    };

    OffreEmploi(int id, const QString& poste, int salaire, int heuresParSemaine, const QString& branche);

    int getId() const;
    QString getPoste() const;
    int getSalaire() const;
    int getHeuresParSemaine() const;
    QString getBranche() const;
    int getNombreCandidats() const;
    EtatPoste getEtatPoste() const;

    void setEtatPoste(EtatPoste etat);

    void incrementerNombreCandidats();

private:
    int id;
    QString poste;
    int salaire;
    int heuresParSemaine;
    QString branche;
    int nombreCandidats;
    EtatPoste etatPoste;
};

#endif // OFFREEMPLOI_H
