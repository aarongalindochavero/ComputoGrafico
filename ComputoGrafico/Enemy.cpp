#include "Enemy.h"

Enemy::Enemy(Player* player,std::string path)
{
	this->player = player;
	model.LoadModel(path);
	model.AddTexture("Assets/Textures/prueba.png");
	transform.SetTranslation(9.5f, 1.5f, 0.0f);
}

void Enemy::Draw()
{
	transform.SetScale(1.0f, 1.0f, 1.0f);//adidier
	transform.SetRotation(0, 0, 0);
	model.SetTransform(transform);
	model.Draw();
}

void Enemy::Update()
{
	glm::vec3 dir = player->GetCamera()->getCameraPosition() - transform.GetTranslation();
	dir = glm::normalize(dir)*0.0004f;
	transform.SetTranslation(transform.GetTranslation().x + dir.x,
		transform.GetTranslation().y + dir.y,
		transform.GetTranslation().z + dir.z);
}