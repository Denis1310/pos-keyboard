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

void CommandWindow::setNum(int other)
{
    num = other;
}

void CommandWindow::on_backButton_clicked()
{
    close();
}


void CommandWindow::on_doneButton_clicked()
{

}

std::string CommandWindow::createCommand(int type, std::string path)
{
    std::string command;

    if (type == commandType::termCommand)
    {
        return path;
    }
    else
    {
        switch (type)
        {
        #ifdef _WIN32 || _WIN64
            case commandType::openLink:
            case commandType::openProgram:
            case commandType::openFile:
            case commandType::openDirectory:
                command = "start";
                break;

            case commandType::shortcut:
            case commandType::specialKey:
                command = "VK key";
                break;
        #elif __linux__
            case commandType::openLink:
            case commandType::openFile:
            case commandType::openDirectory:
                command = "open";
                break;

            case commandType::openProgram:
                command = "./";
                break;

            case commandType::shortcut:
                command = "xdotool key";
                break;
        #endif
        }

        command += " " + path;

        return command;
    }
}

bool CommandWindow::runCommand(std::string command)
{
    char do_command[command.length() + 1];
    strcpy(do_command, command.c_str());

    #ifdef _WIN32 || _WIN64
        if (command.find("VK key") != -1)
    #elif __linux__
        if ((int)command.find("xdotool key") != -1)
    #endif
    {
        system(do_command);

        #ifdef _WIN32 || _WIN64
            command.replace(3, 3, "keyup");
        #elif __linux__
            command.replace(8, 3, "keyup");
        #endif
    }

    return !system(do_command);
}

