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
		InterpretResult(-1.0f, false);
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
		InterpretResult(_distanceNormalised, _isAfterTrigger);
	}
	else
	{
		LOG(Display, "Missed");
		InterpretResult(-1.0f, false);
	}
	_note->Destroy();
	// Envoyer cela A giveScore

}

void DetectNoteComponent::InterpretResult(const float _precision, const bool _isAfter)
{
	BeatMapLevel* _level = Cast<BeatMapLevel>(M_GAME.GetCurrent());
	NoteDetector* _detector = Cast<NoteDetector>(owner);
	if (_precision >= 0.0f && _precision <= 0.1f)
	{
		_level->ComputeNoteResult(NR_PERFECT, _detector);
	}
	else if (_precision > 0.1f && _precision <= 0.2f)
	{
		_level->ComputeNoteResult(NR_GOOD, _detector);
	}
	else if (_precision < 0.0f)
	{
		_level->ComputeNoteResult(NR_MISS, _detector);
	}
	else
	{
		_level->ComputeNoteResult(_isAfter ? NR_TOOLATE : NR_TOOEARLY, _detector);
	}

}
