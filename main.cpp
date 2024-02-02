#include <Novice.h>
#include "Player.h"
#include "EnemyA.h"

const char kWindowTitle[] = "LC1B_06_オノ_ケンジピエール_testshoot";

enum scene {
	title,
	practice,
	stage,
	clear,
	gameOver
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Player* player = new Player({ 150,360 }, 10, 25, 3, true, false, false);

	Enemy* enemy = new Enemy({ 1300,360 }, { 10,5 }, 40, 50, true, false, false);
	enemy->ColorSet(122, 122, 122, 255);

	int nowScene = title;

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		if (nowScene == title) {
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				player->Reset({ 150,360 }, 25, 3, true, false, false);
				for (int i = 0; i < 20; i++) {
					player->bullet_[i]->Reset({ -100,-100 }, false);
				}
				enemy->Reset({ 1300,360 }, 40, 50, true, false, false, 255);
				nowScene = stage;
			}
			Novice::ScreenPrintf(0, 0, "SPACE:Go Stage");
		}
		if (nowScene == stage) {
			player->Move(keys);
			player->Explode();
			player->Collision(enemy->GetPos(), enemy->GetRadius());
			player->Update();
			player->Draw();

			for (int i = 0; i < 20; i++) {
				player->bullet_[i]->Move();
				player->bullet_[i]->Collision(enemy->GetPos(), enemy->GetRadius());
				if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
					if (!player->bullet_[i]->GetFlag()) {
						player->bullet_[i]->SetFlag(true);
						player->bullet_[i]->SetPos(player->GetPos());
						break;
					}
				}
				player->bullet_[i]->Draw();
			}

			for (int i = 0; i < 20; i++) {
				enemy->Collision(player->bullet_[i]->GetPos(), player->bullet_[i]->GetRadius());
			}
			enemy->Move();
			enemy->Update();
			enemy->Explode();

			enemy->Draw();

			if (enemy->GetAlpha() <= 0) {
				nowScene = clear;
			}
			if (player->GetRadius() <= 0) {
				nowScene = gameOver;
			}
			Novice::ScreenPrintf(0, 0, "WASD:Move");
			Novice::ScreenPrintf(0, 20, "SPACE:Shot");
			Novice::ScreenPrintf(0, 40, "Player:%d", player->GetLifes());
			Novice::ScreenPrintf(0, 60, "Enemy:%d", enemy->GetLifes());
		}
		if (nowScene == clear) {
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				nowScene = title;
			}
			Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x55FF55FF, kFillModeSolid);
			Novice::ScreenPrintf(0, 0, "clear");
			Novice::ScreenPrintf(0, 20, "SPACE:Go Title");
		}
		if (nowScene == gameOver) {
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				nowScene = title;
			}
			Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);
			Novice::ScreenPrintf(0, 0, "gameOver");
			Novice::ScreenPrintf(0, 20, "SPACE:Go Title");
		}




		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (nowScene == title) {
			if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
				break;
			}
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
