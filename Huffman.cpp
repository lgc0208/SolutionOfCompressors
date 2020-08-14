#define _CRT_SECURE_NO_WARNINGS
#include"Huffman.h"
#include<string>
#include<bitset>
#include<Windows.h>
#include<fstream>
#include<shlobj.h>

#define MAXNUM 10000


//Weight����ÿ���ַ���Ȩֵ��Number�������ַ�����������Name�������ַ��ľ�������
void Huffman::CreateATree(int Weight[], int Number, char Name[])
{
	CodeTable = new Code[Number]; //CodeTable����Code��data
	HuffmanTree = new Node[2 * Number - 1]; //����˫�׽������Һ����±��Ȩֵ
	for (int i = 0; i < Number; i++) //��ÿ�������г�ʼ��
	{
		HuffmanTree[i].weight = Weight[i]; //��ֵȨֵ
		HuffmanTree[i].LChild = HuffmanTree[i].RChild = HuffmanTree[i].parent = -1; //����ʼ��
		CodeTable[i].data = Name[i]; //��ֵ�ַ�
	}

	int x = 0, y = 0; //��СȨֵ����������±�


	for (int i = Number; i < 2 * Number - 1; i++)
	{
		const int MAXVALUE = (int)1E7;
		//��������޸�����ҽ��Ȩֵ��С���������
		int MinWeight_X = MAXVALUE;
		int	MinWeight_Y = MAXVALUE; 
		x = y = 0; //�洢��С�����±�

		for (int j = 0; j < Number + i; j++) //�ҳ����н����Ȩֵ��С���޸������������
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

		HuffmanTree[x].parent = HuffmanTree[y].parent = i; //����С���������ϲ�
		HuffmanTree[i].weight = HuffmanTree[x].weight + HuffmanTree[y].weight; //Ȩֵ�ϲ�
		HuffmanTree[i].LChild = x; //�����±긳ֵ
		HuffmanTree[i].RChild = y; //�Һ����±긳ֵ
		HuffmanTree[i].parent = -1; //˫�׽���ʼ��


	}
}

//�Ե�Number��������
void Huffman::RecursiveCode(int Num, string NewCode)
{
	if (HuffmanTree[Num].LChild == -1) //���ý�������Ϊ�գ����ý��ΪҶ�ӽ�㣩ʱ
	{
		CodeTable[Num].code = NewCode; //�����Ӧ����

		/*Test*/
		cout << "���" << Num << "������Ϊ��"<<CodeTable[Num].data<<",����Ϊ��" << CodeTable[Num].code << endl; 
		/*Test*/
		
		return;
	}
	RecursiveCode(HuffmanTree[Num].LChild, NewCode + '0'); //�����ӽ��б��룬��������һ��0��ʾ����
	RecursiveCode(HuffmanTree[Num].RChild, NewCode + '1'); //���Һ��ӽ��б��룬��������һ��1��ʾ�Һ���
}

//����Huffman�����
void Huffman::CreateCodeTable()
{
	RecursiveCode(2 * Number - 2, ""); //�Ӹ���㿪ʼ���루2 * Number - 2 Ϊ�������±꣩
}


//Huffman�������������
Huffman::~Huffman()
{
	delete[] CodeTable; //ɾ����̬�����CodeTable����ָ��
	delete[] HuffmanTree; //ɾ����̬�����HuffmanTree����ָ��
}

//��¼Huffman������Ҷ����
void Huffman::StatisticNumberOfLeaves(int Num)
{
	Number = Num;
}

//����Huffman������Ҷ����
int Huffman::GetNumberOfLeaves() 
{
	return Number; 
}

//���±���Huffman���ı��������
Code Huffman::ReturnCodeTable(int i)
{
	return CodeTable[i];
}

//Huffman���룬������ΪEncodeSource
void Huffman::Encode(string Source, string &EncodeSource)
{
	EncodeSource = ""; //��ʼ��
	for (unsigned int i = 0; i < Source.size(); i++)
	{
		for (int j = 0; j < Number; j++)
		{
			if (Source[i] == CodeTable[j].data) //���ݴ�����Huffman���ı������ԭʼ�ַ���һһ����Ϊ01�ͱ���
			{
				EncodeSource += CodeTable[j].code; //������õ��ַ�����ӵ�����Ľ����
				break;
			}
		}
	}
}


//Huffman����,SourceΪԴ�봮��DecodeSourceΪ���봮������10��ɵ�Դ�봮������
void Huffman::Decode(string Source, string &DecodeSource)
{
	string Temp = ""; //��ʼ����ʱ�ַ�����������Ҫ����ı����Ӵ�
	for (unsigned int i = 0; i < Source.size(); i++)
	{
		Temp += Source[i]; //����Ҫ������ַ����ĸ����ַ��������
		for (int j = 0; j < Number; j++)
		{
			if (Temp == CodeTable[j].code) //��ѯ��������Ƿ��иñ�������Ӧ���ַ�
			{
				DecodeSource += CodeTable[j].data; //���У����ñ����Ӧ���ַ����������
				Temp = ""; //������Ҫ����Ľ����Ӵ�
				break;
			}
		}
	}


}

//���ַ��������ӦȨֵ��ϣ��õ����ڴ����Word��������
void GetWords(Word Words[], string Source)
{

	for (unsigned int i = 0; i < Source.size(); i++)
	{
		int Judge = 0; //�ж��ַ��Ƿ�Ψһ
		int WeightTemp = 0; //��ʱ����Ȩ��
		for (unsigned int k = 0; k < i + 1; k++)
		{
			if (k == i && k > 0) //�����޷�����Դ�ַ����ĵ�һ���ַ�
				break; 
			if (Source[i] == Words[k].Name) //ʹ��words�д�����ַ���Ψһ��
				Judge = -1; //����Ψһ��Judge��ֵΪ-1 
			else 
				Words[i].Name = Source[i]; //��Ψһ�������ַ�����Word��ʽ������
		}
		for (unsigned int j = i; j < Source.size() + 1; j++) //Ѱ�Һ͸��ַ���ͬ���ַ�����
		{
			if (Source[j] == Words[i].Name) //������ַ������ҵ���ͬ�ַ�������ʱȨ��ֵ��һ
				WeightTemp++;
		}
		if (Judge == -1) //�����ַ�������ͬ����Ȩ�ؼ�Ϊ0�����ں�����������
			Words[i].Weight = 0;
		else
			Words[i].Weight = WeightTemp; //��¼���ַ����ֵĴ���

	}
}

//��words������Ȩ��Ϊ0�ĳ�Ա�Ƶ���󣨽����е�Word��������ת��Ϊ�ʺϳ�������߼��ĸ�ʽ��
void DeleteZeros(Word Words[], string Source)
{
	int SumOfZero = 0;//�ҵ�����������Ԫ��Ϊ0�ĸ���
	for (unsigned int k = 0; k < Source.size(); k++)
	{
		if (Words[k].Weight != 0) //ͳ��������Ԫ��Ϊ0�ĳ�Ա����
		{
			SumOfZero++; 
		}
	}
	for (int k = 0; k < SumOfZero; k++)//��Ȩ��Ϊ0������Ԫ���Ƶ����
	{
		for (unsigned int i = 0; i < Source.size(); i++)
		{
			if (Words[i].Weight == 0)
			{
				for (unsigned int j = i; j < Source.size() || j == 256; j++)//��0�������Ԫ��ǰ��
				{

					Words[j] = Words[j + 1]; //��j��Ľ��ǰ��һλ
				}
			}
		}
	}

	/*Test*/
	for (unsigned int i = 0; i < Source.size() ; i++)
	{
		if (Words[i].Weight != 0)
		cout << "�õ����ַ���ȨֵΪ��" << Words[i].Name << " " << Words[i].Weight << endl;
	}
	/*Test*/

}

//���������ַ�������
int GetNumber(Word Words[])
{
	int Number = 0;
	while (Words[Number].Weight != 0) //ͳ��Ȩֵ��Ϊ0���ַ���
	{
		Number++;
	}
	return Number;
}



//�õ�Ȩ�����飨����������һһ��Ӧ��
void GetWeightArray(int Weight[], Word Words[], int Number)
{
	for (int i = 0; i < Number; i++)
	{
		Weight[i] = Words[i].Weight;
	}
}

//�õ��������飨��Ȩ������һһ��Ӧ��
void GetNameArray(char Name[], Word Words[], int Number)
{
	for (int i = 0; i < Number; i++)
	{
		Name[i] = Words[i].Name;
	}
}

//��ȡ�ļ��е���������
void read_file(const string& filename, string& filedata)
{
	ifstream infile;
	char* fileBuffer = NULL;
	infile.open(filename, ios::binary);
	if (infile.is_open())
	{
		infile.seekg(0, ios::end);
		auto len = infile.tellg();  //��ȡ�ļ�����
		infile.seekg(0, ios::beg);  //���ö�ȡλ��Ϊ��ʼλ��

		fileBuffer = new char[(size_t)len + 1];
		memset(fileBuffer, 0, (size_t)len + 1);
		infile.read(fileBuffer, len);
		filedata = fileBuffer;
		delete[] fileBuffer;
	}
	else
	{
		cout << "�����ڸ��ļ�,������������иó���" << endl;
		return;
	}
		
	infile.close();
}

//�Զ�������ʽд�������ĵ�
void DesktopwriteBit(string &ch)
{
	int i;
	int j;
	int count = 0; //�����ַ�������
	int  num;    //�洢�ַ���Ҫ�Ķ��ٸ��ֽ� 
	int left;	//�ַ���ʣ�಻��8λ�ĸ��� 
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
		count++;        //ͳ���ַ����� 
	}
	num = count / 8;
	left = count % 8;
	cout << endl << "�ַ��������ַ�" << count << "����ռ" << count << "�ֽ�" << endl << "�洢��Result.txt�ļ���ռ" << (left != 0 ? 4 + num + 1 : 4 + num) << "�ֽ�" << endl;
	if (left == 0)	//���leftΪ0����ônum���ֽڸպ��ܹ���ţ�������Ҫnum + 1�ֽ� 
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
	for (i = 0; i < count; i++)//λ���㣬ÿ8���ַ���2���Ƶ���ʽ������һ���ַ��� 
	{
		if (i % 8 == 0)
		{
			j++;
		}
		p[j] <<= 1;
		ch[i] -= '0';
		p[j] |= ch[i];
	}

	if (left != 0) //���left��Ϊ0����Ҫ��ʣ��ļ���λ����߿�£ 
	{
		p[j] <<= 8 - left; //����leftΪ2����00000011����Ҫ����6λ��Ϊ11000000 
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

//�Զ�������ʽд��Ŀ¼�ĵ�
void writeBit(string& ch)
{
	int i;
	int j;
	int count = 0; //�����ַ�������
	int  num;    //�洢�ַ���Ҫ�Ķ��ٸ��ֽ� 
	int left;	//�ַ���ʣ�಻��8λ�ĸ��� 
	FILE* fp = NULL;
	char* p = NULL;
	if (NULL == (fp = fopen("Result.txt", "wb")))
	{
		cout << "open file error" << endl;
	}

	for (i = 0; ch[i] != 0; i++)
	{
		count++;        //ͳ���ַ����� 
	}
	num = count / 8;
	left = count % 8;
	cout << endl << "�ַ��������ַ�" << count << "����ռ" << count << "�ֽ�" << endl << "�洢��Result.txt�ļ���ռ" << (left != 0 ? 4 + num + 1 : 4 + num) << "�ֽ�" << endl;
	if (left == 0)	//���leftΪ0����ônum���ֽڸպ��ܹ���ţ�������Ҫnum + 1�ֽ� 
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
	for (i = 0; i < count; i++)//λ���㣬ÿ8���ַ���2���Ƶ���ʽ������һ���ַ��� 
	{
		if (i % 8 == 0)
		{
			j++;
		}
		p[j] <<= 1;
		ch[i] -= '0';
		p[j] |= ch[i];
	}

	if (left != 0) //���left��Ϊ0����Ҫ��ʣ��ļ���λ����߿�£ 
	{
		p[j] <<= 8 - left; //����leftΪ2����00000011����Ҫ����6λ��Ϊ11000000 
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


//��ȡ�������ļ�������ת��Ϊ01�ַ���
void readBit(string& String01)
{
	FILE* fp = NULL;
	int count;
	int num;
	int left;
	int i=0, j=0;
	unsigned char flag = 128;	//��0b1000000,������λ����
	char* p = NULL;

	if (NULL == (fp = fopen("Result.txt", "rb")))
	{
		cout << "open file error" << endl;
		return;
	}

	else
	{
	fread(&count, sizeof(count), 1, fp);
	num = count / 8; //ÿ8λΪһ��
	left = count % 8; //ʣ�������
	if (left == 0)
	{
		p = (char*)malloc(sizeof(char) * num);
		if (p != NULL)
			fread(p, 1, num, fp);
		else
			cout << "��ȡ�������ļ����ֳ���" << endl;
	}
	else
	{
		p = (char*)malloc(sizeof(char) * (num + 1));
		if (p != NULL)
			fread(p, 1, num + 1, fp);
		else
			cout << "��ȡ�������ļ����ֳ���" << endl;
	}
	fclose(fp);
	}
	j = -1;
	cout << endl << "Result.txt�ļ��洢�Ķ�����Ϊ:" << endl;
	for (i = 0; i < count; i++)
	{
		if (i % 8 == 0)
		{
			j++;
			flag = 128;
		}
		if (p)
		{
			if ((p[j] & flag))//ͨ���ı�flag�ַ�2����1��λ���ж���һ���ֽ��ĸ�λ��1���ĸ�λ��0,������ַ���ʽ
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

//��ȡ�������ļ�������ת��Ϊ01�ַ���
void DesktopreadBit(string& String01)
{
	FILE* fp = NULL;
	int count;
	int num;
	int left;
	int i = 0, j = 0;
	unsigned char flag = 128;	//��0b1000000,������λ����
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
		num = count / 8; //ÿ8λΪһ��
		left = count % 8; //ʣ�������
		if (left == 0)
		{
			p = (char*)malloc(sizeof(char) * num);
			if (p != NULL)
				fread(p, 1, num, fp);
			else
				cout << "��ȡ�������ļ����ֳ���" << endl;
		}
		else
		{
			p = (char*)malloc(sizeof(char) * (num + 1));
			if (p != NULL)
				fread(p, 1, num + 1, fp);
			else
				cout << "��ȡ�������ļ����ֳ���" << endl;
		}
		fclose(fp);
	}
	j = -1;
	cout << endl << "Result.txt�ļ��洢�Ķ�����Ϊ:" << endl;
	for (i = 0; i < count; i++)
	{
		if (i % 8 == 0)
		{
			j++;
			flag = 128;
		}
		if (p)
		{
			if ((p[j] & flag))//ͨ���ı�flag�ַ�2����1��λ���ж���һ���ֽ��ĸ�λ��1���ĸ�λ��0,������ַ���ʽ
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

//��������ı����б���
string CodingText(Huffman &AHuffmanTree,string &EncodeSource)
{
	string Source=""; //����ԭʼ�ַ����Ա�����
	TextIn:cout << "������һ���ı���" << endl;
	cin >> Source;
	Word* Words = NULL; //������ֵĸ����ַ���
	Words = new Word[MAXNUM * sizeof(Word)];
	GetWords(Words, Source); //��������ַ��洢ΪWord��ʽ�������������ݼ����ʼͳ�Ƶ�Ȩֵ��Ϊ����״̬�����ݣ�
	DeleteZeros(Words, Source); //����һ�������Word��ʽ����ת��Ϊ�ó�������Ͽ���˳�����еĴ洢��ʽ
	int Number = GetNumber(Words); //����ַ�������
	if (Number == 1) //����ֻ����һ���ַ������
	{
		cout << "��ֻ����һ���ַ����ó����޷����д洢ѹ��������������" << endl;
		goto TextIn;
	}
	AHuffmanTree.StatisticNumberOfLeaves(Number); //ͳ��Ҫ������Huffman����Ҷ����
	int Weight[256] = { 0 }; //��ʼ��Ȩ�����飬���ڴ�������
	char Name[256] = { 0 }; //��ʼ���ַ����飬���ڴ�������

	GetWeightArray(Weight, Words, Number); //�����ϴ����ʽ��Word��������ת��ΪȨ������
	GetNameArray(Name, Words, Number); //�����ϴ����ʽ��Word��������ת��Ϊ��������
	//���У����������Ȩ������ͬһ���±��µ�����һһ��Ӧ

	//չʾ��Ԫ��Ȩ��
	cout << "����ַ���������" << Number << endl;

	AHuffmanTree.CreateATree(Weight, Number, Name); //����Ȩ�غ����ƴ���һ��Huffman��
	AHuffmanTree.CreateCodeTable(); //����Huffman�����
	EncodeSource = ""; //��ʼ��������
	int Result = 0; //�������洢
	AHuffmanTree.Encode(Source, EncodeSource); //��Source����Ϊ01��ʽ��EncodeSource���Զ�������ʽ�洢��Result
	cout << "�����Ľ��Ϊ��" << EncodeSource << endl; //���������
	delete[] Words;
	Words = NULL;
	return EncodeSource;
}

//���ļ�Ŀ¼ѡ�����ļ����б���
string CommonCodingFile(Huffman &AHuffmanTree,string &EncodeSource, string FileName)
{
	string Source; //����ԭʼ�ַ����Ա�����
	read_file(FileName, Source);
	Word* Words = NULL; //������ֵĸ����ַ���
	Words = new Word[MAXNUM*sizeof(Word)];
	GetWords(Words, Source); //��������ַ��洢ΪWord��ʽ�������������ݼ����ʼͳ�Ƶ�Ȩֵ��Ϊ����״̬�����ݣ�
	DeleteZeros(Words, Source); //����һ�������Word��ʽ����ת��Ϊ�ó�������Ͽ���˳�����еĴ洢��ʽ
	int Number = GetNumber(Words); //����ַ�������
	if (Number == 1) //����ֻ����һ���ַ������
	{
		cout << "�����ļ���ֻ���ַ����ó����޷����д洢ѹ������������Source.txt�ļ�" << endl;
		exit(-1);
	}
	AHuffmanTree.StatisticNumberOfLeaves(Number); //ͳ��Ҫ������Huffman����Ҷ����
	int Weight[256] = { 0 }; //��ʼ��Ȩ�����飬���ڴ�������
	char Name[256] = { 0 }; //��ʼ���ַ����飬���ڴ�������

	GetWeightArray(Weight, Words, Number); //�����ϴ����ʽ��Word��������ת��ΪȨ������
	GetNameArray(Name, Words, Number); //�����ϴ����ʽ��Word��������ת��Ϊ��������
	//���У����������Ȩ������ͬһ���±��µ�����һһ��Ӧ
	
	AHuffmanTree.CreateATree(Weight, Number, Name); //����Ȩ�غ����ƴ���һ��Huffman��
	AHuffmanTree.CreateCodeTable(); //����Huffman�����

	EncodeSource = ""; //��ʼ��������
	int Result = 0; //�������洢
	AHuffmanTree.Encode(Source, EncodeSource); //��Source����Ϊ01��ʽ��EncodeSource
	cout << "�����Ľ��Ϊ��" << EncodeSource << endl; //���������
	delete [] Words;
	Words = NULL;
	return EncodeSource;
}

//��������ַ�����������
void StringDecode(Huffman &AHuffmanTree)
{
	string DecodeSource = "";
	string EncodeSource = "";
	getline(cin, EncodeSource);
	AHuffmanTree.Decode(EncodeSource, DecodeSource);
	cout << "����01�������Ľ��Ϊ��" << DecodeSource << endl;
}

//��ȡ����·��
string  GetDesktopPath()
{
	LPITEMIDLIST pidl;
	LPMALLOC pShellMalloc;
	char szDir[300];
	if (SUCCEEDED(SHGetMalloc(&pShellMalloc)))
	{
		if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl))) {// ����ɹ�����true  
			SHGetPathFromIDListA(pidl, szDir);
			pShellMalloc->Free(pidl);
		}
		pShellMalloc->Release();
	}
	return string(szDir);
}