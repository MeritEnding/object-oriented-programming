#include<iostream>
#include<string>
#include<stdbool.h>
#include<vector>
#include <algorithm>
#include<windows.h>

using namespace std;
class Unit {								//���� Ŭ���� ����
protected:
	string name;							//���� �̸�
	int speed;										//���� ü��							
public:
	int hp;
	//���� �ӵ�
	Unit() {								//�⺻ ������ ����
		name = "marine";
		hp = 40;
		speed = 1;
	}
	Unit(string name, int hp, int speed) {			//name,hp,speed �� �޴� Unit ������ ����
		this->name = name;
		this->hp = hp;
		this->speed = speed;
		cout << name << "������ �����Ǿ����ϴ�. [ü�� : " << hp << " , �ӵ� : " << speed << " ]" << endl;
		Sleep(1000);
	}
	void move(string location)						//���� �̵� �Լ�
	{

		cout << name << " " << location << " �������� �̵��մϴ�." << "[�ӵ�:" << speed << "]" << endl << endl;
	}
	void damaged(int damage)						//������ ���� ���� �� ü�� �ս� ��
	{
		while (hp > 0)								// hp<0 �� �� ��� ������ �ı���
		{
			cout << name << " : " << damage << "�������� �Ծ����ϴ�." << endl << endl;
			hp -= damage;
			cout << name << " : " << "���� ü���� " << hp << "�Դϴ�." << endl << endl;

		}
		cout << name << " : " << "�ı� �Ǿ����ϴ�." << endl << endl;
	}
};
class AttackUnit :public Unit {						// Unit�� ��� �ް� ���ݷ� ������ �ִ� AttackUnit ����
public:
	void Attack_Unit_skill() {						// �������� �̿��ϱ� ���� �Լ�
		skill();
	}
	virtual void skill()							//�������̵��� ���� �Լ�
	{
		cout << "attack!!" << endl;
	}

	int damage;
public:
	AttackUnit(string name, int hp, int speed, int damage) :Unit(name, hp, speed) {				//attackunit ������
		this->damage = damage;
	}
	void attack(string location)																//��ġ ���� ������ attack �Լ� �ߵ����� ������ ������
	{

		cout << name << " : " << location << " �������� ������ ���� �մϴ�. [���ݷ� " << damage << "]" << endl << endl;

	}
};
class Marine :public AttackUnit {																//AttackUnit Ŭ������ ��ӹ޴� Marine Ŭ���� ����
public:
	Marine(string name, int hp, int speed, int damage) :AttackUnit(name, hp, speed, damage) {
		cout << "[���ݷ� : " << damage << "] ";
		cout << "������ ��밡�� ���� ü��[" << hp << "]" << endl << endl;
	}

	virtual void skill() {																		//�������̵��� ���� �Լ� (������) ������ ��ų
		if (hp > 10)
		{
			hp -= 10;
			damage *= 2;
			cout << name << " : �������� ����մϴ�. ( HP 10 ����, ���ݷ� 2�� < ���� ü�� : " << hp << "," << " ���ݷ� : " << damage << " > )" << endl << endl;
		}
		else
		{
			cout << name << " : ü���� �����Ͽ� �������� ��� �� �� �����ϴ�." << endl;

		}
	}
};
class Tank :public AttackUnit {																	//AttackUnit�� ��ӹ޴� ��ũ Ŭ����
public:
	Tank(string name, int hp, int speed, int damage) :AttackUnit(name, hp, speed, damage) {		//Tank AttackUnit�� ������ �⺻������ �޴´�.
		cout << "[���ݷ� : " << damage << "]" << endl;
		cout << "�����带 ��� ���� [���� ����:" << siege_developed << "]" << endl << endl;
	}
public:
	bool siege_developed = false;							//�����尡 ������ �ȉ��� ��� false

	virtual void skill() {									//�������̵��� ���� �Լ� (������) ��ũ�� ��ų
		if (siege_developed == false)
		{
			damage *= 3;
			speed = 0;
			cout << name << " : ������� ��ȯ�մϴ�. ���ݷ� 3�� �ӵ� 0 <���ݷ� : " << damage << " , " << "�ӵ�(����) : " << speed << " >" << endl << endl;
		}
		else
		{
			cout << name << " : �����带 �����մϴ�." << endl;
			damage /= 2;
		}
	}
};
class Only_FlyableUnit :public Unit {
public:
	Only_FlyableUnit(string name, int hp, int flying_speed) :Unit(name, hp, 5)        //
	{
		cout << "[���� �ӵ� " << flying_speed << "]" << endl;
	}
};
class battlecrusier :public AttackUnit, public Only_FlyableUnit
{
public:
	battlecrusier(string name, int hp, int flying_speed, int damage) :Only_FlyableUnit(name, hp, flying_speed), AttackUnit(name, hp, 0, damage)
	{
		cout << "[���� �ӵ�, ���ݷ� <" << flying_speed << ',' << damage << "> ]" << endl;
	}
};
void game_start()
{
	cout << "[�˸�] ���ο� ������ �����մϴ�." << "\n\n";
}
void game_over()
{
	string chatting;
	cout << "������ �߾��� �ϼ��� : ";
	cin >> chatting;
	cout << "Player1: ����" << endl;
	cout << "Player2: ����" << endl;
	cout << "Player3: ����" << endl;
	cout << "[Player] ���� ���ӿ��� �����ϼ̽��ϴ�.";
}

int main()
{
	game_start();

	vector<string> army;
	int unit;
	for (int i = 0; i < 5; i++)
	{
		cout << "� ������ ���� �Ͻðڽ��ϱ�? < 1. ����  2. ��ũ  3. ��Ʋũ����(������ ���� �ʿ�)> ";
		cin >> unit;


		if (unit == 1)
		{
			army.push_back("����");
			Marine m1("����", 40, 5, 10);
		}
		else if (unit == 2)
		{
			army.push_back("��ũ");
			Tank t1("��ũ", 100, 10, 30);
		}
		else if (unit == 3)
		{
			cout << "��Ʋũ������ ���� �ϱ⿡�� ������ ������ �����մϴ�." << endl << endl;
		}
		else
		{
			cout << "���� ������ �߻� �߽��ϴ�." << endl;
			exit(0);
		}
		sort(army.begin(), army.end());
	}

	vector<string>::iterator iter;
	cout << "���� ���� �Ϸ�! " << endl;
	for (iter = army.begin(); iter != army.end(); iter++)
	{

		cout << *iter << " " << endl;
	}
	cout << endl;



	//���� �̵�
	Only_FlyableUnit air("������ ", 1, 150);
	string move_vector; //�̵����� ����
	cout << "��� �������� ���� �Ͻðڽ��ϱ�? : ";
	cin >> move_vector;

	air.move(move_vector);

	air.damaged(1); // ������ ���ݴ���
	Sleep(1000);

	int answer;
	cout << "������ �����ϰ� ��ų�� ��� �Ͻðڽ��ϱ�? <1. ���� ����, ��ų ��� 2. ��ũ ����, ��ų ��� 3. ���> :";
	cin >> answer;
	if (answer == 1)
	{
		AttackUnit* p_attack_unit = new Marine("����", 40, 5, 10);
		p_attack_unit->Attack_Unit_skill();
	}
	else if (answer == 2)
	{
		AttackUnit* p_attack_unit1 = new Tank("��ũ", 100, 10, 30);
		p_attack_unit1->Attack_Unit_skill();
	}
	else
	{
		cout << "��ų ����� ���� �ʽ��ϴ�." << endl << endl;
	}

	Sleep(2000);
	cout << "���� �¼��� ������ �ڵ� ���ݸ��� ��ȯ�մϴ�." << endl;

	if (air.hp == 0)
	{

		Marine m2("����", 40, 5, 10);
		Tank t2("��ũ", 100, 10, 30);
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
			cout << "�Ʊ��� ���� �߽��ϴ�." << endl;
			game_over();
		}
	}
	else
	{
		air.move("3��");
	}

}
