#include "task_list.h"
TaskList::TaskList(const char* filename)
{
    Load(filename);//从文件中加载信息
}

TaskList::~TaskList()
{
    
}

bool TaskList::Load(const char*fileName) {
    fstream read(fileName, ios::in);//读入文件
    if (!read.is_open())
    {
        cout << "open failed" << endl;// 打开文件失败，返回false
        return false;
    }
    else
        cout << "open succeed" << endl;
    char buf[1024] = { 0 };
    read.getline(buf, 1024);
    m_header = buf;//读取表头
    cout << m_header << endl;
    while (!read.eof())
    {
        char data[1024] = { 0 };
        read.getline(data, 1024);
        if (strlen(data) == 0)// 如果读取的数据为空，则退出循环
            break;
        Other stu;
        stringstream ss(data);//通过sstream流入信息
        int id;
        ss >> id;
      // cout << id << " ";
        ss >> stu.name >> stu.begin_time >> stu.priority >> stu.type >> stu.remind_time;
       // cout << stu.name <<" "<< stu.begin_time <<" "<< stu.priority <<" "<< stu.type << " "<<
            stu.remind_time << endl;
        task_list_.insert(std::make_pair(id, stu));// 将任务插入任务列表中
        remind_order_list_.push_back(std::make_pair(id,stu));// 将任务插入提醒顺序列表中
    }
    read.close();
    sort(remind_order_list_.begin(), remind_order_list_.end(), LessRemind);// 对提醒顺序列表进行排序
    return true;
}
