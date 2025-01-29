#include "Song.h"

Song::Song(const string& _path)
{
	path = "Assets/Musics/" + _path;
	music = new MusicSample(_path + "/music.mp3");
	music->Stop();
	currentBeatMap = nullptr;
	Init();
}

Song::~Song()
{
}

void Song::Start(const string& _difficulty)
{
	if(beatMaps.contains(_difficulty))
	{
		currentBeatMap = &beatMaps[_difficulty];
		currentBeatMap->Start();
		music->Play();
	}
	else
	{
		LOG(Error, "Difficulty not found");
	}
}

void Song::Init()
{
	vector<string> _info = ReadAllFile(path + "/info.txt");
	if (_info.size() < 3)
	{
		LOG(Error, "Missing Information" + path);
		return;
	}

	title = _info[0];
	artist = _info[1];
	duration = music->GetDuration();
	const u_int& _beatMapInfo = CAST(u_int, _info.size());
	for (u_int _i = 2; _i < _beatMapInfo; _i++)
	{
		BeatMap _beatMap = BeatMap(path + "/" + _info[_i] + ".txt");
		beatMaps.insert({ _beatMap.GetDifficulty(), _beatMap });
	}
}

