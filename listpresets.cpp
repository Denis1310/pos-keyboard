#include "listpresets.h"

QString ListPresets::getPreset(int index)
{
    return presets.at(index);
}

int ListPresets::getSize()
{
    return presets.size();
}

ListPresets::ListPresets()
{
    readDB();
}

ListPresets::~ListPresets()
{
    delete query;
}

void ListPresets::readDB()
{
    QString path = "./Data/Database.db";

    this->presets_DB = QSqlDatabase::addDatabase("QSQLITE");
    this->presets_DB.setDatabaseName(path);

    this->presets_DB.open();
    query = new QSqlQuery();
    query->exec("SELECT presetName FROM presets;");

    while(query->next())
    {
        this->presets.push_back(query->value(0).toString());
    }

    this->presets_DB.close();
}

bool ListPresets::addPreset(QString name)
{
    if (db.isValid(name) == true)
    {
        if (this->db.createDB(name) == true)
        {
            this->presets.push_back(name);
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

bool ListPresets::removePreset(QString name)
{
    if (db.readDB(name) == true)
    {
        if (db.deleteDB() == true)
        {
            presets.removeOne(name);
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

bool ListPresets::changePreset(QString name)
{
    if (presets.contains(name))
    {
        config.setLastPreset(name);
          return true;
    }
    else
    {
        return false;
    }
}

bool ListPresets::isEmpty()
{
    return presets.isEmpty() ? (true) : (false);
}
