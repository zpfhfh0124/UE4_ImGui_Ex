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
	for (int idx = 0; idx != TextureArray.Num(); ++idx) 
	{

		FString str = FString::Printf(TEXT("pricone_%d"), idx);
		FName name = FName(*str);
		FImGuiModule::Get().RegisterTexture(name, TextureArray[idx]);
		
	}

	max_texture_array = TextureArray.Num();

	// ImGui의 World Delegate에 처리를 등록 
	FImGuiDelegates::OnWorldDebug().AddUObject(this, &AImGuiTest::ImGuiTest);
#endif // WITH_IMGUI
	
}

void AImGuiTest::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

#if WITH_IMGUI
	// 텍스쳐 해제
	for (int idx = 0; idx != TextureArray.Num(); ++idx)
	{
		FString str = FString::Printf(TEXT("pricone_%d"), idx);
		FName name = FName(*str);
		FImGuiTextureHandle TextureHandle = FImGuiModule::Get().FindTextureHandle(name);
		FImGuiModule::Get().ReleaseTexture(TextureHandle);
	}

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
	
	if (IsOnImgWindow) {
		viewImage();
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
	IsOnImgWindow = false;
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
	SetTitle(FString("View Image"));
	rand_texture_name = GetRandomTextureName(max_texture_array);
	IsOnImgWindow = true;
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

FName AImGuiTest::GetRandomTextureName(int max)
{
	// 텍스쳐 배열에서 랜덤으로 한장 꺼낸다
	// ** 현재 rs가 Null인 이슈 -> FRandomStream 인스턴스를 할당하고 메모리 관리 필요...
	FRandomStream rs;
	int rand_idx = rs.RandRange(0, max - 1);
	FString str = FString::Printf(TEXT("pricone_%d"), rand_idx);
	rand_texture_name = FName(*str);

	return rand_texture_name;
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

void AImGuiTest::viewImage()
{
	ImGui::Begin(TCHAR_TO_ANSI(*Title));
	
	FImGuiTextureHandle TextureHandle = FImGuiModule::Get().FindTextureHandle(rand_texture_name);
	ImGui::Image(TextureHandle, ImVec2(800, 300));

	ImGui::End();
}
