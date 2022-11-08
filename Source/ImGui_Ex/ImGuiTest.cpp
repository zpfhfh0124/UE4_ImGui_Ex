// Fill out your copyright notice in the Description page of Project Settings.

#include "ImGuiTest.h"
#include <time.h>
#include <Math/RandomStream.h>

AImGuiTest::AImGuiTest()
{
 	PrimaryActorTick.bCanEverTick = true;
	SetTitle( FString("ImGui Test") );

	// 색상 값 초기화
	color_v = ImVec4(1.0f, 1.0f, 1.0f, 0.5f);
}

void AImGuiTest::BeginPlay()
{
	Super::BeginPlay();

#if WITH_IMGUI
	// 한글 출력
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	auto& io = ImGui::GetIO();
	font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\malgun.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesKorean());
	//io.Fonts->Build();

	// 텍스쳐 등록
	for (int idx = 0; idx != TextureArray.Num(); ++idx) 
	{

		FString str = FString::Printf(TEXT("pricone_%d"), idx);
		FName name = FName(*str);
		FImGuiModule::Get().RegisterTexture(name, TextureArray[idx]);
		
	}

	max_texture_array = TextureArray.Num();

	// ImGui의 World Delegate에 처리를 등록 
	FImGuiDelegates::OnWorldDebug().AddUObject(this, &AImGuiTest::ImGuiAlwaysShow);

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
		onTick_ImGui_CulcurateNowTime();
	}
	
	if (IsOnImgWindow) {
		onTick_ImGui_ViewImage();
	}

	if (IsOnColorPicker) {
		onTick_ImGui_ColorPicker();
	}

	if (IsOnTextInput) {
		onTick_ImGui_TextInput();
	}

	if (IsOnScrollCheckbox) {
		onTick_ImGui_ScrollCheckbox();
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
	IsOnColorPicker = false;
	IsOnTextInput = false;
	IsOnScrollCheckbox = false;
	ImGui::End();
}

void AImGuiTest::ImGuiAlwaysShow()
{
	ImGui::Begin("Functions");

	// 최초 1회만 실행
	if (onInitAlwaysWindow) 
	{
		ImGui::SetWindowPos( ImVec2(700, 50) );
		onInitAlwaysWindow = false;
	}

	/*ImGui::Text("ImGui World Tick: Actor = '%ls', World = '%ls', CurrentWorld = '%ls'",
		*GetNameSafe(this), *GetNameSafe(GetWorld()), *GetNameSafe(GWorld));*/

	if (ImGui::Button(u8"UMG 입력모드")) 
	{
		GetGameInstance()->GetFirstLocalPlayerController()->ConsoleCommand(FString("ImGui.ToggleInput"));
	};
	ImGui::SameLine();
	if (ImGui::Button("ImGui.ToggleDemo")) 
	{
		GetGameInstance()->GetFirstLocalPlayerController()->ConsoleCommand(FString("ImGui.ToggleDemo"));
	}
	ImGui::SameLine();
	ImGui::End();
}

void AImGuiTest::ImGui_Show_NowTime()
{
	ImGuiClear();
	SetTitle( FString( "Current Time" ) );
	onClickedTimeWindow = true;
	IsOnTimeWindow = true;
}

void AImGuiTest::ImGui_Show_Image()
{
	ImGuiClear();
	SetTitle(FString("View Image"));
	SetRandomTextureName(max_texture_array);
	onClickedImgWindow = true;
	IsOnImgWindow = true;
}
void AImGuiTest::ImGui_Show_Color_Picker()
{
	ImGuiClear();
	SetTitle(FString("Color Picker"));
	onClickedColorPicker = true;
	IsOnColorPicker = true;
}

void AImGuiTest::ImGui_Show_TextInput()
{
	ImGuiClear();
	SetTitle(FString("Text Input"));
	onClickedTextInput = true;
	IsOnTextInput = true;
}

void AImGuiTest::ImGui_Show_ScrollCheckbox()
{
	ImGuiClear();
	SetTitle(FString("ScrollBack and CheckBox"));
	onClickedScrollCheckbox = true;
	IsOnScrollCheckbox = true;
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

void AImGuiTest::SetRandomTextureName(int max)
{
	// 텍스쳐 배열에서 랜덤으로 한장 꺼낸다
	// ** 현재 rs가 Null인 이슈 -> FRandomStream 인스턴스를 할당하고 메모리 관리 필요...
	FRandomStream rs = FRandomStream();
	rs.GenerateNewSeed();
	int rand_idx = rs.RandRange(0, max - 1);
	FString str = FString::Printf(TEXT("pricone_%d"), rand_idx);
	curr_texture_idx = rand_idx;
	rand_texture_name = FName(*str);
}

void AImGuiTest::onTick_ImGui_CulcurateNowTime()
{
	ImGui::Begin(TCHAR_TO_ANSI(*Title));

	// 최초 1회만 실행
	if (onClickedTimeWindow) 
	{
		ImGui::SetWindowSize(ImVec2(280, 80));
		ImGui::SetWindowPos(ImVec2(ImGui::GetCursorPosX() + 300, ImGui::GetCursorPosY() + 50));

		onClickedTimeWindow = false;
	}

	time_t curTime = time(NULL);
	struct tm* pLocalTime = localtime(&curTime);
	wDayToString(pLocalTime->tm_wday);
	ImGui::Text("Today : %04dY %02dM %02dD ", 1900 + pLocalTime->tm_year, pLocalTime->tm_mon + 1, pLocalTime->tm_mday/*, *eWDay_to_string*/);
	ImGui::Text("Now Time { %02d:%02d:%02d }", pLocalTime->tm_hour, pLocalTime->tm_min, pLocalTime->tm_sec);
	ImGui::End();
}

void AImGuiTest::onTick_ImGui_ViewImage()
{
	ImGui::Begin(TCHAR_TO_ANSI(*Title));
	
	// 최초 1회만 실행
	if (onClickedImgWindow)
	{
		int sizeX = TextureArray[curr_texture_idx]->GetSizeX() / 2;
		int sizeY = TextureArray[curr_texture_idx]->GetSizeY() / 2;
		ImGui::SetWindowSize(ImVec2(sizeX, sizeY));
		ImGui::SetWindowPos(ImVec2(ImGui::GetCursorPosX() + 300, ImGui::GetCursorPosY() + 50));

		onClickedImgWindow = false;
	}

	FImGuiTextureHandle TextureHandle = FImGuiModule::Get().FindTextureHandle(rand_texture_name);
	ImGui::Image(TextureHandle, ImVec2(800, 300));
	
	ImGui::End();
}

void AImGuiTest::onTick_ImGui_ColorPicker()
{
	ImGui::Begin(TCHAR_TO_ANSI(*Title));
	
	ImGuiColorEditFlags flags = 0;
	// 최초 1회만 실행
	if (onClickedColorPicker)
	{
		ImGui::SetWindowSize(ImVec2(400, 400));
		flags = ImGuiColorEditFlags_::ImGuiColorEditFlags_AlphaBar & ImGuiColorEditFlags_::ImGuiColorEditFlags_AlphaPreview;

		onClickedColorPicker = false;
	}
	ImGui::ColorPicker4("Current Color", (float*)&color_v, flags, NULL);

	ImGui::End();
}

void AImGuiTest::onTick_ImGui_TextInput()
{
	ImGui::Begin(TCHAR_TO_ANSI(*Title));

	// 최초 1회만 실행
	if (onClickedTextInput) 
	{

		onClickedTextInput = false;
	}

	ImGui::InputTextMultiline("Input Text", text, IM_ARRAYSIZE(text), ImVec2(200, 200));
	//ImGui::TextColored(color_v, text);

	ImGui::End();
}

void AImGuiTest::onTick_ImGui_ScrollCheckbox()
{
	ImGui::Begin(TCHAR_TO_ANSI(*Title));
	ImGuiWindowFlags flags = 0;
	static float scroll_to_off_px;
	static float scroll_to_pos_px;
	// 최초 1회만 실행
	if (onClickedScrollCheckbox)
	{
		flags = ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar;
		scroll_to_off_px = 50.0f;
		scroll_to_pos_px = 50.0f;
		
		onClickedScrollCheckbox = false;
	}

	bool isChildWindow = ImGui::BeginChild(ImGui::GetID((void*)intptr_t(0)), ImVec2(200, 400), false, flags);
	if (ImGui::BeginMenuBar())
	{
		ImGui::TextUnformatted("aaa");
		ImGui::EndMenuBar();
	}
	if (isChildWindow) 
	{
		for (int item = 0; item < 100; item++)
		{
			ImGui::Text("Item %d", item);
		}
	}
	
	ImGui::EndChild();

	ImGui::End();
}
