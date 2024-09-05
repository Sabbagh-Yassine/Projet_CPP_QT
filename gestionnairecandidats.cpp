#include "gestionnairecandidats.h"


void GestionnaireCandidats::ajouterCandidat(const Candidat& candidat) {
    listeCandidats.push_back(candidat);
}


bool GestionnaireCandidats::supprimerCandidat(int cin) {

    QSqlQuery query;
    query.prepare("DELETE FROM Candidat WHERE cin = :cin");
    query.bindValue(":cin", cin);

    if (!query.exec()) {
        qDebug() << "Failed to delete candidate from database:" << query.lastError().text();
        return false;
    }

    return true;
}

void GestionnaireCandidats::sendEmail(const QString& recipient, const QString& subject, const QString& body) {
    QProcess process;

    QString subjectEscaped = subject;
    subjectEscaped.replace("'", "''");

    QString bodyEscaped = body;
    bodyEscaped.replace("'", "''");

    QString script = QString(
        "Send-MailMessage -From 'yassine.sabbagh123@gmail.com' -To '%1' -Subject '%2' -Body '%3' "
        "-SmtpServer 'smtp.gmail.com' -Port 587 -UseSsl "
        "-Credential (New-Object System.Management.Automation.PSCredential('yassine.sabbagh123@gmail.com', "
        "(ConvertTo-SecureString 'xqsj egbh qqww ncsl' -AsPlainText -Force)))"
    ).arg(recipient, subjectEscaped, bodyEscaped);

    QStringList arguments;
    arguments << "-Command" << script;

    qDebug() << "PowerShell Command:" << script;

    process.start("powershell", arguments);

    if (!process.waitForStarted()) {
        qDebug() << "Failed to start PowerShell:" << process.errorString();
        return;
    }
    qDebug() << "PowerShell process started.";

    if (!process.waitForFinished(30000)) {
        qDebug() << "PowerShell process timed out:" << process.errorString();

        QString output = process.readAllStandardOutput();
        QString error = process.readAllStandardError();

        qDebug() << "PowerShell Output:" << output;
        qDebug() << "PowerShell Error:" << error;

        return;
    }

    QString output = process.readAllStandardOutput();
    QString error = process.readAllStandardError();

    qDebug() << "PowerShell Output:" << output;
    qDebug() << "PowerShell Error:" << error;

    if (process.exitStatus() == QProcess::NormalExit && error.isEmpty()) {
        qDebug() << "Email sent successfully!";
    } else {
        qDebug() << "Failed to send email.";
        qDebug() << "Process exit code:" << process.exitCode();
        qDebug() << "Process exit status:" << process.exitStatus();
    }
}







std::vector<Candidat>& GestionnaireCandidats::getListeCandidats() {
    return listeCandidats;
}
