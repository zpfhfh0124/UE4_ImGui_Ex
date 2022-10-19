// Fill out your copyright notice in the Description page of Project Settings.

#include <time.h>
#include "ImGuiTest.h"

AImGuiTest::AImGuiTest()
{
 	PrimaryActorTick.bCanEverTick = true;
	Title = "ImGui Test";
}

void AImGuiTest::BeginPlay()
{
	Super::BeginPlay();

#if WITH_IMGUI
	// ImGui의 World Delegate에 처리를 등록 
	FImGuiDelegates::OnWorldDebug().AddUObject(this, &AImGuiTest::ImGuiTest);
	//FImGuiModule::Get().RegisterTexture("")
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
	ImGui::Begin(Title);
	/*ImGui::Text("Actor Tick: Actor = '%ls', World = '%ls', CurrentWorld = '%ls'",
		*GetNameSafe(this), *GetNameSafe(GetWorld()), *GetNameSafe(GWorld));*/
	ImGui_ShowNowTime();
	ImGui::End();
#endif // WITH_IMGUI
}

#if WITH_IMGUI
FString AImGuiTest::wDayToString(int wDay)
{
	FString eWDay_to_string = TEXT("Invalid");

	wDay %= 7;
	switch (wDay)
	{
		case 0:
			eWDay_to_string = TEXT("SUN");
		break;
		case 1:
			eWDay_to_string = TEXT("MON");
		break;
		case 2:
			eWDay_to_string = TEXT("TUE");
		break;
		case 3:
			eWDay_to_string = TEXT("WED");
		break;
		case 4:
			eWDay_to_string = TEXT("THU");
		break;
		case 5:
			eWDay_to_string = TEXT("FRY");
		break;
		case 6:
			eWDay_to_string = TEXT("SAT");
		break;
	}

	return eWDay_to_string;
}

void AImGuiTest::ImGuiTest()
{
	ImGui::Begin("ImGui Debug Order Test");
	ImGui::Text("ImGui World Tick: Actor = '%ls', World = '%ls', CurrentWorld = '%ls'",
		*GetNameSafe(this), *GetNameSafe(GetWorld()), *GetNameSafe(GWorld));
	ImGui::End();
}

void AImGuiTest::ImGui_ShowNowTime()
{
	time_t curTime = time(NULL);
	struct tm* pLocalTime = localtime(&curTime);

	ImGui::Text("Today : %04d - %02d - %02d (%s)", 1900 + pLocalTime->tm_year, pLocalTime->tm_mon, pLocalTime->tm_mday, FText::FromString(*wDayToString(pLocalTime->tm_wday)) );
	ImGui::Text("Now Time : %02d : %02d : %02d", pLocalTime->tm_hour, pLocalTime->tm_min, pLocalTime->tm_sec);
}

void AImGuiTest::ImGui_ShowImage()
{

}
#endif

