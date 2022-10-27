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

	// 텍스쳐 세팅은 블루프린트 액터에서...
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTexture2D*> TextureArray;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	FString Title;
	FString eWDay_to_string;

	// Tick 체크용
	bool IsOnTimeWindow = false;
	bool IsOnImgWindow = false;

	// Tick에서 최최 1회만 호출하기 위한 bool
	bool onInitAlwaysWindow = false;
	bool onClickedTimeWindow = false;
	bool onClickedImgWindow = false;

	FName rand_texture_name;
	int max_texture_array = 0;
	int curr_texture_idx = 0;
public:	
	virtual void Tick(float DeltaTime) override;
	void SetTitle(FString title);
	
#if WITH_IMGUI
	void ImGuiClear();
	void ImGuiAlwaysShow();
	void ImGui_Show_NowTime();
	void ImGui_Show_Image();
#endif

private:
	void wDayToString(int wDay);
	void SetRandomTextureName(int max);

#if WITH_IMGUI // Tick에서 호출
	void culcurateNowTime();
	void viewImage();
#endif
};
