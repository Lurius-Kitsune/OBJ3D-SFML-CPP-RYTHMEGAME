#include "BeatMap.h"
#include "Level.h"
#include "GameManager.h"
#include "MargeurythmeGame.h"

BeatMap::BeatMap(const string& _path)
{
	path = _path;
	isLoaded = false;

	vector<string> _contentFile = ReadAllFile(path);
	vector<string> _content = SplitString(_contentFile[0], '|');
	missDamage = stoi(_content[1]);
	difficulty = _content[0];

	notes = map<Time, NoteType>();
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
			NoteType _noteType = notes[_time];
			NoteDetector* _triggerNote = Cast<MargeurythmeGame>(M_GAME.GetCurrent())->GetNoteDetector()[_noteType];
			Level::SpawnActor(Note(_noteType, _triggerNote))->SetPosition(Vector2f(60.0f + 120.0f * _noteType, 0));
		}
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
		vector<string> _contentFile = ReadAllFile(path);
		
		//Nombre de ligne total
		const u_int _totalLine = CAST(u_int, _contentFile.size() - 1);

		//Pourcentage de progressino de la map
		for (u_int _i = 1; _i <= _totalLine; _i++)
		{
			vector<string> _content = SplitString(_contentFile[_i], '|');
			notes.insert(pair<Time, NoteType>(Time(seconds((stof(_content[0])))), NoteType(stoi(_content[1]))));
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
