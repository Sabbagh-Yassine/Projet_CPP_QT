#include "connection.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>



Connection::Connection(){}

bool Connection::createconnect()
{
    bool test = false;
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projetQT");
    db.setUserName("hamasin");  // Insert user name
    db.setPassword("hamasin");  // Insert password
    if (db.open()) {
        test = true;

    } else {
        qDebug() << "Database Error:" << db.lastError().text();
    }
    return test;
}

void Connection::closeConnection()
{
    if (db.isOpen()) {
        db.close();
    }
}

