#pragma once

#define WindowName "Крестики нолики"
#define WindowSizeX  267 //676 ?
#define WindowSizeY 328 //401 ? 381

#define INIT(a) static bool init = false; if (!init) { init = true; a; }
