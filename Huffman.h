//Huffman.h

#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include<iostream>
#include<string.h>
#include<bitset>
#include<Windows.h>
#include<fstream>
using namespace std;

//Huffman���Ľ��
struct Node
{
	int weight; //����Ȩֵ
	int parent; //˫�׽����±�
	int LChild; //�����±�
	int RChild; //�Һ����±�
};

//Huffman�����Ľ��
struct Code
{
	string code; //Huffman����
	char data; //��������Ӧ������
	Code()
	{
		code = "";
		data = ' ';
	}
};

//����������ַ�����������Ȩֵ��������ֵ
struct Word
{
	int Weight; //���ַ���Ȩֵ
	char Name; //���ַ�������
	Word()//���캯��
	{
		Weight = 0;
		Name = '0';
	}
};

//Huffman��
class Huffman
{
public:
	void CreateATree(int Weight[], int Number, char Name[]); //����Huffman��
	void CreateCodeTable(); //���������
	void Encode(string Source, string &EncodeSource); //����
	void Decode(string Source, string &DecodeSource); //����
	~Huffman();
	int GetNumberOfLeaves(); //�õ�Ҷ�ӽ����
	void StatisticNumberOfLeaves(int Num); //��Ҷ�ӽ������Ա��ֵ
	Code ReturnCodeTable(int i); //���ص�i�����ı���
private:
	Node* HuffmanTree;
	Code* CodeTable;
	int Number; //�ַ�����������Ҷ�ӽ��������
	void RecursiveCode(int Num, string NewCode); //�Ե�i��������
};

//��words������Ȩ��Ϊ0�ĳ�Ա�Ƶ����
void DeleteZeros(Word Words[], string Source);

//���������ַ�������
int GetNumber(Word Words[]);

//���ַ��������ӦȨֵ���
void GetWords(Word Words[], string Source);

//�õ�Ȩ������
void GetWeightArray(int Weight[], Word Words[], int Number);

//�õ���������
void GetNameArray(char Name[], Word Words[], int Number);

//��ȡ�ļ�����������
void read_file(const string& filename, string& filedata);

//���ַ���ת��Ϊ������д���ļ�
void writeBit(string& ch);

//�Զ�������ʽд�������ĵ�
void DesktopwriteBit(string& ch);

//�����ƶ�ȡ����
void readBit(string &String01);//

//��ȡ�������ļ�������ת��Ϊ01�ַ���
void DesktopreadBit(string& String01);

//��������ı����б���
string CodingText(Huffman &AHuffmanTree,string &EncodeSource);

//���ļ�Ŀ¼ѡ�����ļ����б���
string CommonCodingFile(Huffman &AHuffmanTree,string &EncodeSource, string FileName);

//��������ַ�����������
void StringDecode(Huffman &AHuffmanTree);

//��ȡ����·��
string  GetDesktopPath();
#endif // !_HUFFMAN_H