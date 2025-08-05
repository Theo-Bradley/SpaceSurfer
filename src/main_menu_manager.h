#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/button.hpp"
#include "godot_cpp/classes/texture_button.hpp"
#include "godot_cpp/classes/label.hpp"
#include "godot_cpp/classes/container.hpp"
#include "godot_cpp/classes/resource_loader.hpp"
#include "godot_cpp/classes/resource_saver.hpp"
#include "godot_cpp/classes/json.hpp"
#include "godot_cpp/classes/texture2d.hpp"
#include "godot_cpp/classes/texture_rect.hpp"
#include "godot_cpp/classes/packed_scene.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include "utils.h"

using namespace godot;

class MainMenuManager : public Node {
	GDCLASS(MainMenuManager, Node)

protected:
	static void _bind_methods();

public:
	MainMenuManager() = default;
	~MainMenuManager() override;

	void _ready();
	bool initalized = false;

	//PLANET UNLOCK COSTS
	const int earthCost = 0;
	const int marsCost = 1500;
	const int jupiterCost = 15000;

	TextureButton* earthButton = nullptr;
	TextureButton* marsButton = nullptr;
	TextureButton* jupiterButton = nullptr;
	Label* highscoreLabel = nullptr;
	Button* playButton = nullptr;

	Container* buttonContainer = nullptr; //Horizontal button container
	TextureRect* playButtonIcon = nullptr;
	Label* playButtonCostLabel = nullptr; //label displaying map cost "current coins/cost"

	enum class Maps;
	Maps selectedMap;
	unsigned char mapFlag = 0;
	int coins = 0;
	void ProcessMapFlag(unsigned char mapFlag);
	bool earthUnlocked = false;
	bool marsUnlocked = false;
	bool jupiterUnlocked = false;
	bool shouldLoadMap = false; //should the play button load the map or unlock it
	int unlockCost = 0;
	void SetCostLabel(int cost = 0);

	void PressedPlay();
	void PressedEarth();
	void PressedMars();
	void PressedJupiter();

	void set_buttonContainer(Container* container);
	Container* get_buttonContainer() const;
	void set_playButton(Button* button);
	Button* get_playButton() const;
	void set_highscoreLabel(Label* label);
	Label* get_highscoreLabel() const;

	Ref<Texture2D> playTex = nullptr;
	Ref<Texture2D> coinTex = nullptr;

	void set_playTex(Ref<Texture2D> tex);
	Ref<Texture2D> get_playTex() const;
	void set_coinTex(Ref<Texture2D> tex);
	Ref<Texture2D> get_coinTex() const;

	Ref<Texture2D> earthTex = nullptr;
	Ref<Texture2D> marsTex = nullptr;
	Ref<Texture2D> jupiterTex = nullptr;
	Ref<Texture2D> earthSelectedTex = nullptr;
	Ref<Texture2D> marsSelectedTex = nullptr;
	Ref<Texture2D> jupiterSelectedTex = nullptr;

	void set_earthTex(Ref<Texture2D> tex);
	Ref<Texture2D> get_earthTex() const;
	void set_marsTex(Ref<Texture2D> tex);
	Ref<Texture2D> get_marsTex() const;
	void set_jupiterTex(Ref<Texture2D> tex);
	Ref<Texture2D> get_jupiterTex() const;
	void set_earthSelectedTex(Ref<Texture2D> tex);
	Ref<Texture2D> get_earthSelectedTex() const;
	void set_marsSelectedTex(Ref<Texture2D> tex);
	Ref<Texture2D> get_marsSelectedTex() const;
	void set_jupiterSelectedTex(Ref<Texture2D> tex);
	Ref<Texture2D> get_jupiterSelectedTex()const;

	Ref<PackedScene> earthScene = nullptr;
	Ref<PackedScene> marsScene = nullptr;
	Ref<PackedScene> jupiterScene = nullptr;

	void set_earthScene(Ref<PackedScene> scene);
	Ref<PackedScene> get_earthScene() const;
	void set_marsScene(Ref<PackedScene> scene);
	Ref<PackedScene> get_marsScene() const;
	void set_jupiterScene(Ref<PackedScene> scene);
	Ref<PackedScene> get_jupiterScene() const;
};
