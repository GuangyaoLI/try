#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 

#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>
#include <iostream>
#include <sys/wait.h>
#include <sys/types.h>

#include "subprocess.hpp"

using namespace std;
using namespace subprocess;

#define Trig1  9
#define Echo1  8
#define Trig2  2
#define Echo2  0
#define Trig3  13
#define Echo3  12
#define Trig4  11
#define Echo4  10

//int flag =-1; 
int song1 =0;
int song2 =0;
int song3 =0;
int song4 =0;
int song5 =0;
int song6 =0;

char soundpath1[] ="DesiJourney.wav"; 
char soundpath2[] ="doublebass.wav";
char soundpath3[] ="MoodyLoop.wav";

char soundpath4[] ="TheEnd.mp3"; 
char soundpath5[] ="AroundWorld.mp3";
char soundpath6[] ="Decision.mp3";

char vol0[] ="0";
char vol1[6];
char vol2[6];



void ultraInit(void)
{
	pinMode(Echo1, INPUT);
	pinMode(Trig1, OUTPUT);
	pinMode(Echo2, INPUT);
	pinMode(Trig2, OUTPUT);
	pinMode(Echo3, INPUT);
	pinMode(Trig3, OUTPUT);
	pinMode(Echo4, INPUT);
	pinMode(Trig4, OUTPUT);
}

float disMeasure(int Trig, int Echo)
{
	struct timeval tv1;
	struct timeval tv2;
	long start, stop;
	float dis;

	digitalWrite(Trig, LOW);
	delayMicroseconds(2);

	digitalWrite(Trig, HIGH);
	delayMicroseconds(10);
	digitalWrite(Trig, LOW);

	while(!(digitalRead(Echo) == 1));
	gettimeofday(&tv1, NULL);

	while(!(digitalRead(Echo) == 0));
	gettimeofday(&tv2, NULL);

	start = tv1.tv_sec * 1000000 + tv1.tv_usec;
	stop  = tv2.tv_sec * 1000000 + tv2.tv_usec;

	dis = (float)(stop - start) / 1000000 * 34000 / 2;

	return dis;
}


int main(void)
{
	
	float dis1,dis2,dis3,dis4;
	
	wiringPiSetup();

	if(wiringPiSetup() == -1)
	{
		printf("setuo wiringPi failed !");
		return 1;
	}
	
	ultraInit();
	
	//pid_t pid =-10;
     
	char *path1;
	char *path2;
	
	const char* msgq = "q";
	
	char *volume1;
	char *volume2;
	volume1 =vol0;
	volume2 =vol0;
	float volf1, volf2;
	
	while(1)
	{
		dis1 = disMeasure(Trig1,Echo1);
		cout << "distance1 = " << dis1 << " cm." << endl;
		dis2 = disMeasure(Trig2,Echo2);
		cout << "distance2 = " << dis2 << " cm." << endl;
		dis3 = disMeasure(Trig3,Echo3);
		cout << "distance3 = " << dis3 << " cm." << endl;
		dis4 = disMeasure(Trig4,Echo4);
		cout << "distance4 = " << dis4 << " cm." << endl;
		
		//////Initial music
		path1 =soundpath1;
		path2 =soundpath4;
		auto p=Popen({"omxplayer","-o","local","--loop","--vol",volume1,path1},output{PIPE},input{PIPE});
		auto q=Popen({"omxplayer","-o","local","--loop","--vol",volume2,path2},output{PIPE},input{PIPE});
		
		
		/////////////////////////////////////////////////////////////////////////////////sound1
		if(dis1>=10 && dis1<20)
		{
			path1 =soundpath1;
			song1 = song1 +1;
			if(song1==1)
			{
				p.send(msgq, strlen(msgq));
				auto res = p.communicate(nullptr, 0);
				std::cout << res.first.buf.data() << std::endl;
				song2=0; song3=0;
				
				auto p=Popen({"omxplayer","-o","local","--loop","--vol",volume1,path1},output{PIPE},input{PIPE});
			}
		}
		else if( dis1>=20 && dis1<30)
		{
			path1 =soundpath2;
			song2 = song2 +1;
			if(song2==1)
			{
				p.send(msgq, strlen(msgq));
				auto res = p.communicate(nullptr, 0);
				std::cout << res.first.buf.data() << std::endl;
				song1=0; song3=0;
				
				auto p=Popen({"omxplayer","-o","local","--loop","--vol",volume1,path1},output{PIPE},input{PIPE});
			}
			
		}
		else if( dis1>=30 &&dis1<40)
		{
			path1 =soundpath3;
			song3 = song3 +1;
			if(song3==1)
			{
				p.send(msgq, strlen(msgq));
				auto res = p.communicate(nullptr, 0);
				std::cout << res.first.buf.data() << std::endl;
				song1=0; song2=0;
				
				auto p=Popen({"omxplayer","-o","local","--loop","--vol",volume1,path1},output{PIPE},input{PIPE});
			}

		}
		
		/////////////////////////////////////////////////////////////////////////////////sound2
		if(dis2>=10 && dis2<20)
		{
			path2 =soundpath4;
			song4 = song4 +1;
			if(song4==1)
			{
				q.send(msgq, strlen(msgq));
				auto res = q.communicate(nullptr, 0);
				std::cout << res.first.buf.data() << std::endl;
				song5=0; song6=0;
				
				auto q=Popen({"omxplayer","-o","local","--loop","--vol",volume2,path1},output{PIPE},input{PIPE});
			}

		}
		else if( dis2>=20 && dis2<30)
		{
			path2 =soundpath5;
			song5 = song5 +1;
			if(song5==1)
			{
				q.send(msgq, strlen(msgq));
				auto res = q.communicate(nullptr, 0);
				std::cout << res.first.buf.data() << std::endl;
				song4=0; song6=0;
				
				auto q=Popen({"omxplayer","-o","local","--loop","--vol",volume2,path1},output{PIPE},input{PIPE});
			}
		}
		else if( dis2>=30 &&dis2<40)
		{
			path2 =soundpath6;
			song6 = song6 +1;
			if(song6==1)
			{
				q.send(msgq, strlen(msgq));
				auto res = q.communicate(nullptr, 0);
				std::cout << res.first.buf.data() << std::endl;
				song4=0; song5=0;
				
				auto q=Popen({"omxplayer","-o","local","--loop","--vol",volume2,path1},output{PIPE},input{PIPE});
			}
		}
		/////////////////////////////////////////////////////////////////////////////////volume1
		if(dis3>=5 && dis3<=35)
		{
			p.send(msgq, strlen(msgq));
			auto res = p.communicate(nullptr, 0);
			std::cout << res.first.buf.data() << std::endl;
						
			volf1 = 111*(dis3 -5)-3000;
			sprintf(vol1,"%.0f",volf1);
			volume1 =vol1;
			song1 =0; song2 =0; song3 =0;
		}
		/////////////////////////////////////////////////////////////////////////////////volume2
		if(dis4>=5 && dis4<=35)
		{
			q.send(msgq, strlen(msgq));
			auto res = q.communicate(nullptr, 0);
			std::cout << res.first.buf.data() << std::endl;
						
			volf2 = 111*(dis4 -5)-3000;
			sprintf(vol2,"%.0f",volf2);
			volume2 =vol2;
			song4 =0; song5 =0; song6 =0;
		}
		delay(1000);
	}
	return 0;
}
