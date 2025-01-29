#pragma once
#include "Singleton.h"
namespace File
{
	class FileManager : public Singleton<FileManager>
	{


	public:
		template<typename Type>
		set<Type> ReadFile(const char* _path, const string& _extension = "txt")
		{
			ifstream _stream = ifstream(string(_path) + "." + _extension);
			if (!_stream.is_open())
			{
				const string& _filePath = string(_path);
				const string& _finalFileName = _filePath.empty() ? "Unknown" : _filePath;
				LOG(Fatal, string("Impossible to read the file : " + _finalFileName));
				throw CustomException(string("Impossible to read the file : " + _finalFileName).c_str());
			}
			set<Type> _data;
			string _currentLine;
			while (getline(_stream, _currentLine))
			{
				Type _currentData = Type(_currentLine);
				_data.insert(_currentData);
			}
			return _data;
		}


		template<typename Type>
		set<Type> ReadFolder(const string& _path)
		{
			// TODO faire une s�curit�

			set<Type> _data;
			for (directory_entry _file : directory_iterator{ ".\\" + _path })
			{
				if (_file.exists())
				{
					const Type& _currentData = Type(_file.path().string());
					_data.insert(_currentData);
				}
				else
				{
					LOG(Fatal, string("No folder was found: " + _path));
					throw CustomException(string("No folder was found: " + _path).c_str());
				}
			}
			return _data;
		}
	};
};


