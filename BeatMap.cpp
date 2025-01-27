#include "BeatMap.h"
#include <fstream>

BeatMap::BeatMap(const string& _path)
{
	path = _path;
	isLoaded = false;
	missDamage = 0;
	timeStamp = nullptr;
	difficulty = "Easy";
	notes = map<float, Note>();
}

BeatMap::~BeatMap()
{
}

void BeatMap::Start()
{
	if (!isLoaded)
	{
		LoadBeatMap();
	}
	timeStamp = new Time();
}

void BeatMap::LoadBeatMap()
{
	if (!isLoaded)
	{
		ifstream _file = ifstream(path);
		if (!_file.is_open())
		{
			LOG(Error, "BeatMap file not found at " + path);
			return;
		}
		string line;
		getline(_file, line);
		vector<string> _content = SplitString(line, '|');
		missDamage = stoi(_content[1]);
		difficulty = _content[0];

		while (getline(_file, line))
		{
			_content = SplitString(line, '|');
			notes.insert(pair<float, Note>(stof(_content[0]), Note(NoteType(stoi(_content[1])))));
		}
		_file.close();
		LOG(Display, "BeatMap loaded ! Nb Note : " + to_string(notes.size()));
		isLoaded = true;
	}
	else
	{
		LOG(Error, "BeatMap already loaded !");
	}
}
