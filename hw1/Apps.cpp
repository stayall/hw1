#include <iomanip>
#include <sstream>
#include <algorithm>
#include "Apps.h"
#include "Mesh.h"

#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui.h"



Apps::Apps() :wnd(1270, 800, L"s"), timer(), pl(wnd.GHS()), model(wnd.GHS(), "model//nano_hierarchy.gltf")
{
	
	
	wnd.GHS().setProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));

	
	
}

int Apps::Go()
{



	while (true)
	{
	
		if (const auto r = Window::ProcessMessge())
		{
			return *r;
		}

		doFream();
	}

}

void Apps::doFream()
{
	
	const float c = sin(timer.peek()/1000000000) / 2.0f + 0.5f;
	const float a = timer.mark() * speed;

	wnd.GHS().setCamera(camera.getMatrix());

	
	
	wnd.GHS().beginFream(0.07f, 0.0, 0.12f);
	model.Draw(wnd.GHS(), DirectX::XMMatrixIdentity());
	model.ShowModelWindow();
	pl.Bind(wnd.GHS());



	//boxes.front()->spawnBoxCountroller(1, wnd.GHS());
	pl.lightEditor();
	camera.cameraWindowController();
	pl.DrawCall(wnd.GHS());
	
	

	wnd.GHS().swapBuffer();
}



void Apps::boxController(Graphics& ghs)
{
	for (size_t i = 0; i < boxes.size(); i++)
	{
		if (boxIndexs.find(i) != boxIndexs.end())
		{
			if (!boxes[i]->spawnBoxCountroller(i, ghs))
			{
				boxIndexs.erase(i);
			}
		}
	}
	if (ImGui::Begin("Box"))
	{
		std::string preview = comboIndex ? std::to_string(*comboIndex) : "Choose a Box";

		if (ImGui::BeginCombo("Box Index", preview.c_str()))
		{
			for (size_t i = 0; i < boxes.size(); i++)
			{
				bool selected = comboIndex ? *comboIndex == i : false ;
				if (ImGui::Selectable(std::to_string(i).c_str()))
				{
					comboIndex = i;
				}
				if (selected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		if (ImGui::Button("Look") && comboIndex)
		{
			boxIndexs.insert(*comboIndex);
		}
	}
	ImGui::End();
}
