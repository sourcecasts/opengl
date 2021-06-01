#include <windows.h>
#include <iostream>
#include <SDL2/SDL.h> // ���������� SDL 2
#include <GL/gl.h> // ���������� OpenGL
#include <GL/glu.h> // ���������� GLU

using namespace std;

SDL_Window *window; // ������ ���� ��� SDL

const int width = 640; // ������ ����
const int height = 480; // ������ ����

void drawCube(float xrf, float yrf, float zrf, float wrf);

void init(){

	// ������������� SDL

	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ){
	 	cout << "Unable to init SDL, error: " << SDL_GetError() << endl;
	 	exit(1);
	}

	// �������� ������� �����, ����������� �����

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);

	// ������� ���� � ���������� "Cube", �������� 640�480 � ������������� �� ������ ������.

	window = SDL_CreateWindow("Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	SDL_GLContext glcontext = SDL_GL_CreateContext(window); // ������� �������� OpenGL

	if(window == NULL){	// ���� �� ���������� ������� ����, �� �������
		exit(1);
	}

	// ������������� OpenGL

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // ������������� ������� ���� �� ������
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST); // �������� ���� �������
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float) width / (float) height, 0.1f, 100.0f); // ����������� ���������� �����������
	glMatrixMode(GL_MODELVIEW); // ��������� � ���������� �����

}

int main(int argc, char *argv[]){

	init(); // �������������

	bool running = true;

	float xrf = 0, yrf = 0, zrf = 0, wrf = -7.0; // ���� ��������

	while(running){

		SDL_Event event; // ������� SDL

		while ( SDL_PollEvent(&event) ){ // �������� ��������� �������
			switch(event.type){ // �������:
				case SDL_QUIT: // ���� ��������� ������� �������� ����, �� ��������� ������ ���������
					running = false;
				break;

				case SDL_KEYDOWN: // ���� ������ �������
					switch(event.key.keysym.sym){ // ������� �����
						case SDLK_ESCAPE: // ������� ESC
							running = false; // ��������� ������ ���������
						break;
						case SDLK_LEFT:
							xrf += 10.0;
						break;
						case SDLK_RIGHT:
							yrf += 10.0;
						break;
						case SDLK_UP:
							zrf += 10.0;
						break;
						case SDLK_DOWN:
							wrf -= 0.1;
						break;
						case SDLK_PAGEUP:
							wrf += 0.1;
						break;

					}
				break;
			}
		}

	  	// ���� ��������� �������� �������� ���� ��������, ��� ����� ������ ���

		//xrf -= 0.5;
        //yrf -= 0.5;
		//zrf -= 0.5;

		drawCube(xrf, yrf, zrf, wrf); // ������ ��� ��� � �������� ������ ��������

		// ��������� �����
        //Sleep(3);

		glFlush();
		SDL_GL_SwapWindow(window);
	}

	SDL_Quit(); // ��������� ������ SDL � �������
	return 0;
}

void drawCube(float xrf, float yrf, float zrf, float wrf){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, wrf);	// �������� ������ ������

	glRotatef(xrf, 1.0f, 0.0f, 0.0f);	// �������� ���� �� X, Y, Z
	glRotatef(yrf, 0.0f, 1.0f, 1.0f);	// �������� ���� �� X, Y, Z
	glRotatef(zrf, 0.0f, 0.0f, 1.0f);	// �������� ���� �� X, Y, Z

	glBegin(GL_QUADS);		// ������ ���

	glColor3f(0.5f, 1.0f, 0.0f);		// ������� ������� (�������)
	glVertex3f( 1.0f, 1.0f, -1.0f);		// ������� ������ ���� ��������
	glVertex3f(-1.0f, 1.0f, -1.0f);		// ������� �����
	glVertex3f(-1.0f, 1.0f,  1.0f);		// ������ �����
	glVertex3f( 1.0f, 1.0f,  1.0f);		// ������ ������

	glColor3f(0.0f, 1.0f, 1.5f);		// ��������� ������� (������)
	glVertex3f( 1.0f, -1.0f,  1.0f);	// ������� ������ ���� ��������
	glVertex3f(-1.0f, -1.0f,  1.0f);	// ������� �����
	glVertex3f(-1.0f, -1.0f, -1.0f);	// ������ �����
	glVertex3f( 1.0f, -1.0f, -1.0f);	// ������ ������

	glColor3f(1.0f, 0.0f, 0.0f);		// ������� ������� (��������)
	glVertex3f( 1.0f,  1.0f, 1.0f);		// ������� ������ ���� ��������
	glVertex3f(-1.0f,  1.0f, 1.0f);		// ������� �����
	glVertex3f(-1.0f, -1.0f, 1.0f);		// ������ �����
	glVertex3f( 1.0f, -1.0f, 1.0f);		// ������ ������

	glColor3f(1.0f,1.0f,0.0f);			// ������ ������� (������)
	glVertex3f( 1.0f, -1.0f, -1.0f);	// ������� ������ ���� ��������
	glVertex3f(-1.0f, -1.0f, -1.0f);	// ������� �����
	glVertex3f(-1.0f,  1.0f, -1.0f);	// ������ �����
	glVertex3f( 1.0f,  1.0f, -1.0f);	// ������ ������

	glColor3f(0.5f,0.0f,1.0f);			// ����� ������� (�����)
	glVertex3f(-1.0f,  1.0f,  1.0f);	// ������� ������ ���� ��������
	glVertex3f(-1.0f,  1.0f, -1.0f);	// ������� �����
	glVertex3f(-1.0f, -1.0f, -1.0f);	// ������ �����
	glVertex3f(-1.0f, -1.0f,  1.0f);	// ������ ������

	glColor3f(1.0f,0.0f,1.0f);			// ���������� ������� (������)
	glVertex3f( 1.0f,  1.0f, -1.0f);	// ������� ������ ���� ��������
	glVertex3f( 1.0f,  1.0f,  1.0f);	// ������� �����
	glVertex3f( 1.0f, -1.0f,  1.0f);	// ������ �����
	glVertex3f( 1.0f, -1.0f, -1.0f);	// ������ ������

	glEnd();	// ��������� ��������

}
