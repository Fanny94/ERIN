#include "Engine.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

Engine::Engine(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCommandLine, int nCommandShow)
{
	this->running = true;
	this->camera = new Camera();
	this->graphics = new Graphics();

	// Elevator Sphere
	Esphere = new TSphere();
	Esphere->m_vecCenter = Vector3(0, 0, 0);
	Esphere->m_fRadius = 0.5f;

	this->Objectpool = new ObjectPool();
	this->gameObject = new GameObject();

	this->customImport = new CustomImport();
	this->player = new Player("player", 3.0f, 0.0f, 0.0f);

	this->upperWall = 21.0f;
	this->leftWall = -43.0f;
	this->lowerWall = -21.0f;
	this->rightWall = 43.0f;

	// upper
	this->upper_wall = new Wall();
	this->upper_wall->point = Vector3(0, upperWall, 0);
	this->upper_wall->normal = Vector3(0, -1, 0);
	// left
	this->left_wall = new Wall();
	this->left_wall->point = Vector3(leftWall, 0, 0);
	this->left_wall->normal = Vector3(1, 0, 0);
	// lower
	this->lower_wall = new Wall();
	this->lower_wall->point = Vector3(0, lowerWall, 0);
	this->lower_wall->normal = Vector3(0, 1, 0);
	// right
	this->right_wall = new Wall();
	this->right_wall->point = Vector3(rightWall, 0, 0);
	this->right_wall->normal = Vector3(-1, 0, 0);

	//create window
	wndHandle = InitWindow(hInstance);

	if (!camera->InitDirectInput(hInstance))
	{
		MessageBox(0, "Direct Input Initialization - Failed", "Error", MB_OK);
		return;
	}

	graphics->camera = camera;

	// window is valid
	if (wndHandle)
	{
		// Create SwapChain, Device and Device Context 
		graphics->CreateDirect3DContext(wndHandle);

		graphics->SetViewport(); // Set Viewport

		graphics->CreateShaders();

		graphics->CreateFontWrapper();

		//Ship
		customImport->LoadCustomFormat("../BinaryDataShip.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(0));
		graphics->CreateTexture(customImport->meshes.at(0));
		customImport->meshes.at(0).textureBool = true;

		//Turret
		customImport->LoadCustomFormat("../BinaryDataTurret.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(1));
		graphics->CreateTexture(customImport->meshes.at(1));
		customImport->meshes.at(1).textureBool = true;

		//Enemies
		customImport->LoadCustomFormat("../BinaryDataEnemy.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(2));
		graphics->CreateTexture(customImport->meshes.at(2));
		customImport->meshes.at(2).textureBool = true;

		customImport->LoadCustomFormat("../BinaryDataEnemySpawner.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(3));
		graphics->CreateTexture(customImport->meshes.at(3));
		customImport->meshes.at(3).textureBool = true;

		//Bullets
		customImport->LoadCustomFormat("../BinaryDataBullet.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(4));
		graphics->CreateTexture(customImport->meshes.at(4));
		customImport->meshes.at(4).textureBool = true;

		//HUD
		customImport->LoadCustomFormat("../BinaryDataHUDHP1.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(5));
		graphics->CreateTexture(customImport->meshes.at(5));
		customImport->meshes.at(5).textureBool = true;

		customImport->LoadCustomFormat("../BinaryDataHUDBase.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(6));
		graphics->CreateTexture(customImport->meshes.at(6));
		customImport->meshes.at(6).textureBool = true;

		//Stages
		customImport->LoadCustomFormat("../BinaryDataStageJungle.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(7));
		graphics->CreateTexture(customImport->meshes.at(7));
		customImport->meshes.at(7).textureBool = true;

		customImport->LoadCustomFormat("../BinaryDataStageArctic.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(8));
		graphics->CreateTexture(customImport->meshes.at(8));
		customImport->meshes.at(8).textureBool = true;

		customImport->LoadCustomFormat("../BinaryDataStageDesert.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(9));
		graphics->CreateTexture(customImport->meshes.at(9));
		customImport->meshes.at(9).textureBool = true;

		customImport->LoadCustomFormat("../BinaryDataStageTropical.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(10));
		graphics->CreateTexture(customImport->meshes.at(10));
		customImport->meshes.at(10).textureBool = true;

		customImport->LoadCustomFormat("../BinaryDataStageVolcanic.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(11));
		graphics->CreateTexture(customImport->meshes.at(11));
		customImport->meshes.at(11).textureBool = true;

		// Title Screen
		customImport->LoadCustomFormat("../BinaryDataMenuQuad.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(12));
		graphics->CreateTexture(customImport->meshes.at(12));
		customImport->meshes.at(12).textureBool = true;

		// Main Menu
		// Option 1 - Play
		customImport->LoadCustomFormat("../BinaryDataMain1-Play.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(13));
		graphics->CreateTexture(customImport->meshes.at(13));
		customImport->meshes.at(13).textureBool = true;

		// Option 2 - Highscore
		customImport->LoadCustomFormat("../BinaryDataMain2-Highscore.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(14));
		graphics->CreateTexture(customImport->meshes.at(14));
		customImport->meshes.at(14).textureBool = true;

		//Option 3 - Help & Options
		customImport->LoadCustomFormat("../BinaryDataMain3-Help&Options.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(15));
		graphics->CreateTexture(customImport->meshes.at(15));
		customImport->meshes.at(15).textureBool = true;

		//Option 4 - Quit
		customImport->LoadCustomFormat("../BinaryDataMain4-Quit.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(16));
		graphics->CreateTexture(customImport->meshes.at(16));
		customImport->meshes.at(16).textureBool = true;

		//Option 5 - Are You Sure?
		customImport->LoadCustomFormat("../BinaryDataMain5-Quit-AreYouSure.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(17));
		graphics->CreateTexture(customImport->meshes.at(17));
		customImport->meshes.at(17).textureBool = true;

		// Pause Menu
		// Option 1 - Continue
		customImport->LoadCustomFormat("../BinaryDataPause1-Continue.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(18));
		graphics->CreateTexture(customImport->meshes.at(18));
		customImport->meshes.at(18).textureBool = true;

		// Option 2 - Restart
		customImport->LoadCustomFormat("../BinaryDataPause2-Restart.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(19));
		graphics->CreateTexture(customImport->meshes.at(19));
		customImport->meshes.at(19).textureBool = true;

		//Option 3 - Help & Options
		customImport->LoadCustomFormat("../BinaryDataPause3-Help&Options.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(20));
		graphics->CreateTexture(customImport->meshes.at(20));
		customImport->meshes.at(20).textureBool = true;

		//Option 4 - Main Menu
		customImport->LoadCustomFormat("../BinaryDataPause4-MainMenu.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(21));
		graphics->CreateTexture(customImport->meshes.at(21));
		customImport->meshes.at(21).textureBool = true;

		//Option 5 - Are You Sure?
		customImport->LoadCustomFormat("../BinaryDataPause5-AreYouSure.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(22));
		graphics->CreateTexture(customImport->meshes.at(22));
		customImport->meshes.at(22).textureBool = true;

		// Options Menu
		// Option 1 - How To Play
		customImport->LoadCustomFormat("../BinaryDataOptions1-HowToPlay.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(23));
		graphics->CreateTexture(customImport->meshes.at(23));
		customImport->meshes.at(23).textureBool = true;

		// Option 2 - Controls
		customImport->LoadCustomFormat("../BinaryDataOptions2-Controls.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(24));
		graphics->CreateTexture(customImport->meshes.at(24));
		customImport->meshes.at(24).textureBool = true;

		//Option 3 - Settings
		customImport->LoadCustomFormat("../BinaryDataOptions3-Settings.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(25));
		graphics->CreateTexture(customImport->meshes.at(25));
		customImport->meshes.at(25).textureBool = true;

		//Option 4 - Credits
		customImport->LoadCustomFormat("../BinaryDataOptions4-Credits.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(26));
		graphics->CreateTexture(customImport->meshes.at(26));
		customImport->meshes.at(26).textureBool = true;

		// Results Menu
		// Option 1 - Play Again
		customImport->LoadCustomFormat("../BinaryDataResult1-PlayAgain.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(27));
		graphics->CreateTexture(customImport->meshes.at(27));
		customImport->meshes.at(27).textureBool = true;

		// Option 2 - Highscore
		customImport->LoadCustomFormat("../BinaryDataResult2-Highscore.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(28));
		graphics->CreateTexture(customImport->meshes.at(28));
		customImport->meshes.at(28).textureBool = true;

		//Option 3 - Credits
		customImport->LoadCustomFormat("../BinaryDataResult3-Credits.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(29));
		graphics->CreateTexture(customImport->meshes.at(29));
		customImport->meshes.at(29).textureBool = true;

		//Option 4 - Main Menu
		customImport->LoadCustomFormat("../BinaryDataResult4-MainMenu.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(30));
		graphics->CreateTexture(customImport->meshes.at(30));
		customImport->meshes.at(30).textureBool = true;

		//Option 5 - Are You Sure?
		customImport->LoadCustomFormat("../BinaryDataResult5-MainMenu-AreYouSure.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(31));
		graphics->CreateTexture(customImport->meshes.at(31));
		customImport->meshes.at(31).textureBool = true;

		//Controls
		customImport->LoadCustomFormat("../BinaryDataControlls.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(32));
		graphics->CreateTexture(customImport->meshes.at(32));
		customImport->meshes.at(32).textureBool = true;

		//Credits
		customImport->LoadCustomFormat("../BinaryDataCredits.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(33));
		graphics->CreateTexture(customImport->meshes.at(33));
		customImport->meshes.at(33).textureBool = true;

		// How to Play
		customImport->LoadCustomFormat("../BinaryDataHowToPlay.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(34));
		graphics->CreateTexture(customImport->meshes.at(34));
		customImport->meshes.at(34).textureBool = true;

		//Numbers
		customImport->LoadCustomFormat("../BinaryDataNumber0.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(35));
		graphics->CreateTexture(customImport->meshes.at(35));
		customImport->meshes.at(35).textureBool = true;

		customImport->LoadCustomFormat("../BinaryDataNumber1.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(36));
		graphics->CreateTexture(customImport->meshes.at(36));
		customImport->meshes.at(36).textureBool = true;

		customImport->LoadCustomFormat("../BinaryDataNumber2.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(37));
		graphics->CreateTexture(customImport->meshes.at(37));
		customImport->meshes.at(37).textureBool = true;

		customImport->LoadCustomFormat("../BinaryDataNumber3.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(38));
		graphics->CreateTexture(customImport->meshes.at(38));
		customImport->meshes.at(38).textureBool = true;

		customImport->LoadCustomFormat("../BinaryDataNumber4.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(39));
		graphics->CreateTexture(customImport->meshes.at(39));
		customImport->meshes.at(39).textureBool = true;

		customImport->LoadCustomFormat("../BinaryDataNumber5.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(40));
		graphics->CreateTexture(customImport->meshes.at(40));
		customImport->meshes.at(40).textureBool = true;

		customImport->LoadCustomFormat("../BinaryDataNumber6.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(41));
		graphics->CreateTexture(customImport->meshes.at(41));
		customImport->meshes.at(41).textureBool = true;

		customImport->LoadCustomFormat("../BinaryDataNumber7.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(42));
		graphics->CreateTexture(customImport->meshes.at(42));
		customImport->meshes.at(42).textureBool = true;

		customImport->LoadCustomFormat("../BinaryDataNumber8.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(43));
		graphics->CreateTexture(customImport->meshes.at(43));
		customImport->meshes.at(43).textureBool = true;

		customImport->LoadCustomFormat("../BinaryDataNumber9.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(44));
		graphics->CreateTexture(customImport->meshes.at(44));
		customImport->meshes.at(44).textureBool = true;

		graphics->CreateConstantBuffer();
		ShowWindow(wndHandle, nCommandShow);
	}

	// spawn enemies
	for (int i = 0; i < Objectpool->e_poolSize; i++)
	{
		randomFloat();
		this->Objectpool->createEnemy(Rx, Ry, 0.0f);
	}

	// spawn special enemies
	if (this->gameObject->getSpecialCooldown())
	{
		for (int i = 0; i < Objectpool->Se_poolSize; i++)
		{
			randomFloat();
			this->Objectpool->createSpecialEnemy(Rx, Ry, 0.0f);
			this->gameObject->setSpecialCooldown(false);
		}
	}

	//floorClear = false;
	//resetCooldown();
}

Engine::~Engine()
{
	delete this->graphics;
	delete this->camera;
	delete this->customImport;
	delete this->Esphere;
	delete this->player;
	delete this->Objectpool;
	delete this->gameObject;
	delete this->upper_wall;
	delete this->left_wall;
	delete this->lower_wall;
	delete this->right_wall;
}

void Engine::processInput()
{
	if (player->input->isConnected())
	{
		// Update controller states
		player->input->update();
		// Update player accelerating bool
		if (this->ready)
		{
			player->playerInput();
		}

		switch (gameState)
		{
		case GameRunning:

			// Fire Bullets
			if (this->ready)
			{
				if ((this->player->input->State._right_thumbstick.x || this->player->input->State._right_thumbstick.x) == 1)
				{
					if (Objectpool->getCooldown())
					{
						this->Objectpool->fire(player->getX(), player->getY(), player->getHeading());
						Objectpool->setCooldown(false);
					}
				}
			}

			if (this->player->input->State._buttons[GamePad_Button_START] == true)
			{
				gameState = Pause;
			}


			// Dpad camera movement
			if (this->player->input->State._buttons[GamePad_Button_DPAD_LEFT] == true)
			{
				this->camera->cameraMoveLeft();
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_RIGHT] == true)
			{
				this->camera->cameraMoveRight();
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_UP] == true)
			{
				this->camera->cameraMoveUp();
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_DOWN] == true)
			{
				this->camera->cameraMoveDown();
			}
			break;

		case TitleScreen:
			if (this->player->input->State._buttons[GamePad_Button_START] == true)
			{
				gameState = MainMenu;
			}
			break;

		case MainMenu:
			if (this->player->input->State._buttons[GamePad_Button_DPAD_LEFT] == true)
			{
				if (mainMenuOption == 1)
				{
					mainMenuOption = 0;
				}
				else if (mainMenuOption == 3)
				{
					mainMenuOption = 2;
				}
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_RIGHT] == true)
			{
				if (mainMenuOption == 0)
				{
					mainMenuOption = 1;
				}
				else if (mainMenuOption == 2)
				{
					mainMenuOption = 3;
				}
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_UP] == true)
			{
				if (mainMenuOption == 2)
				{
					mainMenuOption = 0;
				}
				else if (mainMenuOption == 3)
				{
					mainMenuOption = 1;
				}
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_DOWN] == true)
			{
				if (mainMenuOption == 0)
				{
					mainMenuOption = 2;
				}
				else if (mainMenuOption == 1)
				{
					mainMenuOption = 3;
				}
			}

			// If accept
			if (this->player->input->State._buttons[GamePad_Button_A] == true && aButtonActive == false)
			{
				if (mainMenuOption == 0)
				{
					mainMenu = false;
					gameState = GameRunning;
					floorState = Jungle;
					enemyCount = Objectpool->e_poolSize;
					specialEnemyCount = Objectpool->Se_poolSize;
					for (int i = 0; i < Objectpool->e_poolSize; i++)
					{
						Objectpool->enemies[i].setInUse(false);

						this->Objectpool->createEnemy(Rx, Ry, 0.0f);
					}
					for (int i = 0; i < Objectpool->Se_poolSize; i++)
					{
						Objectpool->Senemies[i].setInUse(false);

						this->Objectpool->createSpecialEnemy(Rx, Ry, 0.0f);
						this->gameObject->setSpecialCooldown(false);
					}
					eCount = enemyCount + specialEnemyCount -2;
				}
				else if (mainMenuOption == 1)
				{
					mainMenuOption = 0;
					gameState = HighScore;
				}
				else if (mainMenuOption == 2)
				{
					mainMenuOption = 0;
					aButtonActive = true;
					gameState = HelpAndOptions;
				}
				else if (mainMenuOption == 3)
				{
					mainMenuOption = 4;
					aButtonActive = true;
				}
				else if (mainMenuOption == 4)
					this->running = false;
			}

			if (this->player->input->State._buttons[GamePad_Button_B] == true && bButtonActive == false)
			{
				if (mainMenuOption == 4)
					mainMenuOption = 3;
			}

			if (this->player->input->State._buttons[GamePad_Button_A] == false)
				aButtonActive = false;
			if (this->player->input->State._buttons[GamePad_Button_B] == false)
				bButtonActive = false;
			break;

		case Pause:
			if (this->player->input->State._buttons[GamePad_Button_DPAD_LEFT] == true)
			{
				if (pMenuOption == 1)
				{
					pMenuOption = 0;
				}
				else if (pMenuOption == 3)
				{
					pMenuOption = 2;
				}
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_RIGHT] == true)
			{
				if (pMenuOption == 0)
				{
					pMenuOption = 1;
				}
				else if (pMenuOption == 2)
				{
					pMenuOption = 3;
					gameObject->reset();
				}
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_UP] == true)
			{
				if (pMenuOption == 2)
				{
					pMenuOption = 0;
				}
				else if (pMenuOption == 3)
				{
					pMenuOption = 1;
				}
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_DOWN] == true)
			{
				if (pMenuOption == 0)
				{
					pMenuOption = 2;
				}
				else if (pMenuOption == 1)
				{
					pMenuOption = 3;
					gameObject->reset();
				}
			}

			// If accept
			if (this->player->input->State._buttons[GamePad_Button_A] == true && aButtonActive == false)
			{
				if (pMenuOption == 0)
				{
					gameState = GameRunning;
				}
				else if (pMenuOption == 1)
				{
					pMenuOption = 0;
					floorClear = false;
					gameObject->reset();
					player->PlayerReset();
					camera->ResetCamera();
					enemyCount = Objectpool->e_poolSize;
					specialEnemyCount = Objectpool->Se_poolSize;

					for (int i = 0; i < Objectpool->e_poolSize; i++)
					{
						Objectpool->enemies[i].setInUse(false);

						this->Objectpool->createEnemy(Rx, Ry, 0.0f);
					}
					for (int i = 0; i < Objectpool->Se_poolSize; i++)
					{
						Objectpool->Senemies[i].setInUse(false);

						this->Objectpool->createSpecialEnemy(Rx, Ry, 0.0f);
						this->gameObject->setSpecialCooldown(false);
					}
					eCount = enemyCount + specialEnemyCount - 2;
					gameState = GameRunning;
				}
				else if (pMenuOption == 2)
				{
					aButtonActive = true;
					gameState = HelpAndOptions;
				}
				else if (pMenuOption == 3)
				{
					aButtonActive = true;
					pMenuOption = 4;
				}
				else if (pMenuOption == 4)
				{
					pMenuOption = 0;
					player->PlayerReset();
					gameObject->reset();
					Objectpool->ResetBullet();
					camera->ResetCamera();
					floorClear = false;
					mainMenu = true;

					for (int i = 0; i < 5; i++)
					{
						Objectpool->enemies[i].setInUse(false);
					}
					for (int i = 0; i < 2; i++)
					{
						Objectpool->Senemies[i].setInUse(false);
					}

					aButtonActive = true;
					gameState = MainMenu;
				}
			}

			if (this->player->input->State._buttons[GamePad_Button_B] == true && bButtonActive == false)
			{
				if (pMenuOption == 4)
					pMenuOption = 3;
			}

			if (this->player->input->State._buttons[GamePad_Button_A] == false)
				aButtonActive = false;
			if (this->player->input->State._buttons[GamePad_Button_B] == false)
				bButtonActive = false;
			break;
		case HighScore:
			if (this->player->input->State._buttons[GamePad_Button_B] == true && bButtonActive == false)
			{
				if (resMenu == true)
					gameState = GameOver;
				else
					gameState = MainMenu;
			}
			break;
		case HelpAndOptions:
			if (this->player->input->State._buttons[GamePad_Button_DPAD_LEFT] == true)
			{
				if (haoMenuOption == 1)
				{
					haoMenuOption = 0;
				}
				else if (haoMenuOption == 3)
				{
					haoMenuOption = 2;
				}
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_RIGHT] == true)
			{
				if (haoMenuOption == 0)
				{
					haoMenuOption = 1;
				}
				else if (haoMenuOption == 2)
				{
					haoMenuOption = 3;
				}
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_UP] == true)
			{
				if (haoMenuOption == 2)
				{
					haoMenuOption = 0;
				}
				else if (haoMenuOption == 3)
				{
					haoMenuOption = 1;
				}
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_DOWN] == true)
			{
				if (haoMenuOption == 0)
				{
					haoMenuOption = 2;
				}
				else if (haoMenuOption == 1)
				{
					haoMenuOption = 3;
				}
			}

			// If accept
			if (this->player->input->State._buttons[GamePad_Button_A] == true && aButtonActive == false)
			{
				if (haoMenuOption == 0)
				{
					gameState = HowToPlay;
				}
				else if (haoMenuOption == 1)
				{
					gameState = Controls;
				}
				else if (haoMenuOption == 2)
				{
					gameState = Settings;
				}
				else if (haoMenuOption == 3)
				{
					gameState = Credits;
				}
			}

			if (this->player->input->State._buttons[GamePad_Button_B] == true && bButtonActive == false)
			{
				if (mainMenu == true)
				{
					haoMenuOption = 0;
					bButtonActive = true;
					gameState = MainMenu;
				}
				else
				{
					pMenuOption = 0;
					bButtonActive = true;
					gameState = Pause;
				}
				haoMenuOption = 0;
			}

			if (this->player->input->State._buttons[GamePad_Button_A] == false)
				aButtonActive = false;
			if (this->player->input->State._buttons[GamePad_Button_B] == false)
				bButtonActive = false;
			break;
		case GameOver:
			if (this->player->input->State._buttons[GamePad_Button_DPAD_LEFT] == true)
			{
				if (resMenuOption == 1)
				{
					resMenuOption = 0;
				}
				else if (resMenuOption == 3)
				{
					resMenuOption = 2;
				}
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_RIGHT] == true)
			{
				if (resMenuOption == 0)
				{
					resMenuOption = 1;
				}
				else if (resMenuOption == 2)
				{
					resMenuOption = 3;
				}
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_UP] == true)
			{
				if (resMenuOption == 2)
				{
					resMenuOption = 0;
				}
				else if (resMenuOption == 3)
				{
					resMenuOption = 1;
				}
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_DOWN] == true)
			{
				if (resMenuOption == 0)
				{
					resMenuOption = 2;
				}
				else if (resMenuOption == 1)
				{
					resMenuOption = 3;
				}
			}

			// If accept
			if (this->player->input->State._buttons[GamePad_Button_A] == true && aButtonActive == false)
			{
				if (resMenuOption == 0)
				{
					resMenuOption = 0;
					floorClear = false;
					resMenu = false;
					gameObject->reset();
					player->PlayerReset();
					camera->ResetCamera();
					enemyCount = Objectpool->e_poolSize;
					specialEnemyCount = Objectpool->Se_poolSize;

					for (int i = 0; i < Objectpool->e_poolSize; i++)
					{
						Objectpool->enemies[i].setInUse(false);

						this->Objectpool->createEnemy(Rx, Ry, 0.0f);
					}
					for (int i = 0; i < Objectpool->Se_poolSize; i++)
					{
						Objectpool->Senemies[i].setInUse(false);

						this->Objectpool->createSpecialEnemy(Rx, Ry, 0.0f);
						this->gameObject->setSpecialCooldown(false);
					}
					eCount = enemyCount + specialEnemyCount - 2;
					gameState = GameRunning;
				}
				else if (resMenuOption == 1)
				{
					gameState = HighScore;
				}
				else if (resMenuOption == 2)
				{
					gameState = Credits;
				}
				else if (resMenuOption == 3)
				{
					aButtonActive = true;
					resMenuOption = 4;
				}
				else if (resMenuOption == 4)
				{
					resMenuOption = 0;
					player->PlayerReset();
					gameObject->reset();
					Objectpool->ResetBullet();
					camera->ResetCamera();
					floorClear = false;
					mainMenu = true;
					resMenu = false;

					for (int i = 0; i < 5; i++)
					{
						Objectpool->enemies[i].setInUse(false);
					}
					for (int i = 0; i < 2; i++)
					{
						Objectpool->Senemies[i].setInUse(false);
					}

					gameState = MainMenu;
					aButtonActive = true;
				}
			}

			if (this->player->input->State._buttons[GamePad_Button_B] == true && bButtonActive == false)
			{
				if (resMenuOption == 4)
					resMenuOption = 3;
			}

			if (this->player->input->State._buttons[GamePad_Button_A] == false)
				aButtonActive = false;
			if (this->player->input->State._buttons[GamePad_Button_B] == false)
				bButtonActive = false;
			break;
		case Controls:
			if (this->player->input->State._buttons[GamePad_Button_B] == true && bButtonActive == false)
			{
				bButtonActive = true;
				gameState = HelpAndOptions;
			}
			break;
		case Credits:
			if (this->player->input->State._buttons[GamePad_Button_B] == true && bButtonActive == false)
			{
				bButtonActive = true;
				if (resMenu == true)
					gameState = GameOver;
				else
					gameState = HelpAndOptions;
			}
			break;
		case Settings:
			if (this->player->input->State._buttons[GamePad_Button_B] == true && bButtonActive == false)
			{
				bButtonActive = true;
				gameState = HelpAndOptions;
			}
			break;
		case HowToPlay:
			if (this->player->input->State._buttons[GamePad_Button_B] == true && bButtonActive == false)
			{
				bButtonActive = true;
				gameState = HelpAndOptions;
			}
			break;
		}

		if (this->player->input->State._buttons[GamePad_Button_Y] == true)
		{
			this->running = false;
		}

		if (this->player->input->State._buttons[GamePad_Button_BACK] == true)
		{
			this->running = false;
		}
	}
}

void Engine::update(double deltaTimeMs)
{
	double deltaTimeS; // deltaTimeMs millisecond
	deltaTimeS = deltaTimeMs / 1000; // seconds

	switch (gameState)
	{
	case GameRunning:
		updateCooldown(deltaTimeS);
		Objectpool->bulletupdateCooldown(deltaTimeS);
		gameObject->SpecialupdateCooldown(deltaTimeS);
		Objectpool->spawnTimer(deltaTimeS);

		/* *********** Player Update *********** */
		player->hpCooldown(deltaTimeS);

		if (this->ready)
		{
			player->update(deltaTimeMs);
		}

		camera->UpdateGameCamera(this->player->getX(), this->player->getY(), deltaTimeS);

		// Player Collision Walls
		if (sphereToPlane(*player->sphere, upper_wall->point, upper_wall->normal))
		{
			player->SetY(upper_wall->point.y - 0.5f);
		}
		if (sphereToPlane(*player->sphere, left_wall->point, left_wall->normal))
		{
			player->SetX(left_wall->point.x + 0.5f);
		}
		if (sphereToPlane(*player->sphere, lower_wall->point, lower_wall->normal))
		{
			player->SetY(lower_wall->point.y + 0.5f);
		}
		if (sphereToPlane(*player->sphere, right_wall->point, right_wall->normal))
		{
			player->SetX(right_wall->point.x - 0.5f);
		}

		/* *********** Enemies Updates *********** */
		for (int i = 0; i < this->Objectpool->e_poolSize; i++)
		{
			if (this->ready && Objectpool->enemies[i].getInUse())
			{
				Objectpool->enemies[i].updateBehavior(*player->shipPos, &Objectpool->enemies[i], Objectpool->enemies);
				Objectpool->enemies[i].update(deltaTimeMs);
			}
		}

		// Collision Enemies
		for (int i = 0; i < Objectpool->e_poolSize; i++)
		{
			if (Objectpool->enemies[i].getInUse() && sphereToSphere(*player->sphere, *Objectpool->enemies[i].sphere))
			{
				if (player->getHpCooldown())
				{
					player->HP--;
					eCount--;
					Objectpool->enemies[i].setInUse(false);
					player->setHpCooldown(false);
				}
			}
		}

		// Collision enemies and walls

		// Special enemy update
		for (int i = 0; i < this->Objectpool->Se_poolSize; i++)
		{
			if (this->ready && Objectpool->Senemies[i].getInUse())
			{
				Objectpool->Senemies[i].updateSpecialBehavior(*player->shipPos, &Objectpool->Senemies[i], Objectpool->Senemies);
				Objectpool->Senemies[i].update(deltaTimeMs);
				if (Objectpool->getSpawnCooldown())
				{
					childX = Objectpool->Senemies[i].getX();
					childY = Objectpool->Senemies[i].getY();
					Objectpool->createEnemy(childX, childY, 0);
					eCount++;
					Objectpool->setSpawnCooldown(false);
				}
			}
		}

		// Collision special enemies and walls
		for (int i = 0; i < Objectpool->Se_poolSize; i++)
		{
			if (Objectpool->Senemies[i].getInUse())
			{
				if (sphereToPlane(*Objectpool->Senemies[i].sphere, upper_wall->point, upper_wall->normal))
				{
					Objectpool->Senemies[i].setObjectPosY(upper_wall->point.y - 1.0f);
				}
				if (sphereToPlane(*Objectpool->Senemies[i].sphere, left_wall->point, left_wall->normal))
				{
					Objectpool->Senemies[i].setObjectPosX(left_wall->point.x + 1.0f);
				}
				if (sphereToPlane(*Objectpool->Senemies[i].sphere, lower_wall->point, lower_wall->normal))
				{
					Objectpool->Senemies[i].setObjectPosY(lower_wall->point.y + 1.0f);
				}
				if (sphereToPlane(*Objectpool->Senemies[i].sphere, right_wall->point, right_wall->normal))
				{
					Objectpool->Senemies[i].setObjectPosX(right_wall->point.x - 1.0f);
				}
			}
		}

		for (int i = 0; i < Objectpool->e_poolSize; i++)
		{
			if (Objectpool->enemies[i].getInUse())
			{
				if (sphereToPlane(*Objectpool->enemies[i].sphere, upper_wall->point, upper_wall->normal))
				{
					Objectpool->enemies[i].setObjectPosY(upper_wall->point.y - 1.0f);
				}
				if (sphereToPlane(*Objectpool->enemies[i].sphere, left_wall->point, left_wall->normal))
				{
					Objectpool->enemies[i].setObjectPosX(left_wall->point.x + 1.0f);
				}
				if (sphereToPlane(*Objectpool->enemies[i].sphere, lower_wall->point, lower_wall->normal))
				{
					Objectpool->enemies[i].setObjectPosY(lower_wall->point.y + 1.0f);
				}
				if (sphereToPlane(*Objectpool->enemies[i].sphere, right_wall->point, right_wall->normal))
				{
					Objectpool->enemies[i].setObjectPosX(right_wall->point.x - 1.0f);
				}
			}
		}

		/* *********** Bullet Updates *********** */
		for (int i = 0; i < Objectpool->getBulletPoolSize(); i++)
		{
			Objectpool->bullets[i].update();
		}

		// Collision Bullets
		for (int t = 0; t < Objectpool->e_poolSize; t++)
		{
			if (Objectpool->enemies[t].getInUse())
			{
				for (int i = 0; i < Objectpool->b_poolSize; i++)
				{
					float x = Objectpool->bullets[i].state.alive.x;
					float y = Objectpool->bullets[i].state.alive.y;
					if (Objectpool->bullets[i].getInUse() && pointInSphere(*Objectpool->enemies[t].sphere, Vector3(x, y, 0)))
					{
						eCount--;
						Objectpool->enemies[t].setInUse(false);
						Objectpool->bullets[i].setInUse(false);
					}
				}
			}
		}
		// Collision Bullets with special enemies
		for (int t = 0; t < Objectpool->Se_poolSize; t++)
		{
			if (Objectpool->Senemies[t].getInUse())
			{
				for (int i = 0; i < Objectpool->b_poolSize; i++)
				{
					float x = Objectpool->bullets[i].state.alive.x;
					float y = Objectpool->bullets[i].state.alive.y;
					if (Objectpool->bullets[i].getInUse() && pointInSphere(*Objectpool->Senemies[t].sphere, Vector3(x, y, 0)))
					{
						eCount--;
						Objectpool->Senemies[t].setInUse(false);
						Objectpool->bullets[i].setInUse(false);
					}
				}
			}
		}

		/* *********** HUD Logic *********** */
		if (eCount < 1)
		{
			floorClear = true;
		}

		if (player->HP <= 0)
		{
			player->PlayerReset();
			gameObject->reset();

			for (int i = 0; i < Objectpool->e_poolSize; i++)
			{
				Objectpool->enemies[i].setInUse(false);
			}

			resMenu = true;
			gameState = GameOver;
		}

		if (floorClear == true)
		{
			Elevatorfunc();
		}

		break;
	case TitleScreen:
		if (printTitle == true)
		{
			printTitle = false;
			camera->camPosition.x = 0;
			camera->camPosition.y = 0;
			camera->camPosition.z = -15.8;
		}
		break;
	case MainMenu:
		camera->camPosition.x = 0;
		camera->camPosition.y = 0;
		camera->camPosition.z = -15.8;
		break;
	case Pause:
		camera->camPosition.x = 0;
		camera->camPosition.y = 0;
		camera->camPosition.z = -15.8;
		break;
	case GameOver:
		camera->camPosition.x = 0;
		camera->camPosition.y = 0;
		camera->camPosition.z = -15.8;
		break;
	}
}

void Engine::render()
{
	switch (gameState)
	{
	case GameRunning:

		graphics->Render();

		switch (floorState)
		{
		case Jungle:
			customImport->meshes.at(7).world = XMMatrixTranslation(0, 0, 1) + XMMatrixScaling(10, 10, 3);
			graphics->RenderCustom(customImport->meshes.at(7), customImport->meshes.at(7).world, 7, 7);
			break;
		case Arctic:
			customImport->meshes.at(8).world = XMMatrixTranslation(0, 0, 1) + XMMatrixScaling(10, 10, 3);
			graphics->RenderCustom(customImport->meshes.at(8), customImport->meshes.at(8).world, 8, 8);
			break;
		case Desert:
			customImport->meshes.at(9).world = XMMatrixTranslation(0, 0, 1) + XMMatrixScaling(10, 10, 3);
			graphics->RenderCustom(customImport->meshes.at(9), customImport->meshes.at(9).world, 9, 9);
			break;
		case Tropical:
			customImport->meshes.at(10).world = XMMatrixTranslation(0, 0, 1) + XMMatrixScaling(10, 10, 3);
			graphics->RenderCustom(customImport->meshes.at(10), customImport->meshes.at(10).world, 10, 10);
			break;
		case Volcanic:
			customImport->meshes.at(11).world = XMMatrixTranslation(0, 0, 1) + XMMatrixScaling(10, 10, 3);
			graphics->RenderCustom(customImport->meshes.at(11), customImport->meshes.at(11).world, 11, 11);
			break;
		}

		customImport->meshes.at(0).world = *player->shipMatrix;
		graphics->RenderCustom(customImport->meshes.at(0), customImport->meshes.at(0).world, 0, 0);

		customImport->meshes.at(1).world = *player->turretMatrix;
		graphics->RenderCustom(customImport->meshes.at(1), customImport->meshes.at(1).world, 1, 1);

		if (player->HP > 0)
		{
			RendHUD();
		}

		// Bullet rendering
		for (int i = 0; i < Objectpool->getBulletPoolSize(); i++)
		{
			if (Objectpool->bullets[i].getInUse())
			{
				graphics->RenderCustom(customImport->meshes.at(4), *Objectpool->bullets[i].bulletMatrix, 4, 4);
			}
		}

		// Enemy rendering
		for (int i = 0; i < Objectpool->e_poolSize; i++)
		{
			if (Objectpool->enemies[i].getInUse())
			{
				graphics->RenderCustom(customImport->meshes.at(2), *Objectpool->enemies[i].objectMatrix, 2, 2);
			}
		}

		// Special enemy rendering
		for (int i = 0; i < Objectpool->Se_poolSize; i++)
		{
			if (Objectpool->Senemies[i].getInUse())
			{
				graphics->RenderCustom(customImport->meshes.at(3), *Objectpool->Senemies[i].objectMatrix, 3, 3);
			}
		}

		if (floorClear == true)
		{
			rendElevator();
		}

		if (eCount < 10)
		{
			customImport->meshes.at(35).world = XMMatrixRotationZ(XMConvertToRadians(-90)) * XMMatrixTranslation(-0.85, -2, -0.75) * XMMatrixScaling(0.45, 0.45, 1);
			graphics->RenderCustom(customImport->meshes.at(35), customImport->meshes.at(35).world, 35, 35);
		}

		if (eCount <= 0 || eCount == 10 || eCount == 20)
		{
			customImport->meshes.at(35).world = XMMatrixRotationZ(XMConvertToRadians(-90)) * XMMatrixTranslation(0.85, -2, -0.75) * XMMatrixScaling(0.45, 0.45, 1);
			graphics->RenderCustom(customImport->meshes.at(35), customImport->meshes.at(35).world, 35, 35);
		}

		if (eCount >= 10 && eCount < 20)
		{
			customImport->meshes.at(36).world = XMMatrixRotationZ(XMConvertToRadians(-90)) * XMMatrixTranslation(-0.85, -2, -0.75) * XMMatrixScaling(0.45, 0.45, 1);
			graphics->RenderCustom(customImport->meshes.at(36), customImport->meshes.at(36).world, 36, 36);
		}

		if (eCount == 1 || eCount == 11 || eCount == 21)
		{
			customImport->meshes.at(36).world = XMMatrixRotationZ(XMConvertToRadians(-90)) * XMMatrixTranslation(0.85, -2, -0.75) * XMMatrixScaling(0.45, 0.45, 1);
			graphics->RenderCustom(customImport->meshes.at(36), customImport->meshes.at(36).world, 36, 36);
		}

		if (eCount >= 20 && eCount < 30)
		{
			customImport->meshes.at(37).world = XMMatrixRotationZ(XMConvertToRadians(-90)) * XMMatrixTranslation(-0.85, -2, -0.75) * XMMatrixScaling(0.45, 0.45, 1);
			graphics->RenderCustom(customImport->meshes.at(37), customImport->meshes.at(37).world, 37, 37);
		}

		if (eCount == 2 || eCount == 12 || eCount == 22)
		{
			customImport->meshes.at(37).world = XMMatrixRotationZ(XMConvertToRadians(-90)) * XMMatrixTranslation(0.85, -2, -0.75) * XMMatrixScaling(0.45, 0.45, 1);
			graphics->RenderCustom(customImport->meshes.at(37), customImport->meshes.at(37).world, 37, 37);
		}

		if (eCount == 3 || eCount == 13 || eCount == 23)
		{
			customImport->meshes.at(38).world = XMMatrixRotationZ(XMConvertToRadians(-90)) * XMMatrixTranslation(0.85, -2, -0.75) * XMMatrixScaling(0.45, 0.45, 1);
			graphics->RenderCustom(customImport->meshes.at(38), customImport->meshes.at(38).world, 38, 38);
		}

		if (eCount == 4 || eCount == 14 || eCount == 24)
		{
			customImport->meshes.at(39).world = XMMatrixRotationZ(XMConvertToRadians(-90)) * XMMatrixTranslation(0.85, -2, -0.75) * XMMatrixScaling(0.45, 0.45, 1);
			graphics->RenderCustom(customImport->meshes.at(39), customImport->meshes.at(39).world, 39, 39);
		}

		if (eCount == 5 || eCount == 15 || eCount == 25)
		{
			customImport->meshes.at(40).world = XMMatrixRotationZ(XMConvertToRadians(-90)) * XMMatrixTranslation(0.85, 0.2, -0.75) * XMMatrixScaling(0.45, 0.45, 1);
			graphics->RenderCustom(customImport->meshes.at(40), customImport->meshes.at(40).world, 40, 40);
		}

		if (eCount == 6 || eCount == 16 || eCount == 26)
		{
			customImport->meshes.at(41).world = XMMatrixRotationZ(XMConvertToRadians(-90)) * XMMatrixTranslation(0.85, -2, -0.75) * XMMatrixScaling(0.45, 0.45, 1);
			graphics->RenderCustom(customImport->meshes.at(41), customImport->meshes.at(41).world, 41, 41);
		}

		if (eCount == 7 || eCount == 17 || eCount == 27)
		{
			customImport->meshes.at(42).world = XMMatrixRotationZ(XMConvertToRadians(-90)) * XMMatrixTranslation(0.85, -2, -0.75) * XMMatrixScaling(0.45, 0.45, 1);
			graphics->RenderCustom(customImport->meshes.at(42), customImport->meshes.at(42).world, 42, 42);
		}

		if (eCount == 8 || eCount == 18 || eCount == 28)
		{
			customImport->meshes.at(43).world = XMMatrixRotationZ(XMConvertToRadians(-90)) * XMMatrixTranslation(0.85, 0.2, -0.75) * XMMatrixScaling(0.45, 0.45, 1);
			graphics->RenderCustom(customImport->meshes.at(43), customImport->meshes.at(43).world, 43, 43);
		}

		if (eCount == 9 || eCount == 19 || eCount == 29)
		{
			customImport->meshes.at(44).world = XMMatrixRotationZ(XMConvertToRadians(-90)) * XMMatrixTranslation(0.85, 0.2, -0.75) * XMMatrixScaling(0.45, 0.45, 1);
			graphics->RenderCustom(customImport->meshes.at(44), customImport->meshes.at(44).world, 44, 44);
		}

		// Camera Update
		camera->InitCamera();

		break;
	case TitleScreen:
		graphics->Render();

		customImport->meshes.at(12).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(3, 3, 0);
		graphics->RenderCustom(customImport->meshes.at(12), customImport->meshes.at(12).world, 12, 12);
		//graphics->drawText();
		camera->InitCamera();
		break;
	case MainMenu:
		graphics->Render();
		if (mainMenuOption == 0) // Play
		{
			customImport->meshes.at(13).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(3, 3, 0);
			graphics->RenderCustom(customImport->meshes.at(13), customImport->meshes.at(13).world, 13, 13);
		}
		else if (mainMenuOption == 1) // Highscore
		{
			customImport->meshes.at(14).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(3, 3, 0);
			graphics->RenderCustom(customImport->meshes.at(14), customImport->meshes.at(14).world, 14, 14);
		}
		else if (mainMenuOption == 2) // Help & Options
		{
			customImport->meshes.at(15).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(3, 3, 0);
			graphics->RenderCustom(customImport->meshes.at(15), customImport->meshes.at(15).world, 15, 15);
		}
		else if (mainMenuOption == 3) // Quit
		{
			customImport->meshes.at(16).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(3, 3, 0);
			graphics->RenderCustom(customImport->meshes.at(16), customImport->meshes.at(16).world, 16, 16);
		}
		else if (mainMenuOption == 4) // Are You Sure?
		{
			customImport->meshes.at(17).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(3, 3, 0);
			graphics->RenderCustom(customImport->meshes.at(17), customImport->meshes.at(17).world, 17, 17);
		}

		camera->InitCamera();
		break;
	case Pause:
		graphics->Render();
		if (pMenuOption == 0) // Continue
		{
			customImport->meshes.at(18).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(3, 3, 0);
			graphics->RenderCustom(customImport->meshes.at(18), customImport->meshes.at(18).world, 18, 18);
		}
		else if (pMenuOption == 1) // Restart
		{
			customImport->meshes.at(19).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(3, 3, 0);
			graphics->RenderCustom(customImport->meshes.at(19), customImport->meshes.at(19).world, 19, 19);
		}
		else if (pMenuOption == 2) // Help & Options
		{
			customImport->meshes.at(20).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(3, 3, 0);
			graphics->RenderCustom(customImport->meshes.at(20), customImport->meshes.at(20).world, 20, 20);
		}
		else if (pMenuOption == 3) // Main Menu
		{
			customImport->meshes.at(21).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(3, 3, 0);
			graphics->RenderCustom(customImport->meshes.at(21), customImport->meshes.at(21).world, 21, 21);
		}
		else if (pMenuOption == 4) // Are You Sure?
		{
			customImport->meshes.at(22).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(3, 3, 0);
			graphics->RenderCustom(customImport->meshes.at(22), customImport->meshes.at(22).world, 22, 22);
		}

		camera->InitCamera();
		break;
	case HelpAndOptions:
		graphics->Render();
		if (haoMenuOption == 0) // How To Play
		{
			customImport->meshes.at(23).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(3, 3, 0);
			graphics->RenderCustom(customImport->meshes.at(23), customImport->meshes.at(23).world, 23, 23);
		}
		else if (haoMenuOption == 1) // Controls
		{
			customImport->meshes.at(24).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(3, 3, 0);
			graphics->RenderCustom(customImport->meshes.at(24), customImport->meshes.at(24).world, 24, 24);
		}
		else if (haoMenuOption == 2) // Settings
		{
			customImport->meshes.at(25).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(3, 3, 0);
			graphics->RenderCustom(customImport->meshes.at(25), customImport->meshes.at(25).world, 25, 25);
		}
		else if (haoMenuOption == 3) // Credits
		{
			customImport->meshes.at(26).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(3, 3, 0);
			graphics->RenderCustom(customImport->meshes.at(26), customImport->meshes.at(26).world, 26, 26);
		}

		camera->InitCamera();
		break;
	case GameOver:
		graphics->Render();

		if (resMenuOption == 0)
		{
			customImport->meshes.at(27).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(3, 3, 0);
			graphics->RenderCustom(customImport->meshes.at(27), customImport->meshes.at(27).world, 27, 27);
		}
		else if (resMenuOption == 1)
		{
			customImport->meshes.at(28).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(3, 3, 0);
			graphics->RenderCustom(customImport->meshes.at(28), customImport->meshes.at(28).world, 28, 28);
		}
		else if (resMenuOption == 2)
		{
			customImport->meshes.at(29).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(3, 3, 0);
			graphics->RenderCustom(customImport->meshes.at(29), customImport->meshes.at(29).world, 29, 29);
		}
		else if (resMenuOption == 3)
		{
			customImport->meshes.at(30).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(3, 3, 0);
			graphics->RenderCustom(customImport->meshes.at(30), customImport->meshes.at(30).world, 30, 30);
		}
		else if (resMenuOption == 4)
		{
			customImport->meshes.at(31).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(3, 3, 0);
			graphics->RenderCustom(customImport->meshes.at(31), customImport->meshes.at(31).world, 31, 31);
		}
		camera->InitCamera();
		break;
	case Controls:
		graphics->Render();

		customImport->meshes.at(32).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(3, 3, 0);
		graphics->RenderCustom(customImport->meshes.at(32), customImport->meshes.at(32).world, 32, 32);

		camera->InitCamera();
		break;

	case Credits:
		graphics->Render();

		customImport->meshes.at(33).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(3, 3, 0);
		graphics->RenderCustom(customImport->meshes.at(33), customImport->meshes.at(33).world, 33, 33);

		camera->InitCamera();
		break;
	case HowToPlay:
		graphics->Render();

		customImport->meshes.at(34).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(3, 3, 0);
		graphics->RenderCustom(customImport->meshes.at(34), customImport->meshes.at(34).world, 34, 34);

		camera->InitCamera();
		break;
	case Settings:
		graphics->Render();

		camera->InitCamera();
		break;
	case HighScore:
		graphics->Render();

		camera->InitCamera();
		break;
	}

	// Switch front- and back-buffer
	graphics->swapChain();
}

void Engine::RendHUD()
{
	if (player->HP >= 1)
	{
		customImport->meshes.at(5).world = XMMatrixRotationZ(XMConvertToRadians(60)) * XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(1.5, 1.5, 1);
		graphics->RenderCustom(customImport->meshes.at(5), customImport->meshes.at(5).world, 5, 5);

		if (player->HP >= 2)
		{
			customImport->meshes.at(5).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(1.5, 1.5, 1);
			graphics->RenderCustom(customImport->meshes.at(5), customImport->meshes.at(5).world, 5, 5);

			if (player->HP >= 3)
			{
				customImport->meshes.at(5).world = XMMatrixRotationZ(XMConvertToRadians(-60)) * XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(1.5, 1.5, 1);
				graphics->RenderCustom(customImport->meshes.at(5), customImport->meshes.at(5).world, 5, 5);

				if (player->HP >= 4)
				{
					customImport->meshes.at(5).world = XMMatrixRotationZ(XMConvertToRadians(-120)) * XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(1.5, 1.5, 1);
					graphics->RenderCustom(customImport->meshes.at(5), customImport->meshes.at(5).world, 5, 5);

					if (player->HP >= 5)
					{
						customImport->meshes.at(5).world = XMMatrixRotationZ(XMConvertToRadians(180)) * XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(1.5, 1.5, 1);
						graphics->RenderCustom(customImport->meshes.at(5), customImport->meshes.at(5).world, 5, 5);

						if (player->HP >= 6)
						{
							customImport->meshes.at(5).world = XMMatrixRotationZ(XMConvertToRadians(120)) * XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(1.5, 1.5, 1);
							graphics->RenderCustom(customImport->meshes.at(5), customImport->meshes.at(5).world, 5, 5);
						}
					}
				}
			}
		}
	}
}

bool Engine::sphereToSphere(const TSphere& tSph1, const TSphere& tSph2)
{
	// Calculate the squared distance between the centers of both spheres
	Vector3 vecDist(tSph2.m_vecCenter - tSph1.m_vecCenter);
	float dotProduct = vecDist.x * vecDist.x + vecDist.y * vecDist.y + vecDist.z * vecDist.z;
	float fDistSq(dotProduct);

	// Calculate the squared sum of both radii
	float fRadiiSumSquared(tSph1.m_fRadius + tSph2.m_fRadius);
	fRadiiSumSquared *= fRadiiSumSquared;

	// Check for collision
	// If the distance squared is less than or equal to the square sum
	// of the radii, then we have a collision
	if (fDistSq <= fRadiiSumSquared)
		return true;

	// If not, then return false
	return false;
}

bool Engine::sphereToPlane(const TSphere& tSph, const Vector3& vecPoint, const Vector3& vecNormal)
{
	// Calculate a vector from the point on the plane to the center of the sphere
	Vector3 vecTemp(tSph.m_vecCenter - vecPoint);

	// Calculate the distance: dot product of the new vector with the plane's normal
	float dotProduct = vecTemp.x * vecNormal.x + vecTemp.y * vecNormal.y + vecTemp.z * vecNormal.z;
	float fDist(dotProduct);

	if (fDist > tSph.m_fRadius)
	{
		// The sphere is not touching the plane
		return false;
	}

	// Else, the sphere is colliding with the plane
	return true;
}

bool Engine::pointInSphere(const TSphere& tSph, const Vector3& vecPoint)
{
	// Calculate the squared distance from the point to the center of the sphere
	Vector3 vecDist(tSph.m_vecCenter - vecPoint);
	float dotProduct = vecDist.x * vecDist.x + vecDist.y * vecDist.y + vecDist.z * vecDist.z;
	float fDistSq(dotProduct);

	// Calculate if the squared distance between the sphere's center and the point
	// is less than the squared radius of the sphere
	if (fDistSq < (tSph.m_fRadius * tSph.m_fRadius))
	{
		return true;
	}

	// If not, return false
	return false;
}

bool AABBtoAABB(const TAABB& tBox1, const TAABB& tBox2)
{
	//Check if Box1's max is greater than Box2's min and Box1's min is less than Box2's max
	return(tBox1.m_vecMax.x > tBox2.m_vecMin.x &&
		tBox1.m_vecMin.x < tBox2.m_vecMax.x &&
		tBox1.m_vecMax.y > tBox2.m_vecMin.y &&
		tBox1.m_vecMin.y < tBox2.m_vecMax.y &&
		tBox1.m_vecMax.z > tBox2.m_vecMin.z &&
		tBox1.m_vecMin.z < tBox2.m_vecMax.z);

	//If not, it will return false
}

void Engine::Elevatorfunc()
{
	if (sphereToSphere(*player->sphere, *Esphere))
	{
		Objectpool->ResetBullet();
		gameObject->reset();
		player->NewFloorReset();
		enemyCount = Objectpool->e_poolSize;
		specialEnemyCount = Objectpool->Se_poolSize;
		eCount = enemyCount + specialEnemyCount -1;

		for (int i = 0; i < Objectpool->e_poolSize; i++)
		{
			randomFloat();
			this->Objectpool->createEnemy(Rx, Ry, 0.0f);
		}
		for (int i = 0; i < Objectpool->Se_poolSize; i++)
		{
			randomFloat();
			this->Objectpool->createSpecialEnemy(Rx, Ry, 0.0f);

			this->gameObject->setSpecialCooldown(false);
			this->Objectpool->setSpawnCooldown(false);
		}

		floorClear = false;
		if (floorState == Jungle)
			floorState = Arctic;
		else if (floorState == Arctic)
			floorState = Desert;
		else if (floorState == Desert)
			floorState = Tropical;
		else if (floorState == Tropical)
			floorState = Volcanic;
		else if (floorState == Volcanic)
			floorState = Jungle;

		//resetCooldown();
	}
}

void Engine::rendElevator()
{
	customImport->meshes.at(6).world = XMMatrixTranslation(0, 0, 0) * XMMatrixScaling(1.5, 1.5, 1);
	graphics->RenderCustom(customImport->meshes.at(6), customImport->meshes.at(6).world, 6, 6);
}

void Engine::updateCooldown(double dt)
{
	if (this->cooldown >= this->currentTime)
	{
		this->currentTime += dt;
	}
	else
	{
		this->ready = true;
	}
}

void Engine::resetCooldown()
{
	this->ready = false;
	this->currentTime = 0.0f;
}

void Engine::randomFloat()
{
	//float r3 = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
	Rx = leftWall + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rightWall - (leftWall))));
	Ry = lowerWall + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (upperWall - (lowerWall))));
}

HWND Engine::InitWindow(HINSTANCE hInstance)
{
	// Every window created must belkong to a class

	WNDCLASSEX winClassInfo = { 0 };
	winClassInfo.cbSize = sizeof(WNDCLASSEX);
	winClassInfo.style = CS_HREDRAW | CS_VREDRAW;
	winClassInfo.lpfnWndProc = WndProc; // This function is called for events
	winClassInfo.hInstance = hInstance;
	winClassInfo.lpszClassName = "WindowClass";

	if (!RegisterClassEx(&winClassInfo))
		return false;

	// the window size
	RECT rc = { 0, 0, (LONG)graphics->get_gWidth() , (LONG)graphics->get_gHeight() };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	HWND handle = CreateWindow(
		"WindowClass",	// Class name
		"ERIN",			// Window name
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	return handle;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	//call the default handler function if w do not handle the message here 
	return DefWindowProc(hWnd, message, wParam, lParam);
}