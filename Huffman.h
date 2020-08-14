//Huffman.h

#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include<iostream>
#include<string.h>
#include<bitset>
#include<Windows.h>
#include<fstream>
using namespace std;

//Huffman树的结点
struct Node
{
	int weight; //结点的权值
	int parent; //双亲结点的下标
	int LChild; //左孩子下标
	int RChild; //右孩子下标
};

//Huffman编码后的结果
struct Code
{
	string code; //Huffman编码
	char data; //编码所对应的内容
	Code()
	{
		code = "";
		data = ' ';
	}
};

//处理输入的字符串，计算其权值，保存其值
struct Word
{
	int Weight; //该字符的权值
	char Name; //该字符的内容
	Word()//构造函数
	{
		Weight = 0;
		Name = '0';
	}
};

//Huffman类
class Huffman
{
public:
	void CreateATree(int Weight[], int Number, char Name[]); //创建Huffman树
	void CreateCodeTable(); //创建编码表
	void Encode(string Source, string &EncodeSource); //编码
	void Decode(string Source, string &DecodeSource); //解码
	~Huffman();
	int GetNumberOfLeaves(); //得到叶子结点数
	void StatisticNumberOfLeaves(int Num); //给叶子结点数成员赋值
	Code ReturnCodeTable(int i); //返回第i个结点的编码
private:
	Node* HuffmanTree;
	Code* CodeTable;
	int Number; //字符的种类数（叶子结点数量）
	void RecursiveCode(int Num, string NewCode); //对第i个结点编码
};

//将words数组中权重为0的成员移到最后
void DeleteZeros(Word Words[], string Source);

//获得输入的字符种类数
int GetNumber(Word Words[]);

//将字符种类与对应权值组合
void GetWords(Word Words[], string Source);

//得到权重数组
void GetWeightArray(int Weight[], Word Words[], int Number);

//得到名称数组
void GetNameArray(char Name[], Word Words[], int Number);

//读取文件中所有内容
void read_file(const string& filename, string& filedata);

//将字符串转换为二进制写入文件
void writeBit(string& ch);

//以二进制形式写入桌面文档
void DesktopwriteBit(string& ch);

//二进制读取内容
void readBit(string &String01);//

//读取二进制文件，将其转换为01字符串
void DesktopreadBit(string& String01);

//对输入的文本进行编码
string CodingText(Huffman &AHuffmanTree,string &EncodeSource);

//对文件目录选定的文件进行编码
string CommonCodingFile(Huffman &AHuffmanTree,string &EncodeSource, string FileName);

//对输入的字符串进行译码
void StringDecode(Huffman &AHuffmanTree);

//获取桌面路径
string  GetDesktopPath();
#endif // !_HUFFMAN_H