#include "PiontLight.h"
#include "imgui\imgui.h"

PiontLight::PiontLight(Graphics& ghs, float raduis)
	: mesh(ghs), cuf(ghs, 0), cbuf()
{

}

void PiontLight::lightEditor()
{
	if (ImGui::Begin("light"))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("x", &cbuf.pos.x, -100, 100);
		ImGui::SliderFloat("y", &cbuf.pos.y, -100, 100);
		ImGui::SliderFloat("z", &cbuf.pos.z, -100, 100);
		
		ImGui::Text("DwonOff");
		ImGui::ColorEdit3("Intensy", &cbuf.indensy.x);
		ImGui::SliderFloat3("attr", &cbuf.consAttr, 0, 1);
		if (ImGui::Button("Reset"))
		{
			reset();
		}
	}

	ImGui::End();
}

void PiontLight::DrawCall(Graphics& ghs)
{
	mesh.setPos(cbuf.pos);
	mesh.drawCall(ghs);
}

void PiontLight::Bind(Graphics& ghs)
{
	cuf.update(ghs, cbuf);
	cuf.bind(ghs);
}

void PiontLight::reset()
{
	cbuf = LightPos();
}
