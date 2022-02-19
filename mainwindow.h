#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QInputDialog>
#include <QMainWindow>
#include <QFileDialog>
#include <QLabel>
#include "commandwindow.h"
#include "settingswindow.h"
#include "database.h"
#include "listpresets.h"
#include "configuration.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_commandTable_cellDoubleClicked(int row, int column);
    void on_settingsAction_triggered();
    void on_importAction_triggered();
    void on_exportAction_triggered();
    void on_deleteAction_triggered();
    void on_presetsComboBox_currentIndexChanged(int index);
    void printPresets();
    void loadKeys();

private:
    Ui::MainWindow *ui;
    QLabel *connectingStatus;
    bool isConnected{false};
    DataBase db;
    Configuration conf;
    ListPresets list;
};
#endif // MAINWINDOW_H
