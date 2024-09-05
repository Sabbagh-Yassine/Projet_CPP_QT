#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gestionnaireoffres.h"
#include "gestionnairecandidats.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    
    void on_pushButton_2_clicked();


    void on_addbutton_clicked();

    void on_deletebutton_clicked();

    void on_add_o_1_clicked();

    void on_add_o_3_clicked();

    void on_add_o_4_clicked();

    void on_display_o_2_clicked();

    void on_display_o_3_clicked();

    void on_display_o_4_clicked();

    void on_modify_o_1_clicked();

    void on_modify_o_2_clicked();

    void on_modify_o_4_clicked();

    void on_delete_o_1_clicked();

    void on_delete_o_2_clicked();

    void on_delete_o_3_clicked();

    void on_display_o_1_clicked();

    void on_display_c_1_clicked();

    void on_addbutton_2_clicked();

    void on_modify_c_1_clicked();

    void on_delete_c_1_clicked();

    void on_display_c_2_clicked();

    void on_modify_c_2_clicked();

    void on_delete_c_2_clicked();

    void on_display_c_3_clicked();

    void on_add_c_3_clicked();

    void on_delete_c_3_clicked();

    void on_display_c_4_clicked();

    void on_pushButton_4_clicked();

    void on_modify_c_4_clicked();

    void on_add_c_1_clicked();

    void on_deletebutton_2_clicked();

    void on_trier_selon_cin_clicked();

    void on_trier_selon_nom_clicked();

    void on_trier_selon_date_clicked();

    void on_trier_selon_salaire_clicked();

    void on_trier_selon_nbre_heures_clicked();

    void on_pdf_offres_clicked();

    void on_trier_selon_nrbe_candidats_clicked();

    void on_pdf_candidat_clicked();

    void on_modifybutton_clicked();

    void on_confirm_clicked();

    void on_modifybutton_2_clicked();

    void on_confirm1_clicked();

    void on_statistiques_clicked();

    void on_statts_clicked();

private:
    Ui::MainWindow *ui;
    GestionnaireOffres gestionnaireOffres;
    GestionnaireCandidats gestionnaireCandidats;
    GestionnaireCandidats snail;
    void initializePosteComboBox();
};
#endif // MAINWINDOW_H
