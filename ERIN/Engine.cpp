#include "Engine.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

Engine::Engine(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCommandLine, int nCommandShow)
{
	this->running = true;
	this->camera = new Camera();
	this->graphics = new Graphics();
	this->gameLogic = new GameLogic();

	Esphere = new TSphere();

	this->Objectpool = new ObjectPool();
	this->gameObject = new GameObject();

	//srand(static_cast <unsigned> (time(0)));

	this->customImport = new CustomImport();
	this->player = new Player("player", 3.0f, 0.0f, 0.0f);

	// upper
	this->upper_wall = new Wall();
	this->upper_wall->point = Vector3(0, 20.5, 0);
	this->upper_wall->normal = Vector3(0, -1, 0);
	// left
	this->left_wall = new Wall();
	this->left_wall->point = Vector3(-42.5, 0, 0);
	this->left_wall->normal = Vector3(1, 0, 0);
	// lower
	this->lower_wall = new Wall();
	this->lower_wall->point = Vector3(0, -20.5, 0);
	this->lower_wall->normal = Vector3(0, 1, 0);
	// right
	this->right_wall = new Wall();
	this->right_wall->point = Vector3(42.5, 0, 0);
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

		customImport->LoadCustomFormat("../BinaryDataTextureCube.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(0));
		graphics->CreateTexture(customImport->meshes.at(0));
		customImport->meshes.at(0).textureBool = true;
		/*customImport->LoadCustomFormat("../BinaryDataShip.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(0));*/

		customImport->LoadCustomFormat("../BinaryDataTurret.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(1));

		customImport->LoadCustomFormat("../BinaryDataEnemy.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(2));

		customImport->LoadCustomFormat("../BinaryDataBullet.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(3));

		customImport->LoadCustomFormat("../BinaryDataHUDHP1.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(4));

		customImport->LoadCustomFormat("../BinaryDataHUDHP.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(5));

		customImport->LoadCustomFormat("../BinaryDataHUDHP5.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(6));

		customImport->LoadCustomFormat("../BinaryDataHUDHP4.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(7));

		customImport->LoadCustomFormat("../BinaryDataHUDHP3.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(8));

		customImport->LoadCustomFormat("../BinaryDataHUDHP2.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(9));

		customImport->LoadCustomFormat("../BinaryDataHUDBase.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(10));

		customImport->LoadCustomFormat("../BinaryDataStage.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(11));

		customImport->LoadCustomFormat("../BinaryDataWalls.dat");
		customImport->NewMesh();
		graphics->CustomVertexBuffer(customImport->meshes.at(12));

		graphics->CreateConstantBuffer();
		ShowWindow(wndHandle, nCommandShow);
	}
}

Engine::~Engine()
{
	delete this->graphics;
	delete this->camera;
	delete this->customImport;
	delete this->gameLogic;

	delete this->Esphere;

	delete this->player;
	//delete this->gameObject;

	delete this->Objectpool;
	delete this->gameObject;

	/*for (int i = 0; i < 4; i++)
	{
		delete enemies[i];
	}
	delete enemies;*/

	delete this->upper_wall;
	delete this->left_wall;
	delete this->lower_wall;
	delete this->right_wall;
}

void Engine::processInput()
{
	player->input->update();

	if (player->input->isConnected())
	{
		// Update controller states
		player->input->update();
		// Update player accelerating bool
		player->playerInput();

		switch (gameState)
		{
		case TitleScreen:
			if (this->player->input->State._buttons[GamePad_Button_START] == true)
			{
				cout << "Main Menu" << endl << "Main Menu Option " << mainMenuOption << " (Start Game)" << endl;
				gameState = MainMenu;
			}
			break;

		case MainMenu:
			if (this->player->input->State._buttons[GamePad_Button_DPAD_LEFT] == true)
			{
				if (mainMenuOption == 1)
				{
					mainMenuOption = 0;
					cout << "Main Menu Option " << mainMenuOption << " (Start Game)" << endl;
				}
				else if (mainMenuOption == 3)
				{
					mainMenuOption = 2;
					cout << "Main Menu Option " << mainMenuOption << " (Help & Options)" << endl;
				}
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_RIGHT] == true)
			{
				if (mainMenuOption == 0)
				{
					mainMenuOption = 1;
					cout << "Main Menu Option " << mainMenuOption << " (High Score)" << endl;
				}
				else if (mainMenuOption == 2)
				{
					mainMenuOption = 3;
					cout << "Main Menu Option " << mainMenuOption << " (Quit)" << endl;
				}
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_UP] == true)
			{
				if (mainMenuOption == 2)
				{
					mainMenuOption = 0;
					cout << "Main Menu Option " << mainMenuOption << " (Start Game)" << endl;
				}
				else if (mainMenuOption == 3)
				{
					mainMenuOption = 1;
					cout << "Main Menu Option " << mainMenuOption << " (High Score)" << endl;
				}
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_DOWN] == true)
			{
				if (mainMenuOption == 0)
				{
					mainMenuOption = 2;
					cout << "Main Menu Option " << mainMenuOption << " (Help & Options)" << endl;
				}
				else if (mainMenuOption == 1)
				{
					mainMenuOption = 3;
					cout << "Main Menu Option " << mainMenuOption << " (Quit)" << endl;
				}
			}

			// If accept
			if (aButtonActive == false)
			{
				if (this->player->input->State._buttons[GamePad_Button_A] == true)
				{
					if (mainMenuOption == 0)
					{
						cout << "Game Running" << endl;
						this->ready = true;
						Objectpool->ResetBullet();
						gameState = GameRunning;
					}
					else if (mainMenuOption == 1)
					{
						cout << "High Score" << endl;
						mainMenuOption = 0;
						gameState = HighScore;
					}
					else if (mainMenuOption == 2)
					{
						cout << "Help & Options" << endl;
						mainMenuOption = 0;
						gameState = HelpAndOptions;
					}
					else if (mainMenuOption == 3)
						this->running = false;
				}
			}

			if (this->player->input->State._buttons[GamePad_Button_A] == false)
				aButtonActive = false;
			break;
		case GameRunning:

			//Fire Bullets
			if ((this->player->input->State._right_thumbstick.x || this->player->input->State._right_thumbstick.x) == 1)
			{
				if (Objectpool->getCooldown())
				{
					this->Objectpool->fire(player->getX(), player->getY(), player->getHeading());
					Objectpool->setCooldown(false);
				}
			}

			if (this->player->input->State._buttons[GamePad_Button_X] == true)
			{
				gameObject->enemyCount = 0;
				gameObject->specialEnemyCount = 0;
			}

			if (this->player->input->State._buttons[GamePad_Button_START] == true)
			{
				cout << "Game Paused" << endl << "Pause Menu Option " << pMenuOption << " (Resume)" << endl;
				gameState = Pause;
			}

			// Dpad camera movement
			if (this->player->input->State._buttons[GamePad_Button_DPAD_LEFT] == true)
			{
				if (gameState == GameRunning)
					this->camera->cameraMoveLeft();
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_RIGHT] == true)
			{
				if (gameState == GameRunning)
					this->camera->cameraMoveRight();
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_UP] == true)
			{
				if (gameState == GameRunning)
					this->camera->cameraMoveUp();
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_DOWN] == true)
			{
				if (gameState == GameRunning)
					this->camera->cameraMoveDown();
			}
			break;

		case Pause:
			if (this->player->input->State._buttons[GamePad_Button_DPAD_LEFT] == true)
			{
				if (pMenuOption == 1)
				{
					pMenuOption = 0;
					cout << "Pause Menu Option " << pMenuOption << " (Resume)" << endl;
				}
				else if (pMenuOption == 3)
				{
					pMenuOption = 2;
					cout << "Pause Menu Option " << pMenuOption << " (Help & Options)" << endl;
				}
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_RIGHT] == true)
			{
				if (pMenuOption == 0)
				{
					pMenuOption = 1;
					cout << "Pause Menu Option " << pMenuOption << " (Restart)" << endl;
				}
				else if (pMenuOption == 2)
				{
					pMenuOption = 3;
					cout << "Pause Menu Option " << pMenuOption << " (Main Menu)" << endl;
					gameObject->reset();
				}
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_UP] == true)
			{
				if (pMenuOption == 2)
				{
					pMenuOption = 0;
					cout << "Pause Menu Option " << pMenuOption << " (Resume)" << endl;
				}
				else if (pMenuOption == 3)
				{
					pMenuOption = 1;
					cout << "Pause Menu Option " << pMenuOption << " (Restart)" << endl;
				}
			}
			if (this->player->input->State._buttons[GamePad_Button_DPAD_DOWN] == true)
			{
				if (pMenuOption == 0)
				{
					pMenuOption = 2;
					cout << "Pause Menu Option " << pMenuOption << " (Help & Options)" << endl;
				}
				else if (pMenuOption == 1)
				{
					pMenuOption = 3;
					cout << "Pause Menu Option " << pMenuOption << " (Main Menu)" << endl;
					gameObject->reset();
				}
			}

			// If accept
			if (this->player->input->State._buttons[GamePad_Button_A] == true && aButtonActive == false)
			{
				if (pMenuOption == 0)
				{
					cout << "Game Running" << endl;
					gameState = GameRunning;
				}
				else if (pMenuOption == 1)
				{
					cout << "Restart" << endl;

					pMenuOption = 0;
					floorClear = false;
					gameObject->reset();
					player->PlayerReset();
					Objectpool->ResetBullet();
					camera->ResetCamera();

					for (int i = 0; i < 5; i++)
					{
						Objectpool->enemies[i].setInUse(false);
						Objectpool->Senemies[i].setInUse(false);

						this->Objectpool->createSpecialEnemy(5.0f, 5.0f, 0.0f);
						this->Objectpool->createEnemy(5.0f, 5.0f, 0.0f);
						this->ready = false;
					}

					gameState = GameRunning;
				}
				else if (pMenuOption == 2)
				{
					cout << "Help & Options" << endl;
					gameState = HelpAndOptions;
				}
				else if (pMenuOption == 3)
				{
					cout << "Main Menu " << endl << "Main Menu Option " << mainMenuOption << " (Start Game)" << endl;
					pMenuOption = 0;
					player->PlayerReset();
					gameObject->reset();
					Objectpool->ResetBullet();
					floorClear = false;

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
			break;
		case HighScore:
			if (this->player->input->State._buttons[GamePad_Button_B] == true && bButtonActive == false)
			{
				cout << "Main Menu" << endl << "Main Menu Option " << mainMenuOption << " (Start Game)" << endl;
				gameState = MainMenu;
			}
			break;
		case HelpAndOptions:
			if (this->player->input->State._buttons[GamePad_Button_B] == true && bButtonActive == false)
			{
				cout << "Main Menu" << endl << "Main Menu Option " << mainMenuOption << " (Start Game)" << endl;
				gameState = MainMenu;
			}
			break;
		case GameOver:
			if (this->player->input->State._buttons[GamePad_Button_B] == true && bButtonActive == false)
			{
				cout << "Main Menu" << endl << "Main Menu Option " << mainMenuOption << " (Start Game)" << endl;
				gameState = MainMenu;
			}
			break;
		}

		// fire
		if ((this->player->input->State._right_thumbstick.x || this->player->input->State._right_thumbstick.x) == 1)
		{
			if (Objectpool->getCooldown())
			{
				this->Objectpool->fire(player->getX(), player->getY(), player->getHeading());
				Objectpool->setCooldown(false);
			}
		}
		if (this->player->input->State._buttons[GamePad_Button_Y] == true)
		{
			this->running = false;
		}
		if (this->player->input->State._buttons[GamePad_Button_BACK] == true)
		{
			cout << "Shutting down game!" << endl;
			this->running = false;
		}
	}
}

void Engine::update(double deltaTimeMs)
{
	double deltaTimeS; // millisecond
	deltaTimeS = deltaTimeMs / 1000; // seconds

	switch (gameState)
	{
	case GameRunning:
		Objectpool->bulletupdateCooldown(deltaTimeS);
		updateCooldown(deltaTimeS);
		gameObject->SpecialupdateCooldown(deltaTimeS);
		Objectpool->spawnTimer(deltaTimeS);

		/* *********** Player Update *********** */
		player->hpCooldown(deltaTimeS);
		player->update(deltaTimeMs);

		camera->UpdateGameCamera(this->player->getX(), this->player->getY(), deltaTimeS);
		//camera->cameraFollow(this->player->getX(), this->player->getY());

		// Player Collision Walls
		if (sphereToPlane(*player->sphere, upper_wall->point, upper_wall->normal))
		{
			cout << "upper wall hit" << endl;
			player->SetY(upper_wall->point.y - 0.5f);
		}
		if (sphereToPlane(*player->sphere, left_wall->point, left_wall->normal))
		{
			cout << "left wall hit" << endl;
			player->SetX(left_wall->point.x + 0.5f);
		}
		if (sphereToPlane(*player->sphere, lower_wall->point, lower_wall->normal))
		{
			cout << "lower wall hit" << endl;
			player->SetY(lower_wall->point.y + 0.5f);
		}
		if (sphereToPlane(*player->sphere, right_wall->point, right_wall->normal))
		{
			cout << "right wall hit" << endl;
			player->SetX(right_wall->point.x - 0.5f);
		}

		/* *********** Enemies Updates *********** */
		for (int i = 0; i < this->Objectpool->e_poolSize; i++)
		{
			if (Objectpool->enemies[i].getInUse())
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
				cout << "sphere hit" << endl;
				if (player->getHpCooldown())
				{
					player->HP -= 1;
					gameObject->enemyCount -= 1;
					Objectpool->enemies[i].setInUse(false);
					player->setHpCooldown(false);
				}
			}
		}

		// Collision enemies and walls

		// Special enemy update
		for (int i = 0; i < this->Objectpool->Se_poolSize; i++)
		{
			if (Objectpool->Senemies[i].getInUse())
			{
				Objectpool->Senemies[i].updateSpecialBehavior(*player->shipPos, &Objectpool->Senemies[i], Objectpool->Senemies);
				Objectpool->Senemies[i].update(deltaTimeMs);
				if (Objectpool->getSpawnCooldown())
				{
					Objectpool->createEnemy(savedRx, savedRy, 0);
					//gameObject->enemyCount + 1;
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
					Objectpool->Senemies[i].setObjectPosY(upper_wall->point.y - 0.5f);
				}
				if (sphereToPlane(*Objectpool->Senemies[i].sphere, left_wall->point, left_wall->normal))
				{
					Objectpool->Senemies[i].setObjectPosX(left_wall->point.x + 0.5f);
				}
				if (sphereToPlane(*Objectpool->Senemies[i].sphere, lower_wall->point, lower_wall->normal))
				{
					Objectpool->Senemies[i].setObjectPosY(lower_wall->point.y + 0.5f);
				}
				if (sphereToPlane(*Objectpool->Senemies[i].sphere, right_wall->point, right_wall->normal))
				{
					Objectpool->Senemies[i].setObjectPosX(right_wall->point.x - 0.5f);
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
						gameObject->enemyCount -= 1;
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
						gameObject->specialEnemyCount -= 1;
						Objectpool->Senemies[t].setInUse(false);
						Objectpool->bullets[i].setInUse(false);
					}
				}
			}
		}

		/* *********** HUD Logic *********** */
		if (gameObject->enemyCount <= 0 && gameObject->specialEnemyCount <= 0)
		{
			cout << "Reset Game" << endl;
			floorClear = true;
			gameObject->reset();
			gameObject->SpecialReset();
			Objectpool->ResetBullet();
		}

		if (player->HP <= 0)
		{
			cout << "Game Over" << endl;

			player->PlayerReset();
			gameObject->reset();

			for (int i = 0; i < 5; i++)
			{
				Objectpool->enemies[i].setInUse(false);
			}

			gameState = GameOver;
		}

		break;
	case TitleScreen:
		if (printTitle == true)
		{
			cout << "Title Screen | Press Start to Continue" << endl;
			printTitle = false;
		}
		break;
	case MainMenu:
		break;
	case Pause:
		break;
	}
}

void Engine::render()
{
	switch (gameState)
	{
	case GameRunning:

		graphics->Render();

		Rx = -20 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (20 - (-20))));
		Ry = -10 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (10 - (-10))));

		//spawn enemies
		if (this->ready)
		{
			for (int i = 0; i <Objectpool->e_poolSize; i++)
			{
				cout << "enemy created" << endl;
				this->Objectpool->createEnemy(Rx, Ry, 0.0f);
				this->ready = false;
			}
		}
		//spawn special enemies
		if (this->gameObject->sReady)
		{
			for (int i = 0; i < Objectpool->Se_poolSize; i++)
			{
				cout << "senemy created" << endl;
				this->Objectpool->createSpecialEnemy(Rx, Ry, 0.0f);
				savedRx = Rx;
				savedRy = Ry;
				this->gameObject->sReady = false;
			}
		}

		for (int w = 11; w < 13; w++)
		{
			if (w == 11)
				customImport->meshes.at(w).world = XMMatrixTranslation(0, 0, 1);
			if (w == 12)
				customImport->meshes.at(w).world = XMMatrixTranslation(0, 0, 1);
			graphics->RenderCustom(customImport->meshes.at(w), customImport->meshes.at(w).world, w);
		}

		// Custom Importer
		for (int j = 0; j < 2; j++)
		{
			if (j == 0)
				customImport->meshes.at(j).world = *player->shipMatrix;
			if (j == 1)
				customImport->meshes.at(j).world = *player->turretMatrix;
			graphics->RenderCustom(customImport->meshes.at(j), customImport->meshes.at(j).world, j);
		}

		if (floorClear == true)
		{
			Elevatorfunc();
		}

		if (player->HP > 0)
		{
			RendHUD();
		}

		//Bullet rendering
		for (int i = 0; i < Objectpool->getBulletPoolSize(); i++)
		{
			if (Objectpool->bullets[i].getInUse())
			{
				graphics->RenderCustom(customImport->meshes.at(3), *Objectpool->bullets[i].bulletMatrix, 3);
			}
		}

		// Enemy rendering
		for (int i = 0; i < Objectpool->e_poolSize; i++)
		{
			if (Objectpool->enemies[i].getInUse())
			{
				graphics->RenderCustom(customImport->meshes.at(2), *Objectpool->enemies[i].objectMatrix, 2);
			}
		}
		//special enemy rendering
		for (int i = 0; i < Objectpool->Se_poolSize; i++)
		{
			if (Objectpool->Senemies[i].getInUse())
			{
				graphics->RenderCustom(customImport->meshes.at(2), *Objectpool->Senemies[i].objectMatrix, 2);
			}
		}

		// Camera Update
		camera->InitCamera();

		break;
	case TitleScreen:
		//TitleScreen->render();			// Example of how to render the title screen
		graphics->TitleScreenRender();
		break;
	case MainMenu:
		//MainMenu->render();				// Example of how to render the main menu
		graphics->MainMenuRender();
		break;
	case Pause:
		//graphics->PauseRender();
		break;
	case GameOver:
		graphics->GameOverRender();
		break;
	case HighScore:
		graphics->HighScoreRender();
		break;
	case HelpAndOptions:
		graphics->HelpAndOptionsRender();
		break;
	}

	// Switch front- and back-buffer
	graphics->get_gSwapChain()->Present(1, 0);
}

void Engine::RendHUD()
{
	int i = 4;

	if (player->HP >= 1)
	{
		customImport->meshes.at(i).world = XMMatrixTranslation(0, 0, 0);
		graphics->RenderCustom(customImport->meshes.at(i + 0), customImport->meshes.at(i).world, i + 0);

		if (player->HP >= 2)
		{
			graphics->RenderCustom(customImport->meshes.at(i + 1), customImport->meshes.at(i).world, i + 1);

			if (player->HP >= 3)
			{
				graphics->RenderCustom(customImport->meshes.at(i + 2), customImport->meshes.at(i).world, i + 2);

				if (player->HP >= 4)
				{
					graphics->RenderCustom(customImport->meshes.at(i + 3), customImport->meshes.at(i).world, i + 3);

					if (player->HP >= 5)
					{
						graphics->RenderCustom(customImport->meshes.at(i + 4), customImport->meshes.at(i).world, i + 4);

						if (player->HP >= 6)
						{
							graphics->RenderCustom(customImport->meshes.at(i + 5), customImport->meshes.at(i).world, i + 5);
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
		floorClear = false;
		for (int i = 0; i < Objectpool->e_poolSize; i++)
		{
			Objectpool->enemies[i].setInUse(false);

			this->Objectpool->createEnemy(Rx, Ry, 0.0f);
			this->ready = false;
		}
		for (int i = 0; i < Objectpool->Se_poolSize; i++)
		{
			Objectpool->Senemies[i].setInUse(false);

			this->Objectpool->createSpecialEnemy(Rx, Ry, 0.0f);
			this->gameObject->sReady = false;
			this->Objectpool->setSpawnCooldown(false);
		}
	}
	else
	{
		customImport->meshes.at(10).world = XMMatrixTranslation(0, 0, 0);
		graphics->RenderCustom(customImport->meshes.at(10), customImport->meshes.at(10).world, 10);
		Esphere->m_vecCenter = Vector3(0, 0, 0);
		Esphere->m_fRadius = 0.5f;
		cout << "Render Elevater Cube" << endl;
	}
}

void Engine::updateCooldown(double dt)
{
	if (this->cooldown <= this->currentTime)
	{
		this->currentTime = 0.0f;
		//this->ready = true;
	}
	else
	{
		this->currentTime += dt;
	}
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