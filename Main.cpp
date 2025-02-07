#include "Engine.h"
#include "LevelManager.h"
#include "MeshActor.h"
#include "BeatMapLevel.h"
#include "FileManager.h"
#include "Particle.h"

void InitConfig()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Logger::Reset();
}

int main()
{
	InitConfig();

	/*Level* _level = new Level("LevelDemo");
	_level->SpawnActor<MeshActor>(RectangleShapeData({ 50.f, 50.f }, "Wall", JPG));
	_level->SpawnActor<ParticleActor>(1000, 3.0f);
	M_LEVEL.SetLevel(_level);*/

	//new BeatMapLevel(*allTracks.begin[0], "Medium")
	vector<Track*> allTracks = File::M_FILE.ReadFolder<Track>(new Level("Demo"), "Assets\\Tracks");
	BeatMapLevel* _beatMapLevel = new BeatMapLevel(allTracks[0], "Medium");



	M_LEVEL.SetLevel(_beatMapLevel);

	Engine::GetInstance().Start();

	for (Track* _track : allTracks)
	{
		delete _track;
	}

	return EXIT_SUCCESS;
}