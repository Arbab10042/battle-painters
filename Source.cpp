#include<iostream>
#include<conio.h>
#include"help.h"
#include<math.h>
#include<conio.h>
#include<time.h>
using namespace std;

void keyPressedP1(int& Direction, double& centrex, double& centrey, double &angle);

void keyPressedP2(int& Direction, double& centrex, double& centrey, double &angle);

void outOfBounds(double& centrex, double&centrey);

bool collision(double& centrep1x, double& centrep1y, double& centrep2x, double& centrep2y, double & radius1, double& radius2);

void movePace(double& centrex, double& centrey, double& angle);

void oppositeDirection(double& angle);

void afterCollision(int& Direction1, int& Direction2, double& centrep1x, double& centrep1y, double& centrep2x, double& centrep2y, double& angle1, double& angle2, double& width1, double& width2);

void drawPlayers(int& Direction1, int& Direction2, double& centrep1x, double& centrep1y, double& centrep2x, double& centrep2y, double& angle1, double& angle2, double& width1, double& width2);

int randomgenerator(int minboundary, int maxboundary);

void widepowerup(double& width);

void Player1speedpowerup(int& Direction, double& centrep1x, double& centrep1y, double& angle1, double& width1);

void Player2speedpowerup(int& Direction, double& centrep2x, double& centrep2y, double& angle2, double& width2);

void Player1Decolour(int& Direction1, int& Direction2, double &centrep1x, double& centrep1y, double& centrep2x, double& centrep2y);

void Player2Decolour(int& Direction1, int& Direction2, double &centrep1x, double& centrep1y, double& centrep2x, double& centrep2y);

void calculate(int& p1count, int& p2count);

void results(int& p1count, int& p2count);

int mypowerupturn(int maxnum, int minnum);

int main()
{
	int p1win = 0, p2win = 0;
	int outerloop = 1;
	while (outerloop <= 3)
	{
		cout << "Round " << outerloop;
		Sleep(1000);
		system("cls");
		bool flagx = false;                                                                 // Flag for Player 1.
		bool flagy = false;                                                                // Flag for Player 2.
		bool powerupflag1 = false, powerupflag2 = false, powerupflag3 = false;      // Flags for powerup.
		srand(time(0));
		cout << "  Time:";
		int x = 255, y = 75;
		while (y <= 240)
		{
			myEllipse(y, 2, y + 10, 12, x, x, x, x, x, x);
			y += 15;
		}
		y = 250;                                                         // y is set to y2 of the last ellipse in time.
		int i = 0, z = 80;										        // i used to control loop. z used to print over time ellipses.
		double radius1 = 10, radius2 = 10, powerradius = 5;            //used for radius of ellipses
		double centrep1x = 130, centrep1y = 150;					  // for p1: 1 is left, 3 is right.
		double centrep2x = 160, centrep2y = 140;					 // for p2: 5 is left, 7 is right.
		double angle1 = 0, angle2 = 0;								//angle of player movement
		int Direction1 = 1, Direction2 = 5;                        // Direction1 is player1's, and Direction2 is player2's direction.
		int powerupx1, powerupy1, powerupx2, powerupy2;		      // Power up coordinates.
		int poweruptimer = 0;                                    // Controls the time of powerup.
		int speedpowerupcount = 0;							    // Timer for speed power up function.
		int PowerupTurn = 0;
		double powercentrex, powercentrey;
		myRect(50, 50, 250, 250, 255, 255, 255);
		while (i < 2400)
		{
			drawPlayers(Direction1, Direction2, centrep1x, centrep1y, centrep2x, centrep2y, angle1, angle2, radius1, radius2);
			if (collision(centrep1x, centrep1y, centrep2x, centrep2y, radius1, radius2))
				afterCollision(Direction1, Direction2, centrep1x, centrep1y, centrep2x, centrep2y, angle1, angle2, radius1, radius2);
			else
				Sleep(30);
			if (i == 600 || i == 1200 || i == 1800)
				PowerupTurn = mypowerupturn(3, 1);

			if (PowerupTurn == 1)                   // Acitvates decolour power up.
			{	
				if (powerupflag1 == false)
				{
					powerupx1 = randomgenerator(52, 240);
					powerupy1 = randomgenerator(52, 240);
					powerupx2 = powerupx1 + 10;
					powerupy2 = powerupy1 + 10;
					powercentrex = (powerupx1 + powerupx2) / 2;
					powercentrey = (powerupy1 + powerupy2) / 2;
					myEllipse(powerupx1, powerupy1, powerupx2, powerupy2, 0, 255, 255, 0, 255, 255);
					powerupflag1 = true;
				}
				if (collision(centrep1x, centrep1y, powercentrex, powercentrey, radius1, powerradius) == 1 && flagx == false && flagy == false)
				{
					//flagx = true;
					if (!collision(centrep1x, centrep1y, centrep2x, centrep2y, radius1, radius2))
					{
						Player2Decolour(Direction1, Direction2, centrep1x, centrep1y, centrep2x, centrep2y);
					}
				}
				if (collision(centrep2x, centrep2y, powercentrex, powercentrey, radius2, powerradius) == 1 && flagx == false && flagy == false)
				{
					//flagy = true;
					if (!collision(centrep1x, centrep1y, centrep2x, centrep2y, radius1, radius2))
					{
						Player1Decolour(Direction1, Direction2, centrep1x, centrep1y, centrep2x, centrep2y);

					}
				}
			}

			else if (PowerupTurn == 2)          //Acitvates speed power up.
			{
				if (powerupflag2 == false)
				{
					powerupx1 = randomgenerator(52, 240);
					powerupy1 = randomgenerator(52, 240);
					powerupx2 = powerupx1 + 10;
					powerupy2 = powerupy1 + 10;
					powercentrex = (powerupx1 + powerupx2) / 2;
					powercentrey = (powerupy1 + powerupy2) / 2;
					myEllipse(powerupx1, powerupy1, powerupx2, powerupy2, 255, 255, 255, 0, 0, 0);
					powerupflag2 = true;
				}
				if (collision(centrep1x, centrep1y, powercentrex, powercentrey, radius1, powerradius))
					flagx = true;
				if (flagx == true)
				{
					Player1speedpowerup(Direction1, centrep1x, centrep1y, angle1, radius1);
					speedpowerupcount++;
					if (speedpowerupcount == 200)
					{
						flagx = false;
						powerupflag2 = false;
						speedpowerupcount = 0;
						poweruptimer = 0;
						PowerupTurn = 0;
					}
				}
				if (collision(centrep2x, centrep2y, powercentrex, powercentrey, radius2, powerradius))
					flagy = true;
				if (flagy == true)
				{
					Player2speedpowerup(Direction2, centrep2x, centrep2y, angle2, radius2);
					speedpowerupcount++;
					if (speedpowerupcount == 200)
					{
						flagy = false;
						powerupflag2 = false;
						speedpowerupcount = 0;
						poweruptimer = 0;
						PowerupTurn = 0;
					}
				}
			}

			else if (PowerupTurn == 3)         //Acitvates wide power up.
			{
				if (powerupflag3 == false)
				{
					powerupx1 = randomgenerator(60, 230);
					powerupy1 = randomgenerator(60, 230);
					powerupx2 = powerupx1 + 10;
					powerupy2 = powerupy1 + 10;
					powercentrex = (powerupx1 + powerupx2) / 2;
					powercentrey = (powerupy1 + powerupy2) / 2;
					myEllipse(powerupx1, powerupy1, powerupx2, powerupy2, 255, 255, 255, 255, 255, 255);
					powerupflag3 = true;
				}
				if (collision(centrep1x, centrep1y, powercentrex, powercentrey, radius1, powerradius) == 1 && flagx == false && flagy == false)
				{
					flagx = true;
					widepowerup(radius1);
					if (centrep1x-radius1 < 52)
						centrep1x = 52+radius1;
					if (centrep1x+radius1 > 248)
						centrep1x = 248-radius1;
					if (centrep1y+radius1 < 52)
						centrep1y = 52+radius1;
					if (centrep1y-radius1 > 248)
						centrep1y = 248-radius1;
					poweruptimer = i;
				}
				if (collision(centrep2x, centrep2y, powercentrex, powercentrey, radius2, powerradius) == 1 && flagy == false && flagx == false)
				{
					flagy = true;
					widepowerup(radius2);
					if (centrep2x - radius2 < 52)
						centrep2x = 52 + radius2;
					if (centrep2x + radius2 > 248)
						centrep2x = 248 - radius2;
					if (centrep2y + radius2 < 52)
						centrep2y = 52 + radius2;
					if (centrep2y - radius2 > 248)
						centrep2y = 248 - radius2;
					poweruptimer = i;
				}
				if (flagx == true)
				{
					if (i == poweruptimer + 200)
					{
						myEllipse(centrep1x - radius1, centrep1y - radius1, centrep1x + radius1, centrep1y + radius1, 0, 255, 100, 0, 255, 100);
						radius1 -= 5;
						flagx = false;
						powerupflag3 = false;
						poweruptimer = 0;
						PowerupTurn = 0;
					}
				}
				if (flagy == true)
				{
					if (i == poweruptimer + 200)
					{
						myEllipse(centrep2x - radius2, centrep2y - radius2, centrep2x + radius2, centrep2y + radius2, 255, 0, 0, 255, 0, 0);
						radius2 -= 5;
						flagy = false;
						powerupflag3 = false;
						poweruptimer = 0;
						PowerupTurn = 0;
					}
				}
			}

			i++;
			if (i % 200 == 0)
			{
				myEllipse(y - 10, 2, y, 12, z, z, z, z, z, z);
				y -= 15;
			}
		}
		cout << "\n calculating results.......";
		int p1count = 0, p2count = 0;
		calculate(p1count, p2count);
		system("cls");
		results(p1count, p2count);
		outerloop++;
		system("cls");
		if (p1count > p2count)
			p1win++;
		else if (p2count > p1count)
			p2win++;
		if (p1count == 2 || p2count == 2)
			break;
	}
	myRect(0, 0, 1000, 1000, 0, 0, 0);
	if (p1win > p2win)
		cout << "Player 1 Wins the game!!!";
	else if (p2win > p1win)
		cout << "Player 2 Wins the game!!!";
	Sleep(2000);
	_getch();
}

void keyPressedP1(int& Direction, double& centrex, double& centrey, double &angle)
{
	bool flag = false;
	flag = isCursorKeyPressedP1(Direction);
	if (flag && Direction == 1)
		angle -= 0.1;
	if (flag && Direction == 3)
		angle += 0.1;
	centrex = centrex + cos(angle);
	centrey = centrey + sin(angle);
}

void keyPressedP2(int& Direction, double& centrex, double& centrey, double &angle)
{
	bool flag = false;
	flag = isCursorKeyPressedP2(Direction);
	if (flag && Direction == 5)
		angle -= 0.1;
	if (flag && Direction == 7)
		angle += 0.1;
	centrex = centrex + cos(angle);
	centrey = centrey + sin(angle);
}

void outOfBounds(double& centrex, double&centrey, double& radius)
{
	if ((int)centrex - (1 + radius) == 50)
	{
		centrex++;
	}
	if ((int)centrey - (1 + radius) == 50)
	{
		centrey++;
	}
	if ((int)centrex + (1 + radius) == 250)
	{
		centrex--;
	}
	if ((int)centrey + (1 + radius) == 250)
	{
		centrey--;
	}
}

bool collision(double& centrep1x, double& centrep1y, double& centrep2x, double& centrep2y, double & radius1, double& radius2)
{
	if (radius1 + radius2 >= (sqrt(((centrep1x - centrep2x)*(centrep1x - centrep2x)) + ((centrep1y - centrep2y)*(centrep1y - centrep2y)))))
		return true;
	return false;
}

void movePace(double& centrex, double& centrey, double& angle)
{
	centrex = centrex + cos(angle);
	centrey = centrey + sin(angle);
}

void oppositeDirection(double& angle)
{
	angle = -angle;
}

void afterCollision(int& Direction1, int& Direction2, double& centrep1x, double& centrep1y, double& centrep2x, double& centrep2y, double& angle1, double& angle2, double& width1, double& width2)
{

	oppositeDirection(angle1);
	oppositeDirection(angle2);
	for (int i = 0; i < 20;)
	{
		if (Direction1 == 1 || Direction1 == 3)
		{
			movePace(centrep1x, centrep1y, angle1);
			i++;
		}

		if (Direction2 == 5 || Direction2 == 7)
		{
			movePace(centrep2x, centrep2y, angle2);
			i++;
		}
		outOfBounds(centrep1x, centrep1y, width1);
		outOfBounds(centrep2x, centrep2y, width2);
		drawPlayers(Direction1, Direction2, centrep1x, centrep1y, centrep2x, centrep2y, angle1, angle2, width1, width2);
		Sleep(7);
	}
	oppositeDirection(angle1);
	oppositeDirection(angle2);
	int j = 0;
	while (j < 50) {
		if (collision(centrep1x, centrep1y, centrep2x, centrep2y, width1, width2))
		{
			afterCollision(Direction1, Direction2, centrep1x, centrep1y, centrep2x, centrep2y, angle1, angle2, width1, width2);
			break;
		}
		myEllipse(centrep1x - width1, centrep1y - width1, centrep1x + width1, centrep1y + width1, 0, 255, 100, 0, 170, 0);
		keyPressedP1(Direction1, centrep1x, centrep1y, angle1);
		outOfBounds(centrep1x, centrep1y, width1);
		myEllipse(centrep1x - width1, centrep1y - width1, centrep1x + width1, centrep1y + width1, 0, 255, 100, 255, 255, 255);
		myLine(centrep1x, centrep1y, centrep1x + width1 * cos(angle1), centrep1y + width1 * sin(angle1), 0, 0, 0);
		myEllipse(centrep2x - width2, centrep2y - width2, centrep2x + width2, centrep2y + width2, 255, 0, 0, 255, 0, 0);
		keyPressedP2(Direction2, centrep2x, centrep2y, angle2);
		outOfBounds(centrep2x, centrep2y, width2);
		myEllipse(centrep2x - width2, centrep2y - width2, centrep2x + width2, centrep2y + width2, 255, 0, 0, 255, 255, 255);
		myLine(centrep2x, centrep2y, centrep2x + width2 * cos(angle2), centrep2y + width2 * sin(angle2), 0, 0, 0);
		j++;
		Sleep(50);
	}
}

void drawPlayers(int& Direction1, int& Direction2, double& centrep1x, double& centrep1y, double& centrep2x, double& centrep2y, double& angle1, double& angle2, double& width1, double& width2)
{
	myEllipse(centrep1x - width1, centrep1y - width1, centrep1x + width1, centrep1y + width1, 0, 255, 100, 0, 255, 100);
	keyPressedP1(Direction1, centrep1x, centrep1y, angle1);
	outOfBounds(centrep1x, centrep1y, width1);
	myEllipse(centrep1x - width1, centrep1y - width1, centrep1x + width1, centrep1y + width1, 0, 255, 100, 0, 170, 0);
	myLine(centrep1x, centrep1y, centrep1x + width1 * cos(angle1), centrep1y + width1 * sin(angle1), 255, 255, 255);


	myEllipse(centrep2x - width2, centrep2y - width2, centrep2x + width2, centrep2y + width2, 255, 0, 0, 255, 0, 0);
	keyPressedP2(Direction2, centrep2x, centrep2y, angle2);
	outOfBounds(centrep2x, centrep2y, width2);
	myEllipse(centrep2x - width2, centrep2y - width2, centrep2x + width2, centrep2y + width2, 255, 0, 0, 170, 0, 0);
	myLine(centrep2x, centrep2y, centrep2x + width2 * cos(angle2), centrep2y + width2 * sin(angle2), 255, 255, 255);

}

int randomgenerator(int minboundary, int maxboundary)
{
	int random, temprandom, range;
	srand(time(0));
	range = maxboundary - minboundary;
	temprandom = rand();
	random = temprandom % (range)+minboundary;
	return random;
}

void widepowerup(double& width)
{
	width += 5;
}

void Player1speedpowerup(int& Direction, double& centrep1x, double& centrep1y, double& angle1, double& width1)
{
	keyPressedP1(Direction, centrep1x, centrep1y, angle1);
	outOfBounds(centrep1x, centrep1y, width1);
	myEllipse(centrep1x - 10, centrep1y - 10, centrep1x + 10, centrep1y + 10, 0, 255, 100, 0, 170, 0);
}

void Player2speedpowerup(int& Direction, double& centrep2x, double& centrep2y, double& angle2, double& width2)
{
	keyPressedP2(Direction, centrep2x, centrep2y, angle2);
	outOfBounds(centrep2x, centrep2y, width2);
	myEllipse(centrep2x - width2, centrep2y - width2, centrep2x + width2, centrep2y + width2, 255, 0, 0, 170, 0, 0);
}

void Player1Decolour(int& Direction1, int& Direction2, double &centrep1x, double& centrep1y, double& centrep2x, double& centrep2y)
{

}

void Player2Decolour(int& Direction1, int& Direction2, double &centrep1x, double& centrep1y, double& centrep2x, double& centrep2y)
{

}

void calculate(int& p1count, int& p2count)
{
	HWND myconsole = GetConsoleWindow();
	HDC mydc = GetDC(myconsole);
	COLORREF color;
	for (int i = 51; i < 250; i++)
	{
		for (int j = 51; j < 250; j++)
		{
			color = GetPixel(mydc, j, i);
			if (color == RGB(0, 255, 100))
				p1count++;
			else if (color == RGB(255, 0, 0))
				p2count++;
		}
	}
	ReleaseDC(myconsole, mydc);
}

void results(int& p1count, int& p2count)
{
	if (p1count > p2count)
		cout << "Player 1 wins the round by securing " << (((float)p1count / (p1count + p2count)) * 100) << "% while Player 2 secures " << (((float)p2count / (p1count + p2count)) * 100) << " % of colours!";
	else if (p2count > p1count)
		cout << "Player 2 wins the round by securing " << (((float)p2count / (p1count + p2count)) * 100) << " % while Player1 secures " << (((float)p1count / (p1count + p2count)) * 100) << " % of colours!";
	else
		cout << "Draw!!!";
	Sleep(10000);
	_getch();

}

int mypowerupturn(int maxnum, int minnum)
{
	int random, temprandom, range;
	srand(time(0));
	range = maxnum - minnum;
	temprandom = rand();
	random = temprandom % (range + 1) + minnum;
	return random;
}