#include "database.h"

DataBase::DataBase()
{
    fillVirtualKeys();
    fillCommandType();
}

// Повертає назву активного пресета
QString DataBase::getPresetName()
{
    return preset_name;
}

// Виконати з'єднання з бд, передавши об'єкт бд та шлях
bool DataBase::openDB(QSqlDatabase DB_name, QString path)
{
    DB_name = QSqlDatabase::addDatabase("QSQLITE");
    DB_name.setDatabaseName(path);

    if (DB_name.open() == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Припинити з'єднання з бд, передавши об'єкт бд
void DataBase::closeDB(QSqlDatabase DB_name)
{
    DB_name.close();
}

// Видалення бази даних пресету
bool DataBase::deleteDB()
{
    if (checkExistPreset() == true)
    {
        if (QFile::exists(presetDB_path) == true)
        {
            QFile::remove(presetDB_path);
            deletePreset();
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

// відкрити БД в папці проекту та вигрузити дані в озп
bool DataBase::readDB(QString DB_name)
{
    this->preset_name = DB_name;
    this->presetDB_path = "./" + DB_name + ".db";

    if (checkExistPreset() == true)
    {
        if (openDB(this->presetDB, presetDB_path) == true)
        {
            synchronizationWithDB();

            closeDB(this->presetDB);

            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

// Вигружає дані з БД в ОЗП
void DataBase::synchronizationWithDB()
{
    query = new QSqlQuery();
    query->exec("SELECT * FROM preset");

    for (int i = 0; i < 20; i++)
    {
        query->next();
        this->commands[i][0] = query->value(1).toString(); // назва команди
        this->commands[i][1] = query->value(2).toString(); // команда
        this->command_type[i] = query->value(3).toInt();   // тип команди
    }
}

// Видалити пресет з головної бд
void DataBase::deletePreset()
{
    QString path = "./../pos-keyboardPJ/Data/Database.db";

    if (openDB(this->mainDB, path) == true)
    {
        query = new QSqlQuery(mainDB);
        query->prepare("DELETE FROM presets WHERE presetName = :presetName;");
        query->bindValue(":presetName", this->preset_name);
        query->exec();

        closeDB(this->mainDB);
    }

    this->preset_name = NULL;

    for (int i = 0; i < 20; i++)
    {
        this->command_type[i] = -1;

        for (int j = 0; j < 2; j++)
        {
            this->commands[i][j] = NULL;
        }
    }
}

// Перевірка існування пресету в головній БД
bool DataBase::checkExistPreset()
{
    QString path = "./../pos-keyboardPJ/Data/Database.db";

    if (openDB(this->mainDB, path) == true)
    {
        query = new QSqlQuery(mainDB);
        query->prepare("SELECT COUNT(*) FROM presets "
                       "WHERE presetName = :preset_name;");
        query->bindValue(":preset_name", this->preset_name);
        query->exec();
        query->next();

        int size = query->value(0).toInt();

        if (size == 1)
        {            
            closeDB(mainDB);
            return true;
        }
        else
        {
            closeDB(mainDB);
            return false;
        }
    }
    else
    {
        return false;
    }
}

// Створення БД пресету
bool DataBase::createDB(QString DB_name)
{
    this->preset_name = DB_name;
    this->presetDB_path = "./" + DB_name + ".db";

    if (!checkExistPreset())
    {
        if (openDB(this->presetDB, presetDB_path) == true)
        {
            QString query_text = createTable();
            query = new QSqlQuery(presetDB);
            query->exec(query_text);

            closeDB(this->presetDB);

            insertPreset();
            fillVirtualKeys();
            fillTable();

            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

// Запис назви пресету в головну БД
void DataBase::insertPreset()
{
    QString path = "./../pos-keyboardPJ/Data/Database.db";

    if (openDB(this->mainDB, path) == true)
    {
        query = new QSqlQuery(mainDB);

        query->prepare("INSERT INTO presets (presetName) "
                       "VALUES (:presetName);");
        query->bindValue(":presetName", preset_name);
        query->exec();

        closeDB(this->mainDB);
    }
}

// Створення таблиці для зберігання пресетів
QString DataBase::createTable()
{
    QString query_text = "CREATE TABLE preset ("
                         "virtualKey INT,"
                         "commandName TEXT,"
                         "command TEXT,"
                         "commandType INT"
                         ");";

    return query_text;
}

// Заповнення таблиці з пресетом (внести віртуальні клавіші 0-19)
void DataBase::fillTable()
{
    if (openDB(this->presetDB, presetDB_path) == true)
    {
        query = new QSqlQuery(presetDB);
        query->exec("INSERT INTO preset (virtualKey)"
                    "VALUES(0),(1),(2),(3),(4),(5),(6),(7),(8),(9),(10),"
                    "(11),(12),(13),(14),(15),(16),(17),(18),(19);");

        closeDB(presetDB);
    }
}

// Встановлює NULL у всіх полів по заданій віртуальній клавіші
bool DataBase::clear(int virtual_key)
{
    this->commands[virtual_key][0] = NULL;  // для назви команди
    this->commands[virtual_key][1] = NULL;  // для команди
    this->command_type[virtual_key] = -1;

    QString path = presetDB_path;

    if (openDB(this->presetDB, path) == true)
    {
        query = new QSqlQuery();
        query->prepare("UPDATE preset "
                       "SET commandName = NULL, "
                       "command = NULL, "
                       "commandType = -1 "
                       "WHERE virtualKey = ?;");
        query->addBindValue(virtual_key);
        query->exec();

        closeDB(presetDB);

        return true;
    }
    else
    {
        return false;
    }
}

// Заповнення масиву порядковими номерами віртуальних клавіш
void DataBase::fillVirtualKeys()
{
    for (int i = 0; i < 20; i++)
    {
        this->virtual_keys[i] = i;
    }
}

// Заповнення масиву типу команд значенням -1
void DataBase::fillCommandType()
{
    for (int i = 0; i < 20; i++)
    {
        this->command_type[i] = -1;
    }
}

// Встановлює всі поля для одного пресету
void DataBase::setValues(int _virtual_key, QString _command_name, int _command_type, QString _command)
{
    this->command_type[_virtual_key] = _command_type;
    this->commands[_virtual_key][0] = _command_name;
    this->commands[_virtual_key][1] = _command;

    setValuesInDB(_virtual_key);
}

// Встановлює всі поля для одного пресету в бд
void DataBase::setValuesInDB(int virtual_key)
{
    QString path = presetDB_path;

    if (openDB(presetDB, path) == true)
    {
        query = new QSqlQuery(presetDB);

        query->prepare("UPDATE preset "
                       "SET commandName = (:commandName), "
                       "command = (:command), "
                       "commandType = (:commandType)"
                       "WHERE virtualKey = (:virtualKey);");

        query->bindValue(":commandName", this->commands[virtual_key][0]);
        query->bindValue(":command", this->commands[virtual_key][1]);
        query->bindValue(":commandType", this->command_type[virtual_key]);
        query->bindValue(":virtualKey", virtual_key);
        query->exec();

        closeDB(presetDB);

    }
}

// Повертає команду по заданій віртуальній клавіші
QString DataBase::searchCommand(int virtual_key)
{
    return commands[virtual_key][1];
}

// Повертає назву команди по заданій віртуальній клавіші
QString DataBase::searchCommandName(int virtual_key)
{
    return commands[virtual_key][0];
}

// Повертає тип команди
int DataBase::searchCommandType(int virtual_key)
{
    return this->command_type[virtual_key];
}

// Метод для експорту БД
bool DataBase::exportDB(QString path)
{
    QString folder_path = path + "/" +this->preset_name + ".db";

    if (QFile::exists(presetDB_path) == true)
    {
        if (QFile::exists(folder_path) == true)
        {
             QFile::remove(folder_path);
        }
        QFile::copy(presetDB_path, folder_path);

        return true;
    }
    else
    {
        return false;
    }
}

// Перевірка валідації назви пресету
bool DataBase::isValid(QString DB_name)
{
    DB_name = DB_name.simplified().remove(' ');

    string utf8_DB_name = DB_name.toUtf8().constData();

    if (DB_name.size() > 200 || DB_name.size() < 3)
    {
        return false;
    }
    else
    {
        for (char c : utf8_DB_name)
        {
            switch(c)
            {
                case '\\': return false; break;
                case '/':  return false; break;
                case '"':  return false; break;
                case ':':  return false; break;
                case '*':  return false; break;
                case '?':  return false; break;
                case '<':  return false; break;
                case '>':  return false; break;
                case '|':  return false; break;
            }

        }
        return true;
    }
}

// Метод для імпорту БД
bool DataBase::importDB(QString DB_path)
{    
    QFileInfo fileinfo(DB_path);
    this->preset_name = fileinfo.baseName();

    QString folder_path = DB_path;
    QString this_path = "./" + this->preset_name + ".db";

    this->presetDB_path = folder_path;

    if (!checkExistPreset())
    {
        if (QFile::exists(DB_path) == true)
        {
            if (checkImportedDB() == true)
            {
                QFile::copy(folder_path, this_path);
                insertPreset();
                this->presetDB_path = this_path;

                  return true;
            }
            else
            {
                return false;
            }

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

// Метод для відкриття БД в папці
/*bool DataBase::findDB(QString DB_path)
{
    QFileInfo fileinfo(DB_path);
    this->preset_name = fileinfo.baseName();
    this->presetDB_path = DB_path;

    if (checkExistPreset() == true)
    {
        if (openDB(this->presetDB, presetDB_path) == true)
        {
            synchronizationWithDB();

            closeDB(this->presetDB);

            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}*/

// Деструктор: видалення динамічного об'єкта QsqlQuery *query
DataBase::~DataBase()
{
    delete query;
}

// Перевіряє структуру імпортованої БД
bool DataBase::checkImportedDB()
{
    QString DB_structure;
    QString DB_standard = "0virtualKeyINT1commandNameTEXT2commandTEXT3commandTypeINT";

    openDB(presetDB, presetDB_path);
    query = new QSqlQuery();
    query->exec("PRAGMA table_info(preset);");

    while(query->next())
    {
         DB_structure += query->value(0).toString();
         DB_structure += query->value(1).toString();
         DB_structure += query->value(2).toString();
    }

    closeDB(presetDB);

    return DB_structure == DB_standard? (true) : (false);

}
