#include <iostream>
#include <string>
using namespace std;

const int HPMax = 500; // 최대 체력
const int MPMax = 500; // 최대 마나
const int HPPotionCountMax = 5; // HP 포션 최대 보유량
const int MPPotionCountMax = 5; // MP 포션 최대 보유량
const string PotionType[2] = {"HPPotion","MPPotion"}; // 포션 종류 배열

void SetPotion(int Count, int* p_HPPotion, int* p_MPPotion); // 포션 지급 함수
void ShowCurrentPotionCount(int HPPotionCount,int MPPotionCount); // 현재 포션 개수 출력 함수
void RechargePotion(int& HPPotionCount,int& MPPotionCount); // 포션 충전 함수
void UsePotion(int PotionTypeIndex,int& Count,int Status[]); // 포션 사용 함수
void StatPointAllocation(int& StatPoint,int Status[], char StatIndex); // 스탯 포인트 할당 함수
void ShowStatus(int Status[],int Level,int StatPoint); // 현재 능력치 출력 함수
void LevelUp(int& Level, int& StatPoint); // 레벨업 함수

int main() {
	// int형 배열 Status를 선언하고 HP, MP, 공격력, 방어력은 0으로, 나머지 스탯은 1로 초기화
	int Status[8] = { 0, 0, 0, 0, 1, 1, 1, 1}; // HP, MP, 공격력, 방어력, 힘, 민첩, 지력, 행운

	int HPPotionCount = 0; // HP 포션 개수
	int MPPotionCount = 0; // MP 포션 개수

	char Choice; // 메뉴 선택 변수

	int Level = 1; // 레벨 변수
	int StatPoint = 0; // 스탯 포인트 변수

	char StatIndex; // 스탯 포인트 할당할 스탯 선택 변수

	while (true) {
		// 1. 체력(HP), 마나(MP) 초기값 입력
		cout << "HP와 MP를 입력해주세요: ";
		cin >> Status[0] >> Status[1];
		if (Status[0] <= 50 || Status[1] <= 50) {
			cout << "HP나 MP의 값이 너무 작습니다. 다시 입력해주세요.\n";
			continue;
		}
		if(Status[0] > HPMax || Status[1] > MPMax) {
			cout << "HP나 MP의 값이 너무 큽니다. 다시 입력해주세요.\n";
			continue;
		}
		break;
	}

	while (true) {
		// 2. 공격력, 방어력 초기값 입력
		cout << "공격력과 방어력을 입력해주세요: ";
		cin >> Status[2] >> Status[3];
		if (Status[2] <= 0 || Status[3] <= 0) {
			cout << "공격력이나 방어력의 값이 너무 작습니다. 다시 입력해주세요.\n";
			continue;
		}
		break;
	}

	// 3. 포션 지급 (기본 5개씩)
	SetPotion(5,&HPPotionCount,&MPPotionCount);

	while (true) {

		// 4. <스탯 관리 시스템> 창 출력
		cout << "=============================================\n";
		cout << "<스탯 관리 시스템>\n";
		cout << "1. HP UP\n";
		cout << "2. MP UP\n";
		cout << "3. 공격력 UP\n";
		cout << "4. 방어력 UP\n";
		cout << "5. 현재 능력치\n";
		cout << "6. Level UP\n";
		cout << "7. 스탯 포인트 할당\n";
		cout << "0. 나가기\n";
		cout << "번호를 선택해주세요 : ";

		cin >> Choice;
		switch (Choice)
		{
		case '1': // HP포션 1개 사용, HP 30 증가
			UsePotion(0, HPPotionCount, Status);
			break;
		case '2': // MP포션 1개 사용, MP 30 증가
			UsePotion(1, MPPotionCount, Status);
			break;
		case '3': // 공격력 2배
			Status[2] *= 2;
			cout << "* 공격력이 2배로 증가되었습니다.\n";
			break;
		case '4': // 방어력 2배
			Status[3] *= 2;
			cout << "* 방어력이 2배로 증가되었습니다.\n";
			break;
		case '5': // 현재 능력치와 남은 포션 개수 출력
			ShowStatus(Status, Level, StatPoint);
			ShowCurrentPotionCount(HPPotionCount, MPPotionCount);
			break;
		case '6': // 레벨업 보상으로 포션 1개씩 지급
			LevelUp(Level,StatPoint);
			RechargePotion(HPPotionCount,MPPotionCount);
			ShowCurrentPotionCount(HPPotionCount, MPPotionCount);
			break;
		case '7': // 스탯 포인트 할당
			if(StatPoint <= 0) {
				cout << "* 할당할 수 있는 스탯 포인트가 없습니다.\n";
				break;
			}
			cout << "1포인트를 할당할 스탯을 선택해주세요 : \n";
			cout << "1. 체력\n2. 마나\n3. 공격력\n4. 방어력\n5. 힘\n6. 민첩\n7. 지력\n8. 행운\n";
			cout << "번호를 선택해주세요 : ";
			cin >> StatIndex;
			StatPointAllocation(StatPoint, Status, StatIndex);
			break;
		case '0':
			cout << "프로그램을 종료합니다.\n";
			return 0;
		default:
			cout << "유효하지 않은 입력입니다. 다시 선택해주세요.\n";
			continue;
		}
	}
}

// 포션 지급 함수
// HP, MP 포션을 각각 Count개씩 지급
// 최대 보유량을 초과할 수 없음.
void SetPotion(int Count, int* p_HPPotion, int* p_MPPotion) {
	if (Count <= 0 || p_HPPotion == nullptr || p_MPPotion == nullptr) {
		cout << "유효하지 않은 입력입니다.\n";
		return;
	}

	if (*p_HPPotion >= HPPotionCountMax) {
		cout << "* 가지고 있는 HP 포션이 최대 보유량(" << HPPotionCountMax << "개)을 넘어서 더 이상 받을 수 없습니다.\n";
		return;
	}
	else if (*p_MPPotion >= MPPotionCountMax) {
		cout << "* 가지고 있는 MP 포션이 최대 보유량(" << MPPotionCountMax << "개)을 넘어서 더 이상 받을 수 없습니다.\n";
		return;
	}
	else {
		*p_HPPotion += Count;
		*p_MPPotion += Count;
		cout << "* 포션이 지급되었습니다. (HP, MP 포션 각 " << Count << "개)\n";
	}
}

// 현재 포션 개수 출력 함수
void ShowCurrentPotionCount(int HPPotionCount,int MPPotionCount) {
	cout << "[ 현재 보유 포션 개수 ]\n HP 포션: " << HPPotionCount << "개\n MP 포션: " << MPPotionCount << "개\n";
}

// 포션 충전 함수
// HP, MP 포션을 각각 1개씩 충전
// 최대 보유량을 초과할 수 없음.
void RechargePotion(int& HPPotionCount,int& MPPotionCount) {
	if(HPPotionCount < HPPotionCountMax) {
		HPPotionCount++;
		cout << "* HP 포션이 1개 충전되었습니다.\n";
	} else {
		cout << "* 이미 HP 포션을 최대로 보유하고 있습니다.\n";
	}
	if(MPPotionCount < MPPotionCountMax) {
		MPPotionCount++;
		cout << "* MP 포션이 1개 충전되었습니다.\n";
	} else {
		cout << "* 이미 MP 포션을 최대로 보유하고 있습니다.\n";
	}
}

// 포션 사용 함수
// HP 포션 사용 시 체력 30 증가
// MP 포션 사용 시 마나 30 증가
// 포션이 없을 경우 사용 불가
void UsePotion(int PotionTypeIndex,int& Count,int Status[]) {
	switch(PotionTypeIndex) {
		case 0: // HP 포션
			if(Count > 0) {
				Status[0] += 30;
				if(Status[0] > HPMax) Status[0] = HPMax; // 최대 체력 초과 방지
				Count--;
				cout << "* 체력이 30 증가했습니다.\n";
			} else {
				cout << "* 사용 가능한 HP 포션이 없습니다.\n";
			}
			break;
		case 1: // MP 포션
			if(Count > 0) {
				Status[1] += 30;
				if(Status[1] > MPMax) Status[1] = MPMax; // 최대 마나 초과 방지
				Count--;
				cout << "* 마나가 30 증가했습니다.\n";
			} else {
				cout << "* 사용 가능한 MP 포션이 없습니다.\n";
			}
			break;
		default:
			cout << "* 유효하지 않은 포션 종류입니다.\n";
			break;
	}
}

// 스탯 포인트 할당 함수
// 스탯 포인트 1당
// 체력, 마나 : +10
// 공격력, 방어력 : +2
// 힘, 민첩, 지력, 행운 : +1
// 할당할 스탯 포인트가 부족할 경우 할당 불가
void StatPointAllocation(int& StatPoint,int Status[],char StatIndex) {
	switch(StatIndex) 
	{
		case '1': // 체력
			Status[0] += 10;
			StatPoint--;
			cout << "* 체력이 10 증가했습니다.\n";
			break;
		case '2': // 마나
			Status[1] += 10;
			StatPoint--;
			cout << "* 마나가 10 증가했습니다.\n";
			break;
		case '3': // 공격력
			Status[2] += 2;
			StatPoint--;
			cout << "* 공격력이 2 증가했습니다.\n";
			break;
		case '4': // 방어력
			Status[3] += 2;
			StatPoint--;
			cout << "* 방어력이 2 증가했습니다.\n";
			break;
		case '5': // 힘
			Status[4] += 1;
			StatPoint--;
			cout << "* 힘이 1 증가했습니다.\n";
			break;
		case '6': // 민첩
			Status[5] += 1;
			StatPoint--;
			cout << "* 민첩이 1 증가했습니다.\n";
			break;
		case '7': // 지력
			Status[6] += 1;
			StatPoint--;
			cout << "* 지력이 1 증가했습니다.\n";
			break;
		case '8': // 행운
			Status[7] += 1;
			StatPoint--;
			cout << "* 행운이 1 증가했습니다.\n";
			break;
		default:
			cout << "* 유효하지 않은 입력입니다.\n";
			break;
	}
}

// 현재 능력치 출력 함수
void ShowStatus(int Status[], int Level, int StatPoint) {
	cout << "[ 현재 능력치 ] : \n";
	cout << "Level: " << Level << "\n";
	cout << "HP: " << Status[0] << "\n";
	cout << "MP: " << Status[1] << "\n";
	cout << "공격력: " << Status[2] << "\n";
	cout << "방어력: " << Status[3] << "\n";
	cout << "힘: " << Status[4] << "\n";
	cout << "민첩: " << Status[5] << "\n";
	cout << "지력: " << Status[6] << "\n";
	cout << "행운: " << Status[7] << "\n";
	cout << "남은 스탯 포인트: " << StatPoint << "\n";
}

// 레벨업 함수
// 레벨 상승
// 스탯 포인트 지급
void LevelUp(int& Level, int& StatPoint) {
	Level++;
	cout << "* 레벨이 " << Level << "로 상승했습니다!\n";
	StatPoint += 5; // 레벨업 시 스탯 포인트 5점 지급
	cout << "* 스탯 포인트 5점이 지급되었습니다.\n";
}