//输入的字符子串只有一个元素时，应做出提示；
#include"Interface.h"

int main()
{
	Huffman AHuffmanTree; //定义Huffman树
	int Judge; //判断用户选择
	int JudgeFirstPage; //便于返回首页
	while (true)
	{
		FirstPages:FirstPage();
		cin >> JudgeFirstPage;
		switch (JudgeFirstPage)
		{
			case 1://编码操作
			{
				CodePages:CodeChoosePage();
				cin >> Judge;
				switch (Judge)
				{
					case 1: //对文本编码
					{
						string Source = "";
					CodeTextPages:Source = TextInCodePage(AHuffmanTree);
						cin >> Judge;
						switch (Judge)
						{
						case 1: //返回首页
						{
							goto FirstPages; //https://ask.csdn.net/questions/1064687
							break;
						}
						case 2: //文件保存
						{
							TextSave(Source);
							FileSaveEnd_TextIn:FirstOrOut();
							cin >> Judge;
							switch (Judge)
							{
							case 1:
							{
								goto FirstPages;
								break;
							}
							case 0:
							{
								return 0;
							}
							default:
							{
								Error();
								goto FileSaveEnd_TextIn;
								break;
							}
							}
						case 3: //退出
						{
							return 0;
						}
						default:
						{
							Error();
							goto CodeTextPages;
							break;
						}
						}
						break;
						}
					}
					case 2: //对文件编码
					{	
						string Source = "";
						FileChoosePages:FileChoosePage();
						cin >> Judge;
						switch (Judge)
						{
						case 1: //对示例文本编码
						{
							CodeFilePages:Source = DemoFileInCode(AHuffmanTree);
							cin >> Judge;
							switch (Judge)
							{
							case 1: //回到首页面
							{
								goto FirstPages;
								break;
							}
							case 2: //以文件形式保存
							{
								TextSave(Source);
							DemoFileSaveEnd_FileIn:FirstOrOut();
								cin >> Judge;
								switch (Judge)
								{
								case 1:
								{
									goto FirstPages;
									break;
								}
								case 0:
								{
									return 0;
								}
								default:
								{
									Error();
									goto DemoFileSaveEnd_FileIn;
									break;
								}
								}
								break;
							}
							case 0: //退出
							{
								return 0;
							}
							default:
							{
								Error();
								goto CodeFilePages;
								break;
							}
							}
							break;
						}
						case 2: //对桌面文件编码
						{
							Source = DesktopFileInCode(AHuffmanTree);
							DesktopFilePages:cin >> Judge;
							switch (Judge)
							{
							case 1: //回到首页面
							{
								goto FirstPages;
								break;
							}
							case 2: //以文件形式保存
							{
								DesktopTextSave(Source);
								DesktopFileSaveEnd_FileIn:FirstOrOut();
								cin >> Judge;
								switch (Judge)
								{
								case 1:
								{
									goto FirstPages;
									break;
								}
								case 0:
								{
									return 0;
								}
								default:
								{
									Error();
									goto DesktopFileSaveEnd_FileIn;
									break;
								}
								}
								break;
							}
							case 0: //退出
							{
								return 0;
							}
							default:
							{
								Error();
								goto DesktopFilePages;
								break;
							}
							}
							break;
						}
						case 3: //目录文件编码
						{
							Source = CommonFileInCode(AHuffmanTree);
							CommonFilePages:cin >> Judge;
							switch (Judge)
							{
							case 1: //回到首页面
							{
								goto FirstPages;
								break;
							}
							case 2: //以文件形式保存
							{
								TextSave(Source);
								CommonFileSaveEnd_FileIn:FirstOrOut();
								cin >> Judge;
								switch (Judge)
								{
								case 1:
								{
									goto FirstPages;
									break;
								}
								case 0:
								{
									return 0;
								}
								default:
								{
									Error();
									goto CommonFileSaveEnd_FileIn;
									break;
								}
								}
								break;
							}
							case 0: //退出
							{
								return 0;
							}
							default:
							{
								Error();
								goto CommonFilePages;
								break;
							}
							}
							break;
							break;
						}
						default:
						{
							Error();
							goto FileChoosePages;
							break;
						}
						}

						break;
					}
					case 3: //回到首页面
					{
						goto FirstPages;
						break;
					}
					case 0:
					{
						return 0;
					}
					default:
					{
						Error();
						goto CodePages;
						break;
					}
				}
			break;
			}
			case 2: //译码操作
			{
				DecodePages:DecodePage();
				cin >> Judge;
				switch (Judge)
				{
					case 1: //文本译码
					{
						TextInDecode(AHuffmanTree);
						DecodeTextPages: FirstOrOut();
						cin >> Judge;
						switch (Judge)
						{
						case 1: //回到首页
						{
							goto FirstPages;
							break;
						}
						case 0: //退出
						{
							return 0;
						}
						default:
						{
							Error();
							goto DecodeTextPages;
							break;
						}
						}
					break;
					}
					case 2: //文件译码
					{
						DecodeTheFilePage:DecodeFilePages();
						cin >> Judge;
						switch (Judge)
						{
						case 1://根目录译码
						{
							CommonFileInDecode(AHuffmanTree);
						DecodeFilePages_Common:FirstOrOut();
							cin >> Judge;
							switch (Judge)
							{
							case 1: //回到首页
							{
								goto FirstPages;
								break;
							}
							case 0: //退出
							{
								return 0;
							}
							default:
							{
								Error();
								goto DecodeFilePages_Common;
								break;
							}
							break;
							}

						}
						case 2: //桌面目录译码
						{
							DesktopFileInDecode(AHuffmanTree);
							DecodeFilePages_Desktop:FirstOrOut();
							cin >> Judge;
							switch (Judge)
							{
							case 1: //回到首页
							{
								goto FirstPages;
								break;
							}
							case 0: //退出
							{
								return 0;
							}
							default:
							{
								Error();
								goto DecodeFilePages_Desktop;
								break;
							}
							break;
							}
							break;
						}
						default:
						{
							Error();
							goto DecodeTheFilePage;
							break;
						}
						}
						DecodeFilePages:FirstOrOut();
						cin >> Judge;
						switch (Judge)
						{
							case 1: //回到首页
							{
								goto FirstPages;
								break;
							}
							case 0: //退出
							{
								return 0;
							}
							default:
							{
								Error();
								goto DecodeFilePages;
								break;
							}
						break;

					}
					case 0: //退出
					{
						return 0;
					}
					default:
					{
						Error();
						goto FirstPages;
						break;
					}
					}
					break;
				}
			case 0:
			{
				return 0;
			}
			default:
			{
				Error();
				goto DecodePages;
				break;
			}
		}
		}
	}

	return 0;
}