#include "task_list.h"
#include <ctime>
#include <vector>
#include <string>

using namespace std;

void TaskList::Remind() {
  // TODO Remind
}

vector<pair<int, Other>>::iterator TaskList::FindTask(int id) {
  for (auto it = task_list_.begin(); it != task_list_.end(); it++) {
    if (it->first == id) {
      return it;
    }
  }
  return task_list_.end();
}

vector<pair<int, Other>>::iterator TaskList::FindTask(string name) {
  for (auto it = task_list_.begin(); it != task_list_.end(); it++) {
    if (it->second.name.compare(name) == 0) {
      return it;
    }
  }
  return task_list_.end();
}

void TaskList::Show(int start, int end, int priority_range, bool(*Compare)(pair<int, Other>task1, pair<int, Other>task2))
{
    // 创建一个临时的任务列表，用于保存符合条件的任务
    vector<pair<int, Other>> tempTasks;

    // 遍历任务列表，将符合时间范围和优先级范围的任务添加到临时列表中
    for (const auto& task : task_list_) {
        if (task.first >= start && task.first <= end &&
            task.second.priority <= priority_range) {
            tempTasks.push_back(task);
        }
    }

    // 根据 Compare 函数指针来排序任务列表
    std::sort(tempTasks.begin(), tempTasks.end(), Compare);

    // 显示排序后的任务列表
    for (const auto& task : tempTasks) {
        cout << "开始时间：" << task.first << endl;
        cout << "名称：" << task.second.name << endl;
        cout << "优先级：" << task.second.priority << endl;
        cout << "类型：" << task.second.type << endl;
        cout << "提醒时间：" << task.second.remind_time << endl;
        cout << "---------------------------" << endl;
    }
void TaskList::ShowTask(vector<pair<int, Other>>::iterator it) {
  // TODO ShowTask
}
void TaskList::ShowHead() {
  // TODO ShowHead
}
