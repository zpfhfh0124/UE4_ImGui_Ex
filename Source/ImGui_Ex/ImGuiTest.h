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

	ImFont* font;

	// Tick 체크용
	bool IsOnTimeWindow = false;
	bool IsOnImgWindow = false;
	bool IsOnColorPicker = false;
	bool IsOnTextInput = false;
	bool IsOnScrollCheckbox = false;

	// Tick에서 최최 1회만 호출하기 위한 bool
	bool onInitAlwaysWindow = false;
	bool onClickedTimeWindow = false;
	bool onClickedImgWindow = false;
	bool onClickedColorPicker = false;
	bool onClickedTextInput = false;
	bool onClickedScrollCheckbox = false;

	FName rand_texture_name;
	int max_texture_array = 0;
	int curr_texture_idx = 0;

	ImVec4 color_v;

	char text[256 * 8];
public:	
	virtual void Tick(float DeltaTime) override;
	void SetTitle(FString title);
	
#if WITH_IMGUI
	void ImGuiClear();
	void ImGuiAlwaysShow();
	void ImGui_Show_NowTime();
	void ImGui_Show_Image();
	void ImGui_Show_Color_Picker();
	void ImGui_Show_TextInput();
	void ImGui_Show_ScrollCheckbox();
#endif

private:
	void wDayToString(int wDay);
	void SetRandomTextureName(int max);

#if WITH_IMGUI // Tick에서 호출
	void onTick_ImGui_CulcurateNowTime();
	void onTick_ImGui_ViewImage();
	void onTick_ImGui_ColorPicker();
	void onTick_ImGui_TextInput();
	void onTick_ImGui_ScrollCheckbox();
#endif
};
