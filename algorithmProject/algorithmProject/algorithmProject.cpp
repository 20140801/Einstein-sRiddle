#include <iostream>
using namespace std;
//��� ���� string �迭
string ccolor[5] = { "blue","green","red","white","yellow" };
string nnationality[5]{ "Brit","Dane","German","Norwegian","Swede" };
string bbeverage[5] = { "beer", "coffee","milk", "tea","water" };
string ccigar[5] = { "Blue Maser","Dunhill","Pall Mall","Prince","Blend" };
string ppet[5] = { "cat","bird","dog","fish","horse" };
//enum�� Ȱ���� ������ ����ȭ
enum { blank = -1 };
enum { blue, green, red, white, yellow };
enum { Brit, Dane, German, Norwegian, Swede };
enum { beer, coffee, milk, tea, water };
enum { BlueMaster, Dunhill, PallMall, Prince, Blend };
enum { cat, bird, dog, fish, horse };

enum { Color, Nationality, Beverage, Cigar, Pet };
const int HousesCount = 5; //�� ����
const int possessionsCount = 5; //������ ���� ��
int nodeCount = 0; //find �Լ� ��� ���� ��
int nodeCount2 = 0; //findSolution �Լ� ��� ���� ��
int s[HousesCount][possessionsCount]; //����ǥ 5*5 ���� ����°, ����(����,����,��,���,����) //���� ������ or blank
bool nextHouse(int houseNum, int possession, int value) //��(�¿� ��� ����)�� �ش��ϴ� �������� �ְų� blank�̸� ������ȯ
{
	return !((houseNum > 0 && (s[houseNum - 1][possession] == blank || s[houseNum - 1][possession] == value)) ||
		(houseNum < 4 && (s[houseNum + 1][possession] == blank || s[houseNum + 1][possession] == value)));
}
bool linkPossessions(int houseNum, int poss1, int val1, int poss2, int val2) //�ش� ���� �������� val2�� �ƴϰ� blank�� �ƴϸ� ��
{
	return (s[houseNum][poss1] == val1 && s[houseNum][poss2] != val2 && s[houseNum][poss2] != blank);
}
bool promising() //���ǵ��� �� ����ؾ� ��
{
	//����ȣ�� �ٸ��� ������ �������� �Ȱ��ٸ� false
	for (int i = 0; i < HousesCount; i++)
	{
		for (int j = 0; j < possessionsCount; j++)
		{
			for (int k = i + 1; k < HousesCount; k++) //�� ���� ���� �� �̹� �ؼ� ���ص� ��
			{
				if (s[i][j] != blank && s[k][j] != blank && s[i][j] == s[k][j])
				{
					return 0;
				}
			}
		}
	}
	//1Brit - red
	for (int i = 0; i < HousesCount; i++)
	{
		//if(linkPossessions(i,Nationality,Brit,Color,red))
		if (linkPossessions(i, Color, red, Nationality, Brit)) //�̰��� ȿ����
		{
			return 0;
		}
	}
	//2Swede - dog
	for (int i = 0; i < HousesCount; i++)
	{
		//if(linkPossessions(i,Nationality, Swede, Pet, dog))
		if (linkPossessions(i, Pet, dog, Nationality, Swede))
		{
			return 0;
		}
	}
	//3Dane - tea
	for (int i = 0; i < HousesCount; i++)
	{
		//if (linkPossessions(i, Nationality, Dane, Beverage, tea)) //ù��° �ι�° ���� ��ȿ��, ����° �׹�°�� ȿ��
		if (linkPossessions(i, Beverage, tea, Nationality, Dane))
		{
			return 0;
		}
	}
	//4green -> white 
	for (int i = 0; i < HousesCount; i++)
	{
		if ((i == 0 && s[i][Color] == white) || (s[i][Color] == white && s[i - 1][Color] != green && s[i - 1][Color] != blank))
		{
			return 0;
		}
	}

	//5green - coffee
	for (int i = 0; i < HousesCount; i++)
	{
		if (linkPossessions(i, Color, green, Beverage, coffee))
		{
			return 0;
		}
	}
	//6PallMall - bird
	for (int i = 0; i < HousesCount; i++)
	{
		if(linkPossessions(i, Cigar, PallMall, Pet, bird))
		{
			return 0;
		}
	}
	//7yellow - Dunhill
	for (int i = 0; i < HousesCount; i++)
	{
		if (linkPossessions(i, Color, yellow, Cigar, Dunhill))
		{
			return 0;
		}
	}
	//8center house - milk
	for (int i = 0; i < HousesCount; i++)
	{
		if (s[2][Beverage] != milk && s[2][Beverage] != blank) //01 2(center) 34
		{
			return 0;
		}
	}
	//9Norwegian - first house
	for (int i = 0; i < HousesCount; i++)
	{
		if (s[0][Nationality] != Norwegian && s[0][Nationality] != blank)
		{
			return 0;
		}
	}
	//10Blend next to cat
	for (int i = 0; i < HousesCount; i++) 
	{
		if (s[i][Cigar] == Blend && nextHouse(i, Pet, cat))
		{

			return 0;
		}
	}
	//11horse next to Dunhill
	for (int i = 0; i < HousesCount; i++)
	{
		if (s[i][Pet] == horse && nextHouse(i, Cigar, Dunhill))
		{
			return 0;
		}
	}
	//12Blue Master - beer
	for (int i = 0; i < HousesCount; i++)
	{
		if (linkPossessions(i, Cigar, BlueMaster, Beverage, beer))
		{
			return 0;
		}
	}
	//13German - Prince
	for (int i = 0; i < HousesCount; i++)
	{
		if (linkPossessions(i, Nationality, German, Cigar, Prince))
		{
			return 0;
		}
	}
	//14Norwegian next to blue
	for (int i = 0; i < HousesCount; i++) //0��(�븣����) ���� �������� 1�����ε�.. ���� next to?
	{
		if (s[i][Nationality] == Norwegian && nextHouse(i, Color, blue))
		{
			return 0;
		}
	}
	//15Blend next to water //��� �� �ϳ��� ���� �߰��� �� �� ȿ����
	for (int i = 0; i < HousesCount; i++)
	{
		if (s[i][Cigar] == Blend && nextHouse(i, Beverage, water))
		{
			return 0;
		}
	}

	return 1; //�� ����ϸ� �� ��ȯ
}
int solutionCount = 0; //�� �� find �Լ����� Ȱ���


void find(int houseNum, int possession) //������ �γ��Ҽ��� ��� ���� �� ����
{
	int oldValue = s[houseNum][possession];
	for (int i = 0; i < 5; i++)
	{
		s[houseNum][possession] = i; //��弳��
		nodeCount++;
		if (promising()) //�˻�
		{
			int newHouseNum = (houseNum + 1) % HousesCount;
			int newPossession = possession + (newHouseNum == 0 ? 1 : 0); //���� �ٽ� ù��° �Ǹ� ���ο� �ʱ�ȭ
			if (newPossession >= possessionsCount) //promissing�ϸ� ���ο� ���� �μ��� ��� ȣ��(newPossesion�� 5�� �� �� ����)
			{
				solutionCount++;
				cout << solutionCount << "��° �� : \n\n";
				for (int j = 0; j < HousesCount; j++)
				{
					cout << j + 1 << "��° ��";
					cout.width(15); cout << ccolor[s[j][Color]];
					cout.width(15); cout << nnationality[s[j][Nationality]];
					cout.width(15); cout << bbeverage[s[j][Beverage]];
					cout.width(15); cout << ccigar[s[j][Cigar]];
					cout.width(15); cout << ppet[s[j][Pet]] << "\n";
				}
			}
			else
			{
				find(newHouseNum, newPossession);
			}
		}
	}
	s[houseNum][possession] = oldValue;
	return;
}
bool findSolution(int houseNum, int possession) //���� �Ѱ��� ������ �γ��Ҽ��� ��� ���� �� ������
{
	int oldValue = s[houseNum][possession];
	for (int i = 0; i < 5; i++)
	{
		s[houseNum][possession] = i; //��弳��
		nodeCount2++;
		if (promising()) //�˻�
		{
			int newHouseNum = (houseNum + 1) % HousesCount;
			int newPossession = possession + (newHouseNum == 0 ? 1 : 0); //���� �ٽ� ù��° �Ǹ� ���ο� �ʱ�ȭ
			if (newPossession >= possessionsCount) //promissing�ϸ� ���ο� ���� �μ��� ��� ȣ��(newPossesion�� 5�� �� �� ����)
			{
				return 1;
			}
			else if (findSolution(newHouseNum, newPossession))
			{
				return 1;
			}
		}
	}
	s[houseNum][possession] = oldValue;
	return 0;
}
int main()
{
	//������ �� �ϳ�
	cout << "find�Լ� �� ���� ��� �ʱ�ȭ ��� blank : \n\n";
	for (int i = 0; i < possessionsCount; i++)
	{
		for (int j = 0; j < HousesCount; j++)
		{
			s[i][j] = blank; //�ʱ⿣ ��ĭ���� ä���
		}
	}
	find(0, 0);
	cout << "\nNodes that need to be explored : " << nodeCount << "\n";
	
	cout << "\nfind�Լ� �� ���� ��� �ʱ�ȭ blank, �׸��� ��� �̸� ���� ��忡 �ʱ�ȭ : \n\n";
	nodeCount = 0; solutionCount = 0;
	for (int i = 0; i < possessionsCount; i++)
	{
		for (int j = 0; j < HousesCount; j++)
		{
			s[i][j] = blank; //�ʱ⿣ ��ĭ���� ä���
		}
	}
	//efficient way -> give more answer before backtracing
	s[0][Nationality] = Norwegian;
	s[1][Color] = blue;
	s[2][Beverage] = milk;
	find(0, 0);
	cout << "\nNodes that need to be explored : " << nodeCount << "\n";

	for (int i = 0; i < possessionsCount; i++)
	{
		for (int j = 0; j < HousesCount; j++)
		{
			s[i][j] = blank; //���� �� ��ĭ���� ä���
		}
	}
	cout << "\n\nfindSolution�Լ� �� ���� ��� �ʱ�ȭ ��� blank : \n\n";
	findSolution(0, 0); //������ �� ������ if���� ����

	for (int i = 0; i < HousesCount; i++)
	{
		cout << i + 1 << "��° ��";
		cout.width(15); cout << ccolor[s[i][Color]];
		cout.width(15); cout << nnationality[s[i][Nationality]];
		cout.width(15); cout << bbeverage[s[i][Beverage]];
		cout.width(15); cout << ccigar[s[i][Cigar]];
		cout.width(15); cout << ppet[s[i][Pet]] << "\n";
	}
	cout << "\nNodes that need to be explored : " << nodeCount2 << "\n";
	
	nodeCount2 = 0;
	for (int i = 0; i < possessionsCount; i++)
	{
		for (int j = 0; j < HousesCount; j++)
		{
			s[i][j] = blank; //���� �� ��ĭ���� ä���
		}
	}
	s[0][Nationality] = Norwegian;
	s[1][Color] = blue;
	s[2][Beverage] = milk;
	cout << "\nfindSolution�Լ� �� ���� ��� �ʱ�ȭ blank, �׸��� ��� �̸� ���� ��忡 �ʱ�ȭ : \n\n";
	findSolution(0, 0);

	for (int i = 0; i < HousesCount; i++)
	{
		cout << i + 1 << "��° ��";
		cout.width(15); cout << ccolor[s[i][Color]];
		cout.width(15); cout << nnationality[s[i][Nationality]];
		cout.width(15); cout << bbeverage[s[i][Beverage]];
		cout.width(15); cout << ccigar[s[i][Cigar]];
		cout.width(15); cout << ppet[s[i][Pet]] << "\n";
	}
	cout << "\nNodes that need to be explored : " << nodeCount2 << "\n";
	return 0;
}