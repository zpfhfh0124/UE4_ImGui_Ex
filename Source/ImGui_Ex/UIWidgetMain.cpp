// Fill out your copyright notice in the Description page of Project Settings.


#include "UIWidgetMain.h"

//UUIWidgetMain::UUIWidgetMain(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
//{
//	
//}

void UUIWidgetMain::OnClickImGuiToggleInputBtn()
{
	GetGameInstance()->GetFirstLocalPlayerController()->ConsoleCommand(FString("ImGui.ToggleInput"));
}

void UUIWidgetMain::OnClickImGuiToggleDemoBtn()
{
	GetGameInstance()->GetFirstLocalPlayerController()->ConsoleCommand(FString("ImGui.ToggleDemo"));
}

void UUIWidgetMain::OnClickTimeWindowBtn()
{
	SetImGuiTestActor();
	if (ImGuiTest == nullptr) return;
	ImGuiTest->ImGui_Show_NowTime();
}

void UUIWidgetMain::OnClickImgWindowBtn()
{
	SetImGuiTestActor();
	if (ImGuiTest == nullptr) return;
	ImGuiTest->ImGui_Show_Image();
}

void UUIWidgetMain::OnClickColorDrawBtn()
{
	SetImGuiTestActor();
	if (ImGuiTest == nullptr) return;
	ImGuiTest->ImGui_Show_Color_Picker();
}

// 버튼 클릭 -> ImGui 윈도우를 띄우기 전 호출해야 함.
void UUIWidgetMain::SetImGuiTestActor()
{
	if (ImGuiTest == nullptr)
	{
		for (auto* currActor : TActorRange<AImGuiTest>(GetWorld()))
		{
			ImGuiTest = currActor;
		}
	}
}
