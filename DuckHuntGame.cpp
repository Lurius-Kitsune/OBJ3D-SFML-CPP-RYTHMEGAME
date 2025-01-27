#include "DuckHuntGame.h"
#include "Level.h"
#include "TimerManager.h"
#include "AudioManager.h"
#include "CameraManager.h"

DuckHuntGame::DuckHuntGame() : Game()
{
	background = nullptr;
    music = nullptr;
	floor = nullptr;
	ball = nullptr;
}


void DuckHuntGame::Start()
{
	Super::Start();

    Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(463.0f, 260.0f) * 2.0f, "background", JPG)));
    //music = M_AUDIO.PlaySample<MusicSample>("Crab_Rave", MP3, seconds(50.0f));

    const Vector2f& _floorSize = Vector2f(window.getSize().x, window.getSize().y * 0.2f);
    floor = Level::SpawnActor(MeshActor(RectangleShapeData(_floorSize, "Floor", PNG, true)));
    const float _posX = 0.0f;
    const float _posY = window.getSize().y * 0.8f;
    floor->SetPosition(Vector2f(_posX, _posY));
    floor->SetTextureRect(IntRect(Vector2i(), Vector2i(512 * 3, 512)));

    ball = Level::SpawnActor(Ball(50.0f));
    ball->SetOriginAtMiddle();
    ball->SetPosition(Vector2f(window.getSize().x * 0.5f, window.getSize().y * 0.2f));

    platforme = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(200.0f, 20.0f), "Platforme", PNG, true)));
    platforme->SetPosition(Vector2f(window.getSize().x * 0.45f, window.getSize().y * 0.5f));
    platforme->SetOriginAtMiddle();
    platforme->Rotate(degrees(30.0f));
    Shape* _platformeShape = platforme->GetMesh()->GetShape()->GetDrawable();
    const FloatRect& _platformeRect = _platformeShape->getGlobalBounds();

    MeshActor* _platformHitbox = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(_platformeRect.size.x, _platformeRect.size.y), "Platforme", PNG, true)));
    _platformHitbox->SetPosition(Vector2f(window.getSize().x * 0.45f, window.getSize().y * 0.5f));
    _platformHitbox->SetOriginAtMiddle();
    //_platformHitbox->Rotate(degrees(30.0f));
    _platformHitbox->GetMesh()->GetShape()->GetDrawable()->setOutlineColor(Color::Red);
    _platformHitbox->GetMesh()->GetShape()->GetDrawable()->setOutlineThickness(1.0f);
    _platformHitbox->GetMesh()->GetShape()->GetDrawable()->setFillColor(Color::Transparent);
    ////TODO check
    //if (MovementComponent* _movement = duck->GetComponent<MovementComponent>())
    //{
    //    _movement->SetTarget(_target);
    //}
}

bool DuckHuntGame::Update()
{
	Super::Update();
    Shape* _ballShape = ball->GetMesh()->GetShape()->GetDrawable();
    const FloatRect& _ballRect = _ballShape->getGlobalBounds();

    Shape* _floorShape = floor->GetMesh()->GetShape()->GetDrawable();
    const FloatRect& _floorRect = _floorShape->getGlobalBounds();

    if (const optional<FloatRect>& _intersectRect = _ballRect.findIntersection(_floorRect))
    {
        /*const Vector2f& _normal = Vector2f(0.0f, -1.0f);*/
        const Vector2f& _normal = ComputeNormal(_intersectRect.value());
        ball->ApplyBounce(_normal);
    }

    Shape* _platformeShape = platforme->GetMesh()->GetShape()->GetDrawable();
    const FloatRect& _platformeRect = _platformeShape->getGlobalBounds();

    if(const optional<FloatRect> _intersectRect = _ballRect.findIntersection(_platformeRect))
	{
		const Vector2f& _normal = ComputeNormal(_intersectRect.value());
		ball->ApplyBounce(_normal);
	}

    return IsOver();
}

void DuckHuntGame::Stop()
{
	Super::Stop();
}

Vector2f DuckHuntGame::ComputeNormal(const FloatRect& _rect)
{
    const Vector2f& _normal = { -_rect.size.y, _rect.size.x };
    const float _norme = Lengh(_normal);
    return _normal / _norme;
}

float DuckHuntGame::Lengh(const Vector2f& _vector)
{
    return sqrtf(pow(_vector.x, 2) + pow(_vector.y, 2));
}
