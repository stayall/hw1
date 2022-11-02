#include "Camera.h"
#include "imgui/imgui.h"
#include "Math.h"
Camera::Camera()
{
    r = 20;
    theata = 0;
    phi = 0;

    pitch = 0;
    yaw = 0;
    roll = 0;
}

DirectX::FXMMATRIX Camera::getMatrix() const
{
    const auto pos = DirectX::XMVectorSet(0.0f, 0.0f, -r, 0.0f);
    const auto newPos =  DirectX::XMVector3Transform(pos, DirectX::XMMatrixRotationRollPitchYaw(toRed(phi), toRed(-theata), 0.0f));

    return DirectX::XMMatrixLookAtLH(newPos, DirectX::XMVectorZero(),
        { 0.0f, 1.0f, 0.0f, 0.0f }) * DirectX::XMMatrixRotationRollPitchYaw(toRed(pitch), toRed(-yaw), toRed(roll));
}

void Camera::reset() noexcept
{
    r = 20;
    theata = 0;
    phi = 0;
    
    pitch = 0;
    yaw = 0;
    roll = 0;
}


#define XX(R); \
void Camera::set##R(float news##R) noexcept \
{\
    R = news##R;\
}

    XX(r);
    XX(theata);
    XX(phi);
    XX(pitch);
    XX(yaw);
    XX(roll);
#undef XX

    void Camera::cameraWindowController()
    {
        ImGuiViewport* vp = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(ImVec2(vp->WorkPos.x + 20, vp->WorkPos.y + 200), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(200, 300), ImGuiCond_FirstUseEver);
        if (ImGui::Begin("CameraController"))
        {
            ImGui::Text("Position");
            ImGui::SliderFloat("R ", &r,1.f, 80.0f);
            ImGui::SliderFloat("Theata ", &theata, -180.0f, 180.0f);
            ImGui::SliderFloat("Phi ", &phi, -180.0f, 180.0f);
            ImGui::InputFloat("11", &phi);
            ImGui::Text("Orientation");
            ImGui::SliderFloat("Pitch ", &pitch, -180.0f, 180.0f);
            ImGui::SliderFloat("Yaw ", &yaw, -180.0f, 180.0f);
            ImGui::SliderFloat("Roll ", &roll, -180.0f, 180.0f);
            //yaw = phi;
            if (ImGui::Button("Reset"))
            {
                reset();
            }
        }

        ImGui::End();
    }
