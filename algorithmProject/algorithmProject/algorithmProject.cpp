#include <iostream>
using namespace std;
//출력 위한 string 배열
string ccolor[5] = { "blue","green","red","white","yellow" };
string nnationality[5]{ "Brit","Dane","German","Norwegian","Swede" };
string bbeverage[5] = { "beer", "coffee","milk", "tea","water" };
string ccigar[5] = { "Blue Maser","Dunhill","Pall Mall","Prince","Blend" };
string ppet[5] = { "cat","bird","dog","fish","horse" };
//enum을 활용한 숫자의 문자화
enum { blank = -1 };
enum { blue, green, red, white, yellow };
enum { Brit, Dane, German, Norwegian, Swede };
enum { beer, coffee, milk, tea, water };
enum { BlueMaster, Dunhill, PallMall, Prince, Blend };
enum { cat, bird, dog, fish, horse };

enum { Color, Nationality, Beverage, Cigar, Pet };
const int HousesCount = 5; //집 개수
const int possessionsCount = 5; //소유물 종류 수
int nodeCount = 0; //find 함수 노드 설정 수
int nodeCount2 = 0; //findSolution 함수 노드 설정 수
int s[HousesCount][possessionsCount]; //정답표 5*5 퍼즐 집번째, 소유(색깔,음료,펫,담배,국적) //값은 소유물 or blank
bool nextHouse(int houseNum, int possession, int value) //옆(좌우 모두 가능)에 해당하는 소유물이 있거나 blank이면 거짓반환
{
	return !((houseNum > 0 && (s[houseNum - 1][possession] == blank || s[houseNum - 1][possession] == value)) ||
		(houseNum < 4 && (s[houseNum + 1][possession] == blank || s[houseNum + 1][possession] == value)));
}
bool linkPossessions(int houseNum, int poss1, int val1, int poss2, int val2) //해당 집에 소유물이 val2가 아니고 blank가 아니면 참
{
	return (s[houseNum][poss1] == val1 && s[houseNum][poss2] != val2 && s[houseNum][poss2] != blank);
}
bool promising() //조건들을 다 통과해야 됨
{
	//집번호가 다르고 정해진 소유물이 똑같다면 false
	for (int i = 0; i < HousesCount; i++)
	{
		for (int j = 0; j < possessionsCount; j++)
		{
			for (int k = i + 1; k < HousesCount; k++) //전 순번 집은 비교 이미 해서 안해도 됨
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
		if (linkPossessions(i, Color, red, Nationality, Brit)) //이것이 효율적
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
		//if (linkPossessions(i, Nationality, Dane, Beverage, tea)) //첫번째 두번째 경우는 비효율, 세번째 네번째는 효율
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
	for (int i = 0; i < HousesCount; i++) //0번(노르웨이) 다음 오른쪽인 1번집인데.. 굳이 next to?
	{
		if (s[i][Nationality] == Norwegian && nextHouse(i, Color, blue))
		{
			return 0;
		}
	}
	//15Blend next to water //없어도 답 하나임 조건 추가로 좀 더 효율적
	for (int i = 0; i < HousesCount; i++)
	{
		if (s[i][Cigar] == Blend && nextHouse(i, Beverage, water))
		{
			return 0;
		}
	}

	return 1; //다 통과하면 참 반환
}
int solutionCount = 0; //답 수 find 함수에서 활용됨


void find(int houseNum, int possession) //조건이 널널할수록 노드 설정 수 많음
{
	int oldValue = s[houseNum][possession];
	for (int i = 0; i < 5; i++)
	{
		s[houseNum][possession] = i; //노드설정
		nodeCount++;
		if (promising()) //검사
		{
			int newHouseNum = (houseNum + 1) % HousesCount;
			int newPossession = possession + (newHouseNum == 0 ? 1 : 0); //집이 다시 첫번째 되면 새로운 초기화
			if (newPossession >= possessionsCount) //promissing하면 새로운 값들 인수로 재귀 호출(newPossesion이 5가 될 때 까지)
			{
				solutionCount++;
				cout << solutionCount << "번째 답 : \n\n";
				for (int j = 0; j < HousesCount; j++)
				{
					cout << j + 1 << "번째 집";
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
bool findSolution(int houseNum, int possession) //답이 한개만 조건이 널널할수록 노드 설정 수 적어짐
{
	int oldValue = s[houseNum][possession];
	for (int i = 0; i < 5; i++)
	{
		s[houseNum][possession] = i; //노드설정
		nodeCount2++;
		if (promising()) //검사
		{
			int newHouseNum = (houseNum + 1) % HousesCount;
			int newPossession = possession + (newHouseNum == 0 ? 1 : 0); //집이 다시 첫번째 되면 새로운 초기화
			if (newPossession >= possessionsCount) //promissing하면 새로운 값들 인수로 재귀 호출(newPossesion이 5가 될 때 까지)
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
	//어차피 답 하나
	cout << "find함수 전 상태 노드 초기화 모두 blank : \n\n";
	for (int i = 0; i < possessionsCount; i++)
	{
		for (int j = 0; j < HousesCount; j++)
		{
			s[i][j] = blank; //초기엔 빈칸으로 채우기
		}
	}
	find(0, 0);
	cout << "\nNodes that need to be explored : " << nodeCount << "\n";
	
	cout << "\nfind함수 전 상태 노드 초기화 blank, 그리고 답들 미리 상태 노드에 초기화 : \n\n";
	nodeCount = 0; solutionCount = 0;
	for (int i = 0; i < possessionsCount; i++)
	{
		for (int j = 0; j < HousesCount; j++)
		{
			s[i][j] = blank; //초기엔 빈칸으로 채우기
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
			s[i][j] = blank; //시작 전 빈칸으로 채우기
		}
	}
	cout << "\n\nfindSolution함수 전 상태 노드 초기화 모두 blank : \n\n";
	findSolution(0, 0); //어차피 답 있으니 if설정 안함

	for (int i = 0; i < HousesCount; i++)
	{
		cout << i + 1 << "번째 집";
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
			s[i][j] = blank; //시작 전 빈칸으로 채우기
		}
	}
	s[0][Nationality] = Norwegian;
	s[1][Color] = blue;
	s[2][Beverage] = milk;
	cout << "\nfindSolution함수 전 상태 노드 초기화 blank, 그리고 답들 미리 상태 노드에 초기화 : \n\n";
	findSolution(0, 0);

	for (int i = 0; i < HousesCount; i++)
	{
		cout << i + 1 << "번째 집";
		cout.width(15); cout << ccolor[s[i][Color]];
		cout.width(15); cout << nnationality[s[i][Nationality]];
		cout.width(15); cout << bbeverage[s[i][Beverage]];
		cout.width(15); cout << ccigar[s[i][Cigar]];
		cout.width(15); cout << ppet[s[i][Pet]] << "\n";
	}
	cout << "\nNodes that need to be explored : " << nodeCount2 << "\n";
	return 0;
}