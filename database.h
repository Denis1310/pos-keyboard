#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlRecord>
#include <iostream>
#include <cstdio>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QSqlQuery>
#include <filesystem>
#include <QFileInfo>
#include <QSqlError>

using namespace std;

class DataBase
{
private:
    QString commands[20][2];
    int command_type[20];
    int virtual_keys[20];
    QString preset_name;

public:
    DataBase();
    ~DataBase();
    bool isValid(QString DB_name);
    void setValues(int _virtual_key, QString _command_name, int _command_type, QString _command);
    QString searchCommandName(int virtual_key);
    QString searchCommand(int virtual_key);
    QString getPresetName();
    int searchCommandType(int virtual_key);
    bool deleteDB();
    bool clear(int virtual_key);    
    bool readDB(QString DB_name);    
    bool createDB(QString DB_name);    
    void synchronizationWithDB();
    bool exportDB(QString folder_path);
    bool importDB(QString DB_path);
    //bool findDB(QString DB_path);


private:
    bool checkImportedDB();
    QString presetDB_path;
    QSqlDatabase mainDB, presetDB;
    QSqlQuery *query;
    QString createTable();
    bool openDB(QSqlDatabase DB_name, QString path);
    bool openDB(QSqlDatabase DB_name);
    void closeDB(QSqlDatabase DB_name);
    void fillTable();
    void insertPreset();
    bool checkExistPreset();
    void deletePreset();
    void setValuesInDB(int virtual_key);
    void fillVirtualKeys();
    void fillCommandType();
};

#endif // DATABASE_H
