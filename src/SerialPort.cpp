#include <windows.h>
#include "SerialPort.h"

// It's a long function, moved to the bottom for clarity.
static DCB InitDCB(SerialParity parity, int rate);

bool SerialPort::Connect(const char *port, int rate, SerialParity parity)
{
    handle = CreateFileA(
        port, GENERIC_READ | GENERIC_WRITE,
        0, NULL, OPEN_EXISTING, NULL, NULL
    );
    if (handle == INVALID_HANDLE_VALUE)
        return false;

    SetCommMask(handle, 0);

    COMMTIMEOUTS cto = { 0, 0, 0, 0, 0 };
    SetCommTimeouts(handle, &cto);

    DCB dcb = InitDCB(parity, rate);
    SetCommState(handle, &dcb);

    return true;
}

void SerialPort::Disconnect(void)
{
    CloseHandle(handle);
}

void SerialPort::SendChar(char data)
{
    SendArray(&data, 1);
}

void SerialPort::SendArray(const char *buffer, int len)
{
    unsigned long bytesWritten;
    WriteFile(handle, buffer, len, &bytesWritten, NULL);
}

void operator << (SerialPort& stream, char c)
{
    stream.SendArray(&c, 1);
}

void operator << (SerialPort& stream, const char *ptr)
{
    int len = 0;
    const char* array = ptr;
    while (*ptr != '\0')
    {
        len++;
        ptr++;
    }
    stream.SendArray(array,len);
    stream.SendChar(0x0d);
    stream.SendChar(0x0a);
}


// Initialize a compatible DCB structure with the given options.
static DCB InitDCB(SerialParity parity, int rate)
{
    DCB dcb;
    memset(&dcb, 0, sizeof(dcb));
    dcb.DCBlength = sizeof(dcb);

    dcb.BaudRate = rate;

    switch (parity)
    {
    case SerialParity::None:
        dcb.Parity = NOPARITY;
        dcb.fParity = 0;
        break;
    case SerialParity::Even:
        dcb.Parity = EVENPARITY;
        dcb.fParity = 1;
        break;
    case SerialParity::Odd:
        dcb.Parity = ODDPARITY;
        dcb.fParity = 1;
        break;
    }

    dcb.StopBits = TWOSTOPBITS;
    dcb.ByteSize = 7;

    dcb.fOutxCtsFlow = 0;
    dcb.fOutxDsrFlow = 0;
    dcb.fDtrControl = DTR_CONTROL_DISABLE;
    dcb.fDsrSensitivity = 0;
    dcb.fRtsControl = RTS_CONTROL_DISABLE;
    dcb.fOutX = 0;
    dcb.fInX = 0;

    dcb.fErrorChar = 0;
    dcb.fBinary = 1;
    dcb.fNull = 0;
    dcb.fAbortOnError = 0;
    dcb.wReserved = 0;
    dcb.XonLim = 2;
    dcb.XoffLim = 4;
    dcb.XonChar = 0x13;
    dcb.XoffChar = 0x19;
    dcb.EvtChar = 0;

    return dcb;
}
