
#include "stdafx.h"
#include <tchar.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm> 
#include <vector>
#include <thread>

#include "ThreadPool.h"
using namespace std;


vector<string> data_str;
vector<vector<string>> sep_data;


void SortPiece(void* arr_piece)
{
	vector<string>* obj = (vector<string>*)arr_piece;
	sort(obj->begin(), obj->end());
}

int GetMinValueIndex(vector<string> indata)
{
	string min_value;
	int index;
	for (int i = 0; i < indata.size(); i++)
		if (indata[i] != "")
		{
			min_value = indata[i];
			index = i;
			break;
		}

	for (int i = 0; i < indata.size(); i++)
		if (indata[i] != "")
			if (strcmp(min_value.c_str(), indata[i].c_str()) > 0)
				if (min_value > indata[i])
				{
					min_value = indata[i];
					index = i;
				}
	return index;
}
bool CorrectBuff(vector<string> indata)
{
	for (int i = 0; i < indata.size(); i++)
		if (indata[i] != "")
			return true;
	return false;
}

void FinalSort()
{
	int result_size = data_str.size();
	data_str.clear();
	vector<int> counter;
	counter.reserve(sep_data.size());
	for (int i = 0; i < sep_data.size(); i++)
		counter.push_back(0);
	vector<string> buff;

	while (1)
	{
		buff.clear();
		for (int i = 0; i < sep_data.size(); i++)
			if (sep_data[i].size() > counter[i])
				buff.push_back(sep_data[i][counter[i]]);
			else
				buff.push_back("");
		if (!CorrectBuff(buff))
			break;
		int minvalue_index = GetMinValueIndex(buff);
		data_str.push_back(buff[minvalue_index]);
		counter[minvalue_index]++;
	}
}

void CreateTasks(vector<string> indata, short quantity, TaskQueue* result)
{
	bool isEven = indata.size() % quantity == 0; // делитс€ ли на цело страоки на количество потоков
	int standard_string_capacity = indata.size() / quantity; // вместимость
	if (!isEven)
		standard_string_capacity = indata.size() / quantity + 1; // если не на цело, то вместимость увеличиваем
	int global_counter = 0;
	for (int i = 0; i < quantity; i++) // цикл в котором запихиваем дл€ каждого потока "задачи"
	{
		sep_data[i].clear();
		int tmp_counter = 0;
		while (standard_string_capacity != tmp_counter)
		{
			if (global_counter == indata.size())
				break;
			sep_data[i].push_back(indata[global_counter]);
			global_counter++;
			tmp_counter++;
		}
		Task* newtask = new Task(&SortPiece, (void*)& sep_data[i]);
		result->Enqueue(newtask);
	}
}

string vectorToString(vector<string> vector) {
	string s;
	for (string str : vector) {
		s += str;
		s += "\n";
	}
	return s;
}

string mainFunc(int thread_quantity, vector<string> reader) {
	data_str = reader;
	sep_data.resize(thread_quantity);// создаем вектор на количество потоков
	TaskQueue* taskqueue = new TaskQueue();
	CreateTasks(data_str, thread_quantity, taskqueue); //«аполненеи очереди тасками 
	ThreadPool* threads = new ThreadPool(thread_quantity, taskqueue);
	threads->WaitAll();
	delete(threads);
	delete(taskqueue);
	FinalSort();
	return vectorToString(data_str);
}
