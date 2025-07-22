#include "game_manager.h"

void GameManager::_bind_methods()
{
	//expose property in inspector
	ClassDB::bind_method(D_METHOD("get_doubleTime"), &GameManager::get_doubleTime); //add getters and setters to classdb
	ClassDB::bind_method(D_METHOD("set_doubleTime", "time"), &GameManager::set_doubleTime);

	//add the property by setting the getters and setters function names to the ones we added above
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Double Time"), "set_doubleTime", "get_doubleTime");

	ClassDB::bind_method(D_METHOD("get_maxSpeedMultiplier"), &GameManager::get_maxSpeedMultiplier);
	ClassDB::bind_method(D_METHOD("set_maxSpeedMultiplier", "max"), &GameManager::set_maxSpeedMultiplier);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Maximum Speed multipler"), "set_maxSpeedMultiplier", "get_maxSpeedMultiplier");

	ClassDB::bind_method(D_METHOD("get_scoreMultiplier"), &GameManager::get_scoreMultiplier);
	ClassDB::bind_method(D_METHOD("set_score_multiplier", "mult"), &GameManager::set_score_multiplier);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "Score Multiplier"), "set_score_multiplier", "get_scoreMultiplier");
}

void GameManager::StartGame()
{
	elapsedTime = 0.0f;
}

void GameManager::PauseGame()
{
}

void GameManager::FinishGame()
{
	//save score
}

void GameManager::_ready()
{
	playerMovement = (PlayerMovement*)get_tree()->get_current_scene()->get_node<Player>("%Player")->get_child(1)->get_child(1);
	playerRigidBody = (RigidBody3D*)get_tree()->get_current_scene()->get_node<Player>("%Player")->get_child(1);
}

void GameManager::_physics_process(double delta)
{
	elapsedTime += delta;
	if (playerMovement != nullptr)
	{
		playerMovement->speedMultiplier = Math::min(1.0f + (elapsedTime / doubleTime), maxSpeedMultiplier);
	}

	score = Math::abs(playerRigidBody->get_global_position().z * scoreMultiplier);
	print_line(score);
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
