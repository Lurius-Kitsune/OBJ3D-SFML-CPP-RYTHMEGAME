#include "BeatMap.h"
#include "Level.h"
#include "GameManager.h"
#include "BeatMapLevel.h"
#include "FileManager.h"

using namespace File;

BeatMap::BeatMap(const string& _path)
{
	path = _path;
	isLoaded = false;

	vector<string> _contentFile = M_FILE.ReadFile<string>(string(path).c_str());
	vector<string> _content = SplitString(_contentFile[0], '|');
	missDamage = stoi(_content[1]);
	difficulty = _content[0];

	notes = map<Time, pair<NoteType, bool>>();
	timeStamp = Clock();
	perfectScoreMin = 0;
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
	timeStamp.stop();
	timeStamp.restart();
}

void BeatMap::Update()
{
	if (isLoaded)
	{
		float _currentTime = GetCurrentTime().asSeconds();
		// on prend que 2 chiffre apres la virgule
		_currentTime = CAST(int, _currentTime * 100) / 100.0f;
		Time _time = Time(seconds(_currentTime));
		if(notes.contains(_time))
		{
			pair<NoteType, bool>& _noteType = notes[_time];
			if (!_noteType.second)
			{
				NoteDetector* _triggerNote = Cast<BeatMapLevel>(M_GAME.GetCurrent())->GetNoteDetector(_noteType.first);
				Cast<BeatMapLevel>(M_GAME.GetCurrent())->GetNoteSpawner(_noteType.first)->Spawn();
				_noteType.second = true;
			}
		}
	}
	else
	{
		LOG(Error, "BeatMap not loaded !");
	}
}

void BeatMap::Stop()
{
	for(pair<Time, pair<NoteType, bool>> _note : notes)
	{
		_note.second.second = false;
	}
}


void BeatMap::LoadBeatMap()
{
	if (!isLoaded)
	{
		vector<string> _contentFile = M_FILE.ReadFile<string>(string(path).c_str());
		
		//Nombre de ligne total
		const u_int _totalLine = CAST(u_int, _contentFile.size() - 1);

		//Pourcentage de progressino de la map
		for (u_int _i = 1; _i <= _totalLine; _i++)
		{
			vector<string> _content = SplitString(_contentFile[_i], '|');
			notes.insert({ Time(seconds((stof(_content[0])))), {NoteType(stoi(_content[1])), false} });
			LOG(Display, "Progress : " + to_string((float)notes.size() / _totalLine * 100) + "%)");
			perfectScoreMin += NR_PERFECT;
		}

		LOG(Display, "BeatMap loaded ! Nb Note : " + to_string(notes.size()));
		isLoaded = true;
	}
	else
	{
		LOG(Error, "BeatMap already loaded !");
	}
}
