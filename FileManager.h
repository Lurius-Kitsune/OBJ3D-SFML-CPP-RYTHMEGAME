#pragma once
#include "Singleton.h"

namespace File
{
	class FileManager : public Singleton<FileManager>
	{
	public:
		vector<string> ReadFile(const char* _path, const string& _extension = "txt")
		{
			ifstream _stream = ifstream(string(_path) + "." + _extension);
			if (!_stream.is_open())
			{
				const string& _filePath = string(_path);
				const string& _finalFileName = "Impossible to read the file : " + _filePath.empty() ? "Unknown" : _filePath;
				LOG(Fatal, _finalFileName);
				throw CustomException(string("Impossible to read the file : " + _finalFileName).c_str());
			}

			vector<string> _data;
			string _currentLine;
			while (getline(_stream, _currentLine))
			{
				_data.push_back(_currentLine);
			}

			return _data;
		}

		vector<string> ReadFolder(const string& _path)
		{
			vector<string> _data;
			directory_entry _filePath = directory_entry(_path);

			if (!_filePath.exists())
			{
				LOG(Fatal, string("No folder was found: " + _path));
				throw CustomException(string("No folder was found: " + _path).c_str());
			}

			for (directory_entry _file : directory_iterator{ ".\\" + _path })
			{
				_data.push_back(_file.path().string());
			}

			return _data;
		}
	};
};