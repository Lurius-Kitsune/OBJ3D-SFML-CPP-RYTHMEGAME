#include "Tracks.h"
#include "FileManager.h"

using namespace File;

Tracks::Tracks(const string& _path)
{
	path = _path;
	music = new MusicSample(_path + "\\music.mp3");
	music->Stop();
	currentBeatMap = nullptr;
	Init();
}

Tracks::~Tracks()
{
}

void Tracks::Start(const string& _difficulty)
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

void Tracks::Init()
{
	set<string> _info = M_FILE.ReadFile<string>(string(path + "\\info").c_str());
	if (_info.size() < 3)
	{
		LOG(Error, "Missing Information" + path);
		return;
	}
	vector<function<void(const string& _info)>> _infoInit
	{
		[&](const string& _info)
		{
			string _infoTemp = _info; 
			artist = InitInfo(_infoTemp);
			LOG(Error, artist);
		},
		[&](const string& _info) 
		{
			//TODO faire une surcharge de Init Info pour avoir BeatMap


		},
		[&](const string& _info) 
		{
			string _infoTemp = _info;
			title = InitInfo(_infoTemp);
			LOG(Error, title);
		},
	};

	int _index = 0;
	for (const string& _infoLine : _info)
	{
		_infoInit[_index](_infoLine);
		_index++;
	}

	duration = music->GetDuration();
	//const u_int& _beatMapInfo = CAST(u_int, _info.size());
	//for (u_int _i = 2; _i < _beatMapInfo; _i++)
	//{
	//	BeatMap _beatMap = BeatMap(path + "/" + _info[_i] + ".txt");
	//	beatMaps.insert({ _beatMap.GetDifficulty(), _beatMap });
	//}
}

string Tracks::InitInfo(const string& _infoLine)
{
	string _temp; 
	_temp = CAST(string, _infoLine.substr(_infoLine.find("{") + 1));
	return _temp;
}

bool Tracks::operator < (Tracks _other) const 
{
	return title < _other.title;
}

