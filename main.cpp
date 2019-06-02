#include "pong.h"
#define N 30.0
#define M 30.0


bool gameover = false;
int direction = 3;
int Scale = 25;
int w = Scale * N;
int h = Scale * M;
bool intellegence = true;
bool intellegence2 = true;
double speed_x = 0.00;
double speed_y = 0.03;
const double total_speed = 0.08;
int score1 = 0, score2 = 0;


Platform platform1((N / 2), 1);
Platform platform2((N / 2), M-2);
Ball ball;
std::default_random_engine generator; // процессор случайного числа
std::uniform_int_distribution<int> distribution1(0, 1);
std::uniform_real_distribution <double> u2(0.0, 0.03);
std::uniform_real_distribution <double> u3(0.03, 0.06);

using namespace audiere;
AudioDevicePtr device = OpenDevice(); //Для начала нужно открыть AudioDevice 
OutputStreamPtr sound = OpenSound(device, "sound/sound_pongblip.wav", false); //создаем поток для нашего звука
OutputStreamPtr sound2 = OpenSound(device, "sound/sound_pongblip2.wav", false); //создаем поток для нашего звука
OutputStreamPtr sound3 = OpenSound(device, "sound/sound_goal.wav", false); //создаем поток для нашего звука
OutputStreamPtr sound4 = OpenSound(device, "sound/sound_gameover.wav", false); //создаем поток для нашего звука

Block map[60];

void RenderString(float x, float y, void* font, const unsigned char* string)
{
	char* c;

	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(x, y);

	glutBitmapString(font, string);
}


void Tick() {
	ball.bounce(ball.getx(), ball.gety(), direction, speed_x, speed_y);

	if (intellegence) {
		if (direction == 3 || direction == 4)
			if (ball.getx() > platform2.gettalex(0) && platform2.gettalex(0) < N - 1)
				platform2.moveto(0.045, 0);
			else if (ball.getx() < platform2.gettalex(3) && platform2.gettalex(3) >= 1) platform2.moveto(-0.045, 0);
	}
	if (intellegence2) {
		if (direction == 1 || direction == 2)
			if (ball.getx() > platform1.gettalex(0) && platform1.gettalex(0) < N - 1)
				platform1.moveto(0.045, 0);
			else if (ball.getx() < platform1.gettalex(3) && platform1.gettalex(3) >= 1) platform1.moveto(-0.045, 0);
	}
	if (ball.getx() <= 1 && direction == 3) {
		sound2->play();
		direction = 4;
	}
	if (ball.getx() <= 1 && direction == 2) {
		sound2->play();
		direction = 1;
	}
	if (ball.getx() >= N-2 && direction == 4) {
		sound2->play();
		direction = 3;
	}
	if (ball.getx() >= N-2 && direction == 1) {
		sound2->play();
		direction = 2;
	}
	if (ball.gety() >= M-1) {
		sound3->play();
		score1++;
		ball.moveto(N / 2, M / 2);
		speed_x = 0.00;
		speed_y = 0.03;
	}
	if (ball.gety() <= 0) {
		sound3->play();
		score2++;
		ball.moveto(N / 2, M / 2);
		speed_x = 0.00;
		speed_y = 0.03;
	}
	
	if (platform1.iscollide(ball.getx(), ball.gety(), true)) {
		direction = 3 + distribution1(generator);
		if (ball.getx() > platform1.gettalex(1)) {
			direction = 4;
			speed_x = u3(generator);
		} else if (ball.getx() < platform1.gettalex(2)) {
			direction = 3;
			speed_x = u3(generator);
		}
		else speed_x = u2(generator);
		speed_y = total_speed - speed_x;
		sound->play(); //проигрываем наш звук
	}
	if (platform2.iscollide(ball.getx(), ball.gety(), false)) {
		direction = 1 + distribution1(generator);
		if (ball.getx() > platform1.gettalex(1)) {
			direction = 1;
			speed_x = u3(generator);
		}
		else if (ball.getx() < platform1.gettalex(2)) {
			direction = 2;
			speed_x = u3(generator);
		}
		else speed_x = u2(generator);
		
		speed_y = total_speed - speed_x;
		sound->play(); //проигрываем наш звук
	}
	
	if (score1 == 7 || score2 == 7) {
		sound4->play();
		gameover = true;
	}
	return;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	Tick();
	std::string text;
	platform1.draw();
	platform2.draw();
	for (int i = 0; i < 60; i++) {
		map[i].draw();
	}
	if (gameover) {
		text = " PLAYER # " + std::to_string(score1 > score2 ? 1 : 2) + " WON THE GAME!";
		MessageBoxA(0, (LPCSTR)text.c_str(), (LPCSTR)" GAME OVER ", MB_OK);
		exit(0);
	}
	ball.draw();
	
	text = std::to_string(score2) + '\n' + std::to_string(score1);

	RenderString((N-2)*Scale, (M * Scale / 2) + 1, GLUT_BITMAP_HELVETICA_18, (const unsigned char*)text.c_str());
	RenderString(Scale, (M - 1) * Scale, GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"PLAYER 2");
	RenderString(Scale, Scale/2, GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"PLAYER 1");

	glFlush();
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	case 'a':
		if (platform2.gettalex(3) > 1 && !intellegence)
			platform2.moveto(-1, platform2.gety());
		break;
	case 'A':
		if (platform2.gettalex(3) > 1 && !intellegence)
			platform2.moveto(-1, platform2.gety());
		break;
	case 'd':
		if (platform2.gettalex(0) < N-2 && !intellegence)
		platform2.moveto(1, platform2.gety());
		break;
	case 'D':
		if (platform2.gettalex(0) < N - 2 && !intellegence)
		platform2.moveto(1, platform2.gety());
		break;
	case 'j':
		if (platform1.gettalex(3) > 1 && !intellegence2)
		platform1.moveto(-1, platform2.gety());
		break;
	case 'J':
		if (platform1.gettalex(3) > 1 && !intellegence2)
		platform1.moveto(-1, platform2.gety());
		break;
	case 'l':
		if (platform1.gettalex(0) < N - 2 && !intellegence2)
		platform1.moveto(1, platform2.gety());
		break;
	case 'L':
		if (platform1.gettalex(0) < N - 2 && !intellegence2)
		platform1.moveto(1, platform2.gety());
		break;
	case '1':
		intellegence = !intellegence;
		break;
	case '2':
		intellegence2 = !intellegence2;
		break;
	default:
		break;
	}
	return;
}

void processSpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:
		if (platform2.gettalex(3) > 1 && !intellegence)
			platform2.moveto(-1, platform2.gety());
		break;
	case GLUT_KEY_F3:
		if (platform2.gettalex(0) < N - 2 && !intellegence)
			platform2.moveto(1, platform2.gety());
		break;
	case GLUT_KEY_LEFT:
		if (platform1.gettalex(3) > 1 && !intellegence2)
			platform1.moveto(-1, platform2.gety());
		break;
	case GLUT_KEY_RIGHT:
		if (platform1.gettalex(0) < N - 2 && !intellegence2)
			platform1.moveto(1, platform2.gety());
		break;
	}
	return;
}

void timer(int = 0) {
	display();
	glutTimerFunc(2, timer, 0);
}

int main(int argc, char **argv) {
	generator.seed(time(0));
	sound->setVolume(0.2f);
	sound2->setVolume(0.2f);
	sound3->setVolume(0.2f);
	sound4->setVolume(0.2f);

	ball.setRGB(0.1f, 0.45f, 1.f);
	platform1.setRGB(0.2f, 0.8f, 1.0f);
	platform2.setRGB(0.2f, 0.8f, 1.0f);

	for (int i = 0; i < 30; i++) {
		map[i].setRGB(0.5f, 0.5f, 0.5f);
		map[i].moveto(0, i);
		
	}
	for (int i = 30, j = 0; i < 60; i++, j++) {
		map[i].setRGB(0.5f, 0.5f, 0.5f);
		map[i].moveto(N-1, j);
	}


	ball.moveto(N/2, M/2);

	HWND hWnd = GetForegroundWindow(); // получаем дескриптор окна

	ShowWindow(hWnd, SW_HIDE); // прячем консоль
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(w, h);

	glutCreateWindow("Pong");
	glutPositionWindow((GetSystemMetrics(SM_CXSCREEN) - w) / 2, (GetSystemMetrics(SM_CYSCREEN) - h) / 2);
	glClearColor(0.0, 0.2, 0.4, 1.0); // цвет фона
	hWnd = FindWindowA(NULL, "Pong"); // получаем дескриптор окна
	SetWindowLongPtr(hWnd, GWL_STYLE, (GetWindowLong(hWnd, GWL_STYLE) ^ WS_SIZEBOX) ^ WS_MAXIMIZEBOX); // фиксируем размер окна
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glutDisplayFunc(display);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutTimerFunc(50, timer, 0);
	glutMainLoop();


	return 0;
}
