#include <nds.h>
#include <stdio.h>

int main() {

	//Gives us 1 3D background to work with
	videoSetMode(MODE_0_3D);
	consoleDemoInit();

	//Initialize an opengl context for us to use
	glInit();
	glClearColor(3, 3, 3, 31);
	glViewport(0, 0, 255, 191);

	// Specify which matrix we want to alter in our context
	glMatrixMode(GL_PROJECTION);

	//Load up an identity matrix into out currently select matrix in our context
	glLoadIdentity();

	// Now we load the perspective matrix into the matrix slot in GL_PROJECTION
	// (fov, aspect ratio, znear, zfar)
	gluPerspective(70, 256.0 / 192.0, 0.1, 40);

	//Stores data for our triangle
	struct Transform {
		int rotX = 0;
		int rotY = 0;
		float depth = -1.0f;
	} triangle;

	while (1) {

		printf("\033[2J");  // Clear the terminal.
		printf("\n3D Example\n");
		printf("Depth: %1.2f\n", triangle.depth);
		printf("RotX: %d\n", triangle.rotX);
		printf("RotY: %d\n", triangle.rotY);

		// -- INPUT -- //
		scanKeys();
		int held = keysHeld();
		if (held & KEY_A)
			triangle.depth += 0.05f;
		if (held & KEY_B)
			triangle.depth -= 0.05f;
		if (held & KEY_LEFT)
			triangle.rotY -= 2;
		if (held & KEY_RIGHT)
			triangle.rotY += 2;
		if (held & KEY_UP)
			triangle.rotX -= 2;
		if (held & KEY_DOWN)
			triangle.rotX += 2;
		// ----------- //

		//Specific to the DS, specify our alpha value and whether to cull polygons
		glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// We have to translae first since matrix multiplication is weird and things are applied in reverse.
		glTranslatef(0, 0, triangle.depth);
		glRotateY(triangle.rotY);
		glRotateX(triangle.rotX);

		//Triangle rendering
		glBegin(GL_TRIANGLE);
			glColor3b(255, 0, 0);
			glVertex3f(-0.5f, -0.5f, 0);

			glColor3b(0, 255, 0);
			glVertex3f(0.5f, -0.5f, 0);

			glColor3b(0, 0, 255);
			glVertex3f(0.0f, 0.5f, 0);
		glEnd();

		glFlush(0);  // Waits for a VBlank to swap the buffers and display the graphics.
		swiWaitForVBlank();
	}

	return 0;
}
