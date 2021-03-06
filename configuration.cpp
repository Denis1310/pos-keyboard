#include "configuration.h"

Configuration::Configuration()
{
    directoryCheck();
    checkExistsConfigurationFile();
    readDB();
}

void Configuration::checkExistsConfigurationFile()
{
    QString path = "./Data/config.db";

    if (!QFile::exists(path))
    {
        openDB();
        query = new QSqlQuery();
        query->exec("CREATE TABLE config ("
                    "last_preset TEXT,"
                    "await INTEGER,"
                    "check_autoload INTEGER,"
                    "id INTEGER);");

        query->exec("INSERT INTO config "
                    "(await, check_autoload, id) "
                    "VALUES (30, 0, 1);");
        closeDB();
    }
}

void Configuration::directoryCheck()
{
    QString db_path = "./Data";
    QString presets_path = "./Presets";
    QDir directory;
    directory.mkdir(db_path);
    directory.mkdir(presets_path);
}

// Видаляє динамічний об'єкт QsqlQuery * query
Configuration::~Configuration()
{
    delete query;
}

void Configuration::openDB()
{
    QString path = "./Data/config.db";
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(path);

        db.open();
}

void Configuration::closeDB()
{
    db.close();
}

// Вигружає дані з DB в RAM
void Configuration::readDB()
{
    openDB();

    query = new QSqlQuery;
    query->exec("SELECT * FROM config");
    query->next();

    this->last_preset =
            query->value(0).toString();
    this->await =
            query->value(1).toInt();
    this->check_autoload =
            query->value(2).toBool();

    closeDB();
}

// Внести дані конфігурації
void Configuration::setAwait(int _await)
{
    this->await = _await;

    setConfigurationInDB();
}

void Configuration::setAutoload(bool check)
{
    this->check_autoload = check;

    setConfigurationInDB();
}

void Configuration::setLastPreset(QString preset_name)
{
    this->last_preset = preset_name;

    setConfigurationInDB();
}

// Вносить дані з RAM в DB
void Configuration::setConfigurationInDB()
{
    openDB();

    query = new QSqlQuery;

    query->prepare("UPDATE config "
                   "SET last_preset = (:last_preset), "
                   "await = (:await), "
                   "check_autoload = (:check_autoload) "
                   "WHERE id = (1);");
    query->bindValue(":last_preset", this->last_preset);
    query->bindValue(":await", this->await);
    query->bindValue(":check_autoload", this->check_autoload);
    query->exec();

    closeDB();
}

// Повернути затримку
int Configuration::getAwait()
{
    return this->await;
}

// Повернути стан автозапуску
bool Configuration::getAutoload()
{
    return this->check_autoload;
}

// Повернути назву останнього пресету
QString Configuration::getLastPreset()
{
    return this->last_preset;
}

