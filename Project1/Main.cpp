//------- Ignore this ----------
#include<filesystem>
namespace fs = std::filesystem;
//------------------------------

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>
#include <Windows.h>
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

// Vertices coordinates      -z is back and +z is front
Vertex vertices[] =
{ //     COORDINATES							NORMALS							COLORS						TEXTURE UV	
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
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
	Vertex{glm::vec3( 0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3( 0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3( 0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3( 0.1f,  0.1f,  0.1f)}
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

//std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
std::wstring src;
std::string modelPath = "Model/jinx/scene.gltf";
OPENFILENAME ofn;       // common dialog box structure
char szFile[_MAX_PATH] = "";       // buffer for file name
HWND hwnd = NULL;              // owner window
HANDLE hf;              // file handle


void FileOpen()
{
	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = (LPWSTR)szFile;
	//
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	//
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = TEXT("All\0*.*\0*gltf\0*.gltf\0");
	
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;

	// Display the Open dialog box. 

	if (GetOpenFileName(&ofn) == TRUE)
	{
		//hf = CreateFile(ofn.lpstrFile, GENERIC_READ,0, (LPSECURITY_ATTRIBUTES)NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,(HANDLE)NULL);
		MessageBox(NULL, ofn.lpstrFile, (LPWSTR)"File Name", MB_OK);
		modelPath = szFile;

		
		std::cout << szFile << std::endl;
		//Model model((modelPath).c_str());
	}

};



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


	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Verve (x64) - Lighting test", NULL, NULL);

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
	// Store mesh data in vectors for the mesh
	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
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
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);	// this is mesh colour
	// light and cube position
	glm::vec3 lightPos = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 cubePos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 cubeModel = glm::mat4(1.0f);
	cubeModel = glm::translate(cubeModel, cubePos);

	glm::vec3 basePos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 baseModel = glm::mat4(1.0f);
	baseModel = glm::translate(baseModel, basePos);



	// Activating light shader program and cube shader program
	lightShader.Activate();
	glUniformMatrix4fv(glad_glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glad_glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	shaderProgram.Activate();
	glUniformMatrix4fv(glad_glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(cubeModel));
	glUniform4f(glad_glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glad_glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	basePlaneShader.Activate();
	glUniformMatrix4fv(glad_glGetUniformLocation(basePlaneShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(baseModel));
	glUniform4f(glad_glGetUniformLocation(basePlaneShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	

	// TEXTURES STUFF (WIDTH, HEIGHT, COLOUR CHANNEL)
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);


	// to invert texture as STB reads X and Y differently from GLFW
	glEnable(GL_DEPTH_TEST);

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


	// Imgui variables and uniforms for shaders
	bool drawCube = true;
	float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };	// this is mesh colour
	float size = 0.05f;
	float px = 0.0f;
	float py = 0.0f;
	float pz = 0.0f;
	bool textureBool = false;
	int textureOn = 1;
	bool wireframeMode = false;

	// camera variables
	float field_of_view = 45.0f;
	float near_plane = 0.1f;
	float far_plane = 100.0f;


	// sending data to uniforms in shaders
	glUniform4f(glad_glGetUniformLocation(shaderProgram.ID, "meshCol"), color[0], color[1], color[2], color[3]);
	glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "size"), size);
	glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "px"), px);
	glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "py"), py);
	glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "pz"), pz);
	glUniform1i(glad_glGetUniformLocation(shaderProgram.ID, "textureOn"), textureOn);


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


	//combo box variables
	const char* items[] = { "Point", "Directional", "Spot" };
	static const char* current_item = "Point";
	int lightType = 0;


	

	// Load in a model
	Model model((modelPath).c_str());

	

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);


		// Bind the custom framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		// Specify the color of the background
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Enable depth testing since it's disabled when drawing the framebuffer rectangle
		glEnable(GL_DEPTH_TEST);

		// Camera input handleing
		camera.Inputs(window);

		// Sending view and projection to shader
		camera.updateMatrix(field_of_view, near_plane, far_plane);
		

		// if drawCube is true draw the cube
		if (drawCube)
		{
			// Draw primitives, number of indices, datatype of indices, index of indices
			//floor.Draw(shaderProgram, camera);
			model.Draw(shaderProgram, camera);
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
		// Draw a model
		

		// sending data to uniforms in shaders
		glUniform4f(glad_glGetUniformLocation(shaderProgram.ID, "meshCol"), color[0], color[1], color[2], color[3]);
		glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "size"), size);
		glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "px"), px);
		glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "py"), py);
		glUniform1f(glad_glGetUniformLocation(shaderProgram.ID, "pz"), pz);
		glUniform1i(glad_glGetUniformLocation(shaderProgram.ID, "textureOn"), textureOn);
		glUniform1i(glad_glGetUniformLocation(shaderProgram.ID, "lightType"), lightType);

		// draw the base plane
		grid.DrawGrid(basePlaneShader, camera);

		// Activate light shader program inside the main loop and draw the light source
		lightMesh.DrawLight(lightShader, camera);

		// light colour
		glUniform4f(glad_glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform4f(glad_glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform4f(glad_glGetUniformLocation(basePlaneShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

		// wireframe mode on/off
		if (!wireframeMode)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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

		

		// Bind the default framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST); // prevents framebuffer rectangle from being discarded
		glBindTexture(GL_TEXTURE_2D, framebufferTexture);

		

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
				if (ImGui::MenuItem("Open")) { FileOpen(); }
				if (ImGui::MenuItem("Exit")) { glfwSetWindowShouldClose(window, true); }
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		// ImGui contents (docking)
		ImGui::Begin("Attributes");													// imgui begin and title

		ImGui::Checkbox("Draw Cube", &drawCube);									// draw cube

		if (drawCube)
		{
			ImGui::SameLine();															// draw the next component on the same line and previous
			ImGui::Checkbox("Texture", &textureBool);									// enable texture
			ImGui::SameLine();															// draw the next component on the same line and previous
			ImGui::Checkbox("Wireframe Mode", &wireframeMode);							// enable wireframe mode
			ImGui::ColorEdit4("Color", color);											// change colour
			//ImGui::ColorEdit4("Light color", lightColor);								// change light colour
			ImGui::SliderFloat("Size", &size, 0.0f, 10.0f);								// change size
			ImGui::SliderFloat("Position X", &px, -50.0f, 50.0f);							// change position X
			ImGui::SliderFloat("Position Y", &py, -50.0f, 50.0f);							// change position Y
			ImGui::SliderFloat("Position Z", &pz, -50.0f, 50.0f);							// change position Z
			ImGui::SliderFloat("Field of view", &field_of_view, 10.0f, 100.0f);			// field of view slider
			ImGui::SliderFloat("Near plane", &near_plane, 0.0f, 1000.0f);				// distance where objects appear
			ImGui::SliderFloat("Far plane", &far_plane, 0.0f, 1000.0f);					// distance where objects disappear


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
			
		}

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

		ImGui::End();


		//ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


		ImGui::Render();


		glClearColor(0.160f, 0.160f, 0.160f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Enable depth testing since it's disabled when drawing the framebuffer rectangle
		glEnable(GL_DEPTH_TEST);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());



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
	shaderProgram.Delete();
	basePlaneShader.Delete();
	lightShader.Delete();

	glDeleteFramebuffers(1, &FBO);

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