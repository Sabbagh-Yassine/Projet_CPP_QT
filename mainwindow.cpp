#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "offreemploi.h"
#include "candidat.h"
#include "gestionnaireoffres.h"
#include "gestionnairecandidats.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QComboBox>
#include <QSortFilterProxyModel>
#include <QPrinter>
#include <QPainter>
#include <QTableView>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextDocument>
#include "statistiquesdialog.h"
#include "statsdialog.h"








MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit_modify_poste->hide();
    ui->lineEdit_modify_branche->hide();
    ui->lineEdit_modify_salaire->hide();
    ui->lineEdit_modify_nbreheures->hide();
    ui->label_modify_poste->hide();
    ui->label_modify_branche->hide();
    ui->label_modify_salaire->hide();
    ui->label_modify_nbreheures->hide();
    ui->confirm->hide();

    ui->lineEdit_modify_nom->hide();
    ui->lineEdit_modify_prenom->hide();
    ui->dateEdit_modify_datePostulation->hide();
    ui->lineEdit_modify_cv->hide();
    ui->lineEdit_modify_email->hide();
    ui->comboBox_modify_status->hide();
    ui->confirm1->hide();
    ui->label_18->hide();
    ui->label_19->hide();
    ui->label_20->hide();
    ui->label_21->hide();
    ui->label_22->hide();
    ui->label_23->hide();



    // Initialize the QComboBox with available job posts
    initializePosteComboBox();

    ui->comboBox_modify_status->addItem("Accepte", QVariant::fromValue(static_cast<int>(Candidat::Status::Accepte)));
    ui->comboBox_modify_status->addItem("Refuse", QVariant::fromValue(static_cast<int>(Candidat::Status::Refuse)));
    ui->comboBox_modify_status->addItem("EnAttente", QVariant::fromValue(static_cast<int>(Candidat::Status::EnAttente)));


}
void MainWindow::initializePosteComboBox() {
    QSqlQuery query;
        if (query.exec("SELECT POSTE FROM OFFREEMPLOI WHERE UPPER(ETATPOSTE) = 'DISPONIBLE'")) {
            while (query.next()) {
                QString poste = query.value(0).toString();
                ui->posteComboBox->addItem(poste);
                qDebug() << "Retrieved POSTE: " << poste;
            }
        } else {
            QMessageBox::critical(this, "Error", "Failed to retrieve job posts: " + query.lastError().text());
            qDebug() << query.lastError().text();
        }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
   ui->app->setCurrentIndex(1);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->app->setCurrentIndex(2);
}





void MainWindow::on_addbutton_clicked()
{

    int id = ui->lineEdit_3->text().toInt();
    QString poste = ui->lineEdit_1->text();
    int salaire = ui->lineEdit_4->text().toInt();
    int heures = ui->lineEdit_5->text().toInt();
    QString branche = ui->lineEdit_2->text();

    OffreEmploi::EtatPoste etatPoste = OffreEmploi::Disponible;

    OffreEmploi nouvelleOffre(id, poste, salaire, heures, branche);
    nouvelleOffre.setEtatPoste(etatPoste);
    gestionnaireOffres.ajouterOffre(nouvelleOffre);

    QString etatPosteString;
    switch (nouvelleOffre.getEtatPoste()) {
        case OffreEmploi::Disponible:
            etatPosteString = "disponible";
            break;
        case OffreEmploi::NonDisponible:
            etatPosteString = "non disponible";
            break;
    }

    qDebug() << "ID:" << id;
    qDebug() << "Poste:" << poste;
    qDebug() << "Salaire:" << salaire ;
    qDebug() << "Heures par Semaine:" << heures;
    qDebug() << "Branche:" << branche;
    qDebug() << "EtatPoste:" << etatPosteString;



    QSqlQuery query;
    query.prepare("INSERT INTO offreemploi (id, poste, salaire, heuresParSemaine, branche, nombreCandidats, etatPoste) "
                  "VALUES (:id, :poste, :salaire, :heuresParSemaine, :branche, :nombreCandidats, :etatPoste)");

    query.bindValue(":id", id);
    query.bindValue(":poste", poste);
    query.bindValue(":salaire", salaire);
    query.bindValue(":heuresParSemaine", heures);
    query.bindValue(":branche", branche);
    query.bindValue(":nombreCandidats", 0);
    query.bindValue(":etatPoste", etatPosteString);

       if (!query.exec()) {
           QMessageBox::critical(this, "Error", "Failed to insert the job offer into the database: " + query.lastError().text());
       } else {
           QMessageBox::information(this, "Success", "Job offer added successfully to the database.");
           ui->posteComboBox->clear();
           initializePosteComboBox();
           ui->lineEdit_3->clear();
           ui->lineEdit_1->clear();
           ui->lineEdit_4->clear();
           ui->lineEdit_5->clear();
           ui->lineEdit_2->clear();

               }
}


void MainWindow::on_deletebutton_clicked()
{
    bool ok;
    int id = ui->lineEdit_7->text().toInt(&ok);

    if (ok) {
        if (gestionnaireOffres.supprimerOffreEmploi(id)) {
            QMessageBox::information(this, "Success", "Job offer deleted successfully.");
            ui->posteComboBox->clear();
            initializePosteComboBox();
        } else {
            QMessageBox::critical(this, "Error", "Failed to delete job offer.");
        }
    } else {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid offer ID.");
    }

    ui->lineEdit_7->clear();

}

void MainWindow::on_add_o_1_clicked()
{
    ui->cruds1->setCurrentIndex(1);
}

void MainWindow::on_add_o_3_clicked()
{
    ui->cruds1->setCurrentIndex(1);
}

void MainWindow::on_add_o_4_clicked()
{
    ui->cruds1->setCurrentIndex(1);
}

void MainWindow::on_display_o_2_clicked()
{
    ui->cruds1->setCurrentIndex(0);
}

void MainWindow::on_display_o_3_clicked()
{
    ui->cruds1->setCurrentIndex(0);
}

void MainWindow::on_display_o_4_clicked()
{
    ui->cruds1->setCurrentIndex(0);
}

void MainWindow::on_modify_o_1_clicked()
{
    ui->cruds1->setCurrentIndex(2);
}

void MainWindow::on_modify_o_2_clicked()
{
    ui->cruds1->setCurrentIndex(2);
}

void MainWindow::on_modify_o_4_clicked()
{
    ui->cruds1->setCurrentIndex(2);
}

void MainWindow::on_delete_o_1_clicked()
{
    ui->cruds1->setCurrentIndex(3);
}

void MainWindow::on_delete_o_2_clicked()
{
    ui->cruds1->setCurrentIndex(3);
}

void MainWindow::on_delete_o_3_clicked()
{
    ui->cruds1->setCurrentIndex(3);
}

void MainWindow::on_display_o_1_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM offreemploi");

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve job offers from the database: " + query.lastError().text());
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);

    // Setting the model to the QTableView
    ui->tableView->setModel(model);
    ui->tableView->show();
}

void MainWindow::on_display_c_1_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM candidat");

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve candidats from the database: " + query.lastError().text());
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);

    // Setting the model to the QTableView
    ui->tableView_2->setModel(model);
    ui->tableView_2->show();
}

void MainWindow::on_addbutton_2_clicked()
{
        int cin = ui->lineEdit_8->text().toInt();
        QString nom = ui->lineEdit_9->text();
        QString prenom = ui->lineEdit_10->text();
        QDate datePostulation = QDate::currentDate();
        //QDate datePostulation = QDate::fromString(ui->lineEdit_11->text(), "dd/MM/yyyy");
        QString poste = ui->posteComboBox->currentText();
        QString cv = ui->lineEdit_13->text();
        QString e_mail = ui->lineEdit->text();

        QRegularExpression emailRegex(R"((^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$))");
        QRegularExpressionMatch match = emailRegex.match(e_mail);

        if (!match.hasMatch()) {
            QMessageBox::warning(this, "Invalid Email", "Please enter a valid email address.");
            return;
        }

        Candidat nouveauCandidat(cin, nom, prenom, datePostulation, poste, cv, e_mail);
        gestionnaireCandidats.ajouterCandidat(nouveauCandidat);

        QString statusString;
        switch (nouveauCandidat.getStatus()) {
            case Candidat::Status::Accepte:
                statusString = "accepté";
                break;
            case Candidat::Status::Refuse:
                statusString = "refusé";
                break;
            case Candidat::Status::EnAttente:
                statusString = "en attente";
                break;
        }

        QSqlQuery query;
        query.prepare("INSERT INTO candidat (cin, nom, prenom, datePostulation, poste, cv, status, e_mail) "
                      "VALUES (:cin, :nom, :prenom, :datePostulation, :poste, :cv, :status, :e_mail)");

        query.bindValue(":cin", cin);
        query.bindValue(":nom", nom);
        query.bindValue(":prenom", prenom);
        query.bindValue(":datePostulation", datePostulation);
        query.bindValue(":poste", poste);
        query.bindValue(":cv", cv);
        query.bindValue(":status", statusString);
        query.bindValue(":e_mail", e_mail);

        QString message;

        if (!query.exec()) {
            message = "Failed to insert the candidate into the database: " + query.lastError().text();
        } else {
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE OffreEmploi SET nombreCandidats = nombreCandidats + 1 WHERE poste = :poste");
            updateQuery.bindValue(":poste", poste);

            if (!updateQuery.exec()) {
                message = "Candidate added successfully, but failed to update the job offer: " + updateQuery.lastError().text();
            } else {
                message = "Candidate added successfully and job offer updated.";
            }

            ui->lineEdit_8->clear();
            ui->lineEdit_9->clear();
            ui->lineEdit_10->clear();
            ui->posteComboBox->setCurrentIndex(0);
            ui->lineEdit_13->clear();
            ui->lineEdit->clear();
        }

        QMessageBox::information(this, "Operation Result", message);



}



void MainWindow::on_modify_c_1_clicked()
{
    ui->cruds2->setCurrentIndex(2);

}

void MainWindow::on_delete_c_1_clicked()
{
    ui->cruds2->setCurrentIndex(3);

}

void MainWindow::on_display_c_2_clicked()
{
    ui->cruds2->setCurrentIndex(0);

}

void MainWindow::on_modify_c_2_clicked()
{
    ui->cruds2->setCurrentIndex(2);

}

void MainWindow::on_delete_c_2_clicked()
{
    ui->cruds2->setCurrentIndex(3);

}

void MainWindow::on_display_c_3_clicked()
{
    ui->cruds2->setCurrentIndex(0);

}

void MainWindow::on_add_c_3_clicked()
{
    ui->cruds2->setCurrentIndex(1);

}

void MainWindow::on_delete_c_3_clicked()
{
    ui->cruds2->setCurrentIndex(3);

}

void MainWindow::on_display_c_4_clicked()
{
    ui->cruds2->setCurrentIndex(0);

}

void MainWindow::on_pushButton_4_clicked()
{
    ui->cruds2->setCurrentIndex(1);

}

void MainWindow::on_modify_c_4_clicked()
{
    ui->cruds2->setCurrentIndex(2);

}

void MainWindow::on_add_c_1_clicked()
{
        ui->cruds2->setCurrentIndex(1);
}

void MainWindow::on_deletebutton_2_clicked()
{
    bool ok;
    int cin = ui->lineEdit_15->text().toInt(&ok);

    if (ok) {
        if (gestionnaireCandidats.supprimerCandidat(cin)) {
            QMessageBox::information(this, "Success", "Candidate deleted successfully.");
        } else {
            QMessageBox::critical(this, "Error", "Failed to delete candidate.");
        }
    } else {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid candidate ID.");
    }

    ui->lineEdit_15->clear();
}

void MainWindow::on_trier_selon_cin_clicked()
{
    QSortFilterProxyModel *sortModel = new QSortFilterProxyModel(this);
    sortModel->setSourceModel(ui->tableView_2->model());
    sortModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    sortModel->sort(0, Qt::AscendingOrder);

    // Apply the sorted model to the table view
    ui->tableView_2->setModel(sortModel);
}

void MainWindow::on_trier_selon_nom_clicked()
{
    QSortFilterProxyModel *sortModel = new QSortFilterProxyModel(this);
    sortModel->setSourceModel(ui->tableView_2->model());

    sortModel->sort(1, Qt::AscendingOrder);

    sortModel->sort(2, Qt::AscendingOrder);

    ui->tableView_2->setModel(sortModel);
}

void MainWindow::on_trier_selon_date_clicked()
{
    QSqlQuery query;
        query.prepare("SELECT * FROM candidat ORDER BY datePostulation ASC");

        if (!query.exec()) {
            QMessageBox::critical(this, "Error", "Failed to retrieve candidats from the database: " + query.lastError().text());
            return;
        }

        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(query);

        ui->tableView_2->setModel(model);
}

void MainWindow::on_trier_selon_salaire_clicked()
{
    QSqlQueryModel *queryModel = new QSqlQueryModel();
    queryModel->setQuery("SELECT * FROM offreemploi");

    if (queryModel->lastError().isValid()) {
        QMessageBox::critical(this, "Model Error", "Failed to retrieve data from the database: " + queryModel->lastError().text());
        delete queryModel;
        return;
    }

    qDebug() << "Number of rows:" << queryModel->rowCount();
    qDebug() << "Number of columns:" << queryModel->columnCount();

    // Create and configure the QSortFilterProxyModel
    QSortFilterProxyModel *sortModel = new QSortFilterProxyModel(this);
    sortModel->setSourceModel(queryModel);
    sortModel->setSortRole(Qt::DisplayRole); // Set the role used for sorting

    int columnIndex = 3;
    if (columnIndex < 0 || columnIndex >= queryModel->columnCount()) {
        QMessageBox::critical(this, "Error", "Invalid column index for sorting.");
        delete queryModel;
        delete sortModel;
        return;
    }

    sortModel->sort(columnIndex, Qt::AscendingOrder);

    if (ui->tableView) {
        ui->tableView->setModel(sortModel);
    } else {
        QMessageBox::critical(this, "Error", "Table view is not initialized.");
        delete queryModel;
        delete sortModel;
    }
}


void MainWindow::on_trier_selon_nbre_heures_clicked()
{
       if (!ui->tableView->model()) {
           QMessageBox::critical(this, "Error", "No model is set in the table view.");
           return;
       }

       QSortFilterProxyModel *sortModel = new QSortFilterProxyModel(this);
       sortModel->setSourceModel(ui->tableView->model());

       int columnIndex = 4;
       if (columnIndex < 0 || columnIndex >= ui->tableView->model()->columnCount()) {
           QMessageBox::critical(this, "Error", "Invalid column index for sorting.");
           delete sortModel;
           return;
       }
       sortModel->sort(columnIndex, Qt::AscendingOrder);

       ui->tableView->setModel(sortModel);
}


void MainWindow::on_pdf_offres_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
    QDate currentDate = QDate::currentDate();
    QString date = currentDate.toString("dd-MM-yyyy");

    const int rowCount = ui->tableView->model()->rowCount();
    const int columnCount = ui->tableView->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("col1")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<h3 style='position: absolute; top: 0; right: 0; margin: 0; padding: 10px; text-align: right; font-size: 24px; color: #333;'> Tunis " + date + "</h3>"
        "<h1 style='text-align: center;'>Liste des Factures</h1>\n"
        "<br>\n"
        "<br>\n"
        "<div align='center'>"
        "<table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++) {
        if (!ui->tableView->isColumnHidden(column)) {
            out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
        }
    }
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView->isColumnHidden(column)) {
                QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                out << QString("<td style='background-color:#ffffff;'>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
            "</div>"
        "</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    // Open a file dialog to let the user choose the save location and name
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save PDF"), QString(), "*.pdf");

    if (!fileName.isEmpty()) {
        if (QFileInfo(fileName).suffix().isEmpty()) {
            fileName.append(".pdf");  // Ensure the file has a .pdf extension
        }

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        printer.setPageSize(QPrinter::A4);
        printer.setPageMargins(QMarginsF(15, 15, 15, 15));

        document->print(&printer);  // Print to the selected file
    }

    delete document;
}



void MainWindow::on_trier_selon_nrbe_candidats_clicked()
{
    QSqlQueryModel *queryModel = new QSqlQueryModel();
       QString sqlQuery = "SELECT * FROM offreemploi ORDER BY nombrecandidats ASC";
       queryModel->setQuery(sqlQuery);

       if (queryModel->lastError().isValid()) {
           QMessageBox::critical(this, "Error", "Failed to retrieve data from the database: " + queryModel->lastError().text());
           delete queryModel;
           return;
       }
       ui->tableView->setModel(queryModel);
}

void MainWindow::on_pdf_candidat_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
    QDate currentDate = QDate::currentDate();
    QString date = currentDate.toString("dd-MM-yyyy");

    const int rowCount = ui->tableView_2->model()->rowCount();
    const int columnCount = ui->tableView_2->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("col1")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<h3 style='position: absolute; top: 0; right: 0; margin: 0; padding: 10px; text-align: right; font-size: 24px; color: #333;'> Tunis " + date + "</h3>"
        "<h1 style='text-align: center;'>Liste des Factures</h1>\n"
        "<br>\n"
        "<br>\n"
        "<div align='center'>"
        "<table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++) {
        if (!ui->tableView_2->isColumnHidden(column)) {
            out << QString("<th>%1</th>").arg(ui->tableView_2->model()->headerData(column, Qt::Horizontal).toString());
        }
    }
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView_2->isColumnHidden(column)) {
                QString data = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, column)).toString().simplified();
                out << QString("<td style='background-color:#ffffff;'>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
            "</div>"
        "</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    // Open a file dialog to let the user choose the save location and name
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save PDF"), QString(), "*.pdf");

    if (!fileName.isEmpty()) {
        if (QFileInfo(fileName).suffix().isEmpty()) {
            fileName.append(".pdf");  // Ensure the file has a .pdf extension
        }

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        printer.setPageSize(QPrinter::A4);
        printer.setPageMargins(QMarginsF(15, 15, 15, 15));

        document->print(&printer);  // Print to the selected file
    }

    delete document;
}

void MainWindow::on_modifybutton_clicked()
{
    int id = ui->lineEdit_6->text().toInt();

        QSqlQuery query;
        query.prepare("SELECT poste, branche, salaire, heuresParSemaine FROM offreemploi WHERE id = :id");
        query.bindValue(":id", id);

        if (query.exec() && query.next()) {

            QString poste = query.value(0).toString();
            QString branche = query.value(1).toString();
            int salaire = query.value(2).toInt();
            int heuresParSemaine = query.value(3).toInt();

            ui->lineEdit_modify_poste->show();
            ui->lineEdit_modify_branche->show();
            ui->lineEdit_modify_salaire->show();
            ui->lineEdit_modify_nbreheures->show();
            ui->confirm->show();
            ui->label_modify_poste->show();
            ui->label_modify_branche->show();
            ui->label_modify_salaire->show();
            ui->label_modify_nbreheures->show();


            ui->lineEdit_modify_poste->setText(poste);
            ui->lineEdit_modify_branche->setText(branche);
            ui->lineEdit_modify_salaire->setText(QString::number(salaire));
            ui->lineEdit_modify_nbreheures->setText(QString::number(heuresParSemaine));

        } else {
            QMessageBox::warning(this, "Invalid ID", "No job offer found with the given ID.");
        }
}

void MainWindow::on_confirm_clicked()
{
    QString poste = ui->lineEdit_modify_poste->text();
    QString branche = ui->lineEdit_modify_branche->text();
    int salaire = ui->lineEdit_modify_salaire->text().toInt();
    int heuresParSemaine = ui->lineEdit_modify_nbreheures->text().toInt();
    int id = ui->lineEdit_6->text().toInt();


    QSqlQuery query;
    query.prepare("UPDATE OffreEmploi SET poste = :poste, branche = :branche, salaire = :salaire, heuresParSemaine = :heuresParSemaine WHERE id = :id");
    query.bindValue(":poste", poste);
    query.bindValue(":branche", branche);
    query.bindValue(":salaire", salaire);
    query.bindValue(":heuresParSemaine", heuresParSemaine);
    query.bindValue(":id", id);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Job offer updated successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to update the job offer: " + query.lastError().text());
    }
    ui->lineEdit_modify_poste->clear();
    ui->lineEdit_modify_branche->clear();
    ui->lineEdit_modify_salaire->clear();
    ui->lineEdit_modify_nbreheures->clear();
    ui->lineEdit_modify_poste->hide();
    ui->lineEdit_modify_branche->hide();
    ui->lineEdit_modify_salaire->hide();
    ui->lineEdit_modify_nbreheures->hide();
    ui->label_modify_poste->hide();
    ui->label_modify_branche->hide();
    ui->label_modify_salaire->hide();
    ui->label_modify_nbreheures->hide();
    ui->confirm->hide();
    ui->lineEdit_6->clear();
}

void MainWindow::on_modifybutton_2_clicked() {
    int cin = ui->lineEdit_14->text().toInt();

    QSqlQuery query;
    query.prepare("SELECT nom, prenom, datePostulation, poste, cv, e_mail, status FROM candidat WHERE cin = :cin");
    query.bindValue(":cin", cin);

    if (query.exec() && query.next()) {

        QString nom = query.value(0).toString();
        QString prenom = query.value(1).toString();
        QDate datePostulation = query.value(2).toDate();
        QString poste = query.value(3).toString();
        QString cv = query.value(4).toString();
        QString e_mail = query.value(5).toString();
        QString statusStr = query.value(6).toString();
        Candidat::Status status = stringToStatus(statusStr);


        ui->lineEdit_modify_nom->show();
        ui->lineEdit_modify_prenom->show();
        ui->dateEdit_modify_datePostulation->show();
        ui->lineEdit_modify_cv->show();
        ui->lineEdit_modify_email->show();
        ui->comboBox_modify_status->show();
        ui->confirm1->show();


        ui->lineEdit_modify_nom->setText(nom);
        ui->lineEdit_modify_prenom->setText(prenom);
        ui->dateEdit_modify_datePostulation->setDate(datePostulation);
        ui->lineEdit_modify_cv->setText(cv);
        ui->lineEdit_modify_email->setText(e_mail);


        switch (status) {
            case Candidat::Status::Accepte:
                ui->comboBox_modify_status->setCurrentIndex(0);
                break;
            case Candidat::Status::Refuse:
                ui->comboBox_modify_status->setCurrentIndex(1);
                break;
            case Candidat::Status::EnAttente:
                ui->comboBox_modify_status->setCurrentIndex(2);
                break;
        }
    } else {
        QMessageBox::warning(this, "Invalid CIN", "No candidate found with the given CIN.");
    }
}


void MainWindow::on_confirm1_clicked() {
    QString nom = ui->lineEdit_modify_nom->text();
    QString prenom = ui->lineEdit_modify_prenom->text();
    QDate datePostulation = ui->dateEdit_modify_datePostulation->date();
    QString cv = ui->lineEdit_modify_cv->text();
    QString e_mail = ui->lineEdit_modify_email->text();
    int cin = ui->lineEdit_14->text().toInt();


    Candidat::Status status;
    switch (ui->comboBox_modify_status->currentIndex()) {
        case 0:
            status = Candidat::Status::Accepte;
            break;
        case 1:
            status = Candidat::Status::Refuse;
            break;
        case 2:
            status = Candidat::Status::EnAttente;
            break;
        default:
            status = Candidat::Status::EnAttente;
            break;
    }


    QString statusStr = statusToString(status);
    QString poste;
    QSqlQuery query;
    query.prepare("SELECT poste FROM candidat WHERE cin = :cin");
    query.bindValue(":cin", cin);
    if (query.exec() && query.next()) {
        poste = query.value(0).toString();
    } else {
        QMessageBox::critical(this, "Error", "Failed to retrieve the poste: " + query.lastError().text());
        return;
    }

    query.prepare("UPDATE candidat SET nom = :nom, prenom = :prenom, datePostulation = :datePostulation, cv = :cv, e_mail = :e_mail, status = :status WHERE cin = :cin");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":datePostulation", datePostulation);
    query.bindValue(":cv", cv);
    query.bindValue(":e_mail", e_mail);
    query.bindValue(":status", statusStr);
    query.bindValue(":cin", cin);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Candidate updated successfully.");
        if (status == Candidat::Status::Accepte || status == Candidat::Status::Refuse) {
            gestionnaireOffres.updateEtatPosteIfNeeded(poste);
            ui->posteComboBox->clear();
            initializePosteComboBox();
        }
        if (status == Candidat::Status::Accepte || status == Candidat::Status::Refuse) {
                   QString subject = "Application Status Update";
                   QString body = "Dear " + nom + " " + prenom + ",\n\nYour application status has been updated to " + statusStr + ".\n\nBest regards,\nYour Company";
                   snail.sendEmail(e_mail , subject , body);
               }
    } else {
        QMessageBox::critical(this, "Error", "Failed to update the candidate: " + query.lastError().text());
    }
    ui->lineEdit_modify_nom->clear();
    ui->lineEdit_modify_prenom->clear();
    ui->dateEdit_modify_datePostulation->clear();
    ui->lineEdit_modify_cv->clear();
    ui->lineEdit_modify_email->clear();
    ui->lineEdit_modify_nom->hide();
    ui->lineEdit_modify_prenom->hide();
    ui->dateEdit_modify_datePostulation->hide();
    ui->lineEdit_modify_cv->hide();
    ui->lineEdit_modify_email->hide();
    ui->comboBox_modify_status->hide();
    ui->confirm1->hide();
    ui->lineEdit_14->clear();
}









void MainWindow::on_statistiques_clicked()
{
    StatistiquesDialog dialog(this);
    dialog.exec();
}

void MainWindow::on_statts_clicked()
{
    statsdialog dialog(this);
    dialog.exec();
}
