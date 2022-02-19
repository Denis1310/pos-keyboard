#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectingStatus = new QLabel();

    printPresets();

    // TODO:
    connectingStatus->setText(((isConnected) ? ("Статус: Підключено") : ("Статус: Не підключено")));

    ui->statusbar->addPermanentWidget(connectingStatus);

    // Завантаження останього вибраного пресету
    db.readDB(conf.getLastPreset());
    ui->presetsComboBox->setCurrentText(conf.getLastPreset());
    loadKeys();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printPresets()
{
    for (int i = 0; i < list.getSize(); ++i)
    {
        ui->presetsComboBox->addItem(list.getPreset(i));
    }
}

// Виведення створених команд для клавіш в UI
void MainWindow::loadKeys()
{
    for (int i = 0, x = 0, y = 0; i < 20; ++i)
    {
        ui->commandTable->model()->setData(ui->commandTable->model()->index(y, x), db.searchCommandName(i));

        ++x;
        if (x == 4)
        {
            ++y;
            x = 0;
        }
    }
}

// TODO:
void MainWindow::on_commandTable_cellDoubleClicked(int row, int column)
{
    CommandWindow *commandWindow = new CommandWindow;
    commandWindow->setNum(tableToList(row, column));
    commandWindow->setModal(true);
    commandWindow->exec();

}

// Конвертує
int MainWindow::tableToList(int row, int column)
{
    switch (row)
    {
        case 0: switch (column)
                {
                    case 0: return 0;
                    case 1: return 1;
                    case 2: return 2;
                    case 3: return 3;
                };

        case 1: switch (column)
                {
                    case 0: return 4;
                    case 1: return 5;
                    case 2: return 6;
                    case 3: return 7;
                };

        case 2: switch (column)
                {
                    case 0: return 8;
                    case 1: return 9;
                    case 2: return 10;
                    case 3: return 11;
                };

        case 3: switch (column)
                {
                    case 0: return 12;
                    case 1: return 13;
                    case 2: return 14;
                    case 3: return 15;
                };

        case 4: switch (column)
                {
                    case 0: return 16;
                    case 1: return 17;
                    case 2: return 18;
                    case 3: return 19;
                };

    };
}

// Вибір налаштувань
void MainWindow::on_settingsAction_triggered()
{
    SettingsWindow *settingsWindow = new SettingsWindow;
    settingsWindow->setModal(true);
    settingsWindow->exec();
}

// Вибір імпорту пресету
void MainWindow::on_importAction_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(0, "Імпорт пресету", "", "*.db");
    db.importDB(fileName);
}

// Вибір експорту пресету
void MainWindow::on_exportAction_triggered()
{
    QFileDialog directoryName;
    directoryName.setOptions(QFileDialog::ShowDirsOnly);
    directoryName.setFileMode(QFileDialog::Directory);

    QString path = directoryName.getExistingDirectory();

    db.exportDB(path);
}

// Вибір видалення пресету
void MainWindow::on_deleteAction_triggered()
{
    if (ui->presetsComboBox->count() > 2)
    {
        if (ui->presetsComboBox->currentIndex() != 0)
        {
            if (QMessageBox::warning(this, "", "Ви справді хочете видалити " + db.getPresetName(),
                                     QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel)
                == QMessageBox::Ok)
            {
                if (ui->presetsComboBox->currentIndex() != 0 && ui->presetsComboBox->currentIndex() != -1)
                {
                    db.deleteDB();
                    list.removePreset(db.getPresetName());

                    // Видалення пресету з ComboBox
                    int val = ui->presetsComboBox->currentIndex();
                    ui->presetsComboBox->setCurrentIndex(-1);
                    ui->presetsComboBox->removeItem(val);
                }
            }
        }
    }
    else
    {
        QMessageBox::warning(this, "", "Не можливо видалити пресет. Повинен існувати мінімум один пресет");
    }
}

void MainWindow::on_presetsComboBox_currentIndexChanged(int index)
{
    bool confirmNewPreset = false;

    if (index == 0)
    {
        QString presetName = QInputDialog::getText(this, "Новий пресет", "Назва:", QLineEdit::Normal,
                                                   "Назва пресету", &confirmNewPreset);

        if (confirmNewPreset)
        {
            if (presetName != "Новий пресет" && db.isValid(presetName))
            {
                db.createDB(presetName);
                list.addPreset(presetName);

                // Добавлення пресету в ComboBox та його вибір
                ui->presetsComboBox->addItem(presetName);
                ui->presetsComboBox->setCurrentIndex(ui->presetsComboBox->count()-1);
                conf.setLastPreset(presetName);
            }
            else
            {
                QMessageBox::critical(this, "Помилка", "Введіть коректну назву");
            }
        }
        else
        {
            ui->presetsComboBox->setCurrentText(conf.getLastPreset());
        }
    }
    else
    {
        db.readDB(ui->presetsComboBox->itemText(index));
        conf.setLastPreset(ui->presetsComboBox->itemText(index));
    }
}
