#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>
#include <fcntl.h>
#include <wchar.h>


#pragma pack (1)
wchar_t* head = L"<li>";
wchar_t*foot = L"</li>\n";
struct student
{
	wchar_t* ID;
	wchar_t* name;
	wchar_t* email;
	wchar_t* faculaty;
	int      year;
	wchar_t* DoB;
	wchar_t* link;
	wchar_t* about;
	wchar_t* hobby;
};

void standerdize1(wchar_t* &a)//removecommaattheend
{
	while (a[wcslen(a) - 1] == ',' || a[wcslen(a) - 1]== ' ')
		a[wcslen(a)-1] = NULL;
}

void standerdize2(wchar_t* &a)//removecmmaattheFirst
{
	while (a[0] == ',')
	for (int i = 0; i < wcslen(a); i++)
		a[i] = a[i + 1];
	a[wcslen(a) - 1] = NULL;
}

void outputHobby(wchar_t** a,int count)
{
	for (int i = 0; i < count; i++)
	{
			wprintf(L"%ls", *(a + i));
		wprintf(L"\n");
	}
}

wchar_t* comBine(wchar_t* a)//get fileName
{
	wchar_t* extension = L".html";
	int fileNameLength = wcslen(a) + wcslen(extension);
	wchar_t* fileName = NULL;
	fileName = (wchar_t*)malloc(fileNameLength*sizeof(wchar_t));
	for (int j = 0; j < wcslen(a); j++)
		fileName[j] = a[j];
	for (int j = wcslen(a); j < fileNameLength; j++)
		fileName[j] = extension[j - wcslen(a)];
	fileName[fileNameLength] = '\0';
	return fileName;
}

wchar_t** hanldingHobby(wchar_t* hobby, int& countHobby, int* &length)
{
	countHobby = 0;
	int Start,End;
	Start = End = 0;
	int L = wcslen(hobby);
	while (Start < L)
	{
		if (hobby[Start] == '\"')
		{
			int*stack = (int*)malloc(5 * sizeof(int));
			int top = -1;
			top++;
			stack[top] = 1;
			Start++;
			bool flag = false;
			while (!flag)
			{
				if ((hobby[Start]=='\"')&&(hobby[Start+1] == ',' || hobby[Start+1] == NULL) && (stack[top]==1))
				{
					stack[top] == NULL;
					top--;
					Start = Start + 2;
				}
				else if ((hobby[Start] == '\"') && (hobby[Start + 1] == '\"') && (hobby[Start + 2] == ',' || hobby[Start + 2] == '\0') && (stack[top] == 1))
				{
					top++;
					stack[top] = 2;
					Start = Start + 3;
				}
				else if ((hobby[Start] == '\"') && (hobby[Start + 1] == '\"') && (hobby[Start + 2] == ',' || hobby[Start + 2] == '\0') && (stack[top] == 2))
				{
					stack[top] == NULL;
					top--;
					Start = Start - 3;
				}
				else Start++;
				if (top == -1)
				{
					countHobby++;
					flag = true;
					free(stack);
				}
			}
		}
		else
		{
			if (hobby[Start] != '\"')
			{
				for (int j = Start + 1; j <=L; j++)
				{
					if (hobby[j] == ','|| hobby[j]==NULL) 
					{
						countHobby++;
						Start=(j+1);
						break;
					}
				}
			}
			else Start++;
		}
	}
	length = (int*)malloc(countHobby*sizeof(int));
	countHobby = 0;
	Start = 0;
	while (Start < L)
	{
		if (hobby[Start] == '\"')
		{
			int*stack = (int*)malloc(5 * sizeof(int));
			int top = -1;
			top++;
			stack[top] = 1;
			Start++;
			bool flag = false;
			while (!flag)
			{
				if ((hobby[Start] == '\"') && (hobby[Start + 1] == ',' || hobby[Start + 1] == NULL) && (stack[top] == 1))
				{
					stack[top] == NULL;
					top--;
					Start = Start + 2;
				}
				else if ((hobby[Start] == '\"') && (hobby[Start + 1] == '\"') && (hobby[Start + 2] == ',' || hobby[Start + 2] == '\0') && (stack[top] == 1))
				{
					top++;
					stack[top] = 2;
					Start = Start + 3;
				}
				else if ((hobby[Start] == '\"') && (hobby[Start + 1] == '\"') && (hobby[Start + 2] == ',' || hobby[Start + 2] == '\0') && (stack[top] == 2))
				{
					stack[top] == NULL;
					top--;
					Start = Start - 3;
				}
				else Start++;
				if (top == -1)
				{
					countHobby++;
					length[countHobby-1] = Start;
					flag = true;
					free(stack);
				}
			}
		}
		else
		{
			if (hobby[Start] != '\"')
			{
				for (int j = Start + 1; j <= L; j++)
				{
					if (hobby[j] == ',' || hobby[j] == NULL)
					{
						countHobby++;
						Start = (j + 1);
						length[countHobby-1] = Start;
						break;
					}
				}
			}
			else Start++;
		}
	}
	int tempStart = 0;
	wchar_t** hobbyED = (wchar_t**)malloc(countHobby*sizeof(wchar_t*));
	for (int i = 0; i < countHobby; i++)
	{
		*(hobbyED+i) = (wchar_t*)malloc((length[i] - tempStart +2)*sizeof(wchar_t));
		tempStart = length[i];
	}
	tempStart = 0;
	int i = 0;
	while (i<countHobby)
	{
		for (int j = tempStart; j < length[i]; j++)
		{
			hobbyED[i][j - tempStart] = hobby[j];
			
		}
		hobbyED[i][length[i] - tempStart] = '\0';
		tempStart = length[i];
		i++;
	}
	return hobbyED;
}
void main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	FILE* fp = _wfopen(L"test.csv", L"r,ccs=UTF-8");
	wchar_t* data;
	int dataLength;
	if (fp == NULL)
		wprintf(L"Cannot open file");
	else
	{
		fseek(fp, 0, SEEK_END);
		dataLength = ftell(fp);
	}
	fseek(fp, 3, SEEK_SET);
	data = (wchar_t*)malloc((dataLength)*sizeof(wchar_t));
	fwscanf(fp, L"%[^'\0']", data);
	data[wcslen(data)+1] = '\0';
	fclose(fp);
	dataLength = wcslen(data);
	int countRow = 0;
	for (int i = 0; i < dataLength; i++)
	{
		if (data[i] == '\n' || data[i] == '\0')
			countRow++;
	}
	student* a = (student*)malloc(countRow*sizeof(student));
	int* pos = (int*)malloc(countRow*sizeof(int));
	int i = 0;
	for (int k = 0; k < dataLength;k++)
	if (data[k] == '\n' || data[k] == '\0')
	{
		pos[i] = k;
		i++;
	}
	i = 0;
	int startPos = 0;
	while (i < countRow)
	{
		wchar_t* temp = (wchar_t*)malloc((pos[i] - startPos + 1)*sizeof(wchar_t));
		for (int j = 0; j < pos[i] - startPos; j++)
		{
			temp[j] = data[j + startPos];
		}
		temp[pos[i] - startPos] = '\0';
		int indexStart = 0;
		int indexEnd = 0;
		for (int j = indexStart; j < wcslen(temp); j++)//readID
		if (temp[j] == ',')
		{
			indexEnd = j;
			break;
		}
		a[i].ID = (wchar_t*)malloc((indexEnd - indexStart + 1)*sizeof(wchar_t));
		for (int j = indexStart; j < indexEnd; j++)
			a[i].ID[j - indexStart] = temp[j];
		a[i].ID[indexEnd - indexStart] = '\0';
		indexStart = indexEnd + 1;
		for (int j = indexStart; j < wcslen(temp); j++)//readName
		if (temp[j] == ',')
		{
			indexEnd = j;
			break;
		}
		a[i].name = (wchar_t*)malloc((indexEnd - indexStart + 1)*sizeof(wchar_t));
		for (int j = indexStart; j < indexEnd; j++)
			a[i].name[j - indexStart] = temp[j];
		a[i].name[indexEnd - indexStart] = '\0';
		indexStart = indexEnd + 1;
		for (int j = indexStart; j < wcslen(temp); j++)//readEmmail
		if (temp[j] == ',')
		{
			indexEnd = j;
			break;
		}
		a[i].email = (wchar_t*)malloc((indexEnd - indexStart + 1)*sizeof(wchar_t));
		for (int j = indexStart; j < indexEnd; j++)
			a[i].email[j - indexStart] = temp[j];
		a[i].email[indexEnd - indexStart] = '\0';
		indexStart = indexEnd + 1;
		for (int j = indexStart; j < wcslen(temp); j++)//readFac
		if (temp[j] == ',')
		{
			indexEnd = j;
			break;
		}
		a[i].faculaty = (wchar_t*)malloc((indexEnd - indexStart + 1)*sizeof(wchar_t));
		for (int j = indexStart; j < indexEnd; j++)
			a[i].faculaty[j - indexStart] = temp[j];
		a[i].faculaty[indexEnd - indexStart] = '\0';
		indexStart = indexEnd + 1;
		for (int j = indexStart; j < wcslen(temp); j++)//readYear
		if (temp[j] == ',')
		{
			indexEnd = j;
			break;
		}
		wchar_t* copyYear = (wchar_t*)malloc((indexEnd - indexStart + 1)*sizeof(wchar_t));
		wchar_t* EndPtr;
		for (int j = indexStart; j < indexEnd; j++)
			copyYear[j - indexStart] = temp[j];
		copyYear[indexEnd - indexStart] = '\0';
		a[i].year = wcstol(copyYear, &EndPtr, 10);
		free(copyYear);
		indexStart = indexEnd + 1;
		for (int j = indexStart; j < wcslen(temp); j++)//readDoB
		if (temp[j] == ',')
		{
			indexEnd = j;
			break;
		}
		a[i].DoB = (wchar_t*)malloc((indexEnd - indexStart + 1)*sizeof(wchar_t));
		for (int j = indexStart; j < indexEnd; j++)
			a[i].DoB[j - indexStart] = temp[j];
		a[i].DoB[indexEnd - indexStart] = '\0';
		indexStart = indexEnd + 1;
		for (int j = indexStart; j < wcslen(temp); j++)//readLinkPhoto
		if (temp[j] == ',')
		{
			indexEnd = j;
			break;
		}
		a[i].link = (wchar_t*)malloc((indexEnd - indexStart + 1)*sizeof(wchar_t));
		for (int j = indexStart; j < indexEnd; j++)
			a[i].link[j - indexStart] = temp[j];
		a[i].link[indexEnd - indexStart] = '\0';
		indexStart = indexEnd + 1;
		//readAbout
		int* stack = (int*)malloc(10 * sizeof(int));
		int top = -1;
		if (temp[indexStart] != '\"')//readAbout with the simplest content
		{
			for (int j = indexStart; j < wcslen(temp); j++)
			if (temp[j] == ',')
			{
				indexEnd = j;
				break;
			}
			a[i].about = (wchar_t*)malloc((indexEnd - indexStart + 1)*sizeof(wchar_t));
			for (int j = indexStart; j < indexEnd; j++)
				a[i].about[j - indexStart] = temp[j];
			a[i].about[indexEnd - indexStart] = '\0';
			indexStart = indexEnd + 1;
		}
		else if (temp[indexStart] == '\"')//readAbout with complex content ( more than or with Quote  , ....) 
		{
			top++;
			stack[top] = 1;
			int tempStart = indexStart + 1;
			indexStart++;
			int tempEnd;
			while (1)
			{
				if (temp[tempStart] == '\"')
				{
					if (temp[tempStart + 1] == '\"')
					{
						if (stack[top] == 1)
						{
							top++;
							stack[top] = 2;
							tempStart += 2;
						}
						else
						{
							if (stack[top] == 2)
							{
								stack[top] = NULL;
								top--;
								tempStart += 2;
							}
						}
					}
				}
				if (temp[tempStart] == '\"')
				{
					if (temp[tempStart + 1] == ',')
					if (stack[top] == 1)
					{
						stack[top] = NULL;
						top--;
						free(stack);
					}
				}
				if (top == -1)
				{
					tempEnd = tempStart + 1;
					indexEnd = tempEnd - 1;
					a[i].about = (wchar_t*)malloc((indexEnd - indexStart + 1)*sizeof(wchar_t));
					for (int j = indexStart; j < indexEnd; j++)
						a[i].about[j - indexStart] = temp[j];
					a[i].about[indexEnd - indexStart] = '\0';
					indexStart = indexEnd + 1;
					break;
				}
				tempStart++;
			}
		}
		standerdize1(temp);
		//readHobby
		if (wcslen(temp) - indexEnd < 2)
			a[i].hobby = NULL;
		else
		{
			a[i].hobby = (wchar_t*)malloc((wcslen(temp) - indexEnd + 1)*sizeof(wchar_t));
			if (temp[indexEnd] == '\"')
			for (int j = indexEnd; j < wcslen(temp); j++)
				a[i].hobby[j - indexStart] = temp[j];
			else
			for (int j = indexEnd + 1; j < wcslen(temp); j++)
				a[i].hobby[j - indexStart] = temp[j];
			a[i].hobby[wcslen(temp) - indexStart + 1] = '\0';
			standerdize2(a[i].hobby);
		}
		int countHobby;
		int* length;
		wchar_t** hobbyED;
		hobbyED = hanldingHobby(a[i].hobby, countHobby, length);
		for (int k = 0; k < countHobby; k++)
		{
			standerdize1(*(hobbyED + k));
			if (hobbyED[k][0] == '\"')
			for (int l = 0; l < wcslen(*(hobbyED + k)); l++)
				hobbyED[k][l] = hobbyED[k][l + 1];
			if (hobbyED[k][wcslen(*(hobbyED + k)) - 1] == '\"')
				hobbyED[k][wcslen(*(hobbyED + k)) - 1] = NULL;
		}
		wchar_t* fileName = comBine(a[i].ID);
		//publish HTML file
		wprintf(L"Chọn Thông Tin Muốn Ẩn Của Sinh Viên Thứ %ld/%ld\n", i+1, countRow);
		wprintf(L"1. Mã Số Sinh Viên \n");
		wprintf(L"2. Họ Và Tên \n");
		wprintf(L"3. Email \n");
		wprintf(L"4. Khoa \n");
		wprintf(L"5. Khóa Học \n");
		wprintf(L"6. Ngày Tháng Năm Sinh \n");
		wprintf(L"7. Hình Cá Nhân \n");
		wprintf(L"8. Giới Thiệu Bản Thân \n");
		wprintf(L"9. Sở Thích \n");
		wprintf(L"10. Bắt Đầu In \n");
		wprintf(L"11. Để In Tất Cả \n");
		int selection = 0;
		do
		{
			wprintf(L"Nhập Lựa Chọn: \n");
			wscanf(L"%ld", &selection);
			switch (selection)
			{
			case 1: a[i].ID = NULL;
				break;
			case 2: a[i].name = NULL;
				break;
			case 3: a[i].email = NULL;
				break;
			case 4: a[i].faculaty = NULL;
				break;
			case 5: a[i].year = NULL;
				break;
			case 6: a[i].DoB = NULL;
				break;
			case 7: a[i].link = NULL;
				break;
			case 8: a[i].about = NULL;
				break;
			case 9: a[i].hobby = NULL;
				break;
			}
		} 
		while (selection >= 1 && selection <= 9);
		FILE* fileHTMLout = _wfopen(fileName, L"wt,ccs=UTF-8");
		FILE* templateHTML = _wfopen(L"template.txt", L"r,ccs=UTF-8");
		if (templateHTML == NULL)
			wprintf(L"Cannot Open File");
		else
		{
			wchar_t buffer;
			int tempPos = 1;
			{
				while (!feof(templateHTML))
				{
					fwscanf(templateHTML, L"%lc", &buffer);
					if (buffer != '$')
					{
						fwprintf(fileHTMLout, L"%lc", buffer);
					}
					else if (buffer == '$' && tempPos == 1)
					{
						fwprintf(fileHTMLout, L"%ls", a[i].name);
						tempPos++;
					}
					else if (buffer == '$' && tempPos == 2)
					{
						fwprintf(fileHTMLout, L"%ls", a[i].name);
						tempPos++;
					}
					else if (buffer == '$' && tempPos == 3)
					{
						fwprintf(fileHTMLout, L"%ls", a[i].ID);
						tempPos++;
					}
					else if (buffer == '$' && tempPos == 4)
					{
						fwprintf(fileHTMLout, L"%ls", a[i].faculaty);
						tempPos++;
					}
					else if (buffer == '$' && tempPos == 5)
					{
						fwprintf(fileHTMLout, L"%ls", a[i].email);
						tempPos++;
					}
					else if (buffer == '$' && tempPos == 6)
					{
						fwprintf(fileHTMLout, L"%ls", a[i].link);
						tempPos++;
					}
					else if (buffer == '$' && tempPos == 7)
					{
						fwprintf(fileHTMLout, L"%ls", a[i].name);
						tempPos++;
					}
					else if (buffer == '$' && tempPos == 8)
					{
						fwprintf(fileHTMLout, L"%ls", a[i].ID);
						tempPos++;
					}
					else if (buffer == '$' && tempPos == 9)
					{
						fwprintf(fileHTMLout, L"%ls", a[i].faculaty);
						tempPos++;
					}
					else if (buffer == '$' && tempPos == 10)
					{
						fwprintf(fileHTMLout, L"%ls", a[i].DoB);
						tempPos++;
					}
					else if (buffer == '$' && tempPos == 11)
					{
						fwprintf(fileHTMLout, L"%ls", a[i].email);
						tempPos++;
					}
					else if (buffer == '$' && tempPos == 12)
					{
						if (a[i].hobby == NULL)
						{
							fwprintf(fileHTMLout, L"%ls", head);
							fwprintf(fileHTMLout, L" ");
							fwprintf(fileHTMLout, L"%ls", foot);
						}
						else						
						for (int k = 0; k < countHobby; k++)
						{
							while ((hobbyED[k][0] == ',')) standerdize2(*(hobbyED + k));
							fwprintf(fileHTMLout, L"%ls", head);
							fwprintf(fileHTMLout, L"%ls", *(hobbyED + k));
							fwprintf(fileHTMLout, L"%ls", foot);
						}
						tempPos++;
					}
					else if (buffer == '$' && tempPos == 13)
					{
						fwprintf(fileHTMLout, L"%ls", a[i].about);
					}
				}
			}
		}
		fclose(fileHTMLout);
		i++;
		startPos = pos[i - 1] + 1;
		free(temp);
	}
	free(data);
	free(a);
}
