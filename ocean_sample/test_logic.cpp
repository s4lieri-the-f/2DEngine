#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <thread>
#include <chrono>

class EntityInterface
{
public:
    virtual ~EntityInterface() = default;
    virtual int getType() const = 0;
    virtual void move(int &x, int &y, int width, int height) = 0;
};

class GoodCarp : public EntityInterface
{
public:
    int getType() const override { return 1; }
    void move(int &x, int &y, int width, int height) override
    {
        std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        auto dir = directions[rand() % directions.size()];
        x = (x + dir.first) % width;
        y = (y + dir.second) % height;
    }
};

class BadCarp : public EntityInterface
{
public:
    int getType() const override { return 2; }
    void move(int &x, int &y, int width, int height) override
    {
        std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        auto dir = directions[rand() % directions.size()];
        x = (x + dir.first) % width;
        y = (y + dir.second) % height;
    }
};

class Rock : public EntityInterface
{
public:
    int getType() const override { return 3; }
    void move(int &, int &, int, int) override {}
};

class Ocean
{
public:
    Ocean(int width, int height) : width(width), height(height)
    {
        ocean.resize(height, std::vector<std::shared_ptr<EntityInterface>>(width, nullptr));
    }

    void tick()
    {
        // Add logic for movement and interactions
        std::vector<std::pair<int, int>> newGoodCarps;
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                if (ocean[y][x] && (ocean[y][x]->getType() == 1 || ocean[y][x]->getType() == 2))
                {
                    moveEntity(x, y);
                }
            }
        }
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                if (ocean[y][x] && ocean[y][x]->getType() == 2)
                { // BadCarp
                    huntGoodCarp(x, y);
                }
            }
        }
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                if (ocean[y][x] && ocean[y][x]->getType() == 1)
                { // GoodCarp
                    if (canReproduce(x, y))
                    {
                        newGoodCarps.push_back({(x + 1) % width, (y + 1) % height});
                    }
                }
            }
        }
        for (auto &pos : newGoodCarps)
        {
            int x = pos.first;
            int y = pos.second;
            if (!ocean[y][x])
            {
                ocean[y][x] = std::make_shared<GoodCarp>();
            }
        }
    }

    std::vector<std::vector<int>> generate_map() const
    {
        std::vector<std::vector<int>> map(height, std::vector<int>(width, 0));
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                if (ocean[y][x])
                {
                    map[y][x] = ocean[y][x]->getType();
                }
            }
        }
        return map;
    }

    void addEntity(int x, int y, std::shared_ptr<EntityInterface> entity)
    {
        ocean[y][x] = entity;
    }

private:
    int width, height;
    std::vector<std::vector<std::shared_ptr<EntityInterface>>> ocean;

    void moveEntity(int &x, int &y)
    {
        int newX = x;
        int newY = y;
        ocean[y][x]->move(newX, newY, width, height);
        if (newX < 0 || newX >= width || newY < 0 || newY >= height)
        {
            ocean[y][x] = nullptr; // Entity despawns
        }
        else if (!ocean[newY][newX])
        {
            std::swap(ocean[y][x], ocean[newY][newX]);
            x = newX;
            y = newY;
        }
    }

    void huntGoodCarp(int x, int y)
    {
        // Simple hunting logic: BadCarp eats any adjacent GoodCarp
        std::vector<std::pair<int, int>> directions = {
            {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
        for (auto &dir : directions)
        {
            int newX = (x + dir.first);
            int newY = (y + dir.second);
            if (newX >= 0 && newX < width && newY >= 0 && newY < height &&
                ocean[newY][newX] && ocean[newY][newX]->getType() == 1)
            { // GoodCarp
                ocean[newY][newX] = nullptr;
            }
        }
    }

    bool canReproduce(int x, int y)
    {
        // Check if two GoodCarps are alone and can reproduce
        std::vector<std::pair<int, int>> directions = {
            {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
        bool foundAnotherGoodCarp = false;
        for (auto &dir : directions)
        {
            int newX = (x + dir.first);
            int newY = (y + dir.second);
            if (newX >= 0 && newX < width && newY >= 0 && newY < height && ocean[newY][newX])
            {
                if (ocean[newY][newX]->getType() == 1)
                { // GoodCarp
                    if (foundAnotherGoodCarp)
                    {
                        return false; // More than one GoodCarp around
                    }
                    foundAnotherGoodCarp = true;
                }
                else
                {
                    return false; // Other entities around
                }
            }
        }
        return foundAnotherGoodCarp;
    }
};