#ifndef MAZE_H
#define MAZE_H
#include <cstdint>
#include <random>
#include <stack>
#include <vector>
#include "Core/Renderer/Mesh.h"

#include "glm/vec3.hpp"

#include "Core/Renderer/Shader.h"
#include <iostream>
#include "Object.h"

enum CellWall: uint8_t{
    WALL_N = 1<< 0,
    WALL_E = 1 << 1,
    WALL_S = 1 << 2,
    WALL_W = 1 << 3,
    VISITED = 1<< 4,
};

struct MazeGenerator {
    int width, height;
    std::vector<uint8_t> cells;
    MazeGenerator(int width, int height) : width(width), height(height), cells(width * height, WALL_N | WALL_E | WALL_S | WALL_W  ) {};

    inline int Idx(int x, int y) const {
        return y * width + x;
    }

    bool InBounds(int x, int y) const {
        return x >= 0 && y >= 0 && x < width && y < height;
    }

    void Generate(int seed = 0) {
        std::mt19937 rng(seed ?  seed : std::random_device{}());
        std::stack<std::pair<int, int>> st;
        int sx = 0, sy = 0;
        st.push({sx, sy});

        const int DX[4] = {0, 1, 0, -1};
        const int DY[4] = {-1, 0, 1, 0};

        // mapping for opposite walls and current direction
        const uint8_t OPP[4] = {WALL_S, WALL_W, WALL_N, WALL_E};
        const uint8_t DIR[4] = {WALL_N, WALL_E, WALL_S, WALL_W};

        while (!st.empty()) {
            auto [x, y] = st.top();
            std::vector<int> neighbors;
            for (int i =0 ; i < 4; ++i) {
                int nx = x + DX[i];
                int ny = y + DY[i];
                if (InBounds(nx, ny) && !(cells[Idx(nx, ny)] & VISITED) ) {
                    neighbors.push_back(i);
                }
            }
            if (!neighbors.empty()) {
                std::uniform_int_distribution<int> dist(0, neighbors.size() - 1);
                int choice = neighbors[dist(rng)];
                int nx = x + DX[choice], ny = y + DY[choice];
                cells[Idx(x, y)] &= ~DIR[choice]; //Remove the wall between the choosen neighbour and the currentcell for currentceell
                cells[Idx(nx, ny)] &= ~OPP[choice]; //Remove the wall between the choosen neighbour and currentcell for neighbour
                cells[Idx(nx, ny)] |= VISITED; //Set the VISITED flag
                st.push({nx, ny}); // Push the neighbour cell to the stack
            }
            else {
                st.pop();
            }
        }
        for (auto &c : cells) {
            c &= ~VISITED;
        }
    }
    void PrintMaze() {
        // Top border
        for (int x = 0; x < width; ++x)
            std::cout << "+---";
        std::cout << "+\n";

        for (int y = 0; y < height; ++y) {
            // Left border of each row
            std::cout << "|";
            // Draw each cell
            for (int x = 0; x < width; ++x) {
                auto c = cells[Idx(x, y)];
                // Cell interior (can replace space with '.' for visibility)
                std::cout << "   ";
                // Draw east wall
                if (c & WALL_E)
                    std::cout << "|";
                else
                    std::cout << " ";
            }
            std::cout << "\n";

            // Draw south walls
            for (int x = 0; x < width; ++x) {
                auto c = cells[Idx(x, y)];
                if (c & WALL_S)
                    std::cout << "+---";
                else
                    std::cout << "+   ";
            }
            std::cout << "+\n";
        }
    }
};

struct AABB {
    glm::vec3 min , max;
};

class Maze : public Game::Object  { 
private:
    MazeGenerator m_maze;
    std::vector<AABB> m_wallAABBs;

public:
    Maze();
    inline void AddBox(glm::vec3 min , glm::vec3 max) ;
    void GenerateMesh(float cellSize = 1.0f, float wallThickness = 0.3f, float wallHeight = 0.6f);
    void PrintMaze();

};




#endif //MAZE_H
