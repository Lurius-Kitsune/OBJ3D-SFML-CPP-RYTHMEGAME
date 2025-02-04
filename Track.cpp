#include "Track.h"
#include "FileManager.h"
#include "AudioManager.h"

using namespace File;

Track::Track(const string& _path)
{
	path = _path;
	music = new MusicSample(_path + "\\music.mp3");
	music->Stop();
	currentBeatMap = nullptr;
	info = make_unique<TrackData>();
	Init();
}

Track::~Track()
{
}

void Track::PlayExtrait() const
{
	M_AUDIO.PlaySample<SoundSample>(music->GetPath(), MP3, music->GetDuration() / 2.0f, seconds(10.0f));
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
	UI::Image* _image = new UI::Image(path + "\\cover.png", RectangleShapeData(Vector2f(200.0f, 200.0f)), World);
	info = make_unique<TrackData>(_info[0], _info[1], music->GetDuration(), _image);
	const u_int& _beatMapInfo = CAST(u_int, _info.size());
	for (u_int _i = 2; _i < _beatMapInfo; _i++)
	{
		BeatMap _beatMap = BeatMap(path + "\\" + _info[_i]);
		beatMaps.insert({ _beatMap.GetDifficulty(), _beatMap });
	}
}

bool Track::operator < (Track _other) const 
{
	return info.get()->title < _other.info.get()->title;
}

