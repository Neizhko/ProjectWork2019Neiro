#include "Logic.hpp"
#include <QDebug>
#include <string>
#include <sstream>

using namespace Logic_module;

Logic::Logic()
{
}

Logic::~Logic()
{
}

void Logic::newInputDataSlt(unsigned int IDSignal) 
{
	if (IDSignal > 4)
	{
		return; //Just because we have only 4 signals 
	}

	qDebug() << "Input data: " << IDSignal;
	
	Settings_module::Setting setting;
	for (unsigned int i = 0; i < settings.size(); i++)
	{
		if (IDSignal == settings[i].id)
		{
			setting = settings[i];
		}
	}

	if (setting.keys != "None")
	{
		std::string str = setting.keys;
		int rep = 0;
		for (unsigned int i = 0; i < str.size(); i++)
		{
			if (str[i] == '+')
			{
				rep++;
				str[i] = ' ';
			}
		}
		std::vector<std::string> keys;
		std::string key;
		std::stringstream ss;
		ss << str;
		for (int i = 0; i < rep + 1; i++)
		{
			ss >> key;
			keys.push_back(key);
		}
		for (unsigned int i = 0; i < keys.size(); i++) // Now pressing keys 
		{
			emit pressKeySig(keys[i]);
			emit releaseKeySig(keys[i]);
		}
	}
}

void Logic::updateSettings(std::vector<Settings_module::Setting> settings)
{
	this->settings = settings;
}