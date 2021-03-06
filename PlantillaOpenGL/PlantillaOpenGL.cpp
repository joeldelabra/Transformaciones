// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;

float PosicionXTriangulo = 0.0f;
float PosicionYTriangulo = 0.0f;
float Angulo = 0.0f;
enum  Direccion { Izquierda, Derecha, Arriba, Abajo };
Direccion DireccionTriangulo = Direccion :: Izquierda;
Direccion DireccionVertical = Direccion::Arriba;



void dibujarTriangulo() {
	// Utilizar matriz identidad
	glPushMatrix();
	/*//Transformaciones
	glTranslatef(-0.25f, 0.0f, 0.0f);
	glScalef(0.2f, 0.2f, 0.2f);
	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);*/

	glTranslatef(PosicionXTriangulo, PosicionYTriangulo, 0);
	glRotatef(Angulo, 0.0f, 0.0f, 1.0f);

	//Dibujar los vertices
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 1.0f, 0.8f);
	glVertex3f(-0.4f, -0.4f, 0);
	glVertex3f(0.4f, -0.4f, 0);
	glVertex3f(0.0f, 0.4f, 0);

	glEnd();

	// soltar la matriz
	glPopMatrix();

}

void dibujar() {
	dibujarTriangulo();
}

void actualizar() {

	if (Angulo >= 360) {
		Angulo = 0.0f;
	}
	Angulo += 0.01f;


	if (DireccionTriangulo == Direccion::Izquierda) 
	{
		if (PosicionXTriangulo > -0.6f) {
			PosicionXTriangulo -= 0.001f;
		}
		else {
			DireccionTriangulo = Direccion::Derecha;
		}
	}
	if (DireccionTriangulo == Direccion::Derecha) {
		if (PosicionXTriangulo < 0.6f) 
		{
			PosicionXTriangulo += 0.001f;
		}
		else
		{
			DireccionTriangulo = Direccion::Izquierda;
		}
	}
	if (DireccionVertical == Direccion::Arriba)
	{
		if (PosicionYTriangulo > -0.6f) {
			PosicionYTriangulo -= 0.002f;
		}
		else {
			DireccionVertical = Direccion::Abajo;
		}
	}
	if (DireccionVertical == Direccion::Abajo) {
		if (PosicionYTriangulo < 0.6f)
		{
			PosicionYTriangulo += 0.002f;
		}
		else
		{
			DireccionVertical = Direccion::Arriba;
		}
	}
}

int main()
{
	//Creamos una ventana
	GLFWwindow *window;

	//Si no se puede inicializar glfw
	//Iniciamos ejecucion
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	//Si se pudo iniciar GLFW
	//entonces inicializamosla ventana
	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);
	//Si nopodemos iniciar la ventana
	//Entonces terminamos ejecucion
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//Establecemos el contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto activamos funciones modernas
	glewExperimental = true;
	GLenum errorGlew = glewInit();
	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

	//ciclode dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region de dibujo
		glViewport(0, 0, 1024, 768);
		//Establece el color de borrado
		glClearColor(0, 0.8, 1, 1);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		actualizar();
		dibujar();
		

		//Cambiar los buffers
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}