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
	ImGuiTest->IsOnTimeWindow = true;
}

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
