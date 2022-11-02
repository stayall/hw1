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
};

#endif // !__APPS__H__


