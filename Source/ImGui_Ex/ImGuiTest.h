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

	UPROPERTY(EditAnywhere)
	UTexture2D* Texture;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsOnTimeWindow = false;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	char* Title;

public:	
	virtual void Tick(float DeltaTime) override;

#if WITH_IMGUI
	FString wDayToString(int wDay);
	void ImGuiTest();

	void ImGui_ShowNowTime();
	void ImGui_ShowImage();
#endif

};
