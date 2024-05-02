//
// Created by vasily on 04.09.23.
//

#ifndef CLIENTAGENT_SERIALQT_H
#define CLIENTAGENT_SERIALQT_H

#endif //CLIENTAGENT_SERIALQT_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
//#include <QDebug>
#include <boost/algorithm/hex.hpp>
#include <iostream>

class SerialQT
{
    std::string device_name;
    QSerialPort *SerialPort = new QSerialPort;
public:
    explicit SerialQT(std::string name);
    void init_serial_connection();
    std::string isOpenSerialPort();
    std::string read_from_token(int timeout=30000);
    void close_serial_connection();
    std::string show_error_string();
};
