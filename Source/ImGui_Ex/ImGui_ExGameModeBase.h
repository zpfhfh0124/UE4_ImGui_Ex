// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ImGui_ExGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class IMGUI_EX_API AImGui_ExGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AImGui_ExGameModeBase();

protected:
	virtual void BeginPlay() override;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	//TSubclassOf<UUserWidget> HUDWidget;
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	//UUserWidget* CurrentWidget;
};
