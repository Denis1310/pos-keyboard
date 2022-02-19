#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>
#include <iostream>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class Configuration
{

private:
    QString last_preset;
    bool check_autoload;
    int await;

public:
    Configuration();
    ~Configuration();
    void setAwait(int _await);
    void setLastPreset(QString preset_name);
    void setAutoload(bool check);
    QString getLastPreset();
    bool getAutoload();
    int getAwait();

private:
    QSqlDatabase db;
    QSqlQuery *query;
    void openDB();
    void closeDB();
    void readDB();
    void setConfigurationInDB();

};

#endif // CONFIGURATION_H
