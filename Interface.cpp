#include"Interface.h"

//�ָ���
void DevidedLine()
{
	for (int i = 0; i < 30; i++)
		cout << "-";
	cout << endl;
}

//��ҳ��
void FirstPage()
{
	DevidedLine();
	cout << "��ӭʹ��Huffman�����򣬸ó��������й����л�չʾ�������ร��������ʾ���в���~" << endl;
	cout << "ע�⣬��Ҫ�ȱ������ܽ��н���ร�" << endl;
	cout << endl;
	cout << "����Ҫ���б��������������1��" << endl;
	cout << "����Ҫ�������������������2��" << endl;
	cout << "��Ҫ�˳���������0��" << endl;
	DevidedLine();
}

//����ҳ��
void CodeChoosePage()
{
	DevidedLine();
	cout << "����ǰѡ����ǡ����롱�����~" << endl;
	cout << "����Ҫ�����ı����б��룬������1��" << endl;
	cout << "������Ҫ���ļ����б��룬������2��" << endl;
	cout << "��Ҫ������ҳ�棬������3��" << endl;
	cout << "��Ҫ�˳���������0��" << endl;
	DevidedLine();
}

//ѡ������ʾ���ļ����Զ����ļ�
void FileChoosePage()
{
	DevidedLine();
	cout << "����ǰѡ����ļ����б���" << endl;
	cout << "ѡ��ʾ���ı����б��룬������1" << endl;
	cout << "(ע��ʾ���ı������ڹ����ļ���Ŀ¼�£�����ΪSource.txt������Ϊʵ��ʾ��)" << endl;
	cout << "�Ե��������ϵ��ļ����б��룬������2" << endl;
	cout << "���ļ�Ŀ¼�ڵ��ļ����б��룬������3" << endl;
	DevidedLine();
}


//�ı��������ҳ��
string TextInCodePage(Huffman &AHuffmanTree)
{
	string EncodeSource="";
	DevidedLine();
	EncodeSource=CodingText(AHuffmanTree,EncodeSource);
	cout << endl;
	cout << "��Ҫ�ص���ҳ�棬������1��" << endl;
	cout << "��Ҫ���ļ���ʽ����ñ��룬������2��" << endl;
	cout << "��Ҫ�˳���������0��" << endl;
	DevidedLine();
	return EncodeSource;
}


//��ʾ���ļ�����ҳ��
string DemoFileInCode(Huffman &AHuffmanTree)
{
	string EncodeSource="";
	string FileName="Source.txt";
	DevidedLine();
	cout << "���ڽ��б��룬���Ե�...." << endl;
	EncodeSource=CommonCodingFile(AHuffmanTree,EncodeSource,FileName);
	cout << endl;
	cout << "��Ҫ�ص���ҳ�棬������1��" << endl;
	cout << "��Ҫ���ļ���ʽ����ñ��룬������2��" << endl;
	cout << "��Ҫ�˳���������0��" << endl;
	DevidedLine();
	return EncodeSource;
}

//�������ļ�����ҳ��
string DesktopFileInCode(Huffman& AHuffmanTree)
{
	string EncodeSource = "";
	string DeskPath = GetDesktopPath();
	DeskPath += "//";
	string FileName = "";
	cout << "�����������ϵ��ļ���������׺����";
	cin >> FileName;
	DeskPath += FileName;
	DevidedLine();
	cout << "���ڽ��б��룬���Ե�...." << endl;
	EncodeSource = CommonCodingFile(AHuffmanTree, EncodeSource, DeskPath);
	cout << endl;
	cout << "��Ҫ�ص���ҳ�棬������1��" << endl;
	cout << "��Ҫ���ļ���ʽ����ñ��룬������2��" << endl;
	cout << "��Ҫ�˳���������0��" << endl;
	DevidedLine();
	return EncodeSource;
}

//�Գ���Ŀ¼�ļ�����ҳ��
string CommonFileInCode(Huffman& AHuffmanTree)
{
	string EncodeSource = "";
	string FileName = "";
	cout << "���������Ŀ¼�µ��ļ���������׺����";
	cin >> FileName;
	DevidedLine();
	cout << "���ڽ��б��룬���Ե�...." << endl;
	EncodeSource = CommonCodingFile(AHuffmanTree, EncodeSource, FileName);
	cout << endl;
	cout << "��Ҫ�ص���ҳ�棬������1��" << endl;
	cout << "��Ҫ���ļ���ʽ����ñ��룬������2��" << endl;
	cout << "��Ҫ�˳���������0��" << endl;
	DevidedLine();
	return EncodeSource;
}

//ѡ�񷵻���ҳ���˳�
void FirstOrOut()
{
	DevidedLine();
	cout << "��Ҫ�ص���ҳ�棬������1��" << endl;
	cout << "��Ҫ�˳���������0��" << endl;
	DevidedLine();
}

//�ı�/�ļ��������ҳ��_�ļ�����
void TextSave(string &Result)
{
	DevidedLine();
	cout << "�ļ���ʼ���棬����������ó�����ͬ��Ŀ¼�£�" << endl;
	cout << "�ļ���Ĭ��Ϊ��Result.txt��" << endl;
	writeBit(Result);
	cout << "�ļ�����ɹ�" << endl;
	DevidedLine();
}

//�ı�/�ļ��������ҳ��_�ļ���������
void DesktopTextSave(string& Result)
{
	DevidedLine();
	cout << "�ļ���ʼ���棬����������ó�����ͬ��Ŀ¼�£�" << endl;
	cout << "�ļ���Ĭ��Ϊ��Result.txt��" << endl;
	DesktopwriteBit(Result);
	cout << "�ļ�����ɹ�" << endl;
	DevidedLine();
}

//�������
void DecodePage()
{
	DevidedLine();
	cout << "������ѡ���������ҳ�棬��ȷ�����Ѿ�����ɹ�����" << endl;
	cout << "����Ҫ�����ı����룬������1��" << endl;
	cout << "����Ҫ�����ļ����룬������2��" << endl;
	cout << "���˳�����������0" << endl;
	DevidedLine();
}

//�����ı��������
void TextInDecode(Huffman &AHuffmanTree)
{
	DevidedLine();
	cout << "������һ��01�ַ�������ȷ�����Ѿ����й����룩��" << endl;
	StringDecode(AHuffmanTree);
	DevidedLine();
}

//Ŀ¼�ļ��������
void CommonFileInDecode(Huffman &AHuffmanTree)
{
	string String01 = "";
	string Result = "";
	DevidedLine();
	cout << "���������ڽ����ļ����룬���ڶ�ȡ�ó���Ŀ¼�µ�Result.txt�ļ�����ȷ�����Ѿ�����������ļ���" << endl;
	readBit(String01);
	AHuffmanTree.Decode(String01, Result);
	cout << "����Ľ��Ϊ��" << endl << Result << endl;
	DevidedLine();
}

//�����ļ��������
void DesktopFileInDecode(Huffman& AHuffmanTree)
{
	string String01 = "";
	string Result = "";
	DevidedLine();
	cout << "�����ڽ����ļ����룬���ڶ�ȡ����Ŀ¼�µ�Result.txt�ļ�����ȷ�����Ѿ�����������ļ�" << endl;
	DesktopreadBit(String01);
	AHuffmanTree.Decode(String01, Result);
	cout << "����Ľ��Ϊ��" << endl << Result << endl;
	DevidedLine();
}

//���������ʾ����
void Error()
{
	DevidedLine();
	cout << "����ǰ������������˶Ժ�������~" << endl;
	DevidedLine();
}

//�ļ�����ѡ�����
void DecodeFilePages()
{
	DevidedLine();
	cout << "�����ڽ��н����ļ���������ȷ�����Ѿ����������Ӧ���ļ�" << endl;
	cout << "�Ը�Ŀ¼��Result.txt�ļ�����������1" << endl;
	cout << "�������Result.txt�ļ�����������2" << endl;
	cout << "������ҳ��������3" << endl;
	DevidedLine();
}