/*
THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
(C) Alexander Blade 2017
*/
#include "stdafx.h"
#include "Scriptthread.h";
#pragma once

extern int selectedPlayer;

void main();
void ScriptMain();
void ScriptMain();

class ControlScript : public Script {
public:
	explicit ControlScript() = default;
	~ControlScript() noexcept = default;

	bool IsInitialized() override;
	void Initialize() override;
	void Destroy() override;
	void Tick() override;
private:
	bool s_initialized{};
};

class UpdateScript : public Script {
public:
	explicit UpdateScript() = default;
	~UpdateScript() noexcept = default;

	bool IsInitialized() override;
	void Initialize() override;
	void Destroy() override;
	void Tick() override;
private:
	bool s_initialized{};
};

