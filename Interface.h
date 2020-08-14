#ifndef _INTERFACE_H
#define _INTERFACE_H
#include"Huffman.h"

//�ָ���
void DevidedLine();

//��ҳ��
void FirstPage();

//����ҳ��
void CodeChoosePage();

//�ı��������ҳ��
string TextInCodePage(Huffman &AHuffmanTree);

//��ʾ���ļ�����ҳ��
string DemoFileInCode(Huffman &AHuffmanTree);

//�������ļ�����ҳ��
string DesktopFileInCode(Huffman& AHuffmanTree);

//�Գ���Ŀ¼�ļ�����ҳ��
string CommonFileInCode(Huffman& AHuffmanTree);

//ѡ�񷵻���ҳ���˳�
void FirstOrOut();

//�ı�/�ļ��������ҳ��_�ļ�����
void TextSave(string &Result);

//�ı�/�ļ��������ҳ��_�ļ���������
void DesktopTextSave(string& Result);

//�������
void DecodePage();

//�����ı��������
void TextInDecode(Huffman &AHuffmanTree);

//����Ŀ¼�����ļ��������
void CommonFileInDecode(Huffman &AHuffmanTree);

//�����ļ��������
void DesktopFileInDecode(Huffman& AHuffmanTree);

//���������ʾ����
void Error();

//ѡ������ʾ���ļ����Զ����ļ�
void FileChoosePage();

//�ļ�����ѡ�����
void DecodeFilePages();
#endif // !_INTERFACE_H