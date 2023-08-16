#include <Novice.h>
#include "Function.h"
#include <Vector3.h>
#include <cstdint>
#include <imgui.h>
#include <corecrt_math.h>

const char kWindowTitle[] = "LE2B_29_ヨシダ_タケル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };



	//Affine
	Vector3 scale = { 1.0f,1.0f,1.0f };
	Vector3 rotate = { 0.0f,0.0f,0.0f };
	Vector3 translate = { 0.0f,0.0f,0.0f };

	//カメラ
	//Vector3 cameraPosition = { 0.0f,0.0f,-1.0f };
	Vector3 cameraTranslate = { 0.0f,0.8f,-9.50f };
	Vector3 cameraRotate = { 0.0f,0.0f,0.0f };


	//ローカル
	Vector3 LocalVertics[2] = {};
	LocalVertics[0] = { -0.2f,0.0f,0.0f };
	LocalVertics[1] = { 0.2f,0.0f,0.0f };


	unsigned int segmentColor = WHITE;
	Sphere sphere1LocalCoodinate = { {0.0f,0.0f,0.0f},0.2f };

	Plane planeCoodinate = { {0.0f,1.0f,0.001f},0.0f };
	Segment segment = { {0.45f,0.78f,0.0f},{1.0f,0.58f,0.0f} };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///


#pragma region カメラの計算
		//計算
		Matrix4x4 cameraMatrix = MakeAffineMatrix(scale, cameraRotate, cameraTranslate);
		////ビュー(カメラ)
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);

		//射影
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(WINDOW_SIZE_WIDTH) / float(WINDOW_SIZE_HEIGHT), 0.1f, 100.0f);


		//ビューポート
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(WINDOW_SIZE_WIDTH), float(WINDOW_SIZE_HEIGHT), 0.0f, 1.0f);

#pragma endregion





		if (IsColliionPlaneSegment(segment, planeCoodinate) == true) {
			segmentColor = RED;
		}
		else {
			segmentColor = WHITE;
		}



		///
		/// ↑更新処理ここまで
		///




		///
		/// ↓描画処理ここから
		///


		//Grid
		DrawGrid(viewMatrix, projectionMatrix, viewportMatrix);

		DrawPlane(planeCoodinate, viewMatrix, projectionMatrix, viewportMatrix, WHITE);
		DrawSegment(segment, viewMatrix, projectionMatrix, viewportMatrix, segmentColor);





		ImGui::Begin("Plane");
		ImGui::DragFloat3("Plane.Normal", &planeCoodinate.normal.x, 0.01f);
		planeCoodinate.normal = Normalize(planeCoodinate.normal);
		ImGui::DragFloat("distance", &planeCoodinate.distance, 0.01f);
		ImGui::End();


		ImGui::Begin("Segment");
		ImGui::DragFloat3("Origin", &segment.origin.x, 0.01f);
		ImGui::DragFloat3("Diff", &segment.diff.x, 0.01f);
		ImGui::End();


		ImGui::Begin("Camera");
		ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);

		ImGui::End();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}