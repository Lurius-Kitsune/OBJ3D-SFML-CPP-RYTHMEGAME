#include "Ball.h"
#include "TimerManager.h"

Ball::Ball(const float _radius) : MeshActor(_radius)
{
    canMove = false;
	startPosition = Vector2f();
    velocity = Vector2f();
    mass = 80.0f;
    gravity = 9.81f;
    restitution = 0.85f;
    friction = 0.95f;
    groundLevel = 550.0f;

    SetOriginAtMiddle();
}

void Ball::BeginPlay()
{
    Super::BeginPlay();

    startPosition = GetPosition();
    new Timer([&]() { canMove = true; }, seconds(2.0f), true);
}

void Ball::Tick(const float _deltaTime)
{
    Super::Tick(_deltaTime);

    if (!canMove) return;

    // Appliquer la gravité
    velocity.y += gravity * mass * _deltaTime;

    // Calculer le déplacement
    const Vector2f& _displacement = velocity * _deltaTime;
    // Mettre à jour la position
    Move(_displacement);
}

void Ball::ApplyBounce(const Vector2f& _normal)
{
    ///////////////////////////////////////////////////////////
    Move(-_normal * 0.1f);
    ///////////////////////////////////////////////////////////
    // 
    // Calculer la projection de la vitesse sur la normale
    // Appliquer le rebond : inverser la composante normale de la vitesse
    velocity -= 2.0f * DotProduct(velocity, _normal) * _normal;

    // Réduire la vitesse en fonction du facteur de restitution
    velocity *= restitution;

    // Appliquer la friction à la composante tangentielle
    velocity.x *= friction;

    // Éviter de petites oscillations en annulant de faibles valeurs
    if (abs(velocity.x) < 1.0f)
    {
        velocity.x = 0.0f;
    }

    if (abs(velocity.y) < 1.0f)
    {
        velocity.y = 0.0f;
    }
}