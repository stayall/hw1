#include <iomanip>
#include <sstream>
#include <algorithm>
#include "Apps.h"


#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui.h"

void f()
{
	Proc::VertexLayout layout;

	layout.append(Proc::VertexLayout::ElementType::VertexPosition3D);
	layout.append(Proc::VertexLayout::ElementType::Teture2D);
	Proc::VertexBuferr vb(std::move(layout));

	vb.emplaceBack(DirectX::XMFLOAT3{ 1, 1, 1 }, DirectX::XMFLOAT2{0, 1});
	vb.emplaceBack(DirectX::XMFLOAT3{ 1, 1, 1 }, DirectX::XMFLOAT2{0, 1});
	auto pos = vb[0].attr<Proc::VertexLayout::ElementType::VertexPosition3D>();
	auto pos1 = vb[1].attr<Proc::VertexLayout::ElementType::VertexPosition3D>();
}

Apps::Apps() :wnd(800, 600, L"s"), timer(), pl(wnd.GHS()), comboIndex{}
{
	f();

	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 1.0f);
	std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.08f);
	std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
	std::uniform_real_distribution<float> cdist(0.0f, 1.0f);

	for (auto i = 0; i < 80; i++)
	{
		drawables.push_back(std::make_unique<Box>(
			wnd.GHS(), rng, adist, ddist, odist, rdist, cdist
			));
	}

	for (auto& b : drawables)
	{
		if (Box* p = dynamic_cast<Box*>(b.get()))
		{
			boxes.emplace_back(p);
		}
	}

	wnd.GHS().setProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));

	//pl = std::make_unique<PiontLight>(wnd.GHS());
	
	
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

	if (wnd.kbd.IsPressureKey(VK_SPACE))
	{
		wnd.GHS().disableImGui();
	}
	else
	{
		wnd.GHS().enableImGui();
	}

	wnd.GHS().beginFream(0.07f, 0.0, 0.12f);

	pl.Bind(wnd.GHS());

	for (auto& b : drawables)
	{
		b->update(a);
		b->drawCall(wnd.GHS());
	}

	boxes.front()->spawnBoxCountroller(1, wnd.GHS());
	pl.lightEditor();
	camera.cameraWindowController();
	pl.DrawCall(wnd.GHS());
	
	boxController(wnd.GHS());





	if (wnd.GHS().isShowImGui())
	{
		char buffer[100] = {};
		ImGuiViewport *mainViewPort =  ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(ImVec2(mainViewPort->WorkPos.x, mainViewPort->WorkPos.y), ImGuiCond_FirstUseEver, ImVec2(0, 0));
		ImGui::SetWindowSize(ImVec2(200, 100), ImGuiCond_FirstUseEver);
		if ( ImGui::Begin("Speed"))
		{
			ImGui::SliderFloat("montion speed", &speed, 0.0f, 4.0f);
			ImGui::Text("Application averange %.3f ms/fream (%.1f FPS)", 1000 / ImGui::GetIO().Framerate, 1000 / ImGui::GetIO().Framerate);
			ImGui::InputText(" Input ", buffer, sizeof(buffer));
		}

		ImGui::End();

		
	}

	
	

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
