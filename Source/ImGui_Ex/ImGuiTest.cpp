// Fill out your copyright notice in the Description page of Project Settings.

#include <time.h>
#include "ImGuiTest.h"

AImGuiTest::AImGuiTest()
{
 	PrimaryActorTick.bCanEverTick = true;
	SetTitle( FString("ImGui Test") );
}

void AImGuiTest::BeginPlay()
{
	Super::BeginPlay();

#if WITH_IMGUI
	// 한글 출력
	auto& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\malgun.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesKorean());
	
	// 텍스쳐 등록
	//FImGuiModule::Get().RegisterTexture("")

	// ImGui의 World Delegate에 처리를 등록 
	FImGuiDelegates::OnWorldDebug().AddUObject(this, &AImGuiTest::ImGuiTest);
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
	//ImGui::Begin( TCHAR_TO_ANSI( *Title ) );
	if (IsOnTimeWindow) {
		culcurateNowTime();
	}
	//ImGui::End();
#endif // WITH_IMGUI
}

void AImGuiTest::SetTitle(FString title)
{
	Title = title;
}

#if WITH_IMGUI
void AImGuiTest::ImGuiClear()
{
	IsOnTimeWindow = false;
	ImGui::End();
}

void AImGuiTest::ImGuiTest()
{
	ImGui::Begin("ImGui Debug Order Test");
	ImGui::Text("ImGui World Tick: Actor = '%ls', World = '%ls', CurrentWorld = '%ls'",
		*GetNameSafe(this), *GetNameSafe(GetWorld()), *GetNameSafe(GWorld));
	ImGui::End();
}

void AImGuiTest::ImGui_Show_NowTime()
{
	SetTitle( FString( "Current Time" ) );
	IsOnTimeWindow = true;
}

void AImGuiTest::ImGui_Show_Image()
{
	SetTitle(FString("Image View"));
	ImGui::Begin(TCHAR_TO_ANSI(*Title));
}
#endif

void AImGuiTest::wDayToString(int wDay)
{
	eWDay_to_string = TEXT("Invalid");

	wDay %= 7;

	switch (wDay)
	{
	case 0:
		eWDay_to_string = FString("SUN");
		break;
	case 1:
		eWDay_to_string = FString("MON");
		break;
	case 2:
		eWDay_to_string = FString("TUE");
		break;
	case 3:
		eWDay_to_string = FString("WED");
		break;
	case 4:
		eWDay_to_string = FString("THU");
		break;
	case 5:
		eWDay_to_string = FString("FRI");
		break;
	case 6:
		eWDay_to_string = FString("SAT");
		break;
	}
}

void AImGuiTest::culcurateNowTime()
{
	ImGui::Begin(TCHAR_TO_ANSI(*Title));
	//ImGui::SetWindowPos( ImVec2(800, 300) );
	time_t curTime = time(NULL);
	struct tm* pLocalTime = localtime(&curTime);
	wDayToString(pLocalTime->tm_wday);
	ImGui::Text("Today : %04dY %02dM %02dD (%s)", 1900 + pLocalTime->tm_year, pLocalTime->tm_mon + 1, pLocalTime->tm_mday, *eWDay_to_string);
	ImGui::Text("Now Time { %02d:%02d:%02d }", pLocalTime->tm_hour, pLocalTime->tm_min, pLocalTime->tm_sec);
	ImGui::End();
}
