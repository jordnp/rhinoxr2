#include "GCodeParser.h"

#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <string>

// Behold: The STUPID_MODE macro.
// G-Code as we were taught versus as it actually is defined differ in the functionality of the I, J coordinates.
// AS WE WERE TAUGHT: I, J are absolute coordinates
// AS DEFINED: I, J are *relative coordinates* from the current X, Y position.
//
// If STUPID_MODE is definied, I,J will be absolute coordinates.
// 
//#define STUPID_MODE

GCodeParser GCodeParser::FromFile(const char* path)
{
    // The C++ way of doing this displeases me, so this is the C style.
    FILE* fp;
    fp = fopen(path, "r");
    if (!fp)
    {
        fprintf(stderr, "[GCodeParser] Failed to open file '%s'\n", path);
        exit(1);
    }

    // Read entire file as a null-terminated string
    fseek(fp, 0, SEEK_END);
    size_t len = (size_t)ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* data = (char*)malloc(len + 1);
    if (!data)
    {
        fprintf(stderr, "[GCodeParser] Out of memory\n");
        exit(1);
    }

    size_t bytesRead = fread(data, 1, len, fp);
    data[bytesRead] = 0;
    fclose(fp);

    GCodeParser p;
    p.ownsSrc = true;
    p.src = data;
    return p;
}

GCodeParser GCodeParser::FromText(const char* src)
{
    GCodeParser p;
    p.ownsSrc = false;
    p.src = src;

    return p;
}

static bool IsWhitespace(char c)
{
    return isspace(c);
}

void GCodeParser::SkipWhitespace()
{
    while (IsWhitespace(src[index]))
        index++;
}

void GCodeParser::ExpectEndOfLine()
{
    for (;;)
    {
        if (src[index] == 0 || src[index] == '\n')
            return;
        else if (IsWhitespace(src[index]))
        {
            index++;
            continue;
        }
        else
        {
            index++;
            //fprintf(stderr, "Parser: expected end of line or file, got '%c' (byte %X)\n", src[index], src[index]);
            //exit(1);
        }
    }
}

int GCodeParser::ExpectG()
{
    if (src[index] != 'G')
    {
        fprintf(stderr, "Parser: expected G command, got '%c' (byte %X)\n", src[index], src[index]);
        exit(1);
    }
    index++;
    if (src[index] == '0')
    {
        if (isdigit(src[index + 1]))
        {
            index++;
        }
    }
    int code = src[index] - '0';
    index += 1;
    return code;
    
}

double GCodeParser::ReadDouble()
{
    // this sucks

    std::string Temp = "";
    while (isdigit(src[index]) || src[index] == '.' || src[index] == '-')
    {
        Temp.append(1, src[index]);
        index++;
    }

    double res = atof(Temp.c_str());
    return res;
}

void GCodeParser::ReadVars()
{
    while (src[index] != '\n' && src[index] != 0)
    {
        switch (src[index++])
        {
        case 'X':
            x = ReadDouble();
            break;
        case 'Y':
            y = ReadDouble();
            break;
        case 'I':
#ifdef STUPID_MODE
            i = ReadDouble();
#else
            i = lastX + ReadDouble();
#endif
            break;
        case 'J':
#ifdef STUPID_MODE
            j = ReadDouble();
#else
            j = lastY + ReadDouble();
#endif
            break;
        case ';':
            return;
        default:
            break;
        }
    }


}

Instr GCodeParser::NextInstr()
{
    while (IsWhitespace(src[index]))
    {
        index++;
    }
    Instr i = {};
    return i;
}

GCodeInstr GCodeParser::ParseLine()
{
    while (true)
    {
        if (src[index] == 'G' || src[index] == 0)
            break;
        index++;
    }
    if (src[index] == 0)
        return {GCodeInstrType::Eof};

    SkipWhitespace();
    

    GCodeInstrType type;
    int code = ExpectG();
    if (code == 0)
        type = GCodeInstrType::Move;
    else if (code == 1)
        type = GCodeInstrType::Line;
    else if (code == 2)
        type = GCodeInstrType::ArcCW;
    else if (code == 3)
        type = GCodeInstrType::ArcCCW;
    else if (code == 8)
        return { GCodeInstrType::Eof };
    else
    {
        fprintf(stderr, "Parser: bad G command '0%d'\n", code);
        exit(1);
    }

    ReadVars();

    ExpectEndOfLine();

    lastX = x;
    lastY = y;

    return { type, x, y, i, j };
}


