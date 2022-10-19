// Copyright Epic Games, Inc. All Rights Reserved.


#include "ImGui_ExGameModeBase.h"
//#include "Blueprint/UserWidget.h"

AImGui_ExGameModeBase::AImGui_ExGameModeBase() 
{

}

void AImGui_ExGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidget);
	//CurrentWidget->AddToViewport();
}