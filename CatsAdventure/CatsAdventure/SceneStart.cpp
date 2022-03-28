#include "pch.h"
#include "SceneStart.h"
#include "GameCore.h"
#include "GameObject.h"
#include "Player.h"
#include "Monster.h"
#include "Texture.h"
#include "PathManager.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "CollisionManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "MonsterMouse.h"
#include "MonsterSpider.h"

SceneStart::SceneStart()
{
	// Load Texture
	this->SetTexture(ResourceManager::GetInstance()->LoadTexture(L"BACKGROUND", L"\\texture\\backgroundStart.bmp"));

}
SceneStart::~SceneStart()
{

}

void SceneStart::Enter()
{
	// Player
	GameObject* player = new Player;

	player->SetPosition(Vector2f(50.f, 621.f));
	player->SetScale(Vector2f(50.f, 50.f));
	AddGameObject(player, OBJECT_TYPE::OBJECT_TYPE_PLAYER);

	// Monster
	MonsterMouse* monsterMouse = new MonsterMouse;

	monsterMouse->SetPosition(Vector2f(900.f, 621.f));
	monsterMouse->SetScale(Vector2f(50.f, 50.f));
	monsterMouse->SetOriginalPosition(monsterMouse->GetPosition());
	AddGameObject(monsterMouse, OBJECT_TYPE::OBJECT_TYPE_MONSTER);

	MonsterSpider* monsterSpider = new MonsterSpider;

	monsterSpider->SetPosition(Vector2f(900.f, 100.f));
	monsterSpider->SetScale(Vector2f(50.f, 50.f));
	monsterSpider->SetOriginalPosition(monsterSpider->GetPosition());
	AddGameObject(monsterSpider, OBJECT_TYPE::OBJECT_TYPE_MONSTER);

	// Collision Check
	CollisionManager::GetInstance()->ConnectCollisionMatrix(OBJECT_TYPE::OBJECT_TYPE_PLAYER, OBJECT_TYPE::OBJECT_TYPE_MONSTER);
	CollisionManager::GetInstance()->ConnectCollisionMatrix(OBJECT_TYPE::OBJECT_TYPE_PLAYER, OBJECT_TYPE::OBJECT_TYPE_MONSTER_PROJECTILE);
	CollisionManager::GetInstance()->ConnectCollisionMatrix(OBJECT_TYPE::OBJECT_TYPE_MONSTER, OBJECT_TYPE::OBJECT_TYPE_PLAYER_PROJECTILE);
	CollisionManager::GetInstance()->ConnectCollisionMatrix(OBJECT_TYPE::OBJECT_TYPE_MONSTER, OBJECT_TYPE::OBJECT_TYPE_PLAYER);
}

void SceneStart::Exit()
{
	RemoveAll();
	CollisionManager::GetInstance()->ClearCollisionMatrix();
}

void SceneStart::Update()
{
	GameScene::Update();

	if (KEY_CHECK(KEY::KEY_ENTER, KEY_STATE::KEY_STATE_DOWN))
	{
		ChangeGameScene(SCENE_TYPE::SCENE_TYPE_STAGE_01);
	}
		
}

void SceneStart::Render(HDC _bitmapDC)
{
	Texture* texture = GetTexture();

	int width = texture->GetBitmapInfoWidth();
	int height = texture->GetBitmapInfoHeight();

	// 복사
	BitBlt(_bitmapDC,
		0, 0,
		width, height,
		texture->GetDC(),
		0, 0,
		SRCCOPY);

	// 오브젝트
	GameScene::Render(_bitmapDC);
}