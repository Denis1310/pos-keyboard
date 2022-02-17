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

private:
    Ui::CommandWindow *ui;
};

#endif // COMMANDWINDOW_H
