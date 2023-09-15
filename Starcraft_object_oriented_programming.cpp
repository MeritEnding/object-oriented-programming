#include<iostream>
#include<string>
#include<stdbool.h>
#include<vector>
#include <algorithm>
#include<windows.h>

using namespace std;
class Unit {								//유닛 클래스 생성
protected:
	string name;							//유닛 이름
	int speed;										//유닛 체력							
public:
	int hp;
	//유닛 속도
	Unit() {								//기본 유닛은 마린
		name = "marine";
		hp = 40;
		speed = 1;
	}
	Unit(string name, int hp, int speed) {			//name,hp,speed 를 받는 Unit 생성자 선언
		this->name = name;
		this->hp = hp;
		this->speed = speed;
		cout << name << "유닛이 생성되었습니다. [체력 : " << hp << " , 속도 : " << speed << " ]" << endl;
		Sleep(1000);
	}
	void move(string location)						//유닛 이동 함수
	{

		cout << name << " " << location << " 방향으로 이동합니다." << "[속도:" << speed << "]" << endl << endl;
	}
	void damaged(int damage)						//유닛이 공격 당할 때 체력 손실 값
	{
		while (hp > 0)								// hp<0 이 될 경우 유닛이 파괴됨
		{
			cout << name << " : " << damage << "데미지를 입었습니다." << endl << endl;
			hp -= damage;
			cout << name << " : " << "현재 체력은 " << hp << "입니다." << endl << endl;

		}
		cout << name << " : " << "파괴 되었습니다." << endl << endl;
	}
};
class AttackUnit :public Unit {						// Unit을 상속 받고 공격력 변수가 있는 AttackUnit 생성
public:
	void Attack_Unit_skill() {						// 다형성을 이용하기 위한 함수
		skill();
	}
	virtual void skill()							//오버라이딩을 위한 함수
	{
		cout << "attack!!" << endl;
	}

	int damage;
public:
	AttackUnit(string name, int hp, int speed, int damage) :Unit(name, hp, speed) {				//attackunit 생성자
		this->damage = damage;
	}
	void attack(string location)																//위치 값을 받으면 attack 함수 발동으로 적군을 공격함
	{

		cout << name << " : " << location << " 방향으로 적군을 공격 합니다. [공격력 " << damage << "]" << endl << endl;

	}
};
class Marine :public AttackUnit {																//AttackUnit 클래스를 상속받는 Marine 클래스 생성
public:
	Marine(string name, int hp, int speed, int damage) :AttackUnit(name, hp, speed, damage) {
		cout << "[공격력 : " << damage << "] ";
		cout << "스팀팩 사용가능 현재 체력[" << hp << "]" << endl << endl;
	}

	virtual void skill() {																		//오버라이딩을 위한 함수 (다형성) 마린의 스킬
		if (hp > 10)
		{
			hp -= 10;
			damage *= 2;
			cout << name << " : 스팀팩을 사용합니다. ( HP 10 감소, 공격력 2배 < 현재 체력 : " << hp << "," << " 공격력 : " << damage << " > )" << endl << endl;
		}
		else
		{
			cout << name << " : 체력이 부족하여 스팀팩을 사용 할 수 없습니다." << endl;

		}
	}
};
class Tank :public AttackUnit {																	//AttackUnit을 상속받는 탱크 클래스
public:
	Tank(string name, int hp, int speed, int damage) :AttackUnit(name, hp, speed, damage) {		//Tank AttackUnit의 유닛의 기본정보를 받는다.
		cout << "[공격력 : " << damage << "]" << endl;
		cout << "시즈모드를 사용 가능 [현재 상태:" << siege_developed << "]" << endl << endl;
	}
public:
	bool siege_developed = false;							//시즈모드가 개발이 안됬을 경우 false

	virtual void skill() {									//오버라이딩을 위하 함수 (다형성) 탱크의 스킬
		if (siege_developed == false)
		{
			damage *= 3;
			speed = 0;
			cout << name << " : 시즈모드로 전환합니다. 공격력 3배 속도 0 <공격력 : " << damage << " , " << "속도(고정) : " << speed << " >" << endl << endl;
		}
		else
		{
			cout << name << " : 시즈모드를 해제합니다." << endl;
			damage /= 2;
		}
	}
};
class Only_FlyableUnit :public Unit {
public:
	Only_FlyableUnit(string name, int hp, int flying_speed) :Unit(name, hp, 5)        //
	{
		cout << "[공중 속도 " << flying_speed << "]" << endl;
	}
};
class battlecrusier :public AttackUnit, public Only_FlyableUnit
{
public:
	battlecrusier(string name, int hp, int flying_speed, int damage) :Only_FlyableUnit(name, hp, flying_speed), AttackUnit(name, hp, 0, damage)
	{
		cout << "[공중 속도, 공격력 <" << flying_speed << ',' << damage << "> ]" << endl;
	}
};
void game_start()
{
	cout << "[알림] 새로운 게임을 시작합니다." << "\n\n";
}
void game_over()
{
	string chatting;
	cout << "최후의 발언을 하세요 : ";
	cin >> chatting;
	cout << "Player1: ㅈㅈ" << endl;
	cout << "Player2: ㅋㅋ" << endl;
	cout << "Player3: ㅅㄱ" << endl;
	cout << "[Player] 님이 게임에서 퇴장하셨습니다.";
}

int main()
{
	game_start();

	vector<string> army;
	int unit;
	for (int i = 0; i < 5; i++)
	{
		cout << "어떤 유닛을 생성 하시겠습니까? < 1. 마린  2. 탱크  3. 배틀크루저(발전기 개발 필요)> ";
		cin >> unit;


		if (unit == 1)
		{
			army.push_back("마린");
			Marine m1("마린", 40, 5, 10);
		}
		else if (unit == 2)
		{
			army.push_back("탱크");
			Tank t1("탱크", 100, 10, 30);
		}
		else if (unit == 3)
		{
			cout << "배틀크루저를 생성 하기에는 발전기 레벨이 부족합니다." << endl << endl;
		}
		else
		{
			cout << "게임 오류가 발생 했습니다." << endl;
			exit(0);
		}
		sort(army.begin(), army.end());
	}

	vector<string>::iterator iter;
	cout << "유닛 생성 완료! " << endl;
	for (iter = army.begin(); iter != army.end(); iter++)
	{

		cout << *iter << " " << endl;
	}
	cout << endl;



	//전군 이동
	Only_FlyableUnit air("정찰기 ", 1, 150);
	string move_vector; //이동방향 선정
	cout << "어느 방향으로 정찰 하시겠습니까? : ";
	cin >> move_vector;

	air.move(move_vector);

	air.damaged(1); // 정찰기 공격당함
	Sleep(1000);

	int answer;
	cout << "유닛을 생성하고 스킬을 사용 하시겠습니까? <1. 마린 생성, 스킬 사용 2. 탱크 생성, 스킬 사용 3. 취소> :";
	cin >> answer;
	if (answer == 1)
	{
		AttackUnit* p_attack_unit = new Marine("마린", 40, 5, 10);
		p_attack_unit->Attack_Unit_skill();
	}
	else if (answer == 2)
	{
		AttackUnit* p_attack_unit1 = new Tank("탱크", 100, 10, 30);
		p_attack_unit1->Attack_Unit_skill();
	}
	else
	{
		cout << "스킬 사용을 하지 않습니다." << endl << endl;
	}

	Sleep(2000);
	cout << "전투 태세에 돌입해 자동 공격모드로 전환합니다." << endl;

	if (air.hp == 0)
	{

		Marine m2("마린", 40, 5, 10);
		Tank t2("탱크", 100, 10, 30);
		m2.move(move_vector);
		t2.move(move_vector);
		Sleep(2000);
		m2.attack(move_vector);
		t2.attack(move_vector);
		Sleep(2000);
		m2.damaged(20);
		t2.damaged(20);
		Sleep(1000);
		if (t2.hp == 0 && m2.hp == 0)
		{
			cout << "아군이 전멸 했습니다." << endl;
			game_over();
		}
	}
	else
	{
		air.move("3시");
	}

}
