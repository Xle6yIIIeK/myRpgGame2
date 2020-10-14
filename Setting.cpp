#include "stdafx.h"
#include "Setting.h"
GraphicsSettings::GraphicsSettings()
{
	this->title = "Nova-Warrior";
	this->resolution = sf::VideoMode::getDesktopMode();
	this->fullscreen = 1;
	this->verticalSync = 0;
	this->frameRateLimit = 120;
	this->contextSettings.antialiasingLevel = 2;
	this->videoModes = sf::VideoMode::getFullscreenModes();
}

//Functions
void GraphicsSettings::saveToFile(const std::string path)
{
	std::ofstream ofs(path);

	if (ofs.is_open())
	{
		ofs << this->title << std::endl;
		ofs << this->resolution.width << " " << this->resolution.height << std::endl;
		ofs << this->fullscreen << std::endl;
		ofs << this->frameRateLimit << std::endl;
		ofs << this->verticalSync << std::endl;
		ofs << this->contextSettings.antialiasingLevel;
	}
	ofs.close();
}

void GraphicsSettings::loadFromFile(const std::string path)
{
	std::ifstream ifs(path);

	if (ifs.is_open())
	{
		std::getline(ifs, this->title);
		ifs >> this->resolution.width >> this->resolution.height;
		ifs >> this->fullscreen;
		ifs >> this->frameRateLimit;
		ifs >> this->verticalSync;
		ifs >> this->contextSettings.antialiasingLevel;
	}
	std::cout << "GraphicsSettings::loadFromFile\n \n";
	std::cout << "	title: " << this->title << "\n";
	std::cout << "	resolution " << this->resolution.width << "x" << this->resolution.height << "\n";
	std::cout << "	fullscreen " << this->fullscreen << "\n";
	std::cout << "	frameRateLimit " << this->frameRateLimit << "\n";
	std::cout << "	verticalSyn " << this->verticalSync << "\n";
	std::cout << "	antialiasingLevel " << this->contextSettings.antialiasingLevel << "\n";

	ifs.close();
}





