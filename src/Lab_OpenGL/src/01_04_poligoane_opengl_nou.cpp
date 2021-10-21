// Codul sursa este adaptat dupa OpenGLBook.com

#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h
#include "loadShaders.h"


//////////////////////////////////////

GLuint
VaoId,
VboId,
ColorBufferId,
ProgramId;


void CreateVBO(void)
{
    GLfloat Vertices[] = {
      0.020f * 2 - 1, 0.130f * 2 - 1, 0.0f, 1.0f,
      0.020f * 2 - 1, 0.310f * 2 - 1, 0.0f, 1.0f,
      0.140f * 2 - 1, 0.310f * 2 - 1, 0.0f, 1.0f,
      0.140f * 2 - 1, 0.130f * 2 - 1, 0.0f, 1.0f,

      0.000f * 2 - 1, 0.000f * 2 - 1, 0.0f, 1.0f,
      0.100f * 2 - 1, 0.010f * 2 - 1, 0.0f, 1.0f,
      0.200f * 2 - 1, 0.120f * 2 - 1, 0.0f, 1.0f,
      0.155f * 2 - 1, 0.290f * 2 - 1, 0.0f, 1.0f,

      0.250f * 2 - 1, 0.300f * 2 - 1, 0.0f, 1.0f,
      0.050f * 2 - 1, 0.300f * 2 - 1, 0.0f, 1.0f,
      0.200f * 2 - 1, 0.350f * 2 - 1, 0.0f, 1.0f,
      0.250f * 2 - 1, 0.500f * 2 - 1, 0.0f, 1.0f,
      0.350f * 2 - 1, 0.200f * 2 - 1, 0.0f, 1.0f,

      0.650f * 2 - 1, 0.300f * 2 - 1, 0.0f, 1.0f,
      0.450f * 2 - 1, 0.300f * 2 - 1, 0.0f, 1.0f,
      0.600f * 2 - 1, 0.350f * 2 - 1, 0.0f, 1.0f,
      0.650f * 2 - 1, 0.500f * 2 - 1, 0.0f, 1.0f,
      0.750f * 2 - 1, 0.200f * 2 - 1, 0.0f, 1.0f,
    };

    // culorile, ca atribute ale varfurilor
    GLfloat Colors[] = {
      0.0, 0.0, 1.0,0.0,
      0.0, 0.0, 1.0,0.0,
      0.0, 0.0, 1.0,0.0,
      0.0, 0.0, 1.0,0.0,

      1.0, 0.0, 0.0, 0.0,
      1.0, 0.0, 0.0, 0.0,
      1.0, 0.0, 0.0, 0.0,
      1.0, 0.0, 0.0, 0.0,

      1.0, 0.0, 0.25, 0.0,
      1.0, 0.0, 0.25, 0.0,
      1.0, 0.0, 0.25, 0.0,
      1.0, 0.0, 0.25, 0.0,
      1.0, 0.0, 0.25, 0.0,

      1.0, 0.75, 0.25, 0.0,
      1.0, 0.75, 0.25, 0.0,
      1.0, 0.75, 0.25, 0.0,
      1.0, 0.75, 0.25, 0.0,
      1.0, 0.75, 0.25, 0.0,
    };

    // se creeaza un buffer nou
    glGenBuffers(1, &VboId);
    // este setat ca buffer curent
    glBindBuffer(GL_ARRAY_BUFFER, VboId);
    // varfurile sunt "copiate" in bufferul curent
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

    // se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);
    // se activeaza lucrul cu atribute; atributul 0 = pozitie
    glEnableVertexAttribArray(0);
    // 
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    // un nou buffer, pentru culoare
    glGenBuffers(1, &ColorBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
    // atributul 1 =  culoare
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);


}
void DestroyVBO(void)
{


    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &ColorBufferId);
    glDeleteBuffers(1, &VboId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VaoId);


}

void CreateShaders(void)
{
    ProgramId = LoadShaders("02_01_Shader.vert", "02_01_Shader.frag");
    glUseProgram(ProgramId);
}
void DestroyShaders(void)
{
    glDeleteProgram(ProgramId);
}

void Initialize(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // culoarea de fond a ecranului
    CreateVBO();
    CreateShaders();
}
void RenderFunction(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(20.0);
    glLineWidth(25.0);
    // glEnable (GL_CULL_FACE); // cull face
     //glCullFace (GL_FRONT_AND_BACK);
    glDrawArrays(GL_POLYGON, 0, 4);
    glDrawArrays(GL_POLYGON, 4, 4);
    glDrawArrays(GL_TRIANGLE_FAN, 8, 5);
    glDrawArrays(GL_TRIANGLE_STRIP, 13, 5);
    glFlush();
}
void Cleanup(void)
{
    DestroyShaders();
    DestroyVBO();
}

int main(int argc, char* argv[])
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100); // pozitia initiala a ferestrei
    glutInitWindowSize(800, 600); //dimensiunile ferestrei
    glutCreateWindow("Doua primitive"); // titlul ferestrei
    glewInit(); // nu uitati de initializare glew; trebuie initializat inainte de a a initializa desenarea
    Initialize();
    glutDisplayFunc(RenderFunction);
    glutCloseFunc(Cleanup);
    glutMainLoop();


}

