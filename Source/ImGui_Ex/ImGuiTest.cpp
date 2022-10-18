// Fill out your copyright notice in the Description page of Project Settings.

#include "ImGuiTest.h"

AImGuiTest::AImGuiTest()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void AImGuiTest::BeginPlay()
{
	Super::BeginPlay();

#if WITH_IMGUI
	// ImGui의 World Delegate에 처리를 등록 
	FImGuiDelegates::OnWorldDebug().AddUObject(this, &AImGuiTest::ImGuiTick);
#endif // WITH_IMGUI
	
}

void AImGuiTest::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

#if WITH_IMGUI
	// ImGui의World Delegate에 등록했던 처리를 해제
	FImGuiDelegates::OnWorldDebug().RemoveAll(this);
#endif // WITH_IMGUI
}

// Called every frame
void AImGuiTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#if WITH_IMGUI
	ImGui::Begin("ImGui Debug Order Test");
	ImGui::Text("Actor Tick: Actor = '%ls', World = '%ls', CurrentWorld = '%ls'",
		*GetNameSafe(this), *GetNameSafe(GetWorld()), *GetNameSafe(GWorld));
	ImGui::End();
#endif // WITH_IMGUI
}

#if WITH_IMGUI
void AImGuiTest::ImGuiTick()
{
	ImGui::Begin("ImGui Debug Order Test");
	ImGui::Text("ImGui World Tick: Actor = '%ls', World = '%ls', CurrentWorld = '%ls'",
		*GetNameSafe(this), *GetNameSafe(GetWorld()), *GetNameSafe(GWorld));
	ImGui::End();
}
#endif

