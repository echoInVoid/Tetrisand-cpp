#include "update.h"
#include "setting.h"
#include "sandData.h"
#include "sand.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <random>
#include <ctime>

using namespace sand;

namespace update
{
    static void updateSand()
    {
        for (int y = sandListH - 2; y >= 0; y--)
            for (int x = 0; x < sandListW; x++)
            {
                if (!updatableSand(*sands[x][y]))
                    continue;

                // SUPER UGLY CODE.
                // I may improve this some time later.
                using std::swap;
                using std::rand;
                if (*sands[x][y + 1] == constants::VOID)
                    swap(sands[x][y + 1], sands[x][y]);
                else if (x == 0 && *sands[x + 1][y + 1] == constants::VOID)
                    swap(sands[x + 1][y + 1], sands[x][y]);
                else if (x == sandListW && *sands[x - 1][y + 1] == constants::VOID)
                    swap(sands[x - 1][y + 1], sands[x][y]);
                else if (x != 0 && x != sandListW - 1)
                {
                    if (*sands[x + 1][y + 1] == constants::VOID && *sands[x - 1][y + 1] != constants::VOID)
                        swap(sands[x + 1][y + 1], sands[x][y]);
                    else if (*sands[x + 1][y + 1] != constants::VOID && *sands[x - 1][y + 1] == constants::VOID)
                        swap(sands[x - 1][y + 1], sands[x][y]);
                    else if (*sands[x + 1][y + 1] == constants::VOID && *sands[x - 1][y + 1] == constants::VOID)
                    {
                        if (rand() < RAND_MAX / 2)
                            swap(sands[x - 1][y + 1], sands[x][y]);
                        else
                            swap(sands[x + 1][y + 1], sands[x][y]);
                    }
                }
            }
    }

    void updateThread(sf::RenderWindow* window)
    {
        sf::Clock clock;

        while (window->isOpen())
        {
            updateSand();

            // tps¿ØÖÆ
            sf::Time elapsedTime = clock.restart();
            if (elapsedTime < sf::seconds(1.0 / tps))
                sf::sleep(sf::seconds(1.0 / tps) - elapsedTime);
        }
    }
}