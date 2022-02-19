#ifndef COMMANDWINDOW_H
#define COMMANDWINDOW_H

#include "enums.h"
#include "database.h"
#include <QDialog>

namespace Ui {
class CommandWindow;
}

class CommandWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CommandWindow(QWidget *parent = nullptr);
    void setNum(int other);
    void setDB(DataBase& other);
    std::string createCommand(int, std::string);
    bool runCommand(std::string);
    void keyPress(int keyCode);
    ~CommandWindow();

private slots:
    void on_typeComboBox_currentIndexChanged(int index);
    void on_backButton_clicked();
    void on_doneButton_clicked();

private:
    Ui::CommandWindow *ui;
    DataBase *db;
    int num;
};

#endif // COMMANDWINDOW_H
