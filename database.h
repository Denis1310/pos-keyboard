#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <QtSql/QSqlDatabase>
#include <QFile>
#include <QSqlQuery>
#include <QFileInfo>
#include <QDir>

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
    void setValues(int _virtual_key, QString _command_name, int _command_type, QString _command);
    QString searchCommandName(int virtual_key);
    QString searchCommand(int virtual_key);
    QString getPresetName();
    int searchCommandType(int virtual_key);
    bool deleteDB();
    bool clear(int virtual_key);
    bool readDB(QString DB_name);
    bool createDB(QString DB_name);
    bool exportDB(QString folder_path);
    bool importDB(QString DB_path);
    bool isValid(QString DB_name);

private:
    QString presetDB_path;
    QSqlDatabase mainDB, presetDB;
    QSqlQuery *query;
    QString createTable();
    bool checkImportedDB();
    bool openDB(QSqlDatabase DB_name, QString path);
    bool openDB(QSqlDatabase DB_name);
    bool checkExistPreset();
    void closeDB(QSqlDatabase DB_name);
    void fillTable();
    void insertPreset();
    void deletePreset();
    void setValuesInDB(int virtual_key);
    void fillVirtualKeys();
    void fillCommandType();
    void checkExistsDatabaseFile();
    void directoryCheck();
    void synchronizationWithDB();

};

#endif // DATABASE_H
