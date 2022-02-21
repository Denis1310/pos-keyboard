#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);

    #ifdef __linux__
        ui->autoStartCheckBox->hide();
        ui->autoStartLabel->hide();
    #endif

    #ifdef _WIN32 || _WIN64
        prevLoadState = (bool)ui->autoStartCheckBox->checkState();
    #endif
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::on_QtVersionButton_clicked()
{
    QMessageBox::aboutQt(this, "About Qt");
}

void SettingsWindow::on_doneButton_clicked()
{
    db.setAwait(ui->delaySpinBox->value());
    #ifdef _WIN32 || _WIN64
        db.setAutoload((bool)ui->autoStartCheckBox->checkState());

        if ((bool)ui->autoStartCheckBox->checkState() != prevLoadState)
        {
            QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);

            if ((bool)ui->autoStartCheckBox->checkState())
            {
//                settings.setValue("POS_Keyboard", QDir::toNativeSeparators(QCoreApplication::applicationFilePath()));
                settings.sync();
            }
            else
            {
//                settings.remove(POS_Keyboard);
            }
        }
    #endif

    this->close();
}

void SettingsWindow::on_backButton_clicked()
{
    this->close();
}

