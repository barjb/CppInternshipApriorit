#include <iostream>

#include "cipheredLogger.hpp"
#include "logger.hpp"

int main(int argc, char **argv)
{
    std::string randomString1 = "A sunny start to the day, becoming cloudier through the morning. Chance of an isolated shower from midday, with cloud continuing to thicken through the afternoon. Showers fading by the end of the day. Maximum temperature 23 °C.";
    std::string randomString2 = "A dry but generally cloudy evening for most. Remaining cloudy overnight with a risk of isolated showers forming over the north of the region towards dawn. Minimum temperature 13 °C.";
    std::string randomString3 = "Dry with sunny spells for across the south east, becoming more widespread through the day. Clear skies overnight. Maximum temperature 25 °C.";
    std::string randomString4 = "Prolonged sunny spells Friday. Then a more unsettled weekend, cloudier with outbreaks of rain mostly towards the north and west of the region. Temperatures warm, locally very warm on Saturday.";

    std::string fileName{"cipheredLog"};
    std::string key{"qwerty"};

    if (argc == 3)
    {
        fileName = argv[1];
        key = argv[2];
    }

    {
        Logger l("unciphered" + fileName);
        l.Write(randomString1);
        l.Write(randomString2);
        l.Write(randomString3);
    }
    {
        CipheredLogger l2(fileName, key);
        l2.Write(randomString1);
        l2.Write(randomString2);
        l2.Write(randomString3);
        l2.Write(randomString2);
        l2.Write(randomString3);
    }

    return 0;
}