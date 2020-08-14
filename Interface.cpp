#include"Interface.h"

//分割线
void DevidedLine()
{
	for (int i = 0; i < 30; i++)
		cout << "-";
	cout << endl;
}

//首页面
void FirstPage()
{
	DevidedLine();
	cout << "欢迎使用Huffman树程序，该程序在运行过程中会展示编码过程喔，请根据提示进行操作~" << endl;
	cout << "注意，需要先编码后才能进行解码喔！" << endl;
	cout << endl;
	cout << "若需要进行编码操作，请输入1；" << endl;
	cout << "若需要进行译码操作，请输入2；" << endl;
	cout << "若要退出，请输入0；" << endl;
	DevidedLine();
}

//编码页面
void CodeChoosePage()
{
	DevidedLine();
	cout << "您当前选择的是“编码”操作喔~" << endl;
	cout << "若需要输入文本进行编码，请输入1；" << endl;
	cout << "若是需要对文件进行编码，请输入2；" << endl;
	cout << "若要返回首页面，请输入3；" << endl;
	cout << "若要退出，请输入0；" << endl;
	DevidedLine();
}

//选择运行示例文件或自定义文件
void FileChoosePage()
{
	DevidedLine();
	cout << "您当前选择对文件进行编码" << endl;
	cout << "选择示例文本进行编码，请输入1" << endl;
	cout << "(注：示例文本保存在工程文件的目录下，命名为Source.txt，内容为实验示例)" << endl;
	cout << "对电脑桌面上的文件进行编码，请输入2" << endl;
	cout << "对文件目录内的文件进行编码，请输入3" << endl;
	DevidedLine();
}


//文本输入编码页面
string TextInCodePage(Huffman &AHuffmanTree)
{
	string EncodeSource="";
	DevidedLine();
	EncodeSource=CodingText(AHuffmanTree,EncodeSource);
	cout << endl;
	cout << "若要回到首页面，请输入1；" << endl;
	cout << "若要以文件形式保存该编码，请输入2；" << endl;
	cout << "若要退出，请输入0；" << endl;
	DevidedLine();
	return EncodeSource;
}


//对示例文件编码页面
string DemoFileInCode(Huffman &AHuffmanTree)
{
	string EncodeSource="";
	string FileName="Source.txt";
	DevidedLine();
	cout << "正在进行编码，请稍等...." << endl;
	EncodeSource=CommonCodingFile(AHuffmanTree,EncodeSource,FileName);
	cout << endl;
	cout << "若要回到首页面，请输入1；" << endl;
	cout << "若要以文件形式保存该编码，请输入2；" << endl;
	cout << "若要退出，请输入0；" << endl;
	DevidedLine();
	return EncodeSource;
}

//对桌面文件编码页面
string DesktopFileInCode(Huffman& AHuffmanTree)
{
	string EncodeSource = "";
	string DeskPath = GetDesktopPath();
	DeskPath += "//";
	string FileName = "";
	cout << "请输入桌面上的文件名（带后缀）：";
	cin >> FileName;
	DeskPath += FileName;
	DevidedLine();
	cout << "正在进行编码，请稍等...." << endl;
	EncodeSource = CommonCodingFile(AHuffmanTree, EncodeSource, DeskPath);
	cout << endl;
	cout << "若要回到首页面，请输入1；" << endl;
	cout << "若要以文件形式保存该编码，请输入2；" << endl;
	cout << "若要退出，请输入0；" << endl;
	DevidedLine();
	return EncodeSource;
}

//对程序目录文件编码页面
string CommonFileInCode(Huffman& AHuffmanTree)
{
	string EncodeSource = "";
	string FileName = "";
	cout << "请输入程序目录下的文件名（带后缀）：";
	cin >> FileName;
	DevidedLine();
	cout << "正在进行编码，请稍等...." << endl;
	EncodeSource = CommonCodingFile(AHuffmanTree, EncodeSource, FileName);
	cout << endl;
	cout << "若要回到首页面，请输入1；" << endl;
	cout << "若要以文件形式保存该编码，请输入2；" << endl;
	cout << "若要退出，请输入0；" << endl;
	DevidedLine();
	return EncodeSource;
}

//选择返回首页或退出
void FirstOrOut()
{
	DevidedLine();
	cout << "若要回到首页面，请输入1；" << endl;
	cout << "若要退出，请输入0；" << endl;
	DevidedLine();
}

//文本/文件输入编码页面_文件保存
void TextSave(string &Result)
{
	DevidedLine();
	cout << "文件开始保存，将保存在与该程序相同的目录下；" << endl;
	cout << "文件名默认为“Result.txt”" << endl;
	writeBit(Result);
	cout << "文件保存成功" << endl;
	DevidedLine();
}

//文本/文件输入编码页面_文件保存桌面
void DesktopTextSave(string& Result)
{
	DevidedLine();
	cout << "文件开始保存，将保存在与该程序相同的目录下；" << endl;
	cout << "文件名默认为“Result.txt”" << endl;
	DesktopwriteBit(Result);
	cout << "文件保存成功" << endl;
	DevidedLine();
}

//译码界面
void DecodePage()
{
	DevidedLine();
	cout << "你现在选择的是译码页面，请确保您已经编码成功过；" << endl;
	cout << "若需要输入文本译码，请输入1；" << endl;
	cout << "若需要输入文件译码，请输入2；" << endl;
	cout << "若退出程序，请输入0" << endl;
	DevidedLine();
}

//输入文本译码界面
void TextInDecode(Huffman &AHuffmanTree)
{
	DevidedLine();
	cout << "请输入一段01字符串（请确保您已经进行过编码）：" << endl;
	StringDecode(AHuffmanTree);
	DevidedLine();
}

//目录文件译码界面
void CommonFileInDecode(Huffman &AHuffmanTree)
{
	string String01 = "";
	string Result = "";
	DevidedLine();
	cout << "您现在正在进行文件译码，正在读取该程序目录下的Result.txt文件，请确保您已经编码产生该文件；" << endl;
	readBit(String01);
	AHuffmanTree.Decode(String01, Result);
	cout << "译码的结果为：" << endl << Result << endl;
	DevidedLine();
}

//桌面文件译码界面
void DesktopFileInDecode(Huffman& AHuffmanTree)
{
	string String01 = "";
	string Result = "";
	DevidedLine();
	cout << "您正在进行文件译码，正在读取桌面目录下的Result.txt文件，请确保您已经编码产生该文件" << endl;
	DesktopreadBit(String01);
	AHuffmanTree.Decode(String01, Result);
	cout << "译码的结果为：" << endl << Result << endl;
	DevidedLine();
}

//输入错误提示界面
void Error()
{
	DevidedLine();
	cout << "您当前的输入有误，请核对后再输入~" << endl;
	DevidedLine();
}

//文件解码选择界面
void DecodeFilePages()
{
	DevidedLine();
	cout << "您正在进行解码文件操作，请确保您已经编码产生对应的文件" << endl;
	cout << "对根目录的Result.txt文件解码请输入1" << endl;
	cout << "对桌面的Result.txt文件解码请输入2" << endl;
	cout << "返回首页面请输入3" << endl;
	DevidedLine();
}