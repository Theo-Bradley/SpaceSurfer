#include "game_manager.h"

void GameManager::_bind_methods()
{
	//expose property in inspector
	ClassDB::bind_method(D_METHOD("get_doubleTime"), &GameManager::get_doubleTime); //add getters and setters to classdb
	ClassDB::bind_method(D_METHOD("set_doubleTime", "time"), &GameManager::set_doubleTime);

	//add the property by setting the getters and setters function names to the ones we added above
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Speed Double Time"), "set_doubleTime", "get_doubleTime");

	ClassDB::bind_method(D_METHOD("get_maxSpeedMultiplier"), &GameManager::get_maxSpeedMultiplier);
	ClassDB::bind_method(D_METHOD("set_maxSpeedMultiplier", "max"), &GameManager::set_maxSpeedMultiplier);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Maximum Speed multipler"), "set_maxSpeedMultiplier", "get_maxSpeedMultiplier");

	ClassDB::bind_method(D_METHOD("get_scoreMultiplier"), &GameManager::get_scoreMultiplier);
	ClassDB::bind_method(D_METHOD("set_score_multiplier", "mult"), &GameManager::set_score_multiplier);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "Score Multiplier"), "set_score_multiplier", "get_scoreMultiplier");

	ClassDB::bind_method(D_METHOD("get_UI"), &GameManager::get_UI);
	ClassDB::bind_method(D_METHOD("set_UI", "ref"), &GameManager::set_UI);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "UI node", PROPERTY_HINT_NODE_TYPE, "Control"), "set_UI", "get_UI");

	ClassDB::bind_method(D_METHOD("PauseGame"), &GameManager::PauseGame); //expose the pause func for the pause button
}

void GameManager::StartGame()
{
	elapsedTime = 0.0f;

	//load highscore off disk
	Ref<Resource> res = (ResourceLoader::get_singleton()->load("res://highscore.json"));
	if (res != nullptr)
	{
		Ref<JSON> resJSON = (Ref<JSON>)res;
		highscore = (int)resJSON->get_data();
	}
	if (highscore > 1)
	{
		highscoreLabel->set_text(TO_STRING(highscore));
	}
}

void GameManager::PauseGame()
{
	if (!paused)
	{
		get_tree()->set_pause(true);
		paused = true;
	}
	else
	{
		get_tree()->set_pause(false);
		paused = false;
	}
}

void GameManager::FinishGame()
{
	//save score
	if (HighScore(score, highscore))
	{
		Ref<Resource> res = (ResourceLoader::get_singleton()->load("res://highscore.json"));
		Ref<JSON> resJSON = (Ref<JSON>)res;
		resJSON->set_data(JSON::stringify(highscore));
		ResourceSaver::get_singleton()->save(resJSON, "res://highscore.json");
	}
}

bool GameManager::HighScore(int score, int highScore)
{
	if (score > highScore)
		return true;
	return false;
	//add some other high score stuff here such as particle effects, leaderboard updating etc
}

void GameManager::_ready()
{
	set_process_mode(ProcessMode::PROCESS_MODE_ALWAYS);
	playerMovement = (PlayerMovement*)get_tree()->get_current_scene()->get_node<Player>("%Player")->get_child(1)->get_child(1);
	playerRigidBody = (RigidBody3D*)get_tree()->get_current_scene()->get_node<Player>("%Player")->get_child(1);
	scoreLabel = (Label*)UINode->get_child(0);
	highscoreLabel = (Label*)scoreLabel->get_child(0);
	pauseButton = (Button*)UINode->get_child(1);
	pauseButton->connect("pressed", Callable(this, "PauseGame"));
	progBar = (ProgressBar*)UINode->get_child(2);
	StartGame();
}

void GameManager::_process(double delta)
{
	if (scoreLabel != nullptr)
	{
		scoreLabel->set_text(TO_STRING(score));
	}
	float progress = 0.0f;
	if (highscore > 1) //in case highscore is wrong
		progress = (float)score / highscore;
	progBar->set_value(progress);
	//maybe hide prog bar when highscore reached
	//or maybe get the next highscore from the leaderboard
}

void GameManager::_physics_process(double delta)
{
	elapsedTime += delta;
	if (playerMovement != nullptr)
	{
		playerMovement->speedMultiplier = Math::min(1.0f + (elapsedTime / doubleTime), maxSpeedMultiplier); //slowly increase running speed over time
	}

	score = Math::abs(playerRigidBody->get_global_position().z * scoreMultiplier);
}

float GameManager::get_doubleTime()
{
	return doubleTime;
}

void GameManager::set_doubleTime(float time)
{
	doubleTime = time;
}

float GameManager::get_maxSpeedMultiplier()
{
	return maxSpeedMultiplier;
}

void GameManager::set_maxSpeedMultiplier(float max)
{
	maxSpeedMultiplier = max;
}

int GameManager::get_scoreMultiplier()
{
	return scoreMultiplier;
}
void GameManager::set_score_multiplier(int mult)
{
	scoreMultiplier = mult;
}

Control* GameManager::get_UI()
{
	return UINode;
}
void GameManager::set_UI(Control* ref)
{
	UINode = ref;
}
