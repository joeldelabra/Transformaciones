// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;


void dibujarTriangulo() 
{
	glPushMatrix();
	glTranslated(-0.25f, 0.0f, 0.0f);
	glTranslated(0.25f, 0.0f, 0.0f);
	glScaled(0.2f, 0.2f, 0.2f);
	glRotatef(180.0f, 0.0f, 1.0f);

	glBegin(GL_TRIANGLES);
	glColor3f(0, 0.5, 0.5);
	glVertex3f(-0.4f,-0.4f,0);
	glVertex3f(0.4f, -0.4f, 0);
	glVertex3f(0.0f, 0.4f, 0);

	glEnd();
	glPopMatrix();


}

void dibujar() {

	dibujarTriangulo();
}



void actualizar() {

}


int main()
{
	GLFWwindow * window;

	//Si no se pudo iniciar glfw
	//entonces inicializamos en la ventana
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//Si se pudo iniciar GLFW
	//entonces inicializamos la ventana
	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);

	//Si no podemos iniciar la ventana
	//Entonces terminamos la ejecucion

	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Establecemos el contexto
	glfwMakeContextCurrent(window);
	// Una vez establecido el contexto activamos funciones modernas.
	glewExperimental = true;
	GLenum errorGlew = glewInit();
	
	if (errorGlew != GLEW_OK) 
	{
     	cout << glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

	

	//Ciclo de dibujo (Draw Loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region del dibujo
		glViewport(0, 0, 1024, 768);
		//Establecer el color del borrado
		glClearColor(0, 0.8, 1, 1);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		dibujar();
		actualizar();

		// Cambiar los buffer
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}