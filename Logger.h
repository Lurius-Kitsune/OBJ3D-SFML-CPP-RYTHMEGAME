#pragma once
#include "Macro.h"
#include "Color.h"
#include "CustomException.h"

//#define DEBUG
#ifdef DEBUG
    #define USE_DEBUG 1
#else
    #define USE_DEBUG 0
#endif // DEBUG

#define LOG(_verbosity, _msg) Logger::PrintLog(_verbosity, _msg, DEBUG_INFO)
#define WRITE_IN_LOG(_verbosity)        _verbosity >= Log
#define WRITE_IN_CONSOLE(_verbosity)    _verbosity > Log

enum VerbosityType
{
    VeryVerbose,
    Verbose,
    Log,
    Display,
    Warning,
    Error,
    Fatal,

    VT_COUNT
};

class VerbosityData
{
    Gradient color;
    string prefix;
    string text;
    string debug;
    bool useDebug;
    
public:
    VerbosityData(const VerbosityType& _type, const string& _text, const string& _debug,
                  const bool _useDebug = false)
    {
        ComputeUseDebug(_type);
        ComputeColor(_type);
        ComputePrefix(_type);
        text = _text;
        debug = _debug;
    }

private:
    void ComputeUseDebug(const VerbosityType& _type)
    {
        useDebug = set<VerbosityType>({ Warning, Error }).contains(_type);
    }
    void ComputeColor(const VerbosityType& _type)
    {
        if (_type >= VT_COUNT)
        {
            throw CustomException("Exception => invalid VerbosityType !");
        }

        const vector<Gradient>& _verbosityColors =
        {
            Gradient(ColorData(27, 27, 33), ColorData(37, 37, 51)),         //VERY VERBOSE
            Gradient(ColorData(55, 55, 61), ColorData(69, 69, 93)),         //VERBOSE
            Gradient(ColorData(100, 100, 119), ColorData(143, 143, 194)),   //LOG
            Gradient(ColorData(221, 221, 246), ColorData(122, 122, 236)),   //DISPLAY
            Gradient(ColorData(255, 231, 0), ColorData(255, 76, 17)),       //WARNING
            Gradient(ColorData(193, 6, 11), ColorData(249, 56, 67)),        //ERROR
            Gradient(ColorData(255, 0, 95), ColorData(118, 37, 184)),       //FATAL
        };

        color = _verbosityColors[_type];
    }
    void ComputePrefix(const VerbosityType& _type)
    {
        if (_type >= VT_COUNT)
        {
            throw CustomException("invalid VerbosityType !");
        }

        const vector<string>& _verbosityTexts =
        {
            "VeryVerbose",
            "Verbose",
            "Log",
            "Display",
            "Warning",
            "Error",
            "Fatal",
        };

        prefix = _verbosityTexts[_type];
    }

public:
    string RetrieveFullText(const bool _useColor = true, const bool _useTime = true) const;
};

class Logger
{
    static string logsPath;

private:
    static void WriteInLogs(const string& _text);
    static void WriteInConsole(const string& _text);

public:
    static void Reset();
    static void PrintLog(const VerbosityType& _type, const string& _text, const string& _debug = "");
    static void PrintLog(const VerbosityType& _type, const Vector2f& _vector, const string& _debug);
};