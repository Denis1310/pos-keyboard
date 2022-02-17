#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::printPresets()
{
    for (int i = 1; i < ui->presetsComboBox->count()-1; ++i)
    {
        ui->presetsComboBox->removeItem(i);
    }

    for (int i = 0; i < list.getSize(); ++i)
    {
        ui->presetsComboBox->addItem(list.getPreset(i));
    }
}

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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_commandTable_cellDoubleClicked(int row, int column)
{
    CommandWindow *commandWindow = new CommandWindow;
    commandWindow->setModal(true);
    commandWindow->exec();
}

void MainWindow::on_settingsAction_triggered()
{
    SettingsWindow *settingsWindow = new SettingsWindow;
    settingsWindow->setModal(true);
    settingsWindow->exec();
}

void MainWindow::on_importAction_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(0, "Імпорт пресету", "", "*.db");

    db.importDB(fileName);
}

void MainWindow::on_exportAction_triggered()
{
    QFileDialog directoryName;
    directoryName.setOptions(QFileDialog::ShowDirsOnly);
    directoryName.setFileMode(QFileDialog::Directory);

    QString path = directoryName.getExistingDirectory();

    db.exportDB(path);
}

void MainWindow::on_deleteAction_triggered()
{
    if (QMessageBox::warning(this, "Видалення пресету", "Ви справді хочете видалити " + db.getPresetName(),
                             QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel) == QMessageBox::Ok)
    {
        db.deleteDB();
        list.removePreset(db.getPresetName());
        printPresets();
    }
}


void MainWindow::on_presetsComboBox_currentIndexChanged(int index)
{
    bool ok = false;

    if (index == 0)
    {
        QString presetName = QInputDialog::getText(this, "Новий пресет", "Назва:", QLineEdit::Normal, "Назва пресету", &ok);

        if (ok)
        {
            if (presetName != "Новий пресет" && db.isValid(presetName))
            {
                db.createDB(presetName);
                list.addPreset(presetName);
                printPresets();
                ui->presetsComboBox->setCurrentIndex(ui->presetsComboBox->count()-1);
            }
            else
            {
                QMessageBox::critical(this, "Помилка", "Введіть коректну назву");
            }
        }
    }
    else
    {
        db.readDB(ui->presetsComboBox->itemText(index));
    }
}
