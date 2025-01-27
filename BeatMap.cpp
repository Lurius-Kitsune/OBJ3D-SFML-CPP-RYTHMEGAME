#include "BeatMap.h"
#include <fstream>
#include "Level.h"

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
	timeStamp = new Clock();
	timeStamp->restart();
}

void BeatMap::Update()
{
	if (isLoaded)
	{
		/*if(notes.contains(GetCurrentTime()))
		{
			Note _note = notes[GetCurrentTime()];
			Level::SpawnActor(_note);
		}*/
	}
	else
	{
		LOG(Error, "BeatMap not loaded !");
	}
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
		const u_int& _totalLine = count(istreambuf_iterator<char>(_file), istreambuf_iterator<char>(), '\n');
		_file.seekg(0, ios::beg);

		string line;
		getline(_file, line);
		vector<string> _content = SplitString(line, '|');
		missDamage = stoi(_content[1]);
		difficulty = _content[0];

		//Pourcentage de progressino de la map
		while (getline(_file, line))
		{
			_content = SplitString(line, '|');
			notes.insert(pair<float, Note>(stof(_content[0]), Note(NoteType(stoi(_content[1])))));
			LOG(Display, "Progress : " + to_string((float)notes.size() / _totalLine * 100) + "%)");
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
