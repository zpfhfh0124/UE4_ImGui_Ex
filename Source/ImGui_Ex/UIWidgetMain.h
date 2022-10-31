// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Runtime/Engine/Public/EngineUtils.h>
#include <ImGui_Ex/ImGuiTest.h>
#include "UIWidgetMain.generated.h"

/**
 * 
 */
UCLASS()
class IMGUI_EX_API UUIWidgetMain : public UUserWidget
{
	GENERATED_BODY()

public:
	//UUIWidgetMain(const FObjectInitializer &ObjectInitializer);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AImGuiTest* ImGuiTest;

public:
	UFUNCTION(BlueprintCallable)
	void OnClickImGuiToggleInputBtn();
	UFUNCTION(BlueprintCallable)
	void OnClickImGuiToggleDemoBtn();

	UFUNCTION(BlueprintCallable)
	void OnClickTimeWindowBtn();
	UFUNCTION(BlueprintCallable)
	void OnClickImgWindowBtn();
	UFUNCTION(BlueprintCallable)
	void OnClickColorDrawBtn();
	UFUNCTION(BlueprintCallable)
	void OnClickTextInputBtn();
	UFUNCTION(BlueprintCallable)
	void OnClickScrollCheckBoxBtn();

private:
	void SetImGuiTestActor();
};
