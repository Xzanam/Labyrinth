#include "Maze.h"


MazeMesh::MazeMesh()  : m_maze(10, 10), m_mesh() {
    m_maze.Generate();
    this->GenerateMesh();
    m_mesh.SetupMesh();
}

void MazeMesh::AddBox(glm::vec3 min , glm::vec3 max) {
    // Vertices of 8 Corners
    glm::vec3 p[8]  =  {
        {min.x, min.y, min.z},
        {max.x, min.y, min.z},
        {max.x, max.y, min.z},
        {min.x, max.y, min.z},
        {min.x, min.y, max.z},
        {max.x, min.y, max.z},
        {max.x, max.y, max.z},
        {min.x, max.y, max.z},
    };
     //faces
    const int faceIdx[6][4] = {
        {0, 1, 2, 3},
        {5, 4, 7,6},
        {4, 0, 3, 7},
        {1, 5, 6, 2},
        {3, 2, 6, 7},
        {4, 5, 1, 0}
    };

    const glm::vec3 normals[6] = {
        {0, 0, -1 },
        {0, 0, 1},
        {-1, 0, 0},
        {1, 0, 0},
        {0, 1, 0},
        {0, -1, 0}
    };

    auto  base =  m_mesh.GetVertexSize();
    for (int f = 0 ; f < 6 ; ++f) {
        for (int k = 0; k < 4; ++k) {
            Core::Vertex v;
            v.Position = p[faceIdx[f][k]];
            v.Normal = normals[f];
            v.TexCoords = glm::vec2( (k == 0 || k == 3) ? 0.0f : 1.0f, (k < 2) ? 0.0f : 1.0f);
            m_mesh.PushVertex(v);
        }

        //Add two triangles
        m_mesh.PushIndex(base + f* 4  + 0);
        m_mesh.PushIndex(base + f* 4 + 1);
        m_mesh.PushIndex(base + f* 4 + 2);


        m_mesh.PushIndex(base + f* 4 + 0);
        m_mesh.PushIndex(base + f* 4 + 2);
        m_mesh.PushIndex(base + f* 4 + 3);
    }


}

void MazeMesh::PrintMaze() {
    m_maze.PrintMaze();
}
 


void MazeMesh::OnRender(Core::Shader& shader) const {
    shader.use();
    shader.setMat4("model", glm::mat4(1.0f));
    m_mesh.Draw();

}


void MazeMesh::GenerateMesh(float cellSize, float wallThickness, float wallHeight) {
    m_mesh.Clear();
    m_wallAABBs.clear();

    for (int y = 0; y < m_maze.height; ++y) {
        for (int x = 0; x < m_maze.width; ++x) {
            auto c = m_maze.cells[m_maze.Idx(x, y)];

            float minX = x * cellSize;
            float maxX = (x + 1) * cellSize;
            float minZ = y * cellSize;
            float maxZ = (y + 1) * cellSize;
            float minY = 0.0f;
            float maxY = wallHeight;

            // North wall (along X at minZ)
            if (c & WALL_N) {
                glm::vec3 mn(minX, minY, minZ - wallThickness * 0.5f);
                glm::vec3 mx(maxX, maxY, minZ + wallThickness * 0.5f);
                AddBox(mn, mx);
                m_wallAABBs.push_back({mn, mx});
            }

            // West wall (along Z at minX)
            if (c & WALL_W) {
                glm::vec3 mn(minX - wallThickness * 0.5f, minY, minZ);
                glm::vec3 mx(minX + wallThickness * 0.5f, maxY, maxZ);
                AddBox(mn, mx);
                m_wallAABBs.push_back({mn, mx});
            }

            // East boundary (to avoid double creating, only create for last column)
            if (x == m_maze.width - 1 && (c & WALL_E)) {
                glm::vec3 mn(maxX - wallThickness * 0.5f, minY, minZ);
                glm::vec3 mx(maxX + wallThickness * 0.5f, maxY, maxZ);
                AddBox(mn, mx);
                m_wallAABBs.push_back({mn, mx});
            }

            // South boundary (for the last row)
            if (y == m_maze.height - 1 && (c & WALL_S)) {
                glm::vec3 mn(minX, minY, maxZ - wallThickness * 0.5f);
                glm::vec3 mx(maxX, maxY, maxZ + wallThickness * 0.5f);
                AddBox(mn, mx);
                m_wallAABBs.push_back({mn, mx});
            }
        }
    }
}


