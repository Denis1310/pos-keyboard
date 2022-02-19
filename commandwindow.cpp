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
    if (ui->nameLine->text() != "" && (ui->typeComboBox->currentIndex() == 5 || ui->dataLine->text() != ""))
    {
        db->setValues(num, ui->nameLine->text(), num,
                      QString::fromStdString(createCommand(ui->typeComboBox->currentIndex(),
                                                       db->searchCommand(num).toStdString()))
                  );

        emit inputData();
        close();
    }
    else
    {
        QMessageBox::warning(this, "", "Введіть дані");
    }
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

void CommandWindow::setDB(DataBase &other)
{
    db = &other;
}

void CommandWindow::keyPress(int keyCode)
{
    int id;

    switch(keyCode)
    {
        case B00: id = 0;    break;
        case B01: id = 1;    break;
        case B02: id = 2;    break;
        case B03: id = 3;    break;
        case B04: id = 4;    break;
        case B05: id = 5;    break;
        case B06: id = 6;    break;
        case B07: id = 7;    break;
        case B08: id = 8;    break;
        case B09: id = 9;    break;
        case B10: id = 10;   break;
        case B11: id = 11;   break;
        case B12: id = 12;   break;
        case B13: id = 13;   break;
        case B14: id = 14;   break;
        case B15: id = 15;   break;
        case B16: id = 16;   break;
        case B17: id = 17;   break;
        case B18: id = 18;   break;
        case B19: id = 19;   break;
    }

    runCommand(createCommand(db->searchCommandType(id), db->searchCommand(id).toStdString()));
}
