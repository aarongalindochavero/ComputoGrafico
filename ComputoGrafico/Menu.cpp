#include "Menu.h"
#include<iostream>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

bool activeR = true;
bool activeG = false;
bool activeB = false;

void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

Menu::Menu()
{

}

Menu::~Menu()
{
}

void Menu::Init()
{
	std::cout << " Menu Init" << std::endl;
	this->platform = Platform::GetPtr();
	this->manager = GameStateManager::GetPtr();
	camera = Camera(glm::vec3(0, 0, 0.6f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 55.0f, 0.1f);
	shaderManager = ShaderManager::getPtr();
	shaderManager->initShader(&camera);
	shaderManager->LoadShaders("OneColor", "Assets/Shaders/OneColor.vert", "Assets/Shaders/OneColor.frag");
	shaderManager->LoadShaders("OneColorG", "Assets/Shaders/OneColorG.vert", "Assets/Shaders/OneColorG.frag");
	shaderManager->LoadShaders("OneColorB", "Assets/Shaders/OneColorB.vert", "Assets/Shaders/OneColorB.frag");
	shaderManager->LoadShaders("gouraud-shader", "Assets/Shaders/gouraud-shader.vert", "Assets/Shaders/gouraud-shader.frag");
	shaderManager->LoadShaders("phong-shader", "Assets/Shaders/phong-shader.vert", "Assets/Shaders/phong-shader.frag");//compila el shader y enlaza
	shaderManager->LoadShaders("distance-color", "Assets/Shaders/distance-color.vert", "Assets/Shaders/distance-color.frag");
	shaderManager->LoadShaders("toon-shader", "Assets/Shaders/toon-shader.vert", "Assets/Shaders/toon-shader.frag");
	LoadModels();
	
}

void Menu::LoadModels()
{
	unsigned int indices[] = {
				0,1,2,
				2,3,0,
				0,4,3,
				4,7,3,
				3,7,6,
				6,3,2
	};

	GLfloat vertices[] = {
		// front
		-1.0, -1.0,  1.0, 0.0f, 0.0f,		0.0f, 0.0f, 0.8f,1.0f, 0.0f, 0.0f,//0
		1.0, -1.0,  1.0,1.0f, 0.0f,		0.0f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,//1
		1.0,  1.0,  1.0,0.0f, 1.0f,		0.0f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,//2
		-1.0,  1.0,  1.0,1.0f, 0.0f,		0.0f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,//3
		// back
		-1.0, -1.0, -1.0,1.0f, 1.0f,		0.0f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,//4
		1.0, -1.0, -1.0,1.0f, 0.0f,		0.0f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,//5
		1.0,  1.0, -1.0,1.0f, 1.0f,		0.0f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,//6
		-1.0,  1.0, -1.0,0.0f, 1.0f,		0.7f, -0.7f, 0.0f,1.0f, 0.0f, 0.0f,//7
	};
	calcAverageNormals(indices, 18, vertices, 88, 11, 5);
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 88, 18, 11);
	meshList.push_back(obj1);
}
void Menu::LoadShaders()
{
	
}

void Menu::Draw()
{
	platform->RenderClear();
	/*if (camera.getShaderChange()) {
		shaderManager->Activate("phong-shader");
	}
	else {
		shaderManager->Activate("gouraud-shader");
	}
	shaderManager->draw();*/
	glm::mat4 model(1);
	GLint uniformModel = shaderManager->GetModelLocation();
	/*model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	meshList[0]->RenderMesh();*/


	//shaderManager->Activate("OneColor-shader");
	if (activeR == true)
	{
		shaderManager->Activate("OneColor");
	}
	if (activeG == true)
	{
		shaderManager->Activate("OneColorG");
	}
	if (activeB == true)
	{
		shaderManager->Activate("OneColorB");
	}
	shaderManager->draw();
	uniformModel = shaderManager->GetModelLocation();
	GLint color1 = shaderManager->GetColor1();
	GLint color2 = shaderManager->GetColor2();
	GLint playerPos = shaderManager->GetPlayerPos();
	GLint lightDir = shaderManager->GetLightDir();
	model = glm::translate(model, glm::vec3(10.0f, 0.0f, -8.5f));
	model = glm::scale(model, glm::vec3(0.7f, 0.4f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	glUniform3f(playerPos, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);//le mandas la variable al shader
	glUniform3f(lightDir, 0.11, 0.61, 61);
	//glUniform3f(lightDir, rand(), rand(), rand());
	meshList[0]->RenderMesh();

	platform->RenderPresent();
}
bool Menu::MouseInput(int x, int y, bool leftbutton)
{
	if (x != -1 || y != -1)
		camera.mouseControl(x, y);

	return false;
}

bool Menu::Input(std::map<int, bool> keys)
{
	camera.keyControl(keys, platform->GetDeltaTime());
	if (keys[GLFW_KEY_R])
	{
		activeR = true;
		activeG = false;
		activeB = false;
	}
	if (keys[GLFW_KEY_G])
	{
		activeG = true;
		activeR = false;
		activeB = false;
	}
	if (keys[GLFW_KEY_B])
	{
		activeB = true;
		activeG = false;
		activeR = false;
	}
	return false;
}


void Menu::Update()
{
}

void Menu::Close()
{
	std::cout << " Close Init" << std::endl;
}