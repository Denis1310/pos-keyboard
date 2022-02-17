#include "commandwindow.h"
#include "ui_commandwindow.h"

CommandWindow::CommandWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CommandWindow)
{
    ui->setupUi(this);

#ifdef _WIN32 || _WIN64
    ui->typeComboBox->addItem("Спец клавіша");
#endif
}

CommandWindow::~CommandWindow()
{
    delete ui;
}

#include <QDebug>

void CommandWindow::on_typeComboBox_currentIndexChanged(int index)
{
    ui->dataLine->setDisabled(false);

    switch (index)
    {
    case commandType::openLink:
        ui->dataLabel->setText("Посиланя:");
        break;
    case commandType::openProgram:
        ui->dataLabel->setText("Шлях до програми:");
        break;
    case commandType::openFile:
        ui->dataLabel->setText("Шлях до файлу:");
        break;
    case commandType::openDirectory:
        ui->dataLabel->setText("Шлях до директорії:");
        break;
    case commandType::shortcut:
        ui->dataLabel->setText("Комбінація клавіш:");
        break;
    case commandType::hotKey:
        ui->dataLine->setDisabled(true);
        break;

    case commandType::termCommand:
        ui->dataLabel->setText("Команда:");
        break;

    #ifdef _WIN32 || _WIN64
    case commandType::specialKey:

        break;
    #endif
    }
}

