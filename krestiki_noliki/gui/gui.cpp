//
// Отныне я буду комментировать код связанный с основной целью проекта, 
// не затрагивая методы которые и так были использованы много раз и в представлении не нуждаются,
// т.к делать мне нехуй
//
#include "gui.h"
#include "../defines.h"
#include "../game_logic/game_logic.h"
#include "../images/images.h"



cGui gui;

HWND hwndWindow;

struct fonts
{
	ImFont* fMain;
}font;

void cGui::ImGuiInit(HWND h, LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	ImGui::CreateContext();

	auto io = ImGui::GetIO();
	font.fMain = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 13.9f, NULL, io.Fonts->GetGlyphRangesCyrillic());//wtf

	ImGui_ImplWin32_Init(h);
	ImGui_ImplDX9_Init(g_pd3dDevice);

	auto& style = ImGui::GetStyle();
	style.FramePadding = ImVec2(5, 3);
	style.ItemSpacing = ImVec2(6, 2);
	style.ItemInnerSpacing = ImVec2(6, 4);
	style.WindowRounding = 0.0f;
	style.WindowTitleAlign = ImVec2(0.5, 0.5);
	style.FrameRounding = 0.0f;
	style.IndentSpacing = 6.0f;
	style.ItemInnerSpacing = ImVec2(2, 4);
	style.ColumnsMinSpacing = 50.0f;
	style.GrabMinSize = 14.0f;
	style.GrabRounding = 16.0f;
	style.ScrollbarSize = 9.0f;
	style.ScrollbarRounding = 0.0f;
	style.WindowPadding = ImVec2(7, 7);
	this->colorAccent[0] = 1.f, this->colorAccent[1] = 0.f, this->colorAccent[2] = 0.f;
	hwndWindow = h;
	this->flFontSize = 13.9f;	
}

void cGui::DestroyImgui()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void cGui::Reset(LPDIRECT3DDEVICE9 g_pd3dDevice, D3DPRESENT_PARAMETERS g_d3dpp)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
	if (hr == D3DERR_INVALIDCALL)
		IM_ASSERT(0);
	ImGui_ImplDX9_CreateDeviceObjects();
}

void cGui::Render(LPDIRECT3DDEVICE9 g_pd3dDevice, D3DPRESENT_PARAMETERS g_d3dpp)
{
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, false);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);

	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	if (g_pd3dDevice->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		g_pd3dDevice->EndScene();
	}

	HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		this->Reset(g_pd3dDevice, g_d3dpp);
	}
}

SIZE GetWindowSize(HWND hwnd)
{
	RECT Rect; SIZE sz;
	GetWindowRect(hwnd, &Rect);
	sz.cx = (Rect.right - Rect.left);
	sz.cy = (Rect.bottom - Rect.top);
	return sz;
}

void setColorTheme(int theme)
{
	auto& style = ImGui::GetStyle();
	if (style.Alpha > 1.f)
		style.Alpha = 1.f;
	else if (style.Alpha != 1.f)
		style.Alpha += 0.01f;
	if (theme == 0)
	{
		style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
		style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.81f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.55f, 0.55f, 0.55f, 0.30f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.55f, 0.55f, 0.55f, 0.40f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.55f, 0.55f, 0.55f, 0.45f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.41f, 0.41f, 0.41f, 0.83f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.40f, 0.40f, 0.20f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.57f, 0.57f, 0.57f, 0.87f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.40f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.50f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.00f, 0.00f, 0.30f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.00f, 0.00f, 0.30f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.5f, 0.5f, 0.5f, 0.5f); //ImVec4(1.00f, 0.00f, 0.00f, 0.60f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.67f, 0.40f, 0.40f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.45f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(1.00f, 0.00f, 0.00f, 0.80f); //eto
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.53f, 0.53f, 0.87f, 0.80f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f); //eto
		style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
	}
	else
	{
		style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(33 / 255.f, 35 / 255.f, 47 / 255.f, 1.0f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(58 / 255.f, 62 / 255.f, 71 / 255.f, 1.0f);
		style.Colors[ImGuiCol_Border] = ImVec4(20 / 255.f, 20 / 255.f, 31 / 255.f, 1.0f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(33 / 255.f, 35 / 255.f, 47 / 255.f, 1.0f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(28 / 255.f, 30 / 255.f, 42 / 255.f, 1.0f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(33 / 255.f, 35 / 255.f, 47 / 255.f, 1.0f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(33 / 255.f, 35 / 255.f, 47 / 255.f, 1.0f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(35 / 255.f, 35 / 255.f, 35 / 255.f, 1.0f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(35 / 255.f, 35 / 255.f, 35 / 255.f, 1.0f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(35 / 255.f, 35 / 255.f, 35 / 255.f, 1.0f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.5f, 0.5f, 0.5f, 0.5f); //ImVec4(0.f, 0.40f, 1.f, 1.f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.f, 0.50f, 1.f, 1.f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.f, 0.30f, 1.f, 1.f);
		style.Colors[ImGuiCol_Header] = ImVec4(74 / 255.f, 87 / 255.f, 109 / 255.f, 1.0f); //multicombo, combo selected item color.
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.f, 0.40f, 1.f, 0.5f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(74 / 255.f, 87 / 255.f, 109 / 255.f, 1.0f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	}
}

int theme = 0;
SIZE wndSz;
bool credits_open = false, setup_game_window = true;
time_t* pTime;
float speed = 0.01f;

void RainbowColor(float colors[3], float speed)
{
	static int counter = 0;

	if (colors[counter] >= 1.0f)
	{
		colors[counter] = 1.0f;
		counter += 1;

		if (counter > 2)
			counter = 0;
	}
	else
	{
		int prev = counter - 1;

		if (prev < 0)
			prev = 2;

		colors[prev] -= speed;
		colors[counter] += speed;
	}
}

#define RESET_NUMBER 9

namespace game
{
	namespace drawing
	{
		void AddCircle(const ImVec2& position, float radius, const ImColor& color, int segments)
		{
			auto window = ImGui::GetCurrentWindow();

			window->DrawList->AddCircle(position, radius, ImGui::ColorConvertFloat4ToU32(color), segments, 5.f);
		}

		void AddLine(const ImVec2& from, const ImVec2& to, const ImColor& color, float thickness = 1.f)
		{
			auto window = ImGui::GetCurrentWindow();

			window->DrawList->AddLine(from, to, ImGui::ColorConvertFloat4ToU32(color), thickness);
		}

		void AddImage(const ImVec2& position, const ImVec2& size, const ImTextureID pTexture, const ImColor& color)
		{
			auto window = ImGui::GetCurrentWindow();

			ImRect bb(position, ImVec2(position.x + size.x, position.y + size.y));

			window->DrawList->AddImage(pTexture, bb.Min, bb.Max, ImVec2(0.f, 0.f), ImVec2(1.f, 1.f), ImGui::ColorConvertFloat4ToU32(color));
		}

		void AddСross(const ImVec2& position, ImColor col, const int iLineSize)
		{
			AddLine(ImVec2(position[0] - iLineSize, position[1] - iLineSize), ImVec2(position[0] + iLineSize, position[1] + iLineSize), col, 5.f);
			AddLine(ImVec2(position[0] + iLineSize, position[1] - iLineSize), ImVec2(position[0] - iLineSize, position[1] + iLineSize), col, 5.f);
		}	
	}
	bool win_window_open = false, save_win = false;
	int save_count[9] = 
	{ 
		RESET_NUMBER, RESET_NUMBER, RESET_NUMBER, RESET_NUMBER, RESET_NUMBER, RESET_NUMBER, RESET_NUMBER, RESET_NUMBER, RESET_NUMBER 
	};
	int player_turn = 0;
	int game_mode = 0;
	//метод ии для игры в соло
	void GameAI(int &player_turn, int save_count[9], bool bisOpenWinWindow)
	{
		//говно на рандомайзе чисел
		if (!bisOpenWinWindow && player_turn == 1)
		{
			srand(time(pTime));
			int result = rand() % 8;
			if (!g_pGameLogic.GetStatus(result))
			{
				save_count[result] = 1;
				g_pGameLogic.StatusSet(result, player_turn);
				player_turn == 0 ? player_turn = 1 : player_turn = 0;
			}	
		}
	}
	//метод отрисовки примитивов в оверлее
	void RunOverlayDrawin()
	{
		//крестик красный, нолик синий.
		auto DrawElements = [](const int cell)
		{
			float elements_space_x = cell == 0 || cell == 3 || cell == 6 ? 7.f :
				cell == 1 || cell == 4 || cell == 7 ? 93 : 179;

			float elements_space_y = cell == 0 || cell == 1 || cell == 2 ? 23.5f :
				cell == 3 || cell == 4 || cell == 5 ? 107 : 190;

			if (g_pGameLogic.GetStatusWithPlaya(cell, 0))
			{
				drawing::AddImage(ImVec2(elements_space_x, elements_space_y), ImVec2(80, 90), images::pmTextureData["pd3dtxCross"], ImColor(255, 255, 255, 200));
				//drawing::AddСross(ImVec2(elements_space_x, elements_space_y), ImColor(0, 0, 255), 23);
			}		
			else if (g_pGameLogic.GetStatusWithPlaya(cell, 1))
			{
				drawing::AddImage(ImVec2(elements_space_x - 10, elements_space_y - 11), ImVec2(95, 115), images::pmTextureData["pd3dtxZero"], ImColor(255, 255, 255, 200));
				//drawing::AddCircle(ImVec2(elements_space_x, elements_space_y), 33, ImColor(255, 0, 0), 50);
			}			
		};

		for (int i = 0; i < 9; ++i)
		{
			DrawElements(i);
		}
	}
	//основной метод игры аля точка входа
	void DrawingGame()
	{
		ImGui::SetNextWindowPos(ImVec2(0.f, 20.f), ImGuiCond_Always, ImVec2(0.f, 0.f));
		ImGui::SetNextWindowSize(ImVec2(wndSz.cx - 16, wndSz.cy - 55));

		ImGuiWindowFlags WndFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus;

		ImGui::Begin(WindowName, nullptr, WndFlags);

		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, player_turn == 0 ? ImVec4(1.f, 0.f, 0.f, 0.5f) : player_turn == 1 ? ImVec4(0.f, 0.f, 1.f, 0.5f) :
			ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered));

		ImGui::PushStyleColor(ImGuiCol_ButtonActive, player_turn == 0 ? ImVec4(1.f, 0.f, 0.f, 0.7f) : player_turn == 1 ? ImVec4(0.f, 0.f, 1.f, 0.7f) :
			ImGui::GetStyleColorVec4(ImGuiCol_ButtonActive));
		//метод отрисовки игровых кнопок
		auto Button = [](const int cell, int& player_turn)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, save_count[cell] == 0 ? ImVec4(1.f, 0.f, 0.f, 0.5f) : save_count[cell] == 1 ? ImVec4(0.f, 0.f, 1.f, 0.5f) :
				ImGui::GetStyleColorVec4(ImGuiCol_Button));
			std::string label = std::string("##") + std::to_string(cell);

			static bool kek = false;

			if (save_count[cell] != RESET_NUMBER)
			{
				ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
				kek = true;
			}

			if (ImGui::Button(label.c_str(), ImVec2(80, 80)))
			{
				g_pGameLogic.StatusSet(cell, player_turn);
				save_count[cell] = player_turn;
				player_turn == 0 ? player_turn = 1 : player_turn = 0;
			}

			if ((save_count[cell] != RESET_NUMBER && kek))
				ImGui::PopItemFlag();

			ImGui::PopStyleColor();
		};

		//note: ход ячеек идет слево направо ->
		//0 1 2
		//3 4 5 -> 9 всего
		//6 7 8

		static float col[3];
		INIT(col[0] = 0.5f)

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 4);
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 4);
		ImGui::Image(images::pmTextureData["pd3dtxBackground"], ImVec2(261, 283), ImVec2(0, 0), ImVec2(1, 1), ImVec4(col[0], col[1], col[2], 1.f));

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 285 + 4);

		if (!setup_game_window)
		{
			col[0] = col[1] = col[2] = 1.f;
			for (int j = 0; j < 9; ++j)
			{
				Button(j, player_turn);

				if (j == 2 || j == 5 || j == 8)
					continue;

				ImGui::SameLine();
			}

			ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 3.5f);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);

			std::string player_turn2str = player_turn == 0 ? u8"Красный" : u8"Синий";
			ImGui::Text(u8"Ход игрока: %s", player_turn2str.c_str());
			g_pGameLogic.Run();
		}
		else
		{
			RainbowColor(col, speed);
			ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 3.5f);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 90);
			ImGui::Text(u8"Выберите режим игры");
			ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 6.5f);
			if (ImGui::Button(u8"Один игрок", ImVec2(90, 30))) { game_mode = 2; setup_game_window = false; }
			if (ImGui::IsItemHovered()) ImGui::SetTooltip(u8"Ну ооочень тупой бот");
			ImGui::SameLine();
			if (ImGui::Button(u8"Два игрок", ImVec2(90, 30))) { game_mode = 1; setup_game_window = false; }

			//ImGui::Image(pd3dtxLeraLuchaya, ImVec2(200, 200));

		}

		if (game_mode == 2)
			GameAI(player_turn, save_count, win_window_open);

		ImGui::End();

		ImGui::PopStyleColor();
		ImGui::PopStyleColor();

		if (g_pGameLogic.GetWinStatus())
		{
			win_window_open = true, save_win = true;
		}
		//метод очистки игровых данных
		auto Reset = [](int& player_turn, int save_count[9])
		{
			player_turn = 0;
			for (int i = 0; i < 9; i++)
			{
				save_count[i] = RESET_NUMBER;
			}
			std::cout << __FUNCTION__ " -> reset" << std::endl;
		};

		if (win_window_open)
		{
			ImGui::SetNextWindowPos(ImVec2((wndSz.cx - 16) / 2.f - 39.5f, (wndSz.cy - 55) / 2.f - 17), ImGuiCond_Always, ImVec2(0.f, 0.f));

			ImGuiWindowFlags TwoWndFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove
				| ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;

			ImGui::Begin(u8"Конец", &win_window_open, TwoWndFlags);

			static std::string player_win2str;
			if (save_win)
			{
				player_win2str = g_pGameLogic.GetWinStatus() == 1 ? u8"Красный" : g_pGameLogic.GetWinStatus() == 2 ? u8"Синий" : u8"Никто";
				std::cout << __FUNCTION__ " -> setup reset" << std::endl;
				Reset(player_turn, save_count);
				g_pGameLogic.Reset();
				save_win = false;
			}
			ImGui::Text(u8"Выйграл %s", player_win2str.c_str());
			win_window_open = ImGui::IsAnyWindowHovered();
			ImGui::End();
		}

		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4());
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
		ImGui::Begin("##BackBuffer", nullptr, ImVec2(), 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoSavedSettings);
		ImGui::SetWindowPos(ImVec2(), ImGuiCond_Always);
		ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);

		RunOverlayDrawin(); //простой оверлей, рисуются примитивы аля сами крестики нолики

		ImGui::GetCurrentWindow()->DrawList->PushClipRectFullScreen();
		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();		
	}
}

void cGui::GuiLoop()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::PushFont(font.fMain);

	setColorTheme(theme);

	wndSz = GetWindowSize(hwndWindow);

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu(u8"Интерфейс"))
		{
			//ImGui::ColorEdit4(u8"Цветовой акцент", colorAccent, ImGuiColorEditFlags_NoAlpha);
			const char* szThemeType[] = { u8"Светлая", u8"Темная" };
			ImGui::PushItemWidth(100);
			ImGui::Combo(u8"Тема", &theme, szThemeType, IM_ARRAYSIZE(szThemeType));
			ImGui::SliderFloat(u8"Скорость...", &speed, 0.f, 0.1f);
			ImGui::PopItemWidth();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu(u8"Справка"))
		{
			if (ImGui::MenuItem(u8"О программе")) { credits_open = true; }
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	game::DrawingGame();

	if (credits_open)
	{
		ImGui::SetNextWindowPos(ImVec2((wndSz.cx - 16) / 2.f - 59.5f, (wndSz.cy - 55) / 2.f - 20), ImGuiCond_Always, ImVec2(0.f, 0.f));

		ImGuiWindowFlags ThreeWndFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;

		ImGui::Begin(u8"О программе", &credits_open, ThreeWndFlags);
		ImGui::Text(u8"Крестики, 2D20");
		ImGui::Text(u8"Очень люблю Леру!!!");
		credits_open = ImGui::IsAnyWindowHovered();

		ImGui::End();
	}

	ImGui::PopFont();

	ImGui::EndFrame();
}