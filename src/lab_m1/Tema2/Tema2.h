#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/lab_camera.h"
#include "lab_m1/Tema2/playerTank.h"
#include "lab_m1/Tema2/EnemyTank.h"
#include "lab_m1/Tema2/Collisions.h"
#include "lab_m1/Tema2/Building.h"

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        Tema2();
        ~Tema2();

        void Init() override;

        Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color = glm::vec3(1), const int hp = 0);
        void CreateBuilding(float length, float width, float height, const char* id);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        void DrawPlayer();
        void DrawEnemy(EnemyTank* enemy);
        void DrawBullet(float deltaTimeSeconds);
        void CreateEnemies(float deltaTimeSeconds);
        void DrawScene();

        glm::mat4 RotateOY(float radians);

    protected:
        implemented::Camera* camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;

        // TODO(student): If you need any other class variables, define them here.
        float right;
        float left;
        float bottom;
        float top;
        float fov;
        bool perspective;
        float mapLenght;
        float intervalEnemySpawn;
        int score;
        float gameTime;

        PlayerTank* player;
        EnemyTank* enemy;
        std::vector<Bullet*> bullets;
        std::vector<EnemyTank*> enemies;
        std::vector<Building*> buildings;

    };
}   // namespace m1
