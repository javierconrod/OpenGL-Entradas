// PlantillaGraficos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;

//Declarar una ventana
GLFWwindow* window;

float posXTriangulo = 0.0f, posYTriangulo = 0.0f, velocidadTriangulo = 0.5;

double tiempoActual, tiempoAnterior;


void teclado_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if ((action == GLFW_PRESS || action == GLFW_REPEAT) && key==GLFW_KEY_RIGHT) {
		posXTriangulo += velocidadTriangulo;
	}
	if ((action == GLFW_PRESS || action == GLFW_REPEAT) && key == GLFW_KEY_LEFT) {
		posXTriangulo -= velocidadTriangulo;
	}
	if ((action == GLFW_PRESS || action == GLFW_REPEAT) && key == GLFW_KEY_UP) {
		posYTriangulo += velocidadTriangulo;
	}
	if ((action == GLFW_PRESS || action == GLFW_REPEAT) && key == GLFW_KEY_DOWN) {
		posYTriangulo -= velocidadTriangulo;
	}
}

void actualizar() {
	tiempoActual = glfwGetTime();
	double tiempoDiferencial = tiempoActual - tiempoAnterior;
	//Definir estados
	int estadoDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	int estadoIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	int estadoArriba = glfwGetKey(window, GLFW_KEY_UP);
	int estadoAbajo = glfwGetKey(window, GLFW_KEY_DOWN);
	int estadoShift = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);

	//Movimientos
	if (estadoShift == GLFW_PRESS) {
		velocidadTriangulo = 1.5;
	}
	else
		velocidadTriangulo = 0.5;
	if (estadoDerecha == GLFW_PRESS) {
		posXTriangulo += velocidadTriangulo * tiempoDiferencial;
	}
	if (estadoIzquierda == GLFW_PRESS) {
		posXTriangulo -= velocidadTriangulo * tiempoDiferencial;
	}
	if (estadoArriba == GLFW_PRESS) {
		posYTriangulo += velocidadTriangulo * tiempoDiferencial;
	}
	if (estadoAbajo == GLFW_PRESS) {
		posYTriangulo -= velocidadTriangulo * tiempoDiferencial;
	}
	
	tiempoAnterior = tiempoActual;
}

void dibujar() {
	glPushMatrix();

	glTranslatef(posXTriangulo, posYTriangulo, 0.0f);

	glBegin(GL_TRIANGLES);

	glColor3f(0.2f, 0.6f, 0.1f);

	glVertex3f(0.0f, 0.15f, 0.0f);
	glVertex3f(-0.15f, 0-.15f, 0.0f);
	glVertex3f(0.15f, -0.15f, 0.0f);

	glEnd();

	glPopMatrix();
}

int main()
{
	//Si no se pudo iniciar GLFW
	//Terminamos la ejecución
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	//Si se pudo iniciar GLFW
	//Inicializamos la ventana
	window = glfwCreateWindow(600, 600, "Ventana", NULL, NULL);

	//Si no se pudo crear la ventana
	//Terminamos la ejecución
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//Establecemos la ventana como contexto

	glfwMakeContextCurrent(window);

	//una vez establecido el contexto
	//se activan las funciones "modernas" (gpu)
	glewExperimental = true;

	GLenum errores = glewInit();
	if (errores != GLEW_OK) {
		glewGetErrorString(errores);
	}

	const GLubyte* versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

	//Establecemos que con cada evento de teclado se llama a la función teclado_callback
	//glfwSetKeyCallback(window, teclado_callback); 

	tiempoActual = glfwGetTime();
	tiempoAnterior = tiempoActual;

	//Ciclo de dibujo (DrawLoop)
	while (!glfwWindowShouldClose(window)) {

		//Establecer región de dibujo
		glViewport(00, 0, 600, 600);
		//Establecemos el color de borrado
		//Valores RGBA
		glClearColor(1, 1, 0.5, 1);
		//Borrar
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Actualizar valores y dibujar
		actualizar();
		dibujar();
		glfwPollEvents();
		glfwSwapBuffers(window);

	}
	//Después del ciclo de dibujo
	//Eliminamos ventana y procesos de GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

}