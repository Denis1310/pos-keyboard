#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "configuration.h"

#ifdef _WIN32 || _WIN64
    #include <QSettings>
#endif

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();

private slots:
    void on_QtVersionButton_clicked();
    void on_doneButton_clicked();
    void on_backButton_clicked();

private:
    Ui::SettingsWindow *ui;
    Configuration db;

    #ifdef _WIN32 || _WIN64
        bool prevLoadState;
    #endif
};

#endif // SETTINGSWINDOW_H
