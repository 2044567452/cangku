#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
#include<conio.h>
int maphigh = 28, mapwide = 84;
struct virus
{
	int x;
	int y;
}virus;
unsigned short snakesize = 50, speed = 400, len = 4;
struct snake
{
	int x[50];
	int y[50];
	int len;//�ߵĳ���
	int speed;//�ߵ��ٶ�
 
}snake;
int key = 'w';//��ʼ������
void gotoxy(int x, int y);
void drawmap();
void keydown();
void creatvirus();
int snakestatus();
void startgame();
int menuselect();
void goodbye();
void introduce();
void edition();
int setup();
void respect();
int setup1();
int modifydiffculty();
void diffculty();
int customize();
void customize1();
int main()
{
	for (;;)
	{
		system("cls");//����
		switch (menuselect())
		{
		case 1://��ʼ��Ϸ
			startgame();
			break;
		case 2://��Ϸ����
			introduce();
			break;
		case 3://��Ϸ�汾
			edition();
			break;
		case 4://��Ϸ����
			setup1();
			break;
		case 5://�˳���Ϸ
			goodbye();
			return 0;
		default:
			break;
		}
	}
}
void drawmap()//1.����ͼ
{
	//��: ʳ��   ��������(ռ�������ַ���
	srand((unsigned int)time(NULL));//����������ֵ�λ��
	int i, k;
	for (i = 0; i <= maphigh-1; i++)
	{
		gotoxy(0, i);
		printf("|");//��ӡ��߿�
		gotoxy(mapwide, i);
		printf("|");//��ӡ�ұ߿�
	}
	for (i = 0; i < mapwide-1; i ++)//+=2��Ϊ ռ�����ֽ�
	{
		gotoxy(i, 0);
		printf("һ");//��ӡ�±߿�
		gotoxy(i, maphigh);
		printf("һ");//��ӡ�ϱ߿�
	}
	//����
	snake.len = len;
	snake.speed = speed;
	//��ʼ���ߵ�λ��
	snake.x[0] = mapwide / 2;
	snake.y[0] = maphigh / 2;//[0]Ϊ��ͷ��λ��
	//����ͷ
	gotoxy(snake.x[0], snake.y[0]);
	printf("*");
	//������
	for (k = 1; k < snake.len; k++)
	{
		snake.x[k] = snake.x[k - 1] + 2;
		snake.y[k] = snake.y[k - 1];
		gotoxy(snake.x[k], snake.y[k]);
		printf("*");
	}
	while (1)
	{
		virus.x = rand() % (mapwide - 4) + 2;//+2,+1����먀��ռ���ַ��йأ���ռ�����ַ���1��
		virus.y = rand() % (maphigh - 2) + 1;//����ͼ���Զ��׼�
		if (virus.x % 2 == 0)
			break;
	}
	gotoxy(virus.x, virus.y);
	printf("��");
	gotoxy(mapwide + 4, maphigh);
 
}
void creatvirus()//2.��������
{
	if (snake.x[0] == virus.x && snake.y[0] == virus.y)
	{
		//printf("\a");//����
		snake.len++;
		srand((unsigned)time(NULL));
		while (1)
		{
			int flag = 1;
			virus.x = rand() % (mapwide - 4) + 2;//+2,+1����먀��ռ���ַ��йأ���ռ�����ַ���1��
			virus.y = rand() % (maphigh - 2) + 1;//����ͼ���Զ��׼�
		//�����Ĳ����������ߵ�����
			for (int k = 0; k < snake.len; k++)
			{
				if (snake.x[k] == virus.x && snake.y[k] == virus.y)
				{
					flag = 0;//virus�����ʵı�־
					break;
				}
			}
			if (flag == 1 && virus.x % 2 == 0)//����λ�úϷ���x����Ϊż��
			{//x�������������ֽ�Ϊ��λ�˶��ģ���virus��x����Ϊ�������Ͳ�����snake.x[k] == virus.x
				break;
			}
		}
	}
	gotoxy(virus.x, virus.y);
	printf("��");
	gotoxy(mapwide + 8, 0);//���������
	printf("W");
	gotoxy(mapwide + 6, 1);
	printf("A S D \t���п���");
	gotoxy(mapwide + 4, maphigh);
 
 
 
}
void keydown()//3.����
{
	int i, temp;
	if (_kbhit()) //kbhit������鵱ǰ�Ƿ��м������룬�����򷵻�һ����0ֵ�����򷵻�0
	{
		fflush(stdin);// ������뻺������ͨ����Ϊ��ȷ����Ӱ���������ݶ�ȡ
		temp = _getch();//getch:�ӿ���̨��ȡһ���ַ���������ʾ����Ļ��
		if ((temp == 'a' || temp == 'A') && (key != 'D' && key != 'd'))//����˰������������ɱ������
		{
			key = temp;
		}
		if ((temp == 'w' || temp == 'W') && (key != 's' && key != 'S'))
		{
			key = temp;
		}
		if ((temp == 's' || temp == 'S') && (key != 'W' && key != 'w'))
		{
			key = temp;
		}
		if ((temp == 'D' || temp == 'd') && (key != 'a' && key != 'A'))
		{
			key = temp;
		}
	}
	//�������һ��
	gotoxy(snake.x[snake.len - 1], snake.y[snake.len - 1]);
	printf("  ");
	for (i = snake.len - 1; i > 0; i--)
	{
		snake.x[i] = snake.x[i - 1];//��ǰ1��λ�����ڱ����2��0�����1
		snake.y[i] = snake.y[i - 1];
	}
	switch (key)//���һ���Ѿ�������ǰ�ƺ�0,1λ���غ�,���Ͻ�����Ϊ0��0
	{
	case'w':
	case'W':
		snake.y[0]--;
		break;
	case's':
	case'S':
		snake.y[0]++;
		break;
	case'a':
	case'A':
		snake.x[0] -= 2;
		break;
	case'd':
	case'D':
		snake.x[0] += 2;
		break;
	}
	gotoxy(snake.x[0], snake.y[0]);
	printf("*");
	gotoxy(mapwide + 2, 0);//���������
}
int snakestatus()//4.�ߵ�״̬
{
	if ((snake.x[0] == 0 || snake.x[0] == mapwide) || (snake.y[0] == 0 || snake.y[0] == maphigh))
		return 0;
	for (int k = 1; k < snake.len; k++)
	{
		if (snake.x[0] == snake.x[k] && snake.y[0] == snake.y[k])
			return 0;
	}
	return 1;
}
void gotoxy(int x, int y)
{//1.�ҵ�����̨�������
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	/*HANDLEΪ���  ���õ���������ڵģ������
	Windows��һ���������ڴ�Ϊ�����Ĳ���ϵͳ���ܶ�ʱ��
	���̵Ĵ�������ݲ���ȫ��װ���ڴ棬���̵�ĳһ��װ���ڴ��
	�����ܱ���������棬���ٴ���Ҫʱ����װ���ڴ档����װ��ĵ�ַ�������������ǲ�һ���ġ�
	Ҳ����˵��ͬһ�������ڴ��еĵ�ַ��仯����ô��������ô����׼ȷ�ط��ʵ������أ�Ϊ�˽��������⣬Windows�����˾����
	��ֵ�ϣ���һ��32λ�޷�������ֵ��32λϵͳ�£����߼��ϣ��൱��ָ���ָ�룻��������ϣ���Windows�и��������һ��Ψһ�ġ��̶������ID��
	�����ϣ�Windowsʹ�þ������ʶ���細�ڡ�λͼ�����ʵȶ��󣬲�ͨ������ҵ���Щ����*/
	//2.���ù��
	COORD coord;
	/*COORD ΪWindows.h���Դ�����ԭ�ʹ���Ϊstruct _coord{short x;short y;}coord;*/
	coord.X = x;
	coord.Y = y;
	//4.ͬ��������̨SetConsoleCursorPosition
	SetConsoleCursorPosition(handle, coord);//��λ��handle������ڣ��ѹ�����coord����
}
void startgame()
{
	system("cls");
	drawmap();
	while (1)
	{
		creatvirus();
		keydown();
		Sleep(snake.speed);//void sleep(int seconds)�Դ��������� seconds ΪҪ��ͣ�ĺ�������
		if (!snakestatus())//�ж�����ʱsnakestausΪ0,
		{
			gotoxy(mapwide / 2, maphigh / 2);
			printf("Game Over");
			getchar();
			getchar();
			break;
		}
		if (snake.len == snakesize)
		{
			gotoxy(mapwide / 3, maphigh / 2);
			printf("��ϲ��������ȫ��������ʤ��(�ޣ���)V");
			getchar();
			respect();
			break;
		}
	}
}
int menuselect()
{
	char number;
	int a;
	printf("\n\t\t\t\t\t\t1.��ʼ��Ϸ\n");
	printf("\n\t\t\t\t\t\t2.��Ϸ����\n");
	printf("\n\t\t\t\t\t\t3.��Ϸ�汾\n");
	printf("\n\t\t\t\t\t\t4.��Ϸ����\n");
	printf("\n\t\t\t\t\t\t5.�˳���Ϸ\n");
	printf("\n\t\t\t\t\t\t��������ѡ����:");
	while (1)
	{
		number = getchar();
		a = (int)number - 48;
		if (number <= '5' && number >= '1')
			return a;
		printf("\n\t\t\t\t\t\t\t      ");
	}
}
void goodbye()
{
	system("cls");
	system("color 0f");//�ָ�ԭ����ɫ
	gotoxy(0, 12);
	printf("\t\t\t\t\t\tллʹ�ã�\n");
	getchar();
	getchar();
}
void respect()
{
	system("cls");
	gotoxy(0, 4);
	printf("\t\t*��ϲ������Ϸ��ʤ��*\n\n");
	Sleep(1000);
	printf("\t\t*������Ϸ������õĿ���*\n\n");
	Sleep(1000);
	printf("\t\t*���Ƕ��������Ĺ���*\n\n");
	Sleep(1000);
	printf("\t\t*ϣ������������Ҳͬ���ɹ�*\n\n");
	Sleep(2000);
  printf("\t\t*     ����һ�ְɣ�       *\n\n");
  Sleep(2000);
	startgame();
}
void introduce()
{
	system("cls");
	gotoxy(0, 4);
  printf("\t\t\t\t*********************************************\n\n");
	printf("\t\t\t\t*                   ��Ϸ����                *\n\n");
	printf("\t\t\t\t*            ͨ���������ҿ����ߵķ���       *\n\n");
	printf("\t\t\t\t*            ��ҽ�����������������ֵĶ��� *\n\n");
  printf("\t\t\t\t*            ����ײ���ϰ����Խ��Խ�������� *\n\n");
	printf("\t\t\t\t*            �Ե����ж��Ӽ��ɻ��ʤ����     *\n\n");
	printf("\t\t\t\t*********************************************\n\n");
	printf("\t\t\t\t\tEnter�������˵�");
	getchar();
	getchar();
}
void edition()
{
	system("cls");
	gotoxy(0, 4);
	printf("\t\t\t\t*********************************************\n\n");
	printf("\t\t\t\t*                �汾�ţ� 1.2               *\n\n");
	printf("\t\t\t\t*                                           *\n\n");
	printf("\t\t\t\t*        ���£�1.�޸��˷�������ɱ������     *\n\n");
	printf("\t\t\t\t*              2.�޸����߳�ǽ������         *\n\n");
	printf("\t\t\t\t*              3.�����˲˵������ù���       *\n\n");
	printf("\t\t\t\t*                                           *\n\n");
	printf("\t\t\t\t*********************************************\n\n");
	printf("\t\t\t\t\tEnter�������˵�");
	getchar();
	getchar();
}
 
int setup()
{
 
	char s;
	int a;
	system("cls");
	printf("\n\t\t\t\t\t\t1.�޸��Ѷ�\n");
	printf("\n\t\t\t\t\t\t2.���嶨����\n");
	printf("\n\t\t\t\t\t\t3.��ɫ����\n");
	printf("\n\t\t\t\t\t\t4.�������˵�\n");
	printf("\n\t\t\t\t\t\t��������ѡ����:");
	while (1)
	{
		s = getchar();
		a = (int)s - 48;
		if (s <= '5' && s >= '1')
			return a;
		printf("\n\t\t\t\t\t\t\t      ");
	}
}
int setup1()
{
	switch (setup())
	{
	case 1:
		diffculty();
		break;
	case 2:
		customize1();
		break;
  case 3:
        colors();
    break;
  case 4:
  
    break;
	default:
		break;
	}
	return 0;
}
int modifydiffculty()
{
	char s;
	int a;
	system("cls");
	printf("\n\n\t\t\t\t\t1.��\n");
	printf("\n\t\t\t\t\t\t2.��ͨ\n");
	printf("\n\t\t\t\t\t\t3.����\n");
	printf("\n\t\t\t\t\t\t4.���޵���\n");
	printf("\n\t\t\t\t\t\t��������ѡ����:");
	while (1)
	{
		s = getchar();
		a = (int)s - 48;
		if (s <= '4' && s >= '1')
			return a;
		printf("\n\t\t\t\t\t\t\t      ");
	}
}
void diffculty()
{
	switch (modifydiffculty())
	{
	case 1:
		len = 4;
		speed = 500;
		snakesize = 10;
		system("cls");
		gotoxy(8, 8);
		printf("\t\t\t\t\t\t �޸ĳɹ���\n");
		printf("\t\t\t\t\t\t \n");
		system("pause");
		break;
	case 2:
		len = 4;
		speed = 300;
		snakesize = 25;
		system("cls");
		gotoxy(8, 8);
		printf("\t\t\t\t\t\t �޸ĳɹ���\n");
		printf("\t\t\t\t\t\t \n");
		system("pause");
		break;
	case 3:
		len = 4;
		speed = 70;
		snakesize = 50;
		system("cls");
		gotoxy(8, 8);
		printf("\t\t\t\t\t\t �޸ĳɹ���\n");
		printf("\t\t\t\t\t\t \n");
		system("pause");
		break;
	case 4:
		len = 4;
		speed = 25;
		snakesize = 70;
		system("cls");
		gotoxy(8, 8);
		printf("\t\t\t\t\t\t �޸ĳɹ���\n");
		printf("\t\t\t\t\t\t \n");
		system("pause");
		break;
	default:
		break;
	}
}
int customize()
{
	char s;
	int a;
	system("cls");
	printf("\n\n\t\t\t\t\t\t1.�Զ����ٶ�\n");
	printf("\n\t\t\t\t\t\t2.�Զ����ʼ����\n");
	printf("\n\t\t\t\t\t\t��������ѡ����:");
	while (1)
	{
		s = getchar();
		a = (int)s - 48;
		if (s <= '2' && s >= '1')
			return a;
		printf("\n\t\t\t\t\t\t\t      ");
	}
}
void customize1()
{
	int s;
	switch (customize())
	{
	case 1://�Զ����ٶ�
		system("cls");
		gotoxy(8, 8);
		printf("\t\t\t\t�������ٶ�(1-999)");
		scanf_s("%d", &s);
		speed = (1000 - s);
		break;
	case 2://�Զ����ʼ����
		system("cls");
		gotoxy(8, 8);
		printf("\t\t\t\t�������ʼ����(1-20)��");
		scanf_s("%d", &s);
		len = s;
		break;
	default:
		break;
	}
}
	//system("color 6f"); //��һ��Ϊ����ɫ���ڶ���Ϊ������ɫ
   /*0 = ��ɫ       8 = ��ɫ
	1 = ��ɫ       9 = ����ɫ
	2 = ��ɫ       A = ����ɫ
	3 = ����ɫ     B = ��ǳ��ɫ
	4 = ��ɫ       C = ����ɫ
	5 = ��ɫ       D = ����ɫ
	6 = ��ɫ       E = ����ɫ
	7 = ��ɫ       F = ����ɫ*/
  int color()
{
	char s;
	int a;
	system("cls");
  printf("\t\t\t\t\t��һ��Ϊ����ɫ���ڶ���Ϊ������ɫ\n");
  printf("\t\t\t\t\t\t0 = ��ɫ       8 = ��ɫ\n");
  printf("\t\t\t\t\t\t1 = ��ɫ       9 = ����ɫ\n");
  printf("\t\t\t\t\t\t2 = ��ɫ       A = ����ɫ\n");
  printf("\t\t\t\t\t\t3 = ����ɫ     B = ��ǳ��ɫ\n");
  printf("\t\t\t\t\t\t4 = ��ɫ       C = ����ɫ\n");
  printf("\t\t\t\t\t\t5 = ��ɫ       D = ����ɫ\n");
  printf("\t\t\t\t\t\t6 = ��ɫ       E = ����ɫ\n");
  printf("\t\t\t\t\t\t7 = ��ɫ       F = ����ɫ\n");
	printf("\n\n\t\t\t\t\t1.���� ��ɫ ���� ����ɫ\n");
	printf("\n\t\t\t\t\t\t2.���� ��ɫ ���� ��ɫ\n");
	printf("\n\t\t\t\t\t\t3.���� ��ɫ ���� ����ɫ\n");
	printf("\n\t\t\t\t\t\t4.���� ��ɫ ���� ��ɫ\n");
	printf("\n\t\t\t\t\t\t��������ѡ����:");
	while (1)
	{
		s = getchar();
		a = (int)s - 48;
		if (s <= '4' && s >= '1')
			return a;
		printf("\n\t\t\t\t\t\t\t      ");
	}
}
void colors()
{
	switch (color())
	{
	case 1:
		system("color 0f");
		system("cls");
		gotoxy(8, 8);
		printf("\t\t\t\t\t\t �޸ĳɹ���\n");
		printf("\t\t\t\t\t\t \n");
		system("pause");
		break;
	case 2:
		
    system("color 17");
		system("cls");
		gotoxy(8, 8);
		printf("\t\t\t\t\t\t �޸ĳɹ���\n");
		printf("\t\t\t\t\t\t \n");
		system("pause");
		break;
	case 3:
		
    system("color 8e");
		system("cls");
		gotoxy(8, 8);
		printf("\t\t\t\t\t\t �޸ĳɹ���\n");
		printf("\t\t\t\t\t\t \n");
		system("pause");
		break;
	case 4:
		
    system("color 56");
		system("cls");
		gotoxy(8, 8);
		printf("\t\t\t\t\t\t �޸ĳɹ���\n");
		printf("\t\t\t\t\t\t \n");
		system("pause");
		break;
	default:
		break;
	}
}