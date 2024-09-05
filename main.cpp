    #include <QApplication>
#include <QDebug>
#include <iostream>
#include "mainwindow.h"
#include "connection.h"

int main(int argc, char *argv[]) {
    try {
        QApplication app(argc, argv);
        Connection conn;

        if (!conn.createconnect()) {
            qCritical() << "Failed to connect to the database!";
            return -1;
        }
        MainWindow w;
        w.show();

        // Run the application event loop
        int result = app.exec();

        conn.closeConnection();

        return result;
    } catch (const std::exception &ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        return -1;
    } catch (...) {
        std::cerr << "Unknown exception occurred" << std::endl;
        return -1;
    }
}

