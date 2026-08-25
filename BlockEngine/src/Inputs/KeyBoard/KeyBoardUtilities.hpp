#pragma once

extern int ExitKey;

bool KeyEvent(int key, int event);
void SetExitKey(int key);
void InitializeInput();
void UpdateInput();