#include "comport.h"

ComPort::ComPort()
{
    serial = new QSerialPort;
    data = new QByteArray;

    #ifdef __linux__
        checkSH();
    #endif
    openPort();
}

// Отримання значення з порту
int ComPort::getVal()
{
    if (serial->isOpen())
    {
        return 0;
    }
    else
    {
        QByteArray data = serial->readAll();
        return data.toInt();
    }
}

// Перевірка на існування скрипта для доступу до порта
void ComPort::checkSH()
{
    QString path = "./Scripts";
    QString script = path + "/" + "access.sh";
    QDir directory;

    if (!directory.exists(path))
    {
        directory.mkdir(path);
        if (!QFile::exists(script))
        {
            QFile file(script);
            QTextStream fout(&file);
            file.open(QIODevice::WriteOnly);
            fout << "#!/bin/bash\nsudo chmod +r /dev/ttyUSB0";
            system("chmod +x /Scripts/access.sh");
        }
    }
}

// Відкриття порта
bool ComPort::openPort()
{
    #ifdef __linux__
        system("./Scripts/access.sh");
        serial->setPortName("ttyUSB0");
    #elif _WIN32 || _WIN64
        serial.setPortName("COM1");
    #endif

    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data7);
    serial->setParity(QSerialPort::EvenParity);
    serial->setFlowControl(QSerialPort::HardwareControl);
    serial->setStopBits(QSerialPort::OneStop);
    serial->open(QIODevice::ReadOnly);

    return serial->isOpen();
}

// Чи підключений порт
bool ComPort::isConnected()
{
    return serial->isOpen();
}

// Закриття порта
void ComPort::closePort()
{
    serial->close();
}

ComPort::~ComPort()
{
    closePort();

    delete serial;
    delete data;
}
