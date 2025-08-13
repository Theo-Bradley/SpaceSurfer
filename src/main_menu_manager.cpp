#include "main_menu_manager.h"

enum class MainMenuManager::Maps
{
	Earth,
	Mars,
	Jupiter
};

void MainMenuManager::_bind_methods()
{
	//expose property in inspector
	ClassDB::bind_method(D_METHOD("get_buttonContainer"), &MainMenuManager::get_buttonContainer); //add getters and setters to classdb
	ClassDB::bind_method(D_METHOD("set_buttonContainer", "conatiner"), &MainMenuManager::set_buttonContainer);

	//add the property by setting the getters and setters function names to the ones we added above
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Button Container (Horizontal)", PROPERTY_HINT_NODE_TYPE, "Container"), "set_buttonContainer", "get_buttonContainer");

	ClassDB::bind_method(D_METHOD("get_playButton"), &MainMenuManager::get_playButton);
	ClassDB::bind_method(D_METHOD("set_playButton", "button"), &MainMenuManager::set_playButton);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Play Button", PROPERTY_HINT_NODE_TYPE, "Button"), "set_playButton", "get_playButton");

	ClassDB::bind_method(D_METHOD("get_highscoreLabel"), &MainMenuManager::get_highscoreLabel);
	ClassDB::bind_method(D_METHOD("set_highscoreLabel", "label"), &MainMenuManager::set_highscoreLabel);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Highscore Label", PROPERTY_HINT_NODE_TYPE, "Label"), "set_highscoreLabel", "get_highscoreLabel");

	ADD_GROUP("Scenes", "scn_");
	
	ClassDB::bind_method(D_METHOD("get_earthScene"), &MainMenuManager::get_earthScene);
	ClassDB::bind_method(D_METHOD("set_earthScene", "scene"), &MainMenuManager::set_earthScene);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "scn_Earth Scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_earthScene", "get_earthScene");

	ClassDB::bind_method(D_METHOD("get_marsScene"), &MainMenuManager::get_marsScene);
	ClassDB::bind_method(D_METHOD("set_marsScene", "scene"), &MainMenuManager::set_marsScene);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "scn_Mars Scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_marsScene", "get_marsScene");

	ClassDB::bind_method(D_METHOD("get_jupiterScene"), &MainMenuManager::get_jupiterScene);
	ClassDB::bind_method(D_METHOD("set_jupiterScene", "scene"), &MainMenuManager::set_jupiterScene);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "scn_Jupiter Scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_jupiterScene", "get_jupiterScene");

	ADD_GROUP("Textures", "tex_");

	ClassDB::bind_method(D_METHOD("get_playTex"), &MainMenuManager::get_playTex);
	ClassDB::bind_method(D_METHOD("set_playTex", "tex"), &MainMenuManager::set_playTex);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_Play Texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_playTex", "get_playTex");
	
	ClassDB::bind_method(D_METHOD("get_coinTex"), &MainMenuManager::get_coinTex);
	ClassDB::bind_method(D_METHOD("set_coinTex", "tex"), &MainMenuManager::set_coinTex);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_Coin Texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_coinTex", "get_coinTex");

	ADD_SUBGROUP("Map Textures", "tex_map_");

	ClassDB::bind_method(D_METHOD("get_earthTex"), &MainMenuManager::get_earthTex);
	ClassDB::bind_method(D_METHOD("set_earthTex", "tex"), &MainMenuManager::set_earthTex);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_map_Earth Button Texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_earthTex", "get_earthTex");

	
	ClassDB::bind_method(D_METHOD("get_marsTex"), &MainMenuManager::get_marsTex);
	ClassDB::bind_method(D_METHOD("set_marsTex", "tex"), &MainMenuManager::set_marsTex);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_map_Mars Button Texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_marsTex", "get_marsTex");

	
	ClassDB::bind_method(D_METHOD("get_jupiterTex"), &MainMenuManager::get_jupiterTex);
	ClassDB::bind_method(D_METHOD("set_jupiterTex", "tex"), &MainMenuManager::set_jupiterTex);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_map_Jupiter Button Texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_jupiterTex", "get_jupiterTex");

		ClassDB::bind_method(D_METHOD("get_earthSelectedTex"), &MainMenuManager::get_earthSelectedTex);
	ClassDB::bind_method(D_METHOD("set_earthSelectedTex", "tex"), &MainMenuManager::set_earthSelectedTex);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_map_Earth Button Selected Texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_earthSelectedTex", "get_earthSelectedTex");

	
	ClassDB::bind_method(D_METHOD("get_marsSelectedTex"), &MainMenuManager::get_marsSelectedTex);
	ClassDB::bind_method(D_METHOD("set_marsSelectedTex", "tex"), &MainMenuManager::set_marsSelectedTex);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_map_Mars Button Selected Texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_marsSelectedTex", "get_marsSelectedTex");

	
	ClassDB::bind_method(D_METHOD("get_jupiterSelectedTex"), &MainMenuManager::get_jupiterSelectedTex);
	ClassDB::bind_method(D_METHOD("set_jupiterSelectedTex", "tex"), &MainMenuManager::set_jupiterSelectedTex);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_map_Jupiter Button Selected Texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_jupiterSelectedTex", "get_jupiterSelectedTex");

	//add button callbacks
	ClassDB::bind_method(D_METHOD("PressedEarth"), &MainMenuManager::PressedEarth);
	ClassDB::bind_method(D_METHOD("PressedMars"), &MainMenuManager::PressedMars);
	ClassDB::bind_method(D_METHOD("PressedJupiter"), &MainMenuManager::PressedJupiter);
	ClassDB::bind_method(D_METHOD("PressedPlay"), &MainMenuManager::PressedPlay);
}

void MainMenuManager::_ready()
{
	//load highscore off disk
	Ref<Resource> res = (ResourceLoader::get_singleton()->load("res://highscore.json"));
	int highscore = 0;
	if (res != nullptr)
	{
		Ref<JSON> resJSON = (Ref<JSON>)res;
		highscore = (int)resJSON->get_data();
	}
	if (highscore > 1 && highscoreLabel != nullptr)
	{
		highscoreLabel->set_text(TO_STRING(highscore));
	}
	res = (ResourceLoader::get_singleton()->load("res://map_unlock.json")); //setup map flag to be processed, which unlocks map buttons
	if (res != nullptr)
	{
		Ref<JSON> resJSON = (Ref<JSON>)res;
		mapFlag = (unsigned char)resJSON->get_data();
	}
	res = (ResourceLoader::get_singleton()->load("res://coins.json"));
	if (res != nullptr)
	{
		Ref<JSON> resJSON = (Ref<JSON>)res;
		coins = (int)resJSON->get_data();
	}

	earthButton = (TextureButton*)buttonContainer->get_child(0)->get_child(0);
	marsButton = (TextureButton*)buttonContainer->get_child(1)->get_child(0);
	jupiterButton = (TextureButton*)buttonContainer->get_child(2)->get_child(0);
	ProcessMapFlag(mapFlag);
	earthButton->connect("pressed", Callable(this, "PressedEarth"));
	marsButton->connect("pressed", Callable(this, "PressedMars"));
	jupiterButton->connect("pressed", Callable(this, "PressedJupiter"));

	if (playButton != nullptr)
	{
		playButton->connect("pressed", Callable(this, "PressedPlay"));
		playButtonIcon = (TextureRect*)playButton->get_child(0)->get_child(0);
		playButtonCostLabel = (Label*)playButton->get_child(0)->get_child(1);
	}

	initalized = true; //stops us saving uninitalized data to disk
}

MainMenuManager::~MainMenuManager()
{
	if (initalized)
	{
		//save coins and mapflag to disk
		Ref<JSON>resJSON = Ref<JSON>(memnew(JSON));
		resJSON->set_data(mapFlag);
		ResourceSaver::get_singleton()->save(resJSON, "res://map_unlock.json");
		resJSON.unref();

		resJSON = Ref<JSON>(memnew(JSON));
		resJSON->set_data(coins);
		ResourceSaver::get_singleton()->save(resJSON, "res://coins.json");
		resJSON.unref();
	}
}


void MainMenuManager::ProcessMapFlag(unsigned char mapFlag)
{ //mapFlag layout 00000JME J: Jupiter unlock bool M: Mars unlock bool E: Earth unlock bool

	if ((mapFlag & 0b00000001) == 0b00000001) //Earth is unlocked (always true)
	{
		print_line("Earth unlocked");
		earthUnlocked = true;
		earthButton->set_texture_normal(earthTex);
		earthButton->set_texture_pressed(earthSelectedTex);
	}

	if ((mapFlag & 0b00000010) == 0b00000010) //Mars is unlocked
	{
		print_line("Mars unlocked");
		marsUnlocked = true;
		marsButton->set_texture_normal(marsTex);
		marsButton->set_texture_pressed(marsSelectedTex);
	}

	if ((mapFlag & 0b00000100) == 0b00000100) //Jupiter is unlocked
	{
		print_line("Jupiter unlocked");
		jupiterUnlocked = true;
		jupiterButton->set_texture_normal(jupiterTex);
		jupiterButton->set_texture_pressed(jupiterSelectedTex);
	}
}

void MainMenuManager::PressedPlay()
{
	if (shouldLoadMap)
	{
		switch (selectedMap)
		{
			case (Maps::Earth):
				if (earthScene != nullptr)
					get_tree()->change_scene_to_packed(earthScene);
				break;

			case (Maps::Mars):
				if (marsScene != nullptr)
					get_tree()->change_scene_to_packed(marsScene);
				break;

			case (Maps::Jupiter):
				if (jupiterScene != nullptr)
					get_tree()->change_scene_to_packed(jupiterScene);
				break;
		}
	}
	else
	{
		if (coins >= unlockCost)
		{
			coins = coins - unlockCost;

			switch (selectedMap) //apply the newly unlocked map to mapflag
			{
				case (Maps::Earth):
				{
					mapFlag = mapFlag | 0b00000001;
					ProcessMapFlag(mapFlag);
					PressedEarth();
					break;
				}
				case (Maps::Mars):
				{
					mapFlag = mapFlag | 0b00000010;
					ProcessMapFlag(mapFlag);
					PressedMars();
					break;
				}
				case (Maps::Jupiter):
				{
					mapFlag = mapFlag | 0b00000100;
					ProcessMapFlag(mapFlag);
					PressedJupiter();
					break;
				}
			}
		}
	}
}

void MainMenuManager::set_buttonContainer(Container* container)
{
	buttonContainer = container;
}

Container* MainMenuManager::get_buttonContainer() const
{
	return buttonContainer;
}

void MainMenuManager::set_playButton(Button* button)
{
	playButton = button;
}

Button* MainMenuManager::get_playButton() const
{
	return playButton;
}

void MainMenuManager::set_highscoreLabel(Label* label)
{
	highscoreLabel = label;
}

Label* MainMenuManager::get_highscoreLabel() const
{
	return highscoreLabel;
}

void MainMenuManager::PressedEarth()
{
	selectedMap = Maps::Earth;
	if (earthUnlocked)
	{
		playButtonIcon->set_texture(playTex);
		shouldLoadMap = true;
		SetCostLabel();
	}
	else
	{
		playButtonIcon->set_texture(coinTex);
		shouldLoadMap = false;
		unlockCost = earthCost;
		SetCostLabel(unlockCost);
	}
}

void MainMenuManager::PressedMars()
{
	selectedMap = Maps::Mars;
	if (marsUnlocked)
	{
		playButtonIcon->set_texture(playTex);
		shouldLoadMap = true;
		SetCostLabel();
	}
	else
	{
		playButtonIcon->set_texture(coinTex);
		shouldLoadMap = false;
		unlockCost = marsCost;
		SetCostLabel(unlockCost);
	}
}

void MainMenuManager::PressedJupiter()
{
	selectedMap = Maps::Jupiter;
	if (jupiterUnlocked)
	{
		playButtonIcon->set_texture(playTex);
		shouldLoadMap = true;
		SetCostLabel();
	}
	else
	{
		playButtonIcon->set_texture(coinTex);
		shouldLoadMap = false;
		unlockCost = jupiterCost;
		SetCostLabel(unlockCost);
	}
}

void MainMenuManager::SetCostLabel(int cost)
{
	if (shouldLoadMap)
	{
		if (playButtonCostLabel != nullptr)
			playButtonCostLabel->set_text("");
		playButton->set_disabled(false);
	}
	else
	{
		String text = "%d/%d";
		Array args;
		args.push_back(coins);
		args.push_back(cost);
		text = text%args;
		if (playButtonCostLabel != nullptr)
			playButtonCostLabel->set_text(text);
		if (coins < cost)
		{
			playButton->set_disabled(true);
		}
		else
		{
			playButton->set_disabled(false);
		}
	}
}

Ref<Texture2D> MainMenuManager::get_playTex() const
{
	return playTex;
}

void MainMenuManager::set_playTex(Ref<Texture2D> tex)
{
	playTex = tex;
}

Ref<Texture2D> MainMenuManager::get_coinTex() const
{
	return coinTex;
}

void MainMenuManager::set_coinTex(Ref<Texture2D> tex)
{
	coinTex = tex;
}

Ref<Texture2D> MainMenuManager::get_earthTex() const
{
	return earthTex;
}

void MainMenuManager::set_earthTex(Ref<Texture2D> tex)
{
	earthTex = tex;
}

Ref<Texture2D> MainMenuManager::get_marsTex() const
{
	return marsTex;
}

void MainMenuManager::set_marsTex(Ref<Texture2D> tex)
{
	marsTex = tex;
}

Ref<Texture2D> MainMenuManager::get_jupiterTex() const
{
	return jupiterTex;
}

void MainMenuManager::set_jupiterTex(Ref<Texture2D> tex)
{
	jupiterTex = tex;
}

Ref<Texture2D> MainMenuManager::get_earthSelectedTex() const
{
	return earthSelectedTex;
}

void MainMenuManager::set_earthSelectedTex(Ref<Texture2D> tex)
{
	earthSelectedTex = tex;
}

Ref<Texture2D> MainMenuManager::get_marsSelectedTex() const
{
	return marsSelectedTex;
}

void MainMenuManager::set_marsSelectedTex(Ref<Texture2D> tex)
{
	marsSelectedTex = tex;
}

Ref<Texture2D> MainMenuManager::get_jupiterSelectedTex() const
{
	return jupiterSelectedTex;
}

void MainMenuManager::set_jupiterSelectedTex(Ref<Texture2D> tex)
{
	jupiterSelectedTex = tex;
}

void MainMenuManager::set_earthScene(Ref<PackedScene> scene)
{
	earthScene = scene;
}

Ref<PackedScene> MainMenuManager::get_earthScene() const
{
	return earthScene;
}

void MainMenuManager::set_marsScene(Ref<PackedScene> scene)
{
	marsScene = scene;
}

Ref<PackedScene> MainMenuManager::get_marsScene() const
{
	return marsScene;
}

void MainMenuManager::set_jupiterScene(Ref<PackedScene> scene)
{
	jupiterScene = scene;
}

Ref<PackedScene> MainMenuManager::get_jupiterScene() const
{
	return jupiterScene;
}
