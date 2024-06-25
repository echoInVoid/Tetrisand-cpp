#include "update.h"
#include "setting.h"
#include "sandData.h"
#include "sand.h"
#include "stat.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <queue>
#include <utility>

using namespace sand;

namespace update
{
    // �ж�ʧ��
    static bool failCheck()
    {
        for (int i=0; i<sandListW; i++)
            for (int j = sandListH - 1; j >= failLine; j--)
            {
                if (!updatableSand(*sands[i][j])) // ֻ��Բ��������ɳ����ʧ�ܼ��
                    break;
                if (j == failLine)
                    return true;
            }
        return false;
    }

    // ��(x,y)��ʼ����������Ƭɳ����mark�б��Ϊmarker�����ظ�Ƭɳ���Ƿ����ɾ��
    static bool BFSMark(int x, int y, int** mark, int marker)
    {
        using namespace std;
        typedef pair<int, int> pos;

        bool res = false;

        queue<pos> q;
        q.push(make_pair(x, y));
        
        while (!q.empty())
        {
            const int i = q.front().first, j = q.front().second;
            q.pop();

            if (mark[i][j] != 0)
                continue;
            mark[i][j] = marker;
            if (i == sandListW - 1)
                res = true;

            auto f = [&](int _i, int _j) {
                if (validPos(_i, _j) && *sands[_i][_j] == *sands[i][j])
                    q.push(make_pair(_i, _j));
            };
            f(i + 1, j);
            f(i - 1, j);
            f(i, j + 1);
            f(i, j - 1);
        }

        return res;
    }

    // ������ǵĿ��Ƴ�ɳ���滻ΪREMOVING
    static void replaceMarkedSand(std::vector<int> removing, int** mark, int maxMarker)
    {
        bool* tmp = new bool[maxMarker + 1];
        memset(tmp, 0, sizeof(bool) * (maxMarker + 1));
        for (int i = 0; i < removing.size(); i++)
            tmp[removing[i]] = true;

        for (int i = 0; i < sandListW; i++)
            for (int j = 0; j < sandListH; j++)
                if (tmp[mark[i][j]])
                    sands[i][j] = &constants::REMOVING;

        delete[] tmp;
    }

    // �����Ա��Ƴ���ɳ���滻ΪREMOVING�������Ƿ���ɳ�ӱ��滻
    static bool markSand()
    {
        static int** mark = new int*[sandListW];
        for (int i = 0; i < sandListW; i++)
        {
            mark[i] = new int[sandListH];
            memset(mark[i], 0, sizeof(int)*sandListH);
        }

        std::vector<int> removing; // ��Ҫ�Ƴ��ı��
        int marker = 1;
        for (int j = 0; j < sandListH; j++)
            if (updatableSand(*sands[0][j]) && mark[0][j] == 0)
            {
                if (BFSMark(0, j, mark, marker))
                    removing.push_back(marker);
                marker++;
            }
        
        if (removing.size() == 0)
            return false;

        replaceMarkedSand(removing, mark, marker-1);

        for (int i = 0; i < sandListW; i++)
            delete[] mark[i];

        return true;
    }

    // �Ƴ�REMOVING�����ر��Ƴ���ɳ����
    static int removeMarkedSand()
    {
        int cnt = 0;

        for (int i = 0; i < sandListW; i++)
            for (int j = 0; j < sandListH; j++)
                if (*sands[i][j] == constants::REMOVING)
                {
                    sands[i][j] = &constants::VOID;
                    cnt++;
                }

        return cnt;
    }

    static void updateSand()
    {
        sf::Lock lock(sandsLock);
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
                else if (x == sandListW - 1 && *sands[x - 1][y + 1] == constants::VOID)
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
            if (!status::gameFailed)
            {
                updateSand();
                if (markSand())
                {
                    sf::sleep(sf::seconds(0.5f));
                    statistics::updateScore(removeMarkedSand());
                }
                if (failCheck())
                    status::gameFailed = true;
            }

            // tps����
            sf::Time elapsedTime = clock.restart();
            if (elapsedTime < sf::seconds(1.0f / tps))
                sf::sleep(sf::seconds(1.0f / tps) - elapsedTime);
        }
    }
}