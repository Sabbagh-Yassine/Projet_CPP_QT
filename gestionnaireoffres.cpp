    #include "gestionnaireoffres.h"

void GestionnaireOffres::ajouterOffre(const OffreEmploi& offre) {
    listeOffres.push_back(offre);
}

bool GestionnaireOffres::supprimerOffreEmploi(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM OffreEmploi WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to execute SQL query.";
        qDebug() << "Executed Query:" << query.executedQuery();
        qDebug() << "Error Type:" << query.lastError().type();
        qDebug() << "Error Number:" << query.lastError().number();
        qDebug() << "Error Database Text:" << query.lastError().databaseText();
        qDebug() << "Error Driver Text:" << query.lastError().driverText();
        qDebug() << "Error Text:" << query.lastError().text();
        return false;
    }

    qDebug() << "Successfully deleted job offer with ID:" << id;
    return true;


}


void GestionnaireOffres::updateEtatPosteIfNeeded(const QString& poste) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM candidat WHERE poste = :poste AND status = 'Accepte'");
    query.bindValue(":poste", poste);

    if (query.exec() && query.next()) {
        int acceptedCount = query.value(0).toInt();
        qDebug() << "Accepted candidates count:" << acceptedCount;

        QSqlQuery updateQuery;
        if (acceptedCount > 0) {
            // Update etatPoste to 'non disponible' if there's at least one accepted candidate
            updateQuery.prepare("UPDATE OffreEmploi SET etatPoste = 'non disponible' WHERE poste = :poste");
        } else {
            // Update etatPoste to 'disponible' if no accepted candidates are found
            updateQuery.prepare("UPDATE OffreEmploi SET etatPoste = 'disponible' WHERE poste = :poste");
        }
        updateQuery.bindValue(":poste", poste);

        if (!updateQuery.exec()) {
            QMessageBox::critical(nullptr, "Error", "Failed to update the job offer status: " + updateQuery.lastError().text());
        }
    } else {
        QMessageBox::critical(nullptr, "Error", "Failed to check the candidate's status: " + query.lastError().text());
    }
}




std::vector<OffreEmploi>& GestionnaireOffres::getListeOffres() {
    return listeOffres;
}

