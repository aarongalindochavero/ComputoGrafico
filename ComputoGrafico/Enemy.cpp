#include "Enemy.h"

Enemy::Enemy(Player* player,std::string path)
{
	this->player = player;
	model.LoadModel(path);
	transform.SetTranslation(10.0f, 0.0f, 0.0f);
}

void Enemy::Draw()
{
	transform.SetScale(0.05f, 0.05f, 0.05f);//adidier
	transform.SetRotation(0, 0, 0);
	model.SetTransform(transform);
	model.Draw();
}

void Enemy::Update()
{
	glm::vec3 dir = player->GetCamera()->getCameraPosition() - transform.GetTranslation();
	dir = glm::normalize(dir)*0.001f;
	transform.SetTranslation(transform.GetTranslation().x + dir.x,
		transform.GetTranslation().y + dir.y,
		transform.GetTranslation().z + dir.z);
}