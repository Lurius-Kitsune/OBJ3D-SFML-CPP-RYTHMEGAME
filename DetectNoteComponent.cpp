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
	if (!_note)
	{
		GiveScore(-1.0f, false);
		return;
	}
	// Savoir à combien de difference elle est entre la globaxBox et l'origine
	const FloatRect& _ownerRect = Cast<NoteDetector>(owner)->GetHitbox();
	if(_ownerRect.findIntersection(_note->GetHitbox()) && _note->GetType() == detectType)
	{
		//Calculer la precision
		const float _distance = Distance(owner->GetPosition(), _note->GetPosition());
		const float _distanceNormalised = _distance / 100.0f;
		const bool _isAfterTrigger = _note->GetPosition().y > owner->GetPosition().y;
		LOG(Display, "Distance: " + std::to_string(_distance));
		LOG(Display, "Distance Normalised: " + std::to_string(_distanceNormalised));
		GiveScore(_distanceNormalised, true);
	}
	else
	{
		LOG(Display, "Missed");
		GiveScore(-1.0f, false);
	}
	_note->Destroy();
	// Envoyer cela A giveScore

}

void DetectNoteComponent::GiveScore(const float _precision, const bool _isAfter)
{
	BeatMapLevel* _level = Cast<BeatMapLevel>(M_GAME.GetCurrent());
	if (_precision >= 0.0f && _precision <= 0.1f)
	{
		_level->AddScore(NR_PERFECT);
		_level->IncrementCombo();
	}
	else if (_precision > 0.1f && _precision <= 0.2f)
	{
		_level->AddScore(NR_GOOD);
		_level->IncrementCombo();
	}
	else if (_precision < 0.0f)
	{
		_level->AddScore(NR_MISS);
		_level->ResetCombo();
	}
	else
	{
		_level->AddScore(_isAfter ? NR_TOOLATE : NR_TOOEARLY);
		_level->IncrementCombo();
	}

}
