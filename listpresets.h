#ifndef LISTPRESETS_H
#define LISTPRESETS_H

#include <QList>
#include <QSqlQuery>
#include <QSqlDatabase>
#include "database.h"
#include "configuration.h"

class ListPresets
{

private:
    DataBase db;
    Configuration config;
    QList<QString> presets;

public:
    ListPresets();
    ~ListPresets();
    QString getPreset(int index);
    int getSize();
    bool changePreset(QString name);
    bool addPreset(QString name);
    bool removePreset(QString name);
    bool isEmpty();

private:
    QSqlQuery *query;
    QSqlDatabase presets_DB;
    void readDB();

};

#endif // LISTPRESETS_H
