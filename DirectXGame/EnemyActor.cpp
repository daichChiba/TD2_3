#include "EnemyActor.h"
#include "../DirectXGame/Scene/GameScene.h"

using namespace MathUtility;

void EnemyActor::Initialize(Model* model, Model* bulletModel, Vector3 pos, GameScene* gameScene, ActorManager* actor) {
#ifdef _DEBUG
	assert(model);
	assert(bulletModel);
#endif // _DEBUG

	model_ = model;

	bulletModel_ = bulletModel;

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;

	gameScene_ = gameScene;
	actorManager = actor;

	HPResources = gameScene_->SetEnemyHPResources();
	HPBarResources = gameScene_->SetEnemyHPBarResources();
	
	for (int i = 0; i < 5; ++i)
	{
			HpSprite[i] = Sprite::Create(HPResources, {0.0f, 0.0f});
	}
	HpBarSprite = Sprite::Create(HPBarResources, {0.0f, 0.0f});
}

void EnemyActor::Update()
{
	
}

void EnemyActor::Draw(Camera* camera)
{
	model_->Draw(worldTransform_, *camera);
}

void EnemyActor::DrawHp()
{
	HpBarpos.y = -24.0f;
	HpBarSprite->SetPosition(HpBarpos);
	HpBarSprite->Draw();
	Hppos = Vector2{ 239.0f, 8.0f};
	HpSprite[0]->SetPosition(Hppos);
	int numSpritesToDraw = hp / (kMaxHP / 5);
	for (int i = 0; i < numSpritesToDraw; ++i) {
		HpSprite[i]->Draw();
		Hppos.x += 160.0f;
		if(i != numSpritesToDraw - 1)
		{HpSprite[i + 1]->SetPosition(Hppos);}
    }
}

void EnemyActor::Pos()
{

	HpBarpos	= HpBarSprite->GetPosition();
	
	ImGui::Begin("Hp");
	ImGui::DragFloat2("HPpos", &Hppos.x, 1.0f);
	ImGui::DragFloat2("Barpos", &HpBarpos.x, 1.0f);
	ImGui::End();

	HpBarSprite->SetPosition(HpBarpos);
	
}

void EnemyActor::modeFirst()
{

}

void EnemyActor::modeSecond()
{}

void EnemyActor::DrawImgui() {

}
