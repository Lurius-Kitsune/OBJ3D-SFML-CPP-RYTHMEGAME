#include "DetectNoteComponent.h"
#include "BeatMapLevel.h"

DetectNoteComponent::DetectNoteComponent(Actor* _owner, const NoteType _type)
	: Component(_owner)
{
	detectType = _type;
}

DetectNoteComponent::DetectNoteComponent(Actor* _owner, const DetectNoteComponent& _other)
	: Component(_owner)
{
	detectType = _other.detectType;
}

void DetectNoteComponent::Tick(const float _deltaTime)
{
}

void DetectNoteComponent::DetectNote()
{
	//Savoir ou est la flêche
	Note* _note = Cast<BeatMapLevel>(M_GAME.GetCurrent())->GetNote();

	// Savoir à combien de difference elle est entre la globaxBox et l'origine
	const FloatRect& _ownerRect = Cast<NoteDetector>(owner)->GetHitbox();
	if(_ownerRect.contains(_note->GetPosition()) && _note->GetType() == detectType)
	{
		//Calculer la precision
		const float _distance = Distance(owner->GetPosition(), _note->GetPosition());
		const float _distanceNormalised = _distance / 100.0f;
		LOG(Display, "Distance: " + std::to_string(_distance));
		LOG(Display, "Distance Normalised: " + std::to_string(_distanceNormalised));
	}
	// Envoyer cela A giveScore

}

void DetectNoteComponent::GiveScore(const float _precision)
{
}
