#include "Engine.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

Engine::Engine(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCommandLine, int nCommandShow)
{
	this->running = true;

	this->gameState = TitleScreen;
	cout << "Title Screen" << endl;

	this->camera = new Camera();
	this->graphics = new Graphics();
	this->gameLogic = new GameLogic();

	this->Objectpool = new ObjectPool();

	this->customImport = new CustomImport();
	this->player = new Player("player", 3.0f, 0.0f, 0.0f);


	this->enemies = new GameObject*[5];
	this->enemies[0] = new GameObject(1, "enemy1", 5.0f, 0.0f, 0.1f, true);
	this->enemies[1] = new GameObject(2, "enemy2", 0.0f, 5.0f, 0.1f, true);
	this->enemies[2] = new GameObject(3, "enemy3", -5.0f, 0.0f, 0.1f, true);
	this->enemies[3] = new GameObject(4, "enemy4", 0.0f, -5.0f, 0.1f, true);

	// upper
	this->upper_wall = new Wall();
	this->upper_wall->point = Vector3(0, 10, 0);
	this->upper_wall->normal = Vector3(0, -1, 0);
	// left
	this->left_wall = new Wall();
	this->left_wall->point = Vector3(-20, 0, 0);
	this->left_wall->normal = Vector3(1, 0, 0);
	// lower
	this->lower_wall = new Wall();
	this->lower_wall->point = Vector3(0, -10, 0);
	this->lower_wall->normal = Vector3(0, 1, 0);
	// right
	this->right_wall = new Wall();
	this->right_wall->point = Vector3(20, 0, 0);
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

		graphics->CreateTriangle(this->triangle);

		customImport->LoadCustomFormat("../BinaryDataSphere2.dat");
		customImport->NewMesh();

		customImport->LoadCustomFormat("../BinaryDataCube.dat");
		customImport->NewMesh();
		customImport->NewMesh();

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

	delete this->player;
	//delete this->gameObject;

	delete this->Objectpool;

	/*for (int i = 0; i < 4; i++)
	{
		delete enemies[i];
	}
	delete enemies;*/

	delete triangle;
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
					player->PlayerReset();
					for (int i = 0; i < 4; i++)
					{
						enemies[i]->Reset();
					}
					camera->ResetCamera();
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
		}

		// fire
		if ((this->player->input->State._right_thumbstick.x || this->player->input->State._right_thumbstick.x) == 1)
		{
			if (Objectpool->getCooldown()==true)
			{
				this->Objectpool->fire(player->getX(), player->getY(), player->getHeading());
				Objectpool->setCooldown(false);
			}
		}
		if (this->player->input->State._buttons[GamePad_Button_Y] == true)
		{
			this->running = false;
		}
		/*
		if (this->player->input->State._buttons[GamePad_Button_X] == true)
		{
			if (this->ready)
			{
				cout << "enemy created" << endl;
				this->Objectpool->createEnemy(5.0f, 5.0f, 0.0f);
				this->ready = false;
			}
			//this->running = false;
		}
		if (this->player->input->State._buttons[GamePad_Button_B] == true)
		{
		}
		if (this->player->input->State._buttons[GamePad_Button_A] == true)
		{
		}

		if (this->player->input->State._buttons[GamePad_Button_START] == true)
		{
		}*/
		if (this->player->input->State._buttons[GamePad_Button_BACK] == true)
		{
			cout << "Shutting down game!" << endl;
			this->running = false;
		}

		// BUMPERS & TRIGGERS
		/*if (this->player->input->State._buttons[GamePad_Button_LEFT_THUMB] == true)
		{
		}
		if (this->player->input->State._buttons[GamePad_Button_RIGHT_THUMB] == true)
		{
		}

		if (this->player->input->State._buttons[GamePad_Button_LEFT_SHOULDER] == true)
		{
		}
		if (this->player->input->State._buttons[GamePad_Button_RIGHT_SHOULDER] == true)
		{
		}*/

		// DPAD
		/*if (this->player->input->State._buttons[GamePad_Button_DPAD_LEFT] == true)
		{
		}
		if (this->player->input->State._buttons[GamePad_Button_DPAD_RIGHT] == true)
		{
		}
		if (this->player->input->State._buttons[GamePad_Button_DPAD_UP] == true)
		{
		}
		if (this->player->input->State._buttons[GamePad_Button_DPAD_DOWN] == true)
		{
		}*/
	}
}

void Engine::update(double deltaTimeMs)
{
	double deltaTimeS; // millisecond
	deltaTimeS = deltaTimeMs / 1000; // seconds

	Objectpool->bulletupdateCooldown(deltaTimeS);
	switch (gameState)
	{
	case GameRunning:
		//GameLogic->levelHandler();		// Example of how to start a level
	updateCooldown(deltaTimeS);
	// Player Update
	player->update(deltaTimeMs);

	/*gameObject->updateBehavior(*player->pos, gameObject, enemies);
	gameObject->update(deltaTimeMs);*/

	//Bullet Updates
	for (int i = 0; i < Objectpool->getBulletPoolSize(); i++)
	{
		if (Objectpool->bullets[i].getInUse())
		{
			Objectpool->bullets[i].update(deltaTimeMs);
		}
	}

	// Enemies Updates
	for (int i = 0; i < this->Objectpool->e_poolSize; i++)
	{
		if (Objectpool->enemies[i].getInUse())
		{
			Objectpool->enemies[i].updateBehavior(*player->shipPos, &Objectpool->enemies[i], Objectpool->enemies);
			Objectpool->enemies[i].update(deltaTimeMs);
		}
		/*this->Objectpool->enemies[i]->updateBehavior(*player->shipPos, this->Objectpool->enemies[i], this->Objectpool->enemies);
		Objectpool->enemies[i]->update(deltaTimeMs);*/
	}

	// Collision Walls
	if (sphereToPlane(*player->sphere, upper_wall->point, upper_wall->normal))
	{
		cout << "upper wall hit" << endl;
		player->setY(upper_wall->point.y - 0.5f);
	}
	if (sphereToPlane(*player->sphere, left_wall->point, left_wall->normal))
	{
		cout << "left wall hit" << endl;
		player->setX(left_wall->point.x + 0.5f);
	}
	if (sphereToPlane(*player->sphere, lower_wall->point, lower_wall->normal))
	{
		cout << "lower wall hit" << endl;
		player->setY(lower_wall->point.y + 0.5f);
	}
	if (sphereToPlane(*player->sphere, right_wall->point, right_wall->normal))
	{
		cout << "right wall hit" << endl;
		player->setX(right_wall->point.x - 0.5f);
	}

	//Collision Bullets
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
					Objectpool->enemies[t].reset();
					Objectpool->enemies[t].setInUse(false);
					Objectpool->bullets[i].setInUse(false);
				}

			}
		}
	}

	// Collision Enemies
	for (int i = 0; i < Objectpool->e_poolSize; i++)
	{
		if (Objectpool->enemies[i].getInUse() && sphereToSphere(*player->sphere, *Objectpool->enemies[i].sphere))
		{
			cout << "sphere hit" << endl;
			//Objectpool->enemies[i].reset();
			//Objectpool->enemies[i].setInUse(false);
		}
		}

	//printf("Elapsed time: %fS.\n", deltaTimeS);
		//render();
		break;
	case TitleScreen:
		graphics->TitleScreenRender();
		break;
	case MainMenu:
		break;
	case Pause:
		break;
	}

	// printf("Elapsed time: %fS.\n", deltaTimeS);

}

void Engine::render()
{
	//graphics->UpdateConstantBuffer();

	switch (gameState)
	{
	case GameRunning:

	graphics->Render();
	graphics->RendPlayer(*player->shipMatrix);
	graphics->RendPlayer(*player->turretMatrix);

	// Custom Importer
	for (int j = 0; j < 3; j++)
	{
		if (j == 1)
			customImport->meshes.at(j).world = XMMatrixTranslation(6, 2, 0);
		if (j == 2)
			customImport->meshes.at(j).world = XMMatrixTranslation(6, 0, 0);
		graphics->RenderCustom(customImport->meshes.at(j), customImport->meshes.at(j).world);
	}

		//graphics->RenderCustom(customImport->meshes.at(0));
	
	//Bullet rendering
	for (int i = 0; i < Objectpool->getBulletPoolSize(); i++)
	{
		if (Objectpool->bullets[i].getInUse())
		{
			graphics->RendPlayer(*Objectpool->bullets[i].bulletMatrix);
		}
	}

	// Enemy rendering
	for (int i = 0; i < Objectpool->e_poolSize; i++)
	{
		if (Objectpool->enemies[i].getInUse())
		{

			graphics->RendPlayer(*Objectpool->enemies[i].objectMatrix);
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

void Engine::updateCooldown(double dt)
{
	if (this->cooldown <= this->currentTime)
	{
		this->currentTime = 0.0f;
		this->ready = true;
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