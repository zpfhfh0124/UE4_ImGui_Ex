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
	FString Title;
	FString eWDay_to_string;

public:	
	virtual void Tick(float DeltaTime) override;
	void SetTitle(FString title);
	
#if WITH_IMGUI
	void ImGuiClear();
	void ImGuiTest();
	void ImGui_Show_NowTime();
	void ImGui_Show_Image();
#endif

private:
	void wDayToString(int wDay);
#if WITH_IMGUI
	void culcurateNowTime();
#endif
};
