#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <regex>
#include <algorithm>
#include <ctime>

#define FILE_BASKET_NAME "Basket.txt"		//
#define FILE_NAME "Data.txt"				// ����� ������
#define FILE_MAIN_NAME "DefualtData.txt"	//
#define SEARCH_EXP_NEW R"(\w{2,6}\s\w{2,10}\s\w{3,5}\s\w{3,15}\s\w{3,15}\s\d{1,2}\s\d{2,6}\s\w{3,7}\s\d{1})" //����� ���������� ���������
#define SEARCH_SHOES R"((Shoes)\s\w{2,10}\s\w{3,5}\s\w{3,15}\s\w{3,15}\s\d{1,2}\s\d{2,6}\s\w{3,7}\s\d{1})" // ���������� ��������� ��� ������ Shoes
#define SEARCH_PANTS R"((Pants)\s\w{2,10}\s\w{3,5}\s\w{3,15}\s\w{3,15}\s\d{1,2}\s\d{2,6}\s\w{3,7}\s\d{1})" // ���������� ��������� ��� ������ Pants
#define SEARCH_CLOTH R"((Cloth)\s\w{2,10}\s\w{3,5}\s\w{3,15}\s\w{3,15}\s\d{1,2}\s\d{2,6}\s\w{3,7}\s\d{1})" // ���������� ��������� ��� ������ Cloth


void Travel(int day);

using namespace std;
//
//	��������� ������
//
class Admin //����������� ������� �����
{
public:

	Admin()
	{
		ifstream File(FILE_MAIN_NAME);	// ����������� ������ ��������� ������
		if (!File.is_open()) throw exception("File read error");
		while (!File.eof()) {
			string temp;	// ��������� ���������� ��������� ����
			getline(File, temp);
			this->admin_data.push_back(temp);
		}
		File.close();
	}

	void Print_Admin_Data()
	{
		cout << "View only Administator///////////////////////////////////////////" << endl;
		for (int i = 0; i < admin_data.size(); i++)
			cout << admin_data[i] << endl;
		cout << "/////////////////////////////////////////////////////////////////" << endl;
	}

	string GetPassword()
	{
		return Password;
	}
private:
	string Password = "OOP1337";	//������ ��������������
	vector <string> admin_data;		//������ ��������� ����
};

class User	//������� ������� �����
{
public:

	void Purchase()
	{
		int it = day;
		fstream File(FILE_BASKET_NAME,ios::out);
		thread thr(Travel,it);
		thr.detach();
	}

	void SetDay(int day)
	{
		this->day = day;
	}

	int GetDay()
	{
		return this->day;
	}

private:
	static int day;
};

int User::day = 0;

class Builder	// �������� �����, �������-�������� �� �� ��� ��������...
{
public:

	void virtual item() = 0;	//��������� ����� ????
	void virtual Print() = 0;	//����������� ����� ������ ������ �� �������

	Builder()	// ����������� ������ Builder, ��������� ������ �� ����� � ������ ��������� ����
	{
		ifstream File(FILE_NAME); 
		if (!File.is_open()) throw exception("File read error");
		while (!File.eof()){
			id++; string temp;	// 
			getline(File, temp);
			this->data.push_back(temp);
		}
		File.close();
	}

protected:
	vector <string> data;
	int id = 0; // ����� ���������� 
};

class Object : public Builder	// ������� ���������, ������� ��������� ����, 
{							    // ��� ������� ������ 9 ������ ����, �� �� ����� �������.
public:

	void item() override {	// ������� ���������� "������������" �������
		regex regular(SEARCH_EXP_NEW);	// ���������� ���������
		smatch find_word;
		vector<string>::iterator it = data.begin();// �������� ������
		int i = 0; // ��������� ����������, �� ��� ����������
		count = id;
		while (i < id) {
			if (!regex_match(data[i], find_word, regular)) {// ��������
				data.erase(data.begin() + i);
				id--; i--;									// ����� ��������� 
			}
			i++;
		}
	}

	void basket(int id_) // ����� �������� � �������
	{					 // 
		fstream File(FILE_NAME); fstream File_Basket(FILE_BASKET_NAME,ios_base::app); // �������� ������
		id_--; // �������� ���������� � ����� ������ Object
		string temp; string buff; // ��������� ����������
		temp = (data[id_].c_str()[data[id_].size() - 1]);
		buff = data[id_];
		int count = stoi(temp); // �������������� �� ��������� ���� � �������������
		if (count == 1) {									// ��������, ���� ����� � ����� ����������,
			buff.replace(buff.size() - 1, buff.size(), "1");// �� ������� ��� �� ������ ������ �������
			File_Basket << buff << endl;
			data.erase(data.begin() + id_);
		}
		else {
			buff.replace(buff.size() - 1, buff.size(), "1");
			File_Basket << buff << endl; // ������ ������ � ���� "�������"
			count--; string temp2 = to_string(count); // �������������� ������������ �������� � �������� ���
			this->data[id_].replace(data[id_].size() - 1, data[id_].size(), temp2); // ������ � ������� ���������� ������
		}
		File.close(); File_Basket.close(); // �������� ������������ ������
		ofstream File_New(FILE_NAME, ios_base::trunc); // �������� ����� � ������ "������ � �����"
		if (!File_New.is_open()) throw exception("File read error"); // ������ �������� �����
		for (int i = 0; i < data.size(); i++) {  // ������ ������������ �������� � ����� "�������"
			if (i == data.size() - 1) File_New << data[i]; // �������
			else File_New << data[i] << endl;			   //
		}
		File_New.close();
	}
	void Print() override // ����� ���� ��������������� �������
	{
		for (int i = 0; i < data.size(); i++)
			cout << "id: " << i + 1 << "\t" << data[i] << endl;
	}
	void PrintBasket() // ����� ��������� � "�������"
	{
		cout << "///////////////////////////Your Basket////////////////////////////" << endl; //
		ifstream File_Basket(FILE_BASKET_NAME); // ������ �� ����� Basket.txt
		if (!File_Basket.is_open()) throw exception("File read error");
		int i = 0; string temp;
		while (!File_Basket.eof()) {
			getline(File_Basket, temp);
			basket_.push_back(temp);
			cout << basket_[i] << endl; i++;
		}
		cout << "//////////////////////////////////////////////////////////////////" << endl;
	}

	int GetCount()
	{
		return count;
	}

protected:
	vector <string> basket_;
	int count;
};

class Shoes : public Object	//����� ������������ ������� �������
{
public:
	
	Shoes() // ���������� �������, ������������� ������ Shoes
	{
		smatch find_world;
		regex regular(SEARCH_SHOES);	// ���������� ���������
		count = 0;
		for (int i = 0; i < id; i++) 
		{
			if (regex_search(data[i], find_world, regular)){
				count++;
			}
		}
	}

	void item() override	// ???
	{

	}

	void Print() override // ����� �������, ������������� ������ Shoes
	{	
		
		smatch find_world;
		regex regular(SEARCH_SHOES);	// ���������� ���������
		int it = 0;
		for (int i = 0; i < data.size(); i++) {
			if (regex_search(data[i], find_world, regular)) {
				cout << "id: " << i + 1 << "\t" << data[i] << endl; it++;
				if (it == count) break;
			}
		}
	}

protected:
	vector<string> Shoes_Data;	//������ ������� ����
	int count = 0;			    //����� �� �����?
};

class Pants : public Object	//����� ������������ ������� ������� ������
{
public:

	Pants() // ���������� �������, ������������� ������ �������� ������
	{
		smatch find_world;
		regex regular(SEARCH_PANTS);	// ���������� ���������
		for (int i = 0; i < id; i++)
		{
			if (regex_search(data[i], find_world, regular)) {
				count++;
			}
		}
	}

	void item() override	// ???
	{

	}

	void Print() override // ����� �������, ������������� ������ Pants
	{
		smatch find_world;
		regex regular(SEARCH_PANTS);	// ���������� ���������
		int it = 0;
		for (int i = 0; i < data.size(); i++) {
			if (regex_search(data[i], find_world, regular)) {
				cout << "id: " << i + 1 << "\t" << data[i] << endl; it++;
				if (it == count) break;
			}
		}
	}

protected:
	vector<string> Cloth_Data;	//������ ������� ����
	int count = 0;			    //����� �� �����?
};

class Cloth : public Object	//����� ������������ ������� �������
{
public:

	Cloth() // ���������� �������, ������������� ������ Shoes
	{
		smatch find_world;
		regex regular(SEARCH_CLOTH);	// ���������� ���������
		for (int i = 0; i < id; i++)
		{
			if (regex_search(data[i], find_world, regular)) {
				count++;
			}
		}
	}

	void item() override	// ???
	{

	}

	void Print() override // ����� �������, ������������� ������ Shoes
	{

		smatch find_world;
		regex regular(SEARCH_CLOTH);	// ���������� ���������
		int it = 0;
		for (int i = 0; i < data.size(); i++) {
			if (regex_search(data[i], find_world, regular)) {
				cout << "id: " << i + 1 << "\t" << data[i] << endl; it++;
				if (it == count) break;
			}
		}
	}

protected:
	vector<string> CLOTH_Data;	//������ ������� ����
	int count = 0;			    //����� �� �����?
};

enum class MyEnumClass
{
	Category = 0,
	Type = 1,
	Sex = 2,
	Brand = 3,
	Mark = 4,
	Size = 5,
	Price = 6,
	Color = 7,
	Count = 8
};	 // ����� ��������

void Travel(int day)
{
	User u;
	while (day > 0) {
		this_thread::sleep_for(chrono::seconds(2));
		day--; u.SetDay(day);
	}
	cout << "Your item has been delivered successfully" << endl;
}