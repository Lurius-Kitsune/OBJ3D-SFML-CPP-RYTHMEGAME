#include "Track.h"
#include "FileManager.h"

using namespace File;

Track::Track(const string& _path)
{
	path = _path;
	music = new MusicSample(_path + "\\music.mp3");
	music->Stop();
	currentBeatMap = nullptr;
	info = TrackInfo();
	Init();
}

Track::~Track()
{
}

void Track::Start(const string& _difficulty)
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

void Track::Update()
{
	currentBeatMap->Update();
}

void Track::Stop()
{
	currentBeatMap->Stop();
	music->Stop();
}

void Track::Init()
{
	vector<string> _info = M_FILE.ReadFile<string>(string(path + "\\info").c_str());
	if (_info.size() < 3)
	{
		LOG(Error, "Missing Information" + path);
		return;
	}

	info = TrackInfo(_info[0], _info[1], music->GetDuration());
	const u_int& _beatMapInfo = CAST(u_int, _info.size());
	for (u_int _i = 2; _i < _beatMapInfo; _i++)
	{
		BeatMap _beatMap = BeatMap(path + "\\" + _info[_i]);
		beatMaps.insert({ _beatMap.GetDifficulty(), _beatMap });
	}
}

bool Track::operator < (Track _other) const 
{
	return info.title < _other.info.title;
}

