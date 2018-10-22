/*!
 *@brief	main.cpp
 */
#include "stdafx.h"
#include "Game.h"
#include "Fade.h"
#include "Title.h"
#include "SoundManager.h"
#include <locale>	// ロケール関連
#include <clocale>	// Cのロケール関連
#include <string>	// stdの文字列クラス

//#define USESPECSETTING 	//``有効で低スペック向けのセッティング
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	std::locale::global(std::locale("japanese"));
	// かつ、WindowsAPIを使うなら
	setlocale(LC_ALL,"japanese");
	srand((unsigned)time(NULL));
#if defined (USESPECSETTING)
	SInitParam initParam;
	initParam.nCmdShow = nCmdShow;
	initParam.hInstance = hInstance;
	initParam.screenWidth = 1280;
	initParam.screenHeight = 720;
	initParam.frameBufferWidth = 640;
	initParam.frameBufferHeight = 360;
	//initParam.screenWidth2D = 1280;
	initParam.screenWidth2D = 720;
	//initParam.screenHeight2D = 640;
	initParam.screenHeight2D = 480;
	//影の設定。
	initParam.graphicsConfing.shadowRenderConfig.isEnable = false;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapWidth = 1024;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapHeight = 1024;
	initParam.graphicsConfing.shadowRenderConfig.softShadowLevel = EnSoftShadowQualityLevel::eSSSS_PCF;
	//さてはアンチだなオメー
	initParam.graphicsConfing.aaConfig.isEnable = false;
	//Bloom
	initParam.graphicsConfing.bloomConfig.isEnable = false;
	//tonemap
	initParam.graphicsConfing.tonemapConfig.isEnable = false;
#else
	//tkEngine2の初期化パラメータを設定する。
	SInitParam initParam;
	initParam.nCmdShow = nCmdShow;
	initParam.hInstance = hInstance;
	initParam.screenWidth = 1280;
	initParam.screenHeight = 720;
	initParam.frameBufferWidth = 1280;
	initParam.frameBufferHeight = 720;
	//影の設定。
	initParam.graphicsConfing.shadowRenderConfig.isEnable = true;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapWidth = 2048;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapHeight = 2048;
	initParam.graphicsConfing.shadowRenderConfig.lightHeight = UnitM(100.0f);
	//initParam.graphicsConfing.shadowRenderConfig.lightHeight = UnitM(80.0f);
	initParam.graphicsConfing.shadowRenderConfig.depthOffset[0] = 0.0001f;
	//initParam.graphicsConfing.shadowRenderConfig.depthOffset[0] = 0.00035f;
	initParam.graphicsConfing.shadowRenderConfig.depthOffset[1] = 0.001f;
	initParam.graphicsConfing.shadowRenderConfig.depthOffset[2] = 0.002f;
	//initParam.graphicsConfing.shadowRenderConfig.depthOffset[2] = 0.001f;
	initParam.graphicsConfing.shadowRenderConfig.softShadowLevel = EnSoftShadowQualityLevel::eSSSS_PCF;

	//アンチ
	initParam.graphicsConfing.aaConfig.isEnable = true;
	//Bloom
	initParam.graphicsConfing.bloomConfig.isEnable = false;
	//tonemap
	initParam.graphicsConfing.tonemapConfig.isEnable = true;
	initParam.graphicsConfing.tonemapConfig.luminance = 0.24f;
#endif
	GraphicsEngine().GetShadowMap().SetFar(1000.0f);
	GraphicsEngine().GetShadowMap().SetNear(50.0f);

	//エンジンを初期化。
	if (Engine().Init(initParam) == true) {
		//NewGO<Game>(0,"Game");
		NewGO<Fade>(1, "Fade");
		NewGO<Title>(0, "Title");
		NewGO<SoundManager>(0, "SM");
		//ゲームループを実行。
		Engine().RunGameLoop();
	}
	//エンジンの終了処理。
	Engine().Final();

	return 0;
}

