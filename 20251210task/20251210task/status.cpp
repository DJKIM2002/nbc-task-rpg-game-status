#include <iostream>
#include <string>
using namespace std;

const int HPPotionCountMax = 5; // HP 포션 최대 보유량
const int MPPotionCountMax = 5; // MP 포션 최대 보유량

void SetPotion(int Count, int* p_HPPotion, int* p_MPPotion);

int main() {
	// int형 배열 Status를 선언하고 0으로 초기화
	int Status[4] = { 0, }; // HP, MP, 공격력, 방어력

	int HPPotionCount = 0; // HP 포션 개수
	int MPPotionCount = 0; // MP 포션 개수

	char Choice; // 메뉴 선택 변수

	int Level = 1; // 레벨 변수

	while (true) {
		// 1. 체력(HP), 마나(MP) 초기값 입력
		cout << "HP와 MP를 입력해주세요: ";
		cin >> Status[0] >> Status[1];
		if (Status[0] <= 50 || Status[1] <= 50) {
			cout << "HP나 MP의 값이 너무 작습니다. 다시 입력해주세요.\n";
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
		cout << "0. 나가기\n";
		cout << "번호를 선택해주세요 : ";

		cin >> Choice;
		switch (Choice)
		{
		case '1': // HP 20 증가
			Status[0] += 20;
			cout << "* HP가 20 증가했습니다.\n";
			break;
		case '2': // MP 20 증가
			Status[1] += 20;
			cout << "* MP가 20 증가했습니다.\n";
			break;
		case '3': // 공격력 2배 증가
			Status[2] *= 2;
			cout << "* 공격력이 2배로 증가되었습니다.\n";
			break;
		case '4': // 방어력 2배 증가
			Status[3] *= 2;
			cout << "* 방어력이 2배로 증가되었습니다.\n";
			break;
		case '5': // 현재 능력치 출력
			cout << "[ 현재 능력치 ] : \n";
			cout << "HP: " << Status[0] << "\n";
			cout << "MP: " << Status[1] << "\n";
			cout << "공격력: " << Status[2] << "\n";
			cout << "방어력: " << Status[3] << "\n";
			break;
		case '6': // 레벨업 보상으로 포션 1개씩 지급
			cout << "레벨 업! HP/MP 포션이 지급됩니다.\n";
			SetPotion(1, &HPPotionCount, &MPPotionCount);
			cout << "[ 현재 보유 포션 개수 ]\n HP 포션: " << HPPotionCount << "개\n MP 포션: " << MPPotionCount << "개\n";
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