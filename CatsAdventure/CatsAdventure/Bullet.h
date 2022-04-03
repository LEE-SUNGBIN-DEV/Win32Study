#pragma once
#include "Projectile.h"

const Vector2f bulletScale = { 40.f, 40.f };
const float bulletSpeed = 800.f;
const int bulletDamage = 5;

class Bullet :
    public Projectile
{
private:
    int mDamage;

public:
    Bullet();
    ~Bullet();

    virtual void Update();
    virtual void Render(HDC _bitmapDC);

    virtual void OnCollision(Collider* _opponent);
    virtual void OnCollisionEnter(Collider* _opponent);
    virtual void OnCollisionExit(Collider* _opponent);

    virtual Bullet* Clone() { return new Bullet(*this); }

    // get
    int GetDamage() { return this->mDamage; }
    
    // set
    void SetDamage(int _damage) { this->mDamage = _damage; }
};

