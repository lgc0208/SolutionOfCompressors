#ifndef _INTERFACE_H
#define _INTERFACE_H
#include"Huffman.h"

//分割线
void DevidedLine();

//首页面
void FirstPage();

//编码页面
void CodeChoosePage();

//文本输入编码页面
string TextInCodePage(Huffman &AHuffmanTree);

//对示例文件编码页面
string DemoFileInCode(Huffman &AHuffmanTree);

//对桌面文件编码页面
string DesktopFileInCode(Huffman& AHuffmanTree);

//对程序目录文件编码页面
string CommonFileInCode(Huffman& AHuffmanTree);

//选择返回首页或退出
void FirstOrOut();

//文本/文件输入编码页面_文件保存
void TextSave(string &Result);

//文本/文件输入编码页面_文件保存桌面
void DesktopTextSave(string& Result);

//译码界面
void DecodePage();

//输入文本译码界面
void TextInDecode(Huffman &AHuffmanTree);

//程序目录读入文件译码界面
void CommonFileInDecode(Huffman &AHuffmanTree);

//桌面文件译码界面
void DesktopFileInDecode(Huffman& AHuffmanTree);

//输入错误提示界面
void Error();

//选择运行示例文件或自定义文件
void FileChoosePage();

//文件解码选择界面
void DecodeFilePages();
#endif // !_INTERFACE_H