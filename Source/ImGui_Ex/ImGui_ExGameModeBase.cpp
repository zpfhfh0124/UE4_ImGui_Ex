// Copyright Epic Games, Inc. All Rights Reserved.


#include "ImGui_ExGameModeBase.h"
//#include "Blueprint/UserWidget.h"

AImGui_ExGameModeBase::AImGui_ExGameModeBase() 
{
	static ConstructorHelpers::FClassFinder<UUIWidgetMain> 
		MainWidgetAsset(TEXT("WidgetBlueprint'/Game/UI/BP_Widget_Main.BP_Widget_Main_C'"));
	if (MainWidgetAsset.Succeeded()) MainWidgetClass = MainWidgetAsset.Class;
}

void AImGui_ExGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// ∏ﬁ¿Œ ¿ß¡¨ UI ºº∆√
	if (IsValid(MainWidgetClass)) 
	{
		MainWidget = Cast<UUIWidgetMain>(CreateWidget(GetWorld(), MainWidgetClass));
		if (IsValid(MainWidget)) {
			// ¿ß¡¨¿ª ∫‰∆˜∆Æø° ∂ÁøÓ¥Ÿ
			MainWidget->AddToViewport();
		}
	}
}