#pragma once
#ifndef VISUALKEYBOARD_H
#define VISUALKEYBOARD_H

class ingame_keyboard
{
public:
	//ingame_keyboard(const std::string& default_text);
	ingame_keyboard(const std::string& default_text, std::string* output);
	void start();
	void stop();
	static bool finished_process_;
	std::string output() const;
private:
	static bool on_;
};

#endif // VISUALKEYBOARD_H
