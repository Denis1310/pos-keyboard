#ifndef COMPORT_H
#define COMPORT_H

#include <QtSerialPort>

class ComPort
{
public:
    ComPort();
    ~ComPort();
    bool openPort();
    void closePort();
    void checkSH();
    void inPort();
    bool isConnected();
    int getVal();

private:
    QSerialPort *serial;
    QByteArray *data;
};

#endif // COMPORT_H
