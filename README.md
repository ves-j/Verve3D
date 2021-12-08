# Verve
This is my first attempt at making a 3D rendering engine usgin OpenGL 3.3, GLFW and ImGui. </br>
There are two branches for this project:
<ul>
  <li>Main</li>
    <ul>
    <li>Importing GLTF models from JSON file</li>
    </ul> 
  <li>Assimp</li>
  <ul>
    <li>Importing modern model formats using Assimp library</li>
    </ul> 
</ul> 

<h2>TODO:</h2>
<ul>
  <li>Model importer - DONE</li>
  <li>Post-processing stuff - OnGoing</li>
  <li>Scene graph</li>
  <li>PBR</li>
  <li>Physics stuff</li>
</ul> 

<h2>HOW TO BUILD: (Visual Studio verison)</h2>
<ol>
  <li>Clone the repository</li>
  <li>Go to project property</li>
  <li>VC++ Direcories -> Locate Include Direcories and Library Directories</li>
  <li>Linker -> Input -> Additional dependencies -> Type in the additional libraries *This usually not needed when cloning the project but just in case if it's missing</li>
</ol> 
<h3>Warning:</h3> sometimes visual studio can't locate glad.h even though it is in the directory, to fix that, simply right click on glad.h and "Exclude form project", then remove glad.h from project folder and include it again(just copy glad.h from C++ Libraries into project folder and then drag it inside visual studio)</h3>
