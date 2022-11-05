#ifndef __APPS__H__
#define __APPS__H__
#include "Window.h"
#include "Timer.h"
#include "Box.h"
#include "line.h"
#include "ImGuiManager.h"
#include <memory>
#include <set>
#include <optional>
#include "Camera.h"
#include "PiontLight.h"
#include "Vertex.h"
#include "Mesh.h"


class Apps
{
public:
	Apps();
	int Go();

private:
	void doFream();

	void boxController(Graphics &ghs);

private:
	ImGuiManager ig;
	Window wnd;
	Timer timer;
	std::vector<std::unique_ptr<Drawable>> drawables;
	Camera camera;
	bool show_demo_window = true;
	float speed = 1.0f;
	PiontLight pl;
	std::vector<Box*> boxes;

	std::optional<int> comboIndex ;
	std::set<int> boxIndexs;

	Model model;
	struct 
	{
		float raw = 0.0f;
		float pitch = 0.0f;
		float yaw = 0.0f;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
	};
};

#endif // !__APPS__H__


