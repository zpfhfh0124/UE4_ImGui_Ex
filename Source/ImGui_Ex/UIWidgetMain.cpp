// Fill out your copyright notice in the Description page of Project Settings.


#include "UIWidgetMain.h"

//UUIWidgetMain::UUIWidgetMain(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
//{
//	
//}

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

// ��ư Ŭ�� -> ImGui �����츦 ���� �� ȣ���ؾ� ��.
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
