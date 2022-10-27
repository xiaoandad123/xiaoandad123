#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "ui_head.h"

#include "main.h"
#include "mspkeyapi.h"
#include "ui_head.h"
#include <imgui.h>
#include "XorString.h"

#define dwFlag ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse
#define dwFlag2 ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse
#define dwTabFlag ImGuiTabItemFlags_NoCloseWithMiddleMouseButton

typedef void (*MyImGuiButtonCallBack)(void);

// 自定义输入框
void inline MyImGuiConstomTextBox(char* boxname, char* buf)
{
    ImGui::InputText(boxname, buf, IM_ARRAYSIZE(buf));
}

// ImGui用户名输入框
void inline MyImGuiUserTextBox(char* username)
{
    ImGui::InputText(XorStrV1(u8"用户名"), username, IM_ARRAYSIZE(username));
}

// ImGui密码输入框
void inline MyImGuiPasswordTextBox(char* password)
{
    ImGui::InputTextWithHint(XorStrV1(u8"密码"), "<password>", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);

}

// ImGui回调按钮
void inline MyImGuiCallBackButton(const char* label, MyImGuiButtonCallBack func)
{
    if (ImGui::Button(label))
        func();
}

// 我的ImGui登录器界面
void ShowLauncher(bool* showlogin, int Width, int Height, LPVOID lpParam)
{
    GlobalParam* g_ParamStruct_p = (GlobalParam*)lpParam;
    ImGui::Begin(XorStrV1(u8"-Kota登录器-"), showlogin, dwFlag);
    ImGui::SetWindowSize(ImVec2(Width, Height), ImGuiCond_Once);
    ImGui::SetWindowPos(ImVec2(0, 0));
    ImGui::AlignTextToFramePadding();


    //公告板===============================================================================================//
    ImGui::BeginChild(XorStrV1(u8"##公告##"), ImVec2(Width, 80));
    ImGui::Text(XorStrV1(u8"NULL"));
    ImGui::EndChild();
    //公告板===============================================================================================//


    //主标签栏=============================================================================================//
    if (ImGui::BeginTabBar(XorStrV1(u8"##MainTabBar"), ImGuiTabBarFlags_AutoSelectNewTabs)) //=主标签栏Begin=//
    {
        //登录标签=========================================================================================//
        if (ImGui::BeginTabItem(XorStrV1(u8"登录"), 0, dwTabFlag))
        {
            MyImGuiUserTextBox(g_ParamStruct_p->inputBuffer->logoin_username);
            MyImGuiPasswordTextBox(g_ParamStruct_p->inputBuffer->logoin_password);
            if (ImGui::Button(XorStrV1(u8" 登陆 ")))
            {
                if (g_ParamStruct_p->uiStatus.islogin)
                {
                    *showlogin = false;
                    
                    ZeroMemory(g_ParamStruct_p->inputBuffer->logoin_username, 260);
                    ZeroMemory(g_ParamStruct_p->inputBuffer->logoin_password, 260);
                }
                ((mspkeyapi*)g_ParamStruct_p->mspkeyapi_p)->Login(
                    g_ParamStruct_p->inputBuffer->logoin_username, 
                    g_ParamStruct_p->inputBuffer->logoin_password);
            }
            ImGui::Text(XorStrV1(""));
            ImGui::Text(XorStrV1(""));
            ImGui::Text(XorStrV1("")); 
            ImGui::Text(((mspkeyapi*)g_ParamStruct_p->mspkeyapi_p)->ParseErrMsg().c_str());
            ImGui::EndTabItem();
        }
        //登录标签==========================================================================================//


        //注册标签==========================================================================================//
        if (ImGui::BeginTabItem(XorStrV1(u8"注册"), 0, dwTabFlag))
        {
            MyImGuiUserTextBox(g_ParamStruct_p->inputBuffer->reg_username);
            MyImGuiPasswordTextBox(g_ParamStruct_p->inputBuffer->reg_password);
            ImGui::InputText(XorStrV1(u8"验证码"), g_ParamStruct_p->inputBuffer->vif_code_inpu, sizeof(g_ParamStruct_p->inputBuffer->vif_code_inpu));
            if (ImGui::Button(XorStrV1(u8"获取验证码")))
            {
                ((mspkeyapi*)g_ParamStruct_p->mspkeyapi_p)->GetCode();
            }
            ImGui::SameLine();
            ImGui::Text((((mspkeyapi*)g_ParamStruct_p->mspkeyapi_p)->ParseCheckCode()).c_str());
            if (ImGui::Button(XorStrV1(u8" 注册 ")))
            {
                
                ZeroMemory(g_ParamStruct_p->inputBuffer->reg_username, 260);
                ZeroMemory(g_ParamStruct_p->inputBuffer->reg_password, 260);
                ZeroMemory(g_ParamStruct_p->inputBuffer->vif_code_inpu, 8);
                ((mspkeyapi*)g_ParamStruct_p->mspkeyapi_p)->Register(
                    g_ParamStruct_p->inputBuffer->reg_username,
                    g_ParamStruct_p->inputBuffer->reg_password,
                    g_ParamStruct_p->inputBuffer->vif_code_inpu);
            }
            ImGui::Text(((mspkeyapi*)g_ParamStruct_p->mspkeyapi_p)->ParseErrMsg().c_str());
            ImGui::EndTabItem();
        }
        //注册标签==========================================================================================//


        //充值标签=========================================================================================//
        if (ImGui::BeginTabItem(XorStrV1(u8"充值"), 0, dwTabFlag))
        {
            MyImGuiUserTextBox(g_ParamStruct_p->inputBuffer->pay_newcar_user);
            MyImGuiConstomTextBox(XorStrV1(u8"卡  密:"), g_ParamStruct_p->inputBuffer->new_card_serial);
            if (ImGui::Button(XorStrV1(u8" 充值 ")))
            {
                
                ZeroMemory(g_ParamStruct_p->inputBuffer->pay_newcar_user, 260);
                ZeroMemory(g_ParamStruct_p->inputBuffer->new_card_serial, 260);
                ((mspkeyapi*)g_ParamStruct_p->mspkeyapi_p)->UserPay(
                    g_ParamStruct_p->inputBuffer->pay_newcar_user,
                    g_ParamStruct_p->inputBuffer->new_card_serial);
            }
            ImGui::Text(XorStrV1(""));
            ImGui::Text(XorStrV1("")); 
            ImGui::Text(XorStrV1("")); 
            ImGui::Text(((mspkeyapi*)g_ParamStruct_p->mspkeyapi_p)->ParseErrMsg().c_str());
            ImGui::EndTabItem();
        }
        //充值标签==========================================================================================//


        //机器改绑标签======================================================================================//
        if (ImGui::BeginTabItem(XorStrV1(u8"换绑"), 0, dwTabFlag))
        {
            MyImGuiUserTextBox(g_ParamStruct_p->inputBuffer->rebind_hwid_user);
            MyImGuiPasswordTextBox(g_ParamStruct_p->inputBuffer->rebind_hwid_pswd);
            if (ImGui::Button(XorStrV1(u8" 换绑 ")))
            {
                
                ZeroMemory(g_ParamStruct_p->inputBuffer->rebind_hwid_user, 260);
                ZeroMemory(g_ParamStruct_p->inputBuffer->rebind_hwid_pswd, 260);
                ((mspkeyapi*)g_ParamStruct_p->mspkeyapi_p)->BindDeviceID(
                    g_ParamStruct_p->inputBuffer->rebind_hwid_user,
                    g_ParamStruct_p->inputBuffer->rebind_hwid_pswd);
            }
            ImGui::Text(XorStrV1(""));
            ImGui::Text(XorStrV1("")); 
            ImGui::Text(XorStrV1("")); 
            ImGui::Text(((mspkeyapi*)g_ParamStruct_p->mspkeyapi_p)->ParseErrMsg().c_str());
            ImGui::EndTabItem();
        }
        //机器改绑标签======================================================================================//


        //修改密码标签======================================================================================//
        if (ImGui::BeginTabItem(XorStrV1(u8"修改密码"), 0, dwTabFlag))
        {
            MyImGuiUserTextBox(g_ParamStruct_p->inputBuffer->reset_pswd_user);
            MyImGuiPasswordTextBox(g_ParamStruct_p->inputBuffer->reset_pswd_oldpswd), XorStrV1(u8"旧密码:");
            MyImGuiPasswordTextBox(g_ParamStruct_p->inputBuffer->reset_pswd_newpswd), XorStrV1(u8"新密码:");
            if (ImGui::Button(XorStrV1(u8" 修改 ")))
            {
                
                ZeroMemory(g_ParamStruct_p->inputBuffer->reset_pswd_user, 260);
                ZeroMemory(g_ParamStruct_p->inputBuffer->reset_pswd_newpswd, 260);
                ZeroMemory(g_ParamStruct_p->inputBuffer->reset_pswd_oldpswd, 260);
                ((mspkeyapi*)g_ParamStruct_p->mspkeyapi_p)->UpUserPwd(
                    g_ParamStruct_p->inputBuffer->reset_pswd_user,
                    g_ParamStruct_p->inputBuffer->reset_pswd_oldpswd,
                    g_ParamStruct_p->inputBuffer->reset_pswd_newpswd);
            }
            ImGui::Text(XorStrV1(""));
            ImGui::Text(XorStrV1("")); 
            ImGui::Text(((mspkeyapi*)g_ParamStruct_p->mspkeyapi_p)->ParseErrMsg().c_str());
            ImGui::EndTabItem();
        }
        //修改密码标签======================================================================================//


        //=主标签栏End======================================================================================//
        ImGui::EndTabBar();//=主标签栏End===================================================================//
    }
    //主标签栏==============================================================================================//
    ImGui::End();//=主标签栏==End=//
}
