// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ImGuiCommon.h"
#include "ImGuiTest.generated.h"

UCLASS()
class IMGUI_EX_API AImGuiTest : public AActor
{
	GENERATED_BODY()
	
public:	
	AImGuiTest();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	virtual void Tick(float DeltaTime) override;

#if WITH_IMGUI
	void ImGuiTick();
#endif

};
