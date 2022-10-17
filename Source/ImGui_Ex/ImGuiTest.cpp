// Fill out your copyright notice in the Description page of Project Settings.


#include "ImGuiTest.h"

// Sets default values
AImGuiTest::AImGuiTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AImGuiTest::BeginPlay()
{
	Super::BeginPlay();

#if WITH_IMGUI
	// ImGuiのWorld Delegateに処理を登録
	FImGuiDelegates::OnWorldDebug().AddUObject(this, &AImGuiTest::ImGuiTick);
#endif // WITH_IMGUI
	
}

void AImGuiTest::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

#if WITH_IMGUI
	// ImGuiのWorld Delegateに登録した処理を解除
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

