#include "Scene.h"

int windowWidth = WINDOW_WIDTH; int windowHeight = WINDOW_HEIGHT;

// OpenGL major and minor versions
int majorVersion = 3, minorVersion = 0;

Scene* scene;
bool keyStates[256];

void onInitialization() {
	glViewport(0, 0, windowWidth, windowHeight);

	scene = new Scene();
}

void onExit() {
	delete scene;

	printf("exit");
}

void onDisplay() {
	glClearColor(0, 0, 0, 0); // background color 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen

	scene->Draw();

	glutSwapBuffers(); // exchange the two buffers
}

void onIdle() {
	float t = glutGet(GLUT_ELAPSED_TIME);
	scene->Update(t * .001, keyStates);

	glutPostRedisplay();
}

void onKeyboard(unsigned char key, int mX, int mY) {
	keyStates[key] = true;
}

void onKeyboardUp(unsigned char key, int mX, int mY) {
	keyStates[key] = false;
}

void onMouse(int button, int state, int x, int y) {
}

void onReshape(int width, int height) {
	scene->Resize(width, height);
}

int main(int argc, char * argv[])
{
	glutInit(&argc, argv);
#if !defined(__APPLE__)
	glutInitContextVersion(majorVersion, minorVersion);
#endif
	glutInitWindowSize(windowWidth, windowHeight); 	// application window is initially of resolution 512x512
	glutInitWindowPosition(50, 50);			// relative location of the application window
#if defined(__APPLE__)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);  // 8 bit R,G,B,A + double buffer + depth buffer
#else
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
#endif
	glutCreateWindow("Triangle Rendering");

#if !defined(__APPLE__)
	glewExperimental = true;
	glewInit();
#endif
	printf("GL Vendor    : %s\n", glGetString(GL_VENDOR));
	printf("GL Renderer  : %s\n", glGetString(GL_RENDERER));
	printf("GL Version (string)  : %s\n", glGetString(GL_VERSION));
	glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
	printf("GL Version (integer) : %d.%d\n", majorVersion, minorVersion);
	printf("GLSL Version : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	onInitialization();

	glutDisplayFunc(onDisplay); // register event handlers
	glutIdleFunc(onIdle);
	glutKeyboardFunc(onKeyboard);
	glutKeyboardUpFunc(onKeyboardUp);
	glutMouseFunc(onMouse);
	glutReshapeFunc(onReshape);

	glutMainLoop();
	onExit();
	return 1;
}