//------- Ignore this ----------
#include<filesystem>
namespace fs = std::filesystem;
//------------------------------


#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>
#include <imfilebrowser/imfilebrowser.h>
#include <algorithm>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include"Mesh.h"
#include"Model.h"



/*
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5 f, 5.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};
*/


//width and height of the escreen
const GLuint SCR_WIDTH = 1600;
const GLuint SCR_HEIGHT = 900;

unsigned int samples = 8;

float rectangleVertices[] =
{
	//  Coords   // texCoords
	 1.0f, -1.0f,  1.0f, 0.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	-1.0f,  1.0f,  0.0f, 1.0f,

	 1.0f,  1.0f,  1.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	-1.0f,  1.0f,  0.0f, 1.0f
};

// Vertices coordinates      -z is back and +z is front
Vertex vertices[] =
{ //     COORDINATES							NORMALS							COLORS						TEXTURE UV	
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
};

// Base plane grid
Vertex baseVertices[] =
{
	// Up to down			
	Vertex{glm::vec3(-4.0f,  0.0f, -4.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(-4.0f,  0.0f,  4.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(-3.0f,  0.0f, -4.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(-3.0f,  0.0f,  4.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(-2.0f,  0.0f, -4.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(-2.0f,  0.0f,  4.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(-1.0f,  0.0f, -4.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(-1.0f,  0.0f,  4.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3( 0.0f,  0.0f, -4.0f), glm::vec3(0.0f, 0.0f, 1.0f)},// middle line = Z axis
	Vertex{glm::vec3( 0.0f,  0.0f,  4.0f), glm::vec3(0.0f, 0.0f, 1.0f)},// middle line = Z axis
	Vertex{glm::vec3( 1.0f,  0.0f, -4.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f,  0.0f,  4.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3( 2.0f,  0.0f, -4.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3( 2.0f,  0.0f,  4.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3( 3.0f,  0.0f, -4.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3( 3.0f,  0.0f,  4.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3( 4.0f,  0.0f, -4.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3( 4.0f,  0.0f,  4.0f), glm::vec3(1.0f, 1.0f, 1.0f)},

	// Left to right
	Vertex{glm::vec3(-4.0f,  0.0f, -4.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3( 4.0f,  0.0f, -4.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(-4.0f,  0.0f, -3.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3( 4.0f,  0.0f, -3.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(-4.0f,  0.0f, -2.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3( 4.0f,  0.0f, -2.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(-4.0f,  0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3( 4.0f,  0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(-4.0f,  0.0f,  0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},// middle line = x axis
	Vertex{glm::vec3( 4.0f,  0.0f,  0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},// middle line = x axis
	Vertex{glm::vec3(-4.0f,  0.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3( 4.0f,  0.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(-4.0f,  0.0f,  2.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3( 4.0f,  0.0f,  2.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(-4.0f,  0.0f,  3.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3( 4.0f,  0.0f,  3.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(-4.0f,  0.0f,  4.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3( 4.0f,  0.0f,  4.0f), glm::vec3(1.0f, 1.0f, 1.0f)},

	// Y axis line
	//0.0f,  4.0f,  0.0f,		0.0f, 1.0f, 0.0f, // middle line = Y axis
	//0.0f, -4.0f,  0.0f,		0.0f, 1.0f, 0.0f, // middle line = Y axis

};

GLuint baseIndices[] =
{
	0, 1,
	2, 3,
	4, 5,
	6, 7,
	8, 9,
	10, 11,
	12, 13,
	14, 15,
	16, 17,
	18, 19,
	20, 21,
	22, 23,
	24, 25,
	26, 27,
	28, 29,
	30, 31,
	32, 33,
	34, 35,
	//36, 37
};

// light source vertices and indices
Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


// cubemap vert
float skyboxVertices[] =
{
	//   Coordinates
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f
};

// cubemap ind
unsigned int skyboxIndices[] =
{
	// Right
	1, 2, 6,
	6, 5, 1,
	// Left
	0, 4, 7,
	7, 3, 0,
	// Top
	4, 5, 6,
	6, 7, 4,
	// Bottom
	0, 3, 2,
	2, 1, 0,
	// Back
	0, 1, 5,
	5, 4, 0,
	// Front
	3, 7, 6,
	6, 2, 3
};

// create a file browser instance
ImGui::FileBrowser fileDialog;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// MAIN FUNCTION
int main()
{
	// Initialize GLFW
	glfwInit();


	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Create a GLFWwindow object
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Verve (x64) Debug - Post-Processing test", NULL, NULL);

	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Load GLAD so it configures OpenGL
	gladLoadGL();


	/*Texture textures[]
	{
		Texture("planks.png", "diffuse", 0),
		Texture("planksSpec.png", "specular", 1)
	};*/

	// Generates Shader object using shaders defualt.vert and default.frag + light
	Shader shaderProgram("default.vert", "default.frag");
	Shader outliningProgram("outlining.vert", "outlining.frag");
	Shader skyboxShader("skybox.vert", "skybox.frag");
	Shader framebufferProgram("framebuffer.vert", "framebuffer.frag");
	// Store mesh data in vectors for the mesh
	//std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	//std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	//std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	// Create floor mesh
	//Mesh floor(verts, ind, tex);

	// grid VAO, VBO, EBO
	Shader basePlaneShader("base.vert", "base.frag");
	std::vector <Vertex> BaseVerts(baseVertices, baseVertices + sizeof(baseVertices) / sizeof(Vertex));
	std::vector <GLuint> BaseInds(baseIndices, baseIndices + sizeof(baseIndices) / sizeof(GLuint));
	Mesh grid(BaseVerts, BaseInds);


	// LIGHT VAO, VBO, EBO
	Shader lightShader("light.vert", "light.frag");
	std::vector <Vertex> LightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> LightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	Mesh lightMesh(LightVerts, LightInd);


	// Light color
	//glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);	// this is mesh colour
	float	  lightColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };	// this is mesh colour
	// light and cube position

	float lx = 0.0f;
	float ly = 0.0f;
	float lz = 0.0f;
	glm::vec3 lightPos = glm::vec3(lx, ly, lz);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 cubePos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 cubeModel = glm::mat4(1.0f);
	cubeModel = glm::translate(cubeModel, cubePos);

	glm::vec3 basePos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 baseModel = glm::mat4(1.0f);
	baseModel = glm::translate(baseModel, basePos);


	// gamma correction value
	float gamma = 2.2f;

	// Activating light shader program and model shader program
	lightShader.Activate();
	glUniformMatrix4fv(glad_glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glad_glGetUniformLocation(lightShader.ID, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);

	shaderProgram.Activate();
	glUniformMatrix4fv(glad_glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(cubeModel));
	glUniform4f(glad_glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
	glUniform3f(glad_glGetUniformLocation(shaderProgram.ID, "lightPos"), lx, ly, lz);

	basePlaneShader.Activate();
	glUniformMatrix4fv(glad_glGetUniformLocation(basePlaneShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(baseModel));
	glUniform4f(glad_glGetUniformLocation(basePlaneShader.ID, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);

	skyboxShader.Activate();
	glUniform1i(glGetUniformLocation(skyboxShader.ID, "skybox"), 0);

	framebufferProgram.Activate();
	glUniform1i(glGetUniformLocation(framebufferProgram.ID, "screenTexture"), 0);
	glUniform1f(glGetUniformLocation(framebufferProgram.ID, "gamma"), gamma);

	


	// TEXTURES STUFF (WIDTH, HEIGHT, COLOUR CHANNEL)
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);


	// to invert texture as STB reads X and Y differently from GLFW
	glEnable(GL_DEPTH_TEST);


	// enabling stencil buffer for object outlining
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	// Camera object for viewign the model
	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 1.0f, 5.0f));

	
	// IMGUI STUFF
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

	ImGui::StyleColorsLight();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	auto& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.08f, 0.50f, 0.72f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
	style.Colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.33f, 0.34f, 0.36f, 0.83f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.23f, 0.23f, 0.24f, 1.00f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
	style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	style.GrabRounding = style.FrameRounding = 2.3f;


	// (optional) set browser properties
	fileDialog.SetTitle("title");
	fileDialog.SetTypeFilters({ ".*", ".gltf" });


	

	// Imgui variables and uniforms for shaders
	bool	drawCube = false;
	bool	modelOutline = false;
	float	color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };	// this is mesh colour
	float	size = 0.05f;
	bool	normalLoaded = false;
	float	outliningWidth = 0.1f;
	std::string normalPath = "";
	Texture* normalMap;
	normalMap = new Texture((normalPath).c_str(), "normal", 1);

	//position
	float	px = 0.0f;
	float	py = 0.0f;
	float	pz = 0.0f;
	
	// rotation
	float	rx = 0.0f;
	float	ry = 0.0f;
	float	rz = 0.0f;
		    

	//light
	bool	gammaCorrection = false;
	bool	hideLight = false;
	bool	blinn = true;
	int		blinnOn = 1;
	float	amb  = 0.5f;
	float	spec = 0.5f;
	int		specAmount = 16;
	float	outerCone = 0.90f;

	int		normalLoadedUniform = 0;	// checking if normal texture is loaded and sending in shader
	bool	textureBool = false;
	int		textureOn = 1;
	bool	wireframeMode = false;

	

	//combo box variables***
	const char* items[] = { "Point", "Directional", "Spot" };
	static const char* current_item = "Point";
	int lightType = 0;


	// post processing
	const char* renderItems[] = { "None", "Inverse", "Gray", "Blur", "Sharpen", "Emboss", "Outline"};
	static const char* current_renderItem = "None";
	int		option = 0;
	//bool	postFBO = false;
	//bool	inverseColour = false;
	//int		option = 1;

	// camera variables
	bool	drawSkybox = true;
	bool	drawGrid = true;
	float	backColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };	// this is mesh colour
	float	field_of_view = 45.0f;
	float	near_plane = 0.1f;
	float	far_plane = 100.0f;
	bool	faceCull = false;


	// sending data to uniforms in shaders
	glUniform4f(glad_glGetUniformLocation(shaderProgram.ID, "meshCol"), color[0], color[1], color[2], color[3]);
	glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "size"), size);
	glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "px"), px);
	glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "py"), py);
	glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "pz"), pz);
	

	// sending the normal texture to the fragment shader
	if (normalLoaded)
	{
		normalMap = new Texture((normalPath).c_str(), "normal", 1);
		normalMap->Bind();
		glUniform1i(glad_glGetUniformLocation(shaderProgram.ID, "normal0"), 1);
	}

	glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "rx"), rx);
	glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "ry"), ry);
	glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "rz"), rz);

	glUniform4f(glad_glGetUniformLocation(lightShader.ID, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
	glUniform4f(glad_glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
	glUniform4f(glad_glGetUniformLocation(basePlaneShader.ID, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
	glUniform1f(glad_glGetUniformLocation(lightShader.ID, "lx"), lx);
	glUniform1f(glad_glGetUniformLocation(lightShader.ID, "ly"), ly);
	glUniform1f(glad_glGetUniformLocation(lightShader.ID, "lz"), lz);
	glUniform3f(glad_glGetUniformLocation(shaderProgram.ID, "lightPos"), lx, ly, lz);


	glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "amb"), amb);
	glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "specLight"), spec);
	glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "outerConeM"), outerCone);
	glUniform1i(glad_glGetUniformLocation(shaderProgram.ID, "spPower"), specAmount);
	glUniform1i(glad_glGetUniformLocation(shaderProgram.ID, "blinn"), blinnOn);

	glUniform1i(glad_glGetUniformLocation(shaderProgram.ID, "textureOn"), textureOn);
	glUniform1i(glad_glGetUniformLocation(shaderProgram.ID, "normalLoaded"), normalLoadedUniform);

	glUniform1i(glad_glGetUniformLocation(framebufferProgram.ID, "option"), option);




	// MODEL LOADING
	//std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string modelPath = "Model/test/scene.gltf";

	//Model model((modelPath).c_str());
	// model object
	Model* model;
	model = new Model((modelPath).c_str());

	// Create VAO, VBO, and EBO for the skybox
	unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glGenBuffers(1, &skyboxEBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// All the faces of the cubemap (make sure they are in this exact order)
	std::string facesCubemap[6] =
	{
		"Skybox/right.jpg",
		"Skybox/left.jpg",
		"Skybox/top.jpg",
		"Skybox/bottom.jpg",
		"Skybox/front.jpg",
		"Skybox/back.jpg"
	};

	// Creates the cubemap texture object
	unsigned int cubemapTexture;
	glGenTextures(1, &cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// These are very important to prevent seams
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	// This might help with seams on some systems
	//glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	// Cycles through all the textures and attaches them to the cubemap object
	for (unsigned int i = 0; i < 6; i++)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load texture: " << facesCubemap[i] << std::endl;
			stbi_image_free(data);
		}
	}

	// Prepare framebuffer rectangle VBO and VAO
	unsigned int rectVAO, rectVBO;
	glGenVertexArrays(1, &rectVAO);
	glGenBuffers(1, &rectVBO);
	glBindVertexArray(rectVAO);
	glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	

	// Create Frame Buffer Object
	unsigned int FBO;
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	// Create Framebuffer Texture
	unsigned int framebufferTexture;
	glGenTextures(1, &framebufferTexture);
	glBindTexture(GL_TEXTURE_2D, framebufferTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTexture, 0);

	// Create Render Buffer Object
	unsigned int RBO;
	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	// Error checking framebuffer
	auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer error: " << fboStatus << std::endl;


	// Create Frame Buffer Object for POST PROCESSING
	unsigned int postProcessingFBO;
	glGenFramebuffers(1, &postProcessingFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, postProcessingFBO);
	
	// Create Framebuffer Texture
	unsigned int postProcessingTexture;
	glGenTextures(1, &postProcessingTexture);
	glBindTexture(GL_TEXTURE_2D, postProcessingTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, postProcessingTexture, 0);

	// Error checking framebuffer
	fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Post-Processing Framebuffer error: " << fboStatus << std::endl;


	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Variables to create periodic event for FPS displaying
	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	// Keeps track of the amount of frames in timeDiff
	unsigned int counter = 0;


	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		

		processInput(window);

		//if (modelPath != "")
		//{
		//	//Model model((modelPath).c_str());
		//	model1->Load((modelPath).c_str());
		//	modelPath = "";
		//}

		// Updates counter and times
		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		counter++;

		if (timeDiff >= 1.0 / 30.0)
		{
			// Creates new title
			std::string FPS = std::to_string((1.0 / timeDiff) * counter);
			std::string ms = std::to_string((timeDiff / counter) * 1000);
			std::string newTitle = "Verve(x64) Debug - (Post-Processing test) " + FPS + "FPS";
			glfwSetWindowTitle(window, newTitle.c_str());

			// Resets times and counter
			prevTime = crntTime;
			counter = 0;

			// Use this if you have disabled VSync
			//camera.Inputs(window);
		}
		
		// Bind the custom framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);

		// Specify the color of the background
		glClearColor(pow(backColor[0], gamma), pow(backColor[1], gamma), pow(backColor[2], gamma), backColor[3]);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//framebufferProgram.Activate();
		glEnable(GL_DEPTH_TEST);

		glUniform1i(glad_glGetUniformLocation(framebufferProgram.ID, "option"), option);
		
		// Since the cubemap will always have a depth of 1.0, we need that equal sign so it doesn't get discarded
		glDepthFunc(GL_LEQUAL);

		

		skyboxShader.Activate();
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		// We make the mat4 into a mat3 and then a mat4 again in order to get rid of the last row and column
		// The last row and column affect the translation of the skybox (which we don't want to affect)
		view = glm::mat4(glm::mat3(glm::lookAt(camera.Position, camera.Position + camera.Orientation, camera.Up)));
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// Draws the cubemap as the last object so we can save a bit of performance by discarding all fragments
		// where an object is present (a depth of 1.0f will always fail against any object's depth value)
		if (drawSkybox)
		{
			glBindVertexArray(skyboxVAO);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		

		// Switch back to the normal depth function
		glDepthFunc(GL_LESS);

		// Camera input handleing
		camera.Inputs(window);

		// Sending view and projection to shader
		
		camera.updateMatrix(field_of_view, near_plane, far_plane);

		if (drawGrid)
		{
			// draw the base plane
			grid.DrawGrid(basePlaneShader, camera);
		}
		

		// Activate light shader program inside the main loop and draw the light source
		if (!hideLight)
		{
			lightMesh.DrawLight(lightShader, camera);
		}
		


		// sending light data to light shader for before model loading
		glUniform4f(glad_glGetUniformLocation(lightShader.ID, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
		glUniform4f(glad_glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
		glUniform4f(glad_glGetUniformLocation(basePlaneShader.ID, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
		glUniform1f(glad_glGetUniformLocation(lightShader.ID, "lx"), lx);
		glUniform1f(glad_glGetUniformLocation(lightShader.ID, "ly"), ly);
		glUniform1f(glad_glGetUniformLocation(lightShader.ID, "lz"), lz);
		glUniform3f(glad_glGetUniformLocation(shaderProgram.ID, "lightPos"), lx, ly, lz);
		glUniform1i(glad_glGetUniformLocation(shaderProgram.ID, "blinn"), blinnOn);
		

		

		if (blinn)
		{
			blinnOn = 1;
		}
		else
		{
			blinnOn = 0;
		}

		if (faceCull)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);
			glFrontFace(GL_CW);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}


		
		shaderProgram.Activate();

		if (normalLoaded)
		{
			normalMap->Bind();
			glUniform1i(glad_glGetUniformLocation(shaderProgram.ID, "normal0"), 1);
		}
		
		
		// if drawCube is true draw the cube
		if (drawCube)
		{
			
			
			// Draw primitives, number of indices, datatype of indices, index of indices
			//floor.Draw(shaderProgram, camera);

			// Make it so the stencil test always passes
			glStencilFunc(GL_ALWAYS, 1, 0xFF);

			// Enable modifying of the stencil buffer
			glStencilMask(0xFF);

			// Draw the normal model
			model->Draw(shaderProgram, camera);


			// Make it so only the pixels without the value 1 pass the test
			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);

			// Disable modifying of the stencil buffer
			glStencilMask(0x00);

			// Disable the depth buffer (can see the model through anything)
			//glDisable(GL_DEPTH_TEST);
	
		}
		

		// for texture on and off
		if (textureBool)
		{
			textureOn = 1;
		}
		else
		{
			textureOn = 0;
		}
		
		if (normalLoaded)
		{
			normalLoadedUniform = 1;
		}
		else
		{
			normalLoadedUniform = 0;
		}





		// sending data to uniforms in shaders

		// light colour
		glUniform4f(glad_glGetUniformLocation(lightShader.ID, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
		glUniform4f(glad_glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
		glUniform4f(glad_glGetUniformLocation(basePlaneShader.ID, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
		glUniform1f(glad_glGetUniformLocation(lightShader.ID, "lx"), lx);
		glUniform1f(glad_glGetUniformLocation(lightShader.ID, "ly"), ly);
		glUniform1f(glad_glGetUniformLocation(lightShader.ID, "lz"), lz);
		glUniform3f(glad_glGetUniformLocation(shaderProgram.ID, "lightPos"), lx, ly, lz);
		glUniform1i(glad_glGetUniformLocation(shaderProgram.ID, "blinn"), blinnOn);


		glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "amb"), amb);
		glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "specLight"), spec);
		glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "outerConeM"), outerCone);
		glUniform1i(glad_glGetUniformLocation(shaderProgram.ID, "spPower"), specAmount);
		glUniform1f(glad_glGetUniformLocation(framebufferProgram.ID, "gamma"), gamma);


		glUniform1i(glad_glGetUniformLocation(shaderProgram.ID, "normalLoaded"), normalLoadedUniform);
		glUniform1i(glad_glGetUniformLocation(shaderProgram.ID, "textureOn"), textureOn);
		glUniform1i(glad_glGetUniformLocation(shaderProgram.ID, "lightType"), lightType);


		glUniform4f(glad_glGetUniformLocation(shaderProgram.ID, "meshCol"), color[0], color[1], color[2], color[3]);
		glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "size"), size);
		glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "px"), px);
		glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "py"), py);
		glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "pz"), pz);

		glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "rx"), rx);
		glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "ry"), ry);
		glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "rz"), rz);

		glUniform1i(glad_glGetUniformLocation(framebufferProgram.ID, "option"), option);

		

		// model outlining should be at the very end of drawing process
		if (modelOutline)
		{
			outliningProgram.Activate();
			glUniform1f(glad_glGetUniformLocation(outliningProgram.ID, "outlining"), outliningWidth);
			glUniform1f(glad_glGetUniformLocation(outliningProgram.ID, "size"), size);
			glUniform1f(glad_glGetUniformLocation(outliningProgram.ID, "px"), px);
			glUniform1f(glad_glGetUniformLocation(outliningProgram.ID, "py"), py);
			glUniform1f(glad_glGetUniformLocation(outliningProgram.ID, "pz"), pz);

			glUniform1f(glad_glGetUniformLocation(outliningProgram.ID, "rx"), rx);
			glUniform1f(glad_glGetUniformLocation(outliningProgram.ID, "ry"), ry);
			glUniform1f(glad_glGetUniformLocation(outliningProgram.ID, "rz"), rz);

			model->Draw(outliningProgram, camera);
		}

		// wireframe mode on/off
		if (!wireframeMode)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		
		if (option != 0)
		{
			// Make it so the multisampling FBO is read while the post-processing FBO is drawn
			glBindFramebuffer(GL_READ_FRAMEBUFFER, FBO);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, postProcessingFBO);

		}
		else
		{
			// Bind the default framebuffer
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		


		if (gammaCorrection)
		{
			glEnable(GL_FRAMEBUFFER_SRGB);
		}
		else
		{
			glDisable(GL_FRAMEBUFFER_SRGB);
		}

		
		

		//Imgui frames
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		


		/* //Simple timer
		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.3f;
			prevTime = crntTime;
		}
		*/


		// Docking imgui
		static bool dockingSpaceOpen = true;

		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.

		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockingSpaceOpen, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}



		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open")) { fileDialog.Open(); }
				if (ImGui::MenuItem("Exit")) { glfwSetWindowShouldClose(window, true); }
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		fileDialog.Display();
		if (fileDialog.HasSelected())
		{
			std::cout << "Selected filename: " << fileDialog.GetSelected().string() << std::endl;

			// unload current model and normal map
			textureBool = false;
			drawCube = false;
			normalPath = "";
			normalMap->Unbind();
			glUniform1i(glad_glGetUniformLocation(shaderProgram.ID, "normal0"), 0);
			normalLoaded = false;

			size = 0.05f;

			px = 0.0f;
			py = 0.0f;
			pz = 0.0f;

			rx = 0.0f;
			ry = 0.0f;
			rz = 0.0f;

			// load new model path
			modelPath = fileDialog.GetSelected().string();
			std::cout << "Model path before edit: " << modelPath << std::endl;
			std::replace(modelPath.begin(), modelPath.end(), '\\', '/');
			std::cout << "Model path after edit: " << modelPath << std::endl;
			model = new Model((modelPath).c_str());
			drawCube = true;

			fileDialog.ClearSelected();
		}
		
		

		// ImGui contents (docking)
		ImGui::Begin("Attributes");													// imgui begin and title

		//ImGui::Checkbox("Draw Cube", &drawCube);									// draw cube
		

		if (drawCube)
		{
			//ImGui::SameLine();														// draw the next component on the same line and previous
			ImGui::Checkbox("Texture", &textureBool);									// enable texture														// draw the next component on the same line and previous
			ImGui::Checkbox("Wireframe Mode", &wireframeMode);							// enable wireframe mode
			ImGui::Checkbox("Model outline", &modelOutline);							// chnga model colour
			if (modelOutline)
			{
				ImGui::DragFloat("Outline width ", &outliningWidth, 0.01f, 0.0f, 1.0f);
			}
			ImGui::ColorEdit4("Color", color);											// change colour


			//ImGui::ColorEdit4("Light color", lightColor);								// change light colour


			// load normal map
			if (ImGui::Button("Load Normal Texture"))
			{
				fileDialog.Open();
			}


			fileDialog.Display();
			if (fileDialog.HasSelected())
			{
				std::cout << "Selected filename: " << fileDialog.GetSelected().string() << std::endl;

				// unload current model
				normalLoaded = false;
				drawCube = false;

				// load new normal path
				normalPath = fileDialog.GetSelected().string();
				std::cout << "\nNormal map path before edit: " << normalPath << std::endl;
				std::replace(normalPath.begin(), normalPath.end(), '\\', '/');
				std::cout << "Normal map path after edit: " << normalPath << std::endl;
				normalMap = new Texture((normalPath).c_str(), "normal", 1);
				normalMap->Bind();
				glUniform1i(glGetUniformLocation(shaderProgram.ID, "normal0"), 1);
				normalLoaded = true;
				drawCube = true;

				fileDialog.ClearSelected();
			}

			if (!normalPath.empty())
			{
				if (ImGui::Button("Delete Normal Texture"))
				{
					drawCube = false;
					normalPath = "";
					normalMap->Unbind();
					glUniform1i(glad_glGetUniformLocation(shaderProgram.ID, "normal0"), 0);
					normalLoaded = false;
					drawCube = true;
				}
			}

		}

		

		ImGui::Begin("Transformation");													// imgui begin and title
		if (drawCube)
		{
			ImGui::PushItemWidth(70);

			ImGui::Text("Scale");
			ImGui::DragFloat("Size", &size, 0.01f, 0.0f);								// change size

			ImGui::Text("Position");
			ImGui::DragFloat("X ", &px, 0.05f, 0.1f);									// change position X
			ImGui::SameLine();
			ImGui::DragFloat("Y ", &py, 0.05f, 0.1f);									// change position Y
			ImGui::SameLine();
			ImGui::DragFloat("Z ", &pz, 0.05f, 0.1f);									// change position Z

			ImGui::Text("Rotation");
			ImGui::DragFloat("RX", &rx, 0.05f, 0.1f);									// change position X
			ImGui::SameLine();
			ImGui::DragFloat("RY", &ry, 0.05f, 0.1f);									// change position Y
			ImGui::SameLine();
			ImGui::DragFloat("RZ", &rz, 0.05f, 0.1f);									// change position Z
	

			if (ImGui::Button("Default"))
			{
				size = 0.05f;

				px = 0.0f;
				py = 0.0f;
				pz = 0.0f;

				rx = 0.0f;
				ry = 0.0f;
				rz = 0.0f;
			}
		}

		

		//LIGHT
		ImGui::Begin("Light");															// imgui begin and title
		ImGui::Checkbox("Hide Light", &hideLight);
		ImGui::SameLine();
		ImGui::Checkbox("Blinn", &blinn);
		ImGui::SameLine();
		ImGui::Checkbox("Gamma Correction", &gammaCorrection);

		ImGui::ColorEdit4("Light Color", lightColor);									// change colour

		ImGui::PushItemWidth(70);

		ImGui::Text("Position");
		ImGui::DragFloat("LX ", &lx, 0.05f, 0.1f);										// change position X
		ImGui::SameLine();
		ImGui::DragFloat("LY ", &ly, 0.05f, 0.1f);										// change position Y
		ImGui::SameLine();
		ImGui::DragFloat("LZ ", &lz, 0.05f, 0.1f);										// change position Z


		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.60f);
		// Types of light combo box
		ImGuiComboFlags flags = ImGuiComboFlags_NoArrowButton;

		if (ImGui::BeginCombo("Light Type", current_item, ImGuiComboFlags_NoArrowButton))
		{
			for (int n = 0; n < IM_ARRAYSIZE(items); n++)
			{
				bool is_selected = (current_item == items[n]);
				if (ImGui::Selectable(items[n], is_selected))
					current_item = items[n];
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		if (current_item == "Directional")
		{
			lightType = 1;
		}
		else if (current_item == "Spot")
		{
			lightType = 2;
		}
		else
		{
			lightType = 0;
		}

		ImGui::DragFloat("Ambient", &amb, 0.1f, 0.1f);									// change ambient
		ImGui::DragFloat("Specular light", &spec, 0.1f, 0.1f);							// change specular light
		ImGui::DragInt("Specular amount", &specAmount, 2, 1, 512);						// change specular amount

		if (current_item == "Spot")
		{
			ImGui::DragFloat("Cone area", &outerCone, 0.1f, 0.1f);							// change cone area
		}

		if (ImGui::Button("Reset light values"))
		{
			lx = 0.0f;
			ly = 0.0f;
			lz = 0.0f;
			amb = 0.5f;
			spec = 0.5f;
			specAmount = 16;
			outerCone = 0.90f;

			//current_item = "Point";
			//lightType = 0;
		}

		//POST PROCESSING
		ImGui::Begin("Post-processing");
		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.60f);
		if (ImGui::BeginCombo("Render Mode", current_renderItem, ImGuiComboFlags_NoArrowButton))
		{
			for (int n = 0; n < IM_ARRAYSIZE(renderItems); n++)
			{
				bool is_selected = (current_renderItem == renderItems[n]);
				if (ImGui::Selectable(renderItems[n], is_selected))
					current_renderItem = renderItems[n];
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		if (current_renderItem == "Inverse")
		{
			option = 1;
		}
		else if (current_renderItem == "Gray")
		{
			option = 2;
		}
		else if (current_renderItem == "Blur")
		{
			option = 3;
		}
		else if (current_renderItem == "Sharpen")
		{
			option = 4;
		}
		else if (current_renderItem == "Emboss")
		{
			option = 5;
		}
		else if (current_renderItem == "Outline")
		{
			option = 6;
		}
		else
		{
			option = 0;
		}
		

		//CAMERA
		ImGui::Begin("Camera");													// imgui begin and title
		ImGui::Checkbox("Skybox", &drawSkybox);
		ImGui::SameLine();
		ImGui::Checkbox("Grid", &drawGrid);
		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.60f);
		ImGui::ColorEdit4("Background Color", backColor);									// change colour
		ImGui::SliderFloat("Field of view", &field_of_view, 10.0f, 100.0f);			// field of view slider
		ImGui::SliderFloat("Near plane", &near_plane, 0.0f, 1000.0f);				// distance where objects appear
		ImGui::SliderFloat("Far plane", &far_plane, 0.0f, 1000.0f);					// distance where objects disappear
		ImGui::Checkbox("Face Culling", &faceCull);

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		// SCENE VIEW *********************************
		ImGui::Begin("Scene");

		// get width andheight of the window
		int w;
		int h;
		glfwGetWindowSize(window, &w, &h);

		// camera.width and camera.height??? show the actual size of the object??? RESPONSIVEEEE???
		//ImVec2 wsize = ImGui::GetWindowSize(); // x and y

		ImGui::Image((void*)framebufferTexture, ImVec2(w / 1.1, h - 55), ImVec2(0, 1), ImVec2(1, 0));

		//std::cout << "Camera(" << camera.Position.x << ", " << camera.Position.y << ", " << camera.Position.z << ")" << std::endl;

		
		
		
		ImGui::End();

		ImGui::End();

		ImGui::End(); //attributes

		ImGui::End(); //scene viewport

		ImGui::End(); //transformation

		ImGui::End(); //light

		ImGui::End(); //camera


		//ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		

		ImGui::Render();

		

		
		glClearColor(pow(backColor[0], gamma), pow(backColor[1], gamma), pow(backColor[2], gamma), backColor[3]);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Enable depth testing since it's disabled when drawing the framebuffer rectangle
		glEnable(GL_DEPTH_TEST);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		// Enable modifying of the stencil buffer
		glStencilMask(0xFF);
		// Clear stencil buffer
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		// Enable the depth buffer
		glEnable(GL_DEPTH_TEST);

		
		if (option != 0)
		{
			// Bind the default framebuffer
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			// Draw the framebuffer rectangle
			framebufferProgram.Activate();
			glBindVertexArray(rectVAO);
			glDisable(GL_DEPTH_TEST); // prevents framebuffer rectangle from being discarded
			glBindTexture(GL_TEXTURE_2D, postProcessingTexture);
			glDrawArrays(GL_TRIANGLES, 0, 6);


			glUniform1i(glad_glGetUniformLocation(framebufferProgram.ID, "option"), option);
		}
		else
		{
			glDisable(GL_DEPTH_TEST); // prevents framebuffer rectangle from being discarded
			glBindTexture(GL_TEXTURE_2D, framebufferTexture);
		}

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);



		// Take care of all GLFW events (keys pressed/released, mouse moved etc.)
		glfwPollEvents();

	} // END OF WHILE LOOP

	// Delete all ImGui objects
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	

	// Delete all the objects we've created
	delete model;
	delete normalMap;
	shaderProgram.Delete();
	outliningProgram.Delete();
	framebufferProgram.Delete();
	basePlaneShader.Delete();
	lightShader.Delete();
	
	glDeleteFramebuffers(1, &FBO);
	glDeleteFramebuffers(1, &postProcessingFBO);
	

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;

}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
