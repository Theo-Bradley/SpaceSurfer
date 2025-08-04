#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "player_movement.h"
#include "follow_camera.h"
#include "obstacle.h"
#include "spawn_node.h"
#include "coin.h"
#include "coin_manager.h"
#include "player.h"
#include "moving_obstacle.h"
#include "game_manager.h"
#include "follow_floor.h"
#include "floor_spawn.h"
#include "main_menu_manager.h"

using namespace godot;

void initialize_gdextension_types(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	GDREGISTER_RUNTIME_CLASS(PlayerMovement);
	GDREGISTER_CLASS(FollowCamera);
	GDREGISTER_RUNTIME_CLASS(Obstacle);
	GDREGISTER_RUNTIME_CLASS(SpawnNode);
	GDREGISTER_RUNTIME_CLASS(Coin);
	GDREGISTER_RUNTIME_CLASS(CoinManager);
	GDREGISTER_RUNTIME_CLASS(Player);
	GDREGISTER_RUNTIME_CLASS(MovingObstacle);
	GDREGISTER_RUNTIME_CLASS(GameManager);
	GDREGISTER_RUNTIME_CLASS(FollowFloor);
	GDREGISTER_RUNTIME_CLASS(FloorSpawn);
	GDREGISTER_RUNTIME_CLASS(MainMenuManager);
}

void uninitialize_gdextension_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C"
{
// Initialization
GDExtensionBool GDE_EXPORT SpaceSurfer_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
{
	GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
	init_obj.register_initializer(initialize_gdextension_types);
	init_obj.register_terminator(uninitialize_gdextension_types);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}
