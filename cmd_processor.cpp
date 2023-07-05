#include "cmd_processor.h"

#include <iostream>
#include <sstream>
#include <string>
#include <list>

#include "task_list.h"
#include "tools.h"

using namespace std;

bool CmdProcessor::GetArgv(int argc, char* argv[], int start) {
  if (start == argc) {
    return false;
  }

  for (int i = start; i < argc; i++) {
    cmd_.push_back(argv[i]);
  }
  return true;
}

bool CmdProcessor::GetCmd() {
  string tmp;
  getline(cin, tmp);
  istringstream cmd(tmp);

  cmd >> tmp;
  if (!cmd) return false;
  cmd_.push_back(tmp);
  while (cmd >> tmp) {
    cmd_.push_back(tmp);
  }
  return true;
}

int CmdProcessor::CmdDistributor(TaskList& task_list) const {
  const int kSize = cmd_.size();
  if (kSize < 1) return false;

  bool flag = false;
  string first_cmd = cmd_.front();
  to_lower(first_cmd);

  if (first_cmd == "login") {
    // TODO login
  } else if (first_cmd == "addtask" || first_cmd == "add") {
    if (kSize == 1)
      flag = AddTaskNoOp(task_list);
    else
      flag = AddTaskOp(task_list, cmd_);
  } else if (first_cmd == "modifytask" || first_cmd == "modify") {
    if (kSize == 1)
      flag = ModifyTaskNoOp(task_list);
    else
      flag = ModifyTaskOp(task_list, cmd_);
  } else if (first_cmd == "deletetask" || first_cmd == "delete") {
    if (kSize == 1)
      flag = DeleteTaskNoOp(task_list);
    else
      flag = DeleteTaskOp(task_list, cmd_);
  } else if (first_cmd == "showtask" || first_cmd == "show") {
    if (kSize == 1)
      flag = ShowTaskNoOp(task_list);
    else
      flag = ShowTaskOp(task_list, cmd_);
  } else if (first_cmd == "searchtask" || first_cmd == "search") {
    if (kSize == 1)
      flag = SearchTaskNoOp(task_list);
    else
      flag = SearchTaskOp(task_list, cmd_);
  } else if (first_cmd == "quit" || first_cmd == "q") {
    cout << "Bye.\n";
    return -1;
  } else {
    cout << "\"" << cmd_.front() << "\" is not a valid command.\n";
    return 0;
  }
  return flag;
}
bool AddTaskNoOp(TaskList& task_list)
{
	Other newtask;
	// 添加任务名字
	std::cout << "Please input the name of the task" << endl;
	std::cin >> newtask.name;
	// 添加任务的开始时间
	std::cout << "Please input the begin time of the task" << endl;
	std::cout << "Time format should be 2022/02/02/03:00:00" << endl;
	string begin_t;
	bool valid_input = false;
	while (!valid_input)//检查任务的开始时间是不是%Y/%M/%D/%h:%m:%s的形式
	{
		std::cin >> begin_t;
		if (isValidDate(begin_t))//如果是退出循环
			valid_input = true;
		else
			std::cout << "Invalid format. Please try again." << endl;//否则一直输入直到是为止
	}
	newtask.begin_time = to_time_t(begin_t);//将用户输入的形式转化成time_t格式保存
	// 添加任务的优先级
	std::cout << "Please input the priority of the task" << endl;
	std::cout << "1-low, 2-medium, 4-high" << endl;
	std::cin >> newtask.priority;
	// 检查优先级是不是符合1，2，4
	while (newtask.priority != 1 && newtask.priority != 2 && newtask.priority != 4)
	{
		std::cout << "Invalid priority. Please try again." << endl;
		std::cin >> newtask.priority;
	}
	// 添加任务的种类
	std::cout << "Please input the type of the task：entertainment  sport  study  routine" << endl;
	std::cin >> newtask.type;
	// 添加任务的提醒时间
	std::cout << "Please input the remind time of the task" << endl;
	std::cout << "Time format should be 2022/02/02/03:00:00" << endl;
	string remind_t;
	valid_input = false;
	//检查任务的开始时间是不是%Y/%M/%D/%h:%m:%s的形式
	while (!valid_input)
	{
		std::cin >> remind_t;
		if (isValidDate(remind_t))
			valid_input = true;
		else
			std::cout << "Invalid format. Please try again." << endl;
	}
	newtask.remind_time = to_time_t(remind_t);//将用户输入的形式转化成time_t格式保存
	//id和开始时间一样
	int id = to_time_t(begin_t);
	if (!task_list.Add(make_pair(id, newtask)))//如果用户输入的开始时间重复了，makepair在这里会失效
	{
		std::cout << "Failure!" << endl;
		return false;
	}
	else
	{
		return true;
	}
}

bool ShowTaskNoOp(TaskList& task_list)
{
	std::cout << "If you want to see all the tasks, input 0" << endl;
	std::cout << "If you need to select according to the importance of the task, input 1" << endl;
	std::cout << "If you need to select according to the time of the task, input 2" << endl;
	std::cout << "If you need to select according to both the time and importance of the task, input 3" << endl;
	std::cout << "default: show all" << endl;
	int option;
	std::cin >> option;
	while (!std::cin) // 检查输入是否有效
	{
		std::cin.clear(); // 清除输入流状态标志
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略剩余的输入
		//输入的不是数字
		std::cout << "Invalid input. Please enter a valid choice: " << endl;
		std::cin >> option;
	}
	int priority = 7;//默认展示所有的优先级
	int startTime = 0;
	int endTime = pow(2, 31) - 1;
	string startTimeStr = "";//由用户决定开始时间段
	string endTimeStr = "";//由用户决定结束时间段
	string c;//由用户决定是否要设定时间
	

	switch (option)
	{
	case 0:
		task_list.Show(); // 显示所有任务
		break;
	case 1:
		std::cout << "1 for low, 2 for medium, 4 for high" << endl;
		std::cout << "3 for low and medium, 6 for medium and high, 5 for low and high" << endl;
		std::cout << "7 for all" << endl;
		std::cin >> priority;
		while (priority > 7 || priority < 1)
		{
			std::cout << "invalid" << endl;
			std::cin >> priority;
		}
		while (!std::cin) // 检查输入是否有效
		{
			std::cin.clear(); // 清除输入流状态标志
			std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略剩余的输入

			std::cout << "Invalid input. Please enter a valid choice: " << endl;
			std::cin >> priority;
		}
		task_list.Show(0, pow(2, 31) - 1, priority); // 根据优先级显示任务
		break;
	case 2:
		std::cout << "If you want to see all the tasks before the specified date, enter y/n" << endl;
		std::cout << "format: 2022/02/02/10:00:00" << endl;
		std::cin >> c;
		if (c == "y" || c == "Y") {
			std::cout << "Please input the date" << endl;
			std::cin >> startTimeStr;

			while (!isValidDate(startTimeStr))
			{
				std::cout << "Invalid input, please try again" << endl;
				std::cin >> startTimeStr;
			}

		}

		if (startTimeStr != "")
			startTime = to_time_t(startTimeStr);

		std::cout << "If you want to see all the tasks after the specified date, enter y/n" << endl;
		std::cout << "format: 2022/02/02/10:00:00" << endl;
		std::cin >> c;

		if (c == "y" || c == "Y")
		{
			std::cout << "Please input the date" << endl;
			std::cin >> endTimeStr;

			while (!isValidDate(endTimeStr))
			{
				std::cout << "Invalid input, please try again" << endl;
				std::cin >> endTimeStr;
			}

		}

		if (endTimeStr != "")
			endTime = to_time_t(endTimeStr);

		task_list.Show(startTime, endTime); // 根据时间范围显示任务
		break;
	case 3:
		std::cout << "1 for low, 2 for medium, 4 for high" << endl;
		std::cout << "3 for low and medium, 6 for medium and high, 5 for low and high" << endl;
		std::cout << "7 for all" << endl;
		std::cin >> priority;
		while (priority > 7 || priority < 1)
		{
			std::cout << "invalid" << endl;
			std::cin >> priority;
		}
		while (!std::cin) // 检查输入是否有效
		{
			std::cin.clear(); // 清除输入流状态标志
			std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略剩余的输入

			std::cout << "Invalid input. Please enter a valid choice: " << endl;
			std::cin >> priority;
		}
		std::cout << "If you want to see all the tasks before the specified date, enter y/n" << endl;
		std::cout << "format: 2022/02/02/10:00:00" << endl;
		std::cin >> c;

		if (c == "y" || c == "Y") {
			std::cout << "Please input the date" << endl;
			std::cin >> startTimeStr;

			while (!isValidDate(startTimeStr))
			{
				std::cout << "Invalid input, please try again" << endl;
				std::cin >> startTimeStr;
			}

		}

		if (startTimeStr != "")
			startTime = to_time_t(startTimeStr);

		std::cout << "If you want to see all the tasks after the specified date, enter y/n" << endl;
		std::cout << "format: 2022/02/02/10:00:00" << endl;
		std::cin >> c;

		if (c == "y" || c == "Y") {
			std::cout << "Please input the date" << endl;
			std::cin >> endTimeStr;

			while (!isValidDate(endTimeStr))
			{
				std::cout << "Invalid input, please try again" << endl;
				std::cin >> endTimeStr;
			}

		}

		if (endTimeStr != "")
			endTime = to_time_t(endTimeStr);

		task_list.Show(startTime, endTime, priority); // 根据时间范围和优先级
	}
	return true;
}

bool DeleteTaskNoOp(TaskList& task_list)
{
	std::cout << "Delete tasks based on name or ID" << endl;
	std::cout << "1 represents deletion based on ID\nwhile the remaining numbers represents deletion based on name" << endl;
	int choice;
	std::cin >> choice;
	while (!std::cin) // 检查输入是否有效
	{
		std::cin.clear(); // 清除输入流状态标志
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略剩余的输入
		//如果输入的不是数字，就会让他重新输入
		std::cout << "Invalid input. Please enter a valid number: " << endl;
		std::cin >> choice;
	}
	if (choice == 1)
	{
		std::cout << "Please input the ID of the task to be deleted" << endl;
		long long id;
		std::cin >> id;
		while (!std::cin) // 检查输入是否有效
		{
			std::cin.clear(); // 清除输入流状态标志
			std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略剩余的输入
			//如果输入的不是数字，就会让他重新输入
			std::cout << "Invalid input. Please enter a valid ID: " << endl;
			std::cin >> id;
		}
		while (!task_list.Erase(id))// 根据ID删除任务
		{
			cout << id << " not found" << endl;
			std::cin >> id;
		}
	}
	else
	{
		std::cout << "Please input the name of the task to be deleted" << endl; // 根据名称删除任务
		string taskName;
		std::cin >> taskName;
		while (!task_list.Erase(taskName))
		{
			cout << taskName << " not found" << endl;
			std::cin >> taskName;
		}

	}
	cout << "success" << endl;
	task_list.saveFile();//保存文件
	return true;
}

bool ModifyTaskNoOp( TaskList& task_list)
{
	std::cout << "search tasks based on name or ID" << endl;
	std::cout << "1 represents search based on ID\nwhile the remaining represents search based on name" << endl;
	int choice;
	std::cin >> choice;
	while (!std::cin) // 检查输入是否有效
	{
		std::cin.clear(); // 清除输入流状态标志
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略剩余的输入

		std::cout << "Invalid input. Please enter a valid choice: " << endl;
		std::cin >> choice;
	}
	vector<pair<int, Other>>::iterator it;
	string newstart;
	string newremind;
	switch (choice)
	{
	case 1:
		std::cout << "please input the id of the wanted task" << endl;
		long long id;
		std::cin >> id;
		if (!task_list.FindShow(id))
		{
			cout << "no such id" << endl;
			cin >> id;
		}
		it = task_list.FindTask(id);
		break;
	default:
		std::cout << "please input the name of the wanted task" << endl;
		string idx;
		std::cin >> idx;
		while (!task_list.FindShow(idx))
		{
			cout << "no such task" << endl;
			cin >> idx;
		}
		it = task_list.FindTask(idx);
	}
	std::cout << "n : change name" << endl;
	std::cout << "s : change start time" << endl;
	std::cout << "r : change remind time" << endl;
	std::cout << "t : change type " << endl;
	std::cout << "p : change priority " << endl;

	string xx;
	std::cin >> xx;
	if (xx == "n" || xx == "N") {
		std::cout << "change name" << endl;
		std::cin >> it->second.name;
	}
	else if (xx == "s" || xx == "S") {
		std::cout << "change begin_time" << endl;
		std::cin >> newstart;
		it->second.begin_time = to_time_t(newstart);
	}
	else if (xx == "t" || xx == "T") {
		std::cout << "change type" << endl;
		std::cin >> it->second.type;
	}
	else if (xx == "r" || xx == "R") {
		std::cout << "change remind_time" << endl;
		std::cin >> newremind;
		it->second.remind_time = to_time_t(newremind);
	}
	else if (xx == "p" || xx == "P") {
		std::cout << "change prority" << endl;
		std::cin >> it->second.priority;
	}
	else
		std::cout << "invalid" << endl;
	task_list.saveFile();
	return true;
}

bool SearchTaskNoOp( TaskList& task_list)
{
	std::cout << "search tasks based on name or ID" << endl;
	std::cout << "1 represents search based on ID\nwhile the remaining represents search based on name" << endl;
	int choice;
	std::cin >> choice;
	while (!std::cin) // 检查输入是否有效
	{
		std::cin.clear(); // 清除输入流状态标志
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略剩余的输入

		std::cout << "Invalid input. Please enter a valid choice: " << endl;
		std::cin >> choice;
	}
	switch (choice)
	{
	case 1:
		std::cout << "please input the id of the wanted task" << endl;
		int id;
		std::cin >> id;
		if (task_list.FindShow(id))
		{
			while (!std::cin) // 检查输入是否有效
			{
				std::cin.clear(); // 清除输入流状态标志
				std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略剩余的输入

				std::cout << "Invalid input. Please enter a valid id: " << endl;
				std::cin >> id;
			}
			return true;
		}
		else
		{
			return false;
		}
		break;
	default:
		std::cout << "please input the name of the wanted task" << endl;
		string ix;
		std::cin >> ix;
		if (task_list.FindShow(ix))
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	}
	return true;
}
