#pragma once

// This is the class to open and operate on a serial port connection.
// This is the only Windows-specific code. For a Linux/BSD/other port, this is
// the class you need to rewrite. The rest of the code is platform-independent.

//TODO: dumb down, this program never needs the extra serial parity options.
// Make it more RhinoXR-specific (even parity, rate 9600).

#include <windows.h>

enum class SerialParity
{
    None, Odd, Even
};

// Serial port communication abstraction
class SerialPort
{
    HANDLE handle = INVALID_HANDLE_VALUE;
public:
    friend void operator << (SerialPort& stream, char c);
    friend void operator << (SerialPort& stream, const char *ptr);

    // Returns `true` if the connection is successfull, `false` otherwise.
    bool Connect(const char *port, int rate, SerialParity parity);

    // Does no error checking. Don't `Disconnect()` twice.
    void Disconnect();
    
    void SendChar(char c);
    void SendArray(const char *buffer, int len);

    // Future implementation: add GetChar/GetArray functions.
    // The Rhino XR-2 can send data to the host computer. This is most useful
    // to determine when a motor has completed its motion for optimal movement
    // speed. However in practice the arm and its support has a lot of bounce,
    // and a longer delay between movements is necessary, as such the flat
    // few hundred millisecond delay that is currently implemented is good enough.
};
