#include "lab_m1/Tema2/Tema2.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    renderCameraTarget = false;

    right = 20.f;
    left = .02f;
    bottom = .02f;
    top = 20.f;
    fov = 80.f;

    gameTime = 0;
    score = 0;

    camera = new implemented::Camera();
    camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    player = new PlayerTank(camera->GetTargetPosition().x, camera->GetTargetPosition().z);

    enemy = new EnemyTank();
    enemy->CreateRandomPosition();
    enemy->bullets = bullets;
    enemies.push_back(enemy);

    for (int i = 0; i < 10; i++) {
        Building* building = new Building();
        building->CreateRandomPosition();
        building->CreateRandomSize();

        std::string id = std::to_string(i);
        const char* id_cstr = id.c_str();
        CreateBuilding(building->length, building->width, building->height, id_cstr);


        buildings.push_back(building);
    }

   
    mapLenght = 25;
    intervalEnemySpawn = 0.f;

    //player tank
    {
        Mesh* mesh = new Mesh("roti_dr");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "roti_dr.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("roti_st");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "roti_st.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("banda_dr");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "banda_dr.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("banda_st");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "banda_st.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("tun");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "tun.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("turela");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "turela.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("corp");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "corp.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    //enemy tank

    {
        Mesh* mesh = new Mesh("roti_drE");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "enemyTank"), "roti_dr.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("roti_stE");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "enemyTank"), "roti_st.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("banda_drE");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "enemyTank"), "banda_dr.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("banda_stE");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "enemyTank"), "banda_st.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("tunE");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "enemyTank"), "tun.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("turelaE");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "enemyTank"), "turela.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("corpE");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "enemyTank"), "corp.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    //plan
    {
        Mesh* mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Shader* shader = new Shader("PlayerShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "PlayerVertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "PlayerFragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        Shader* shader = new Shader("EnemyShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "EnemyVertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "EnemyFragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        Shader* shader = new Shader("PlayerShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "PlayerVertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "PlayerFragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        Shader* shader = new Shader("ObjectsShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.0f, 0.5f, 1.0f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
    gameTime += deltaTimeSeconds;

    if (gameTime >= 120 || player->destroyed == true) {
        cout << "Game Over" << endl << "SCORE: " << score << endl;
        window->Close();
    }

    projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, 0.01f, 200.0f);

    if (!window->KeyHold(GLFW_KEY_X)) {
        window->HidePointer();
        window->SetPointerPosition(window->GetResolution().x / 2, window->GetResolution().y / 2);
    }  

    DrawPlayer();
    DrawBullet(deltaTimeSeconds);
    DrawScene();
    CreateEnemies(deltaTimeSeconds);

    player->timeBulletSpawn += deltaTimeSeconds;

    for (auto& enemy : enemies) {
        DrawEnemy(enemy);

        enemy->timeBulletSpawn += deltaTimeSeconds;
        enemy->Move(deltaTimeSeconds);
        Collisions::PlayerEnemyCollision(player, enemy, camera);
        enemy->Attack(player, deltaTimeSeconds, bullets);

        for (auto& bullet : bullets) {
            Collisions::BulletTankCollision(bullet, enemy, score);
        }
        for (auto& enemy1 : enemies) {
            if (enemy != enemy1) {
                Collisions::EnemyEnemyCollision(enemy, enemy1);
            }         
        }
    }

    for (auto& bullet : bullets) {
        Collisions::BulletPlayerCollision(bullet, player);
    }

    for (auto& building : buildings) {
        Collisions::PlayerBuildingsCollision(player, building, camera);

        for (auto& bullet : bullets) {
            Collisions::BulletBuildingsCollision(bullet, building);
        }

        for (auto& enemy : enemies) {
            Collisions::EnemyBuildingsCollision(enemy, building);
        }
    }
}

void Tema2::CreateBuilding(float length, float width, float height, const char* id) {
    float halfLength = length / 2.0f;
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;

    vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(-halfLength, -halfHeight, halfWidth), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.2)),
        VertexFormat(glm::vec3(halfLength, -halfHeight, halfWidth), glm::vec3(1, 0, 1), glm::vec3(0.9, 0.4, 0.2)),
        VertexFormat(glm::vec3(-halfLength, halfHeight, halfWidth), glm::vec3(1, 0, 0), glm::vec3(0.7, 0.7, 0.1)),
        VertexFormat(glm::vec3(halfLength, halfHeight, halfWidth), glm::vec3(0, 1, 0), glm::vec3(0.7, 0.3, 0.7)),
        VertexFormat(glm::vec3(-halfLength, -halfHeight, -halfWidth), glm::vec3(1, 1, 1), glm::vec3(0.3, 0.5, 0.4)),
        VertexFormat(glm::vec3(halfLength, -halfHeight, -halfWidth), glm::vec3(0, 1, 1), glm::vec3(0.5, 0.2, 0.9)),
        VertexFormat(glm::vec3(-halfLength, halfHeight, -halfWidth), glm::vec3(1, 1, 0), glm::vec3(0.7, 0.0, 0.7)),
        VertexFormat(glm::vec3(halfLength, halfHeight, -halfWidth), glm::vec3(0, 0, 1), glm::vec3(0.1, 0.5, 0.8)),
    };

    vector<unsigned int> indices =
    {
        0, 1, 2,        1, 3, 2,
        2, 3, 7,        2, 7, 6,
        1, 7, 3,        1, 5, 7,
        6, 7, 4,        7, 5, 4,
        0, 4, 1,        1, 4, 5,
        2, 6, 4,        0, 2, 4,
    };

    CreateMesh(id, vertices, indices);
}


Mesh* Tema2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
{
    unsigned int VAO = 0;
    // Create the VAO and bind it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create the VBO and bind it
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // Create the IBO and bind it
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // Send indices data into the IBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);


    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // Unbind the VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    CheckOpenGLError();

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    meshes[name]->vertices = vertices;
    meshes[name]->indices = indices;
    return meshes[name];
}

glm::mat4 Tema2::RotateOY(float radians) {
    return glm::transpose(
        glm::mat4(cos(radians), 0, sin(radians), 0,
            0, 1, 0, 0,
            -sin(radians), 0, cos(radians), 0,
            0, 0, 0, 1));
}

void Tema2::DrawBullet(float deltaTimeSeconds) {
    for (auto it = bullets.begin(); it != bullets.end();) {
        auto& bullet = *it;
        bullet->MoveForward(8 * deltaTimeSeconds);

        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, bullet->position);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
        RenderSimpleMesh(meshes["sphere"], shaders["ObjectsShader"], modelMatrix, glm::vec3(0));

        if (bullet->toBeErased) {
            it = bullets.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Tema2::DrawPlayer() {
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, player->position);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
        modelMatrix *= RotateOY(player->angle);
        modelMatrix = glm::rotate(modelMatrix, RADIANS(180), glm::vec3(0, 1, 0));
        RenderSimpleMesh(meshes["banda_dr"], shaders["PlayerShader"], modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f), player->hp);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, player->position);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
        modelMatrix *= RotateOY(player->angle);
        modelMatrix = glm::rotate(modelMatrix, RADIANS(180), glm::vec3(0, 1, 0));
        RenderSimpleMesh(meshes["banda_st"], shaders["PlayerShader"], modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f), player->hp);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, player->position);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
        modelMatrix *= RotateOY(player->angle);
        modelMatrix = glm::rotate(modelMatrix, RADIANS(180), glm::vec3(0, 1, 0));
        RenderSimpleMesh(meshes["roti_dr"], shaders["PlayerShader"], modelMatrix, glm::vec3(0.1f), player->hp);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, player->position);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
        modelMatrix *= RotateOY(player->angle);
        modelMatrix = glm::rotate(modelMatrix, RADIANS(180), glm::vec3(0, 1, 0));
        RenderSimpleMesh(meshes["roti_st"], shaders["PlayerShader"], modelMatrix, glm::vec3(0.1f), player->hp);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, player->position);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
        modelMatrix *= RotateOY(player->angle);
        modelMatrix *= RotateOY(player->turela->angle);
        modelMatrix = glm::rotate(modelMatrix, RADIANS(180), glm::vec3(0, 1, 0));
        RenderSimpleMesh(meshes["tun"], shaders["PlayerShader"], modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f), player->hp);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, player->position);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
        modelMatrix *= RotateOY(player->angle);
        modelMatrix *= RotateOY(player->turela->angle);
        modelMatrix = glm::rotate(modelMatrix, RADIANS(180), glm::vec3(0, 1, 0));
        RenderSimpleMesh(meshes["turela"], shaders["PlayerShader"], modelMatrix, glm::vec3(1, 1, 0), player->hp);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, player->position);
        modelMatrix *= RotateOY(player->angle);
        modelMatrix = glm::rotate(modelMatrix, RADIANS(180), glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
        RenderSimpleMesh(meshes["corp"], shaders["PlayerShader"], modelMatrix, glm::vec3(0.1f, 0.1f, 0), player->hp);
    }
}

void Tema2::DrawEnemy(EnemyTank* enemy) {
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, enemy->position);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
        modelMatrix *= RotateOY(enemy->angle);
        RenderSimpleMesh(meshes["banda_drE"], shaders["EnemyShader"], modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f), enemy->hp);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, enemy->position);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
        modelMatrix *= RotateOY(enemy->angle);
       
        RenderSimpleMesh(meshes["banda_stE"], shaders["EnemyShader"], modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f), enemy->hp);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, enemy->position);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
        modelMatrix *= RotateOY(enemy->angle);
        RenderSimpleMesh(meshes["roti_drE"], shaders["EnemyShader"], modelMatrix, glm::vec3(0.1f), enemy->hp);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, enemy->position);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
        modelMatrix *= RotateOY(enemy->angle);
        RenderSimpleMesh(meshes["roti_stE"], shaders["EnemyShader"], modelMatrix, glm::vec3(0.1f), enemy->hp);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, enemy->position);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
        modelMatrix *= RotateOY(enemy->turela->angle);
        modelMatrix *= RotateOY(enemy->angle);
        RenderSimpleMesh(meshes["tunE"], shaders["EnemyShader"], modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f), enemy->hp);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, enemy->position);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
        modelMatrix *= RotateOY(enemy->turela->angle);
        modelMatrix *= RotateOY(enemy->angle);
        RenderSimpleMesh(meshes["turelaE"], shaders["EnemyShader"], modelMatrix, glm::vec3(glm::vec3(0, 0.1f, 0)), enemy->hp);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, enemy->position);
        modelMatrix *= RotateOY(enemy->angle);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
        RenderSimpleMesh(meshes["corpE"], shaders["EnemyShader"], modelMatrix, glm::vec3(0.5f, 0.5f, 0.0f), enemy->hp);
    }
}

void Tema2::CreateEnemies(float deltaTimeSeconds) {
    intervalEnemySpawn += deltaTimeSeconds;

    if (intervalEnemySpawn >= 10) {
        EnemyTank* enemy = new EnemyTank();
        enemy->bullets = bullets;
        enemy->CreateRandomPosition();
        enemies.push_back(enemy);
        intervalEnemySpawn = 0.f;
    }
}

void Tema2::DrawScene() {
    // ground
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.01f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1.2f));
        RenderSimpleMesh(meshes["plane"], shaders["ObjectsShader"], modelMatrix, glm::vec3(0.2f, 0.8f, 0));
    }

    //buildings
    int i = 0;
    for (auto& building : buildings) {
        std::string id = std::to_string(i);
        const char* id_cstr = id.c_str();
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, building->position + glm::vec3(0, 0, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.8f));
        RenderSimpleMesh(meshes[id_cstr], shaders["ObjectsShader"], modelMatrix, glm::vec3(0.6f, 0.6f, 0.6f));
        i++;
    }
}

void Tema2::FrameEnd()
{
}


void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, int hp)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = camera->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    int object_col = glGetUniformLocation(shader->program, "object_color");
    glUniform3fv(object_col, 1, glm::value_ptr(color));

    int loc_hp = glGetUniformLocation(shader->program, "enemy_hp");
    glUniform1f(loc_hp, hp); 

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */

void Tema2::OnInputUpdate(float deltaTime, int mods) {
    float cameraSpeed = 3.0f;

    if (window->KeyHold(GLFW_KEY_W)) {
        camera->MoveForward(deltaTime * cameraSpeed, player);
        player->MoveForward(deltaTime * cameraSpeed);
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        player->RotateRight(deltaTime * cameraSpeed * 0.5f);
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        camera->MoveForward(-deltaTime * cameraSpeed, player);
        player->MoveForward(-deltaTime * cameraSpeed);
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        player->RotateRight(-deltaTime * cameraSpeed * 0.5f);
    }
}


void Tema2::OnKeyPress(int key, int mods)
{
 
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            renderCameraTarget = true;
            // TODO(student): Rotate the camera in third-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateThirdPerson_OX(deltaX * sensivityOX);
            camera->RotateThirdPerson_OY(deltaY * sensivityOY);
        }
    }
    else {
        player->turela->RotateRight(-deltaX * 0.0003);
    }
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (button == 1) {
        player->Fire(bullets);
    }
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    const int fovMin = 30;
    const int fovMax = 120;

    if (offsetY < 0) {
        // Zoom in
        fov += 5;
    }
    else {
        // Zoom out
        fov -= 5;
    }
    if (fov < fovMin) {
        fov = fovMin;
    }
    else if (fov > fovMax) {
        fov = fovMax;
    }
}



void Tema2::OnWindowResize(int width, int height)
{
}
