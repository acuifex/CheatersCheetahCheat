#pragma once

#include <vector>
#include <string>

namespace Settings
{
	namespace Spammer
	{
		inline bool enabled = false;
		inline float delay = 0.850f;
		inline std::vector<std::string> messages =
				{
						"CheatersCheetahCheatC++ that's 4 C's!",
						"Get CCC right now https://github.com/acuifex/CheatersCheetahCheat",
						"Admin, he's meta cheating!!! - You, probably",
						"AimTux owns me and all",
						"Your Windows p2c sucks my AimTux dry",
						"It's free as in FREEDOM!",
						"Tux only let me out so I could play this game, please be nice!",
						"Tux nutted but you keep sucken",
						">tfw no vac on Linux",
						"Cathook - more fun than a ball of yarn!",
						"GNU/Linux is the best OS!",
						"Cathook - Free and Open-Source tf2 cheat!",
						"Cathook - ca(n)t stop me meow!"
				};
	}
	namespace BypassLegit
	{
		inline bool enabled = false;
	}
	namespace VoiceSpammer
	{
		inline bool enabled = false;
	}
	namespace AutoFire
	{
		inline bool enabled = false;
		inline int mindmg = 30;
	}
}