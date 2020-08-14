#define _CRT_SECURE_NO_WARNINGS
#include"Huffman.h"
#include<string>
#include<bitset>
#include<Windows.h>
#include<fstream>
#include<shlobj.h>

#define MAXNUM 10000


//Weight储存每个字符的权值，Number储存了字符的种类数，Name储存了字符的具体内容
void Huffman::CreateATree(int Weight[], int Number, char Name[])
{
	CodeTable = new Code[Number]; //CodeTable包含Code和data
	HuffmanTree = new Node[2 * Number - 1]; //包含双亲结点和左右孩子下标和权值
	for (int i = 0; i < Number; i++) //对每个结点进行初始化
	{
		HuffmanTree[i].weight = Weight[i]; //赋值权值
		HuffmanTree[i].LChild = HuffmanTree[i].RChild = HuffmanTree[i].parent = -1; //结点初始化
		CodeTable[i].data = Name[i]; //赋值字符
	}

	int x = 0, y = 0; //最小权值的两个结点下标


	for (int i = Number; i < 2 * Number - 1; i++)
	{
		const int MAXVALUE = (int)1E7;
		//存放两个无父结点且结点权值最小的两个结点
		int MinWeight_X = MAXVALUE;
		int	MinWeight_Y = MAXVALUE; 
		x = y = 0; //存储最小结点的下标

		for (int j = 0; j < Number + i; j++) //找出所有结点中权值最小、无父结点的两个结点
		{
			if (HuffmanTree[j].weight < MinWeight_X && HuffmanTree[j].parent == -1)
			{
				MinWeight_Y = MinWeight_X;
				y = x;
				MinWeight_X = HuffmanTree[j].weight;
				x = j;
			}
			else if (HuffmanTree[j].weight < MinWeight_Y && HuffmanTree[j].parent == -1)
			{
				MinWeight_Y = HuffmanTree[j].weight;
				y = j;
			}
		}

		HuffmanTree[x].parent = HuffmanTree[y].parent = i; //将最小的两个结点合并
		HuffmanTree[i].weight = HuffmanTree[x].weight + HuffmanTree[y].weight; //权值合并
		HuffmanTree[i].LChild = x; //左孩子下标赋值
		HuffmanTree[i].RChild = y; //右孩子下标赋值
		HuffmanTree[i].parent = -1; //双亲结点初始化


	}
}

//对第Number个结点编码
void Huffman::RecursiveCode(int Num, string NewCode)
{
	if (HuffmanTree[Num].LChild == -1) //当该结点的左孩子为空（即该结点为叶子结点）时
	{
		CodeTable[Num].code = NewCode; //储存对应编码

		/*Test*/
		cout << "结点" << Num << "的内容为："<<CodeTable[Num].data<<",编码为：" << CodeTable[Num].code << endl; 
		/*Test*/
		
		return;
	}
	RecursiveCode(HuffmanTree[Num].LChild, NewCode + '0'); //对左孩子进行编码，编码结果加一个0表示左孩子
	RecursiveCode(HuffmanTree[Num].RChild, NewCode + '1'); //对右孩子进行编码，编码结果加一个1表示右孩子
}

//生成Huffman编码表
void Huffman::CreateCodeTable()
{
	RecursiveCode(2 * Number - 2, ""); //从根结点开始编码（2 * Number - 2 为根结点的下标）
}


//Huffman编码表析构函数
Huffman::~Huffman()
{
	delete[] CodeTable; //删除动态申请的CodeTable数组指针
	delete[] HuffmanTree; //删除动态申请的HuffmanTree数组指针
}

//记录Huffman编码表的叶子数
void Huffman::StatisticNumberOfLeaves(int Num)
{
	Number = Num;
}

//返回Huffman编码表的叶子数
int Huffman::GetNumberOfLeaves() 
{
	return Number; 
}

//按下表返回Huffman树的编码表内容
Code Huffman::ReturnCodeTable(int i)
{
	return CodeTable[i];
}

//Huffman编码，编码结果为EncodeSource
void Huffman::Encode(string Source, string &EncodeSource)
{
	EncodeSource = ""; //初始化
	for (unsigned int i = 0; i < Source.size(); i++)
	{
		for (int j = 0; j < Number; j++)
		{
			if (Source[i] == CodeTable[j].data) //根据创建的Huffman树的编码表，将原始字符串一一翻译为01型编码
			{
				EncodeSource += CodeTable[j].code; //将翻译好的字符串添加到编码的结果中
				break;
			}
		}
	}
}


//Huffman解码,Source为源码串，DecodeSource为解码串。给定10组成的源码串，返回
void Huffman::Decode(string Source, string &DecodeSource)
{
	string Temp = ""; //初始化临时字符串，储存需要翻译的编码子串
	for (unsigned int i = 0; i < Source.size(); i++)
	{
		Temp += Source[i]; //将需要解码的字符串的各个字符逐个输入
		for (int j = 0; j < Number; j++)
		{
			if (Temp == CodeTable[j].code) //查询编码表中是否有该编码所对应的字符
			{
				DecodeSource += CodeTable[j].data; //若有，将该编码对应的字符加入解码结果
				Temp = ""; //重置需要翻译的解码子串
				break;
			}
		}
	}


}

//将字符种类与对应权值组合，得到便于处理的Word类型数据
void GetWords(Word Words[], string Source)
{

	for (unsigned int i = 0; i < Source.size(); i++)
	{
		int Judge = 0; //判断字符是否唯一
		int WeightTemp = 0; //临时储存权重
		for (unsigned int k = 0; k < i + 1; k++)
		{
			if (k == i && k > 0) //避免无法处理源字符串的第一个字符
				break; 
			if (Source[i] == Words[k].Name) //使得words中储存的字符是唯一的
				Judge = -1; //若不唯一，Judge赋值为-1 
			else 
				Words[i].Name = Source[i]; //若唯一，将该字符存入Word格式数据中
		}
		for (unsigned int j = i; j < Source.size() + 1; j++) //寻找和该字符相同的字符个数
		{
			if (Source[j] == Words[i].Name) //如果在字符串中找到相同字符，则临时权重值加一
				WeightTemp++;
		}
		if (Judge == -1) //若该字符存在相同，则权重记为0，便于后续处理数据
			Words[i].Weight = 0;
		else
			Words[i].Weight = WeightTemp; //记录该字符出现的次数

	}
}

//将words数组中权重为0的成员移到最后（将已有的Word类型数据转换为适合程序设计逻辑的格式）
void DeleteZeros(Word Words[], string Source)
{
	int SumOfZero = 0;//找到数组中所以元素为0的个数
	for (unsigned int k = 0; k < Source.size(); k++)
	{
		if (Words[k].Weight != 0) //统计数组中元素为0的成员个数
		{
			SumOfZero++; 
		}
	}
	for (int k = 0; k < SumOfZero; k++)//将权重为0的数组元素移到最后
	{
		for (unsigned int i = 0; i < Source.size(); i++)
		{
			if (Words[i].Weight == 0)
			{
				for (unsigned int j = i; j < Source.size() || j == 256; j++)//将0后的数组元素前移
				{

					Words[j] = Words[j + 1]; //将j后的结点前移一位
				}
			}
		}
	}

	/*Test*/
	for (unsigned int i = 0; i < Source.size() ; i++)
	{
		if (Words[i].Weight != 0)
		cout << "得到的字符及权值为：" << Words[i].Name << " " << Words[i].Weight << endl;
	}
	/*Test*/

}

//获得输入的字符种类数
int GetNumber(Word Words[])
{
	int Number = 0;
	while (Words[Number].Weight != 0) //统计权值不为0的字符数
	{
		Number++;
	}
	return Number;
}



//得到权重数组（与名称数组一一对应）
void GetWeightArray(int Weight[], Word Words[], int Number)
{
	for (int i = 0; i < Number; i++)
	{
		Weight[i] = Words[i].Weight;
	}
}

//得到名称数组（与权重数组一一对应）
void GetNameArray(char Name[], Word Words[], int Number)
{
	for (int i = 0; i < Number; i++)
	{
		Name[i] = Words[i].Name;
	}
}

//读取文件中的所有内容
void read_file(const string& filename, string& filedata)
{
	ifstream infile;
	char* fileBuffer = NULL;
	infile.open(filename, ios::binary);
	if (infile.is_open())
	{
		infile.seekg(0, ios::end);
		auto len = infile.tellg();  //获取文件长度
		infile.seekg(0, ios::beg);  //设置读取位置为起始位置

		fileBuffer = new char[(size_t)len + 1];
		memset(fileBuffer, 0, (size_t)len + 1);
		infile.read(fileBuffer, len);
		filedata = fileBuffer;
		delete[] fileBuffer;
	}
	else
	{
		cout << "不存在该文件,请检查后重新运行该程序" << endl;
		return;
	}
		
	infile.close();
}

//以二进制形式写入桌面文档
void DesktopwriteBit(string &ch)
{
	int i;
	int j;
	int count = 0; //计算字符串个数
	int  num;    //存储字符需要的多少个字节 
	int left;	//字符串剩余不足8位的个数 
	FILE* fp = NULL;
	char* p = NULL;
	string DesktopPath = GetDesktopPath();
	DesktopPath += "\\";
	string FileName = "Result.txt";
	DesktopPath += FileName;
	const char* File = DesktopPath.c_str();
	if (NULL == (fp = fopen(File, "wb")))
	{
		cout << "open file error" << endl;
	}

	for (i = 0; ch[i] != 0; i++)
	{
		count++;        //统计字符个数 
	}
	num = count / 8;
	left = count % 8;
	cout << endl << "字符串共有字符" << count << "个，占" << count << "字节" << endl << "存储成Result.txt文件后，占" << (left != 0 ? 4 + num + 1 : 4 + num) << "字节" << endl;
	if (left == 0)	//如果left为0，那么num个字节刚好能够存放，否则需要num + 1字节 
	{
		p = (char*)malloc(sizeof(char) * num);
		memset(p, 0, num);
	}
	else
	{
		p = (char*)malloc(sizeof(char) * (num + 1));
		memset(p, 0, num + 1);
	}


	j = -1;
	for (i = 0; i < count; i++)//位运算，每8个字符以2进制的形式储存在一个字符中 
	{
		if (i % 8 == 0)
		{
			j++;
		}
		p[j] <<= 1;
		ch[i] -= '0';
		p[j] |= ch[i];
	}

	if (left != 0) //如果left不为0，需要把剩余的几个位向左边靠拢 
	{
		p[j] <<= 8 - left; //例如left为2，即00000011，需要左移6位变为11000000 
		fwrite(&count, sizeof(count), 1, fp);
		fwrite(p, 1, num + 1, fp);

	}
	else
	{
		fwrite(&count, sizeof(count), 1, fp);
		fwrite(p, 1, num, fp);

	}
	
	fclose(fp);
	free(p);
}

//以二进制形式写入目录文档
void writeBit(string& ch)
{
	int i;
	int j;
	int count = 0; //计算字符串个数
	int  num;    //存储字符需要的多少个字节 
	int left;	//字符串剩余不足8位的个数 
	FILE* fp = NULL;
	char* p = NULL;
	if (NULL == (fp = fopen("Result.txt", "wb")))
	{
		cout << "open file error" << endl;
	}

	for (i = 0; ch[i] != 0; i++)
	{
		count++;        //统计字符个数 
	}
	num = count / 8;
	left = count % 8;
	cout << endl << "字符串共有字符" << count << "个，占" << count << "字节" << endl << "存储成Result.txt文件后，占" << (left != 0 ? 4 + num + 1 : 4 + num) << "字节" << endl;
	if (left == 0)	//如果left为0，那么num个字节刚好能够存放，否则需要num + 1字节 
	{
		p = (char*)malloc(sizeof(char) * num);
		memset(p, 0, num);
	}
	else
	{
		p = (char*)malloc(sizeof(char) * (num + 1));
		memset(p, 0, num + 1);
	}


	j = -1;
	for (i = 0; i < count; i++)//位运算，每8个字符以2进制的形式储存在一个字符中 
	{
		if (i % 8 == 0)
		{
			j++;
		}
		p[j] <<= 1;
		ch[i] -= '0';
		p[j] |= ch[i];
	}

	if (left != 0) //如果left不为0，需要把剩余的几个位向左边靠拢 
	{
		p[j] <<= 8 - left; //例如left为2，即00000011，需要左移6位变为11000000 
		fwrite(&count, sizeof(count), 1, fp);
		fwrite(p, 1, num + 1, fp);

	}
	else
	{
		fwrite(&count, sizeof(count), 1, fp);
		fwrite(p, 1, num, fp);

	}

	fclose(fp);
	free(p);
}


//读取二进制文件，将其转换为01字符串
void readBit(string& String01)
{
	FILE* fp = NULL;
	int count;
	int num;
	int left;
	int i=0, j=0;
	unsigned char flag = 128;	//即0b1000000,用于做位运算
	char* p = NULL;

	if (NULL == (fp = fopen("Result.txt", "rb")))
	{
		cout << "open file error" << endl;
		return;
	}

	else
	{
	fread(&count, sizeof(count), 1, fp);
	num = count / 8; //每8位为一组
	left = count % 8; //剩余的数量
	if (left == 0)
	{
		p = (char*)malloc(sizeof(char) * num);
		if (p != NULL)
			fread(p, 1, num, fp);
		else
			cout << "读取二进制文件部分出错" << endl;
	}
	else
	{
		p = (char*)malloc(sizeof(char) * (num + 1));
		if (p != NULL)
			fread(p, 1, num + 1, fp);
		else
			cout << "读取二进制文件部分出错" << endl;
	}
	fclose(fp);
	}
	j = -1;
	cout << endl << "Result.txt文件存储的二进制为:" << endl;
	for (i = 0; i < count; i++)
	{
		if (i % 8 == 0)
		{
			j++;
			flag = 128;
		}
		if (p)
		{
			if ((p[j] & flag))//通过改变flag字符2进制1的位置判读，一个字节哪个位是1，哪个位是0,并输出字符形式
			{
				printf("1");
				String01 += "1";
				flag /= 2;
			}
			else
			{
				printf("0");
				String01 += "0";
				flag /= 2;
			}
		}
	}
	cout << endl;
	free(p);
	p = NULL;
}

//读取二进制文件，将其转换为01字符串
void DesktopreadBit(string& String01)
{
	FILE* fp = NULL;
	int count;
	int num;
	int left;
	int i = 0, j = 0;
	unsigned char flag = 128;	//即0b1000000,用于做位运算
	char* p = NULL;
	string DesktopPath = GetDesktopPath();
	DesktopPath += "\\";
	string FileName = "Result.txt";
	DesktopPath += FileName;
	const char* File = DesktopPath.c_str();
	if (NULL == (fp = fopen(File, "rb")))
	{
		cout << "open file error" << endl;
		return;
	}

	else
	{
		fread(&count, sizeof(count), 1, fp);
		num = count / 8; //每8位为一组
		left = count % 8; //剩余的数量
		if (left == 0)
		{
			p = (char*)malloc(sizeof(char) * num);
			if (p != NULL)
				fread(p, 1, num, fp);
			else
				cout << "读取二进制文件部分出错" << endl;
		}
		else
		{
			p = (char*)malloc(sizeof(char) * (num + 1));
			if (p != NULL)
				fread(p, 1, num + 1, fp);
			else
				cout << "读取二进制文件部分出错" << endl;
		}
		fclose(fp);
	}
	j = -1;
	cout << endl << "Result.txt文件存储的二进制为:" << endl;
	for (i = 0; i < count; i++)
	{
		if (i % 8 == 0)
		{
			j++;
			flag = 128;
		}
		if (p)
		{
			if ((p[j] & flag))//通过改变flag字符2进制1的位置判读，一个字节哪个位是1，哪个位是0,并输出字符形式
			{
				printf("1");
				String01 += "1";
				flag /= 2;
			}
			else
			{
				printf("0");
				String01 += "0";
				flag /= 2;
			}
		}
	}
	cout << endl;
	free(p);
	p = NULL;
}

//对输入的文本进行编码
string CodingText(Huffman &AHuffmanTree,string &EncodeSource)
{
	string Source=""; //定义原始字符串以便输入
	TextIn:cout << "请输入一段文本：" << endl;
	cin >> Source;
	Word* Words = NULL; //储存出现的各种字符数
	Words = new Word[MAXNUM * sizeof(Word)];
	GetWords(Words, Source); //将输入的字符存储为Word格式（包含数组内容及其初始统计的权值，为过渡状态的数据）
	DeleteZeros(Words, Source); //将上一步储存的Word格式数据转换为该程序设计上可以顺利进行的存储格式
	int Number = GetNumber(Words); //获得字符种类数
	if (Number == 1) //处理只输入一种字符的情况
	{
		cout << "您只输入一种字符，该程序无法进行存储压缩，请重新输入" << endl;
		goto TextIn;
	}
	AHuffmanTree.StatisticNumberOfLeaves(Number); //统计要建立的Huffman树的叶子树
	int Weight[256] = { 0 }; //初始化权重数组，便于处理数据
	char Name[256] = { 0 }; //初始化字符数组，便于处理数据

	GetWeightArray(Weight, Words, Number); //将符合处理格式的Word类型数据转换为权重数组
	GetNameArray(Name, Words, Number); //将符合处理格式的Word类型数据转换为名称数组
	//其中，名称数组和权重数组同一个下标下的数据一一对应

	//展示各元素权重
	cout << "获得字符种类数：" << Number << endl;

	AHuffmanTree.CreateATree(Weight, Number, Name); //根据权重和名称创建一个Huffman树
	AHuffmanTree.CreateCodeTable(); //创建Huffman编码表
	EncodeSource = ""; //初始化编码结果
	int Result = 0; //编码结果存储
	AHuffmanTree.Encode(Source, EncodeSource); //将Source编码为01格式的EncodeSource，以二进制形式存储到Result
	cout << "编码后的结果为：" << EncodeSource << endl; //输出编码结果
	delete[] Words;
	Words = NULL;
	return EncodeSource;
}

//对文件目录选定的文件进行编码
string CommonCodingFile(Huffman &AHuffmanTree,string &EncodeSource, string FileName)
{
	string Source; //定义原始字符串以便输入
	read_file(FileName, Source);
	Word* Words = NULL; //储存出现的各种字符数
	Words = new Word[MAXNUM*sizeof(Word)];
	GetWords(Words, Source); //将输入的字符存储为Word格式（包含数组内容及其初始统计的权值，为过渡状态的数据）
	DeleteZeros(Words, Source); //将上一步储存的Word格式数据转换为该程序设计上可以顺利进行的存储格式
	int Number = GetNumber(Words); //获得字符种类数
	if (Number == 1) //处理只输入一种字符的情况
	{
		cout << "您的文件中只有字符，该程序无法进行存储压缩，请检查您的Source.txt文件" << endl;
		exit(-1);
	}
	AHuffmanTree.StatisticNumberOfLeaves(Number); //统计要建立的Huffman树的叶子树
	int Weight[256] = { 0 }; //初始化权重数组，便于处理数据
	char Name[256] = { 0 }; //初始化字符数组，便于处理数据

	GetWeightArray(Weight, Words, Number); //将符合处理格式的Word类型数据转换为权重数组
	GetNameArray(Name, Words, Number); //将符合处理格式的Word类型数据转换为名称数组
	//其中，名称数组和权重数组同一个下标下的数据一一对应
	
	AHuffmanTree.CreateATree(Weight, Number, Name); //根据权重和名称创建一个Huffman树
	AHuffmanTree.CreateCodeTable(); //创建Huffman编码表

	EncodeSource = ""; //初始化编码结果
	int Result = 0; //编码结果存储
	AHuffmanTree.Encode(Source, EncodeSource); //将Source编码为01格式的EncodeSource
	cout << "编码后的结果为：" << EncodeSource << endl; //输出编码结果
	delete [] Words;
	Words = NULL;
	return EncodeSource;
}

//对输入的字符串进行译码
void StringDecode(Huffman &AHuffmanTree)
{
	string DecodeSource = "";
	string EncodeSource = "";
	getline(cin, EncodeSource);
	AHuffmanTree.Decode(EncodeSource, DecodeSource);
	cout << "根据01编码解码的结果为：" << DecodeSource << endl;
}

//获取桌面路径
string  GetDesktopPath()
{
	LPITEMIDLIST pidl;
	LPMALLOC pShellMalloc;
	char szDir[300];
	if (SUCCEEDED(SHGetMalloc(&pShellMalloc)))
	{
		if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl))) {// 如果成功返回true  
			SHGetPathFromIDListA(pidl, szDir);
			pShellMalloc->Free(pidl);
		}
		pShellMalloc->Release();
	}
	return string(szDir);
}