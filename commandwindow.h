#ifndef COMMANDWINDOW_H
#define COMMANDWINDOW_H

#include "enums.h"
#include <QDialog>

namespace Ui {
class CommandWindow;
}

class CommandWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CommandWindow(QWidget *parent = nullptr);
    ~CommandWindow();

private slots:
    void on_typeComboBox_currentIndexChanged(int index);
    void on_backButton_clicked();
    void on_doneButton_clicked();

private:
    Ui::CommandWindow *ui;
};

#endif // COMMANDWINDOW_H
