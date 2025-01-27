#include "Logger.h"
#include "TimerManager.h"

/// VerbosityData
string VerbosityData::RetrieveFullText(const bool _useColor, const bool _useTime) const
{
    string _fullText;

    if (_useTime)
    {
        _fullText += "[" + M_TIMER.GetCurrentRealTime() + "]";
    }

    _fullText += " " + prefix + ": " + text;

    if (USE_DEBUG || useDebug)
    {
        _fullText += " " + debug;
    }

    return _useColor ? color.GradientString(_fullText) : _fullText;
}

/// Logger
string Logger::logsPath = "Logs/log.txt";

void Logger::WriteInConsole(const string& _text)
{
	cout << _text << endl;
}

void Logger::WriteInLogs(const string& _text)
{
    ofstream _stream = ofstream(logsPath, ios_base::app);
    _stream << _text << endl;
}

void Logger::Reset()
{
    ofstream(logsPath, ios_base::trunc);
}

void Logger::PrintLog(const VerbosityType& _type, const string& _text, const string& _debug)
{
	if (WRITE_IN_LOG(_type))
	{
		const VerbosityData& _verbosity = VerbosityData(_type, _text, _debug);
		WriteInLogs(_verbosity.RetrieveFullText(false));

		if (WRITE_IN_CONSOLE(_type))
		{
			WriteInConsole(_verbosity.RetrieveFullText(true));
		}
	}
}
void Logger::PrintLog(const VerbosityType& _type, const Vector2f& _vector, const string& _debug)
{
	const string& _vectorString = "X: " + to_string(_vector.x) + " Y: " + to_string(_vector.y);
	PrintLog(_type, _vectorString, _debug);
}