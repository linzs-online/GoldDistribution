#include <iostream>
#include <algorithm>
#include <tabulate/table.hpp>
#include <list>
#include <math.h>

using namespace std;
using namespace tabulate;
using Row_t = std::vector<variant<std::string, const char *, string_view, tabulate::Table>>;

/**
 * @brief 用于打印分配结果的
 * 
 * @param _result 
 */

void printResult(list<int>& _result)
{
    tabulate::Table table0; // 表头
    tabulate::Table table;  // 分配结果显示表格
    table.format().font_align(FontAlign::center);
    table.column(0).format().width(14);
    table.column(1).format().width(20);
    table0.add_row({"海盗分金问题 1 号海盗的分配方案"});
    table.add_row({"海盗序号","分配的金币"});
    int index = 0;
    for (auto result : _result)
    {
        table.add_row({to_string(++index),to_string(result)});
    }
    table0.add_row({table});
    table0.column(0).format().font_align(FontAlign::center);
    cout << table0 << endl;  // 这是 table 库提供的API用法
}

/**
 * @brief 通过递归得到分配方案
 * 
 * @param _pNum 
 * @return list<int> 
 */
list<int> distribution(int _pNum){
    
    if (_pNum == 5) {     // 终止递归条件
        list<int> res({97, 0, 1, 2, 0});
        return res;
    }
    if (_pNum > 5){
        list<int> res =  distribution(_pNum - 1); // 递归
        *res.begin() = 100 - (_pNum/2 + 1);
        if (_pNum % 2 == 0){
            res.emplace_back(1);
        }
        else{
            res.emplace_back(0);
        }
        return res;
    }
}

int main(int argc, char const *argv[])
{
    int pNum;
    cout << "请输入海盗总人数：" ;
    cin >> pNum; // 输入海盗人数 
    list<int> result; // 分配结果存放
    if (pNum >= 1){  // 一个人的时候直接获得所有金币不需要递推
        result.emplace_back(100);
    }
    if (pNum >= 2){  // 两人的时候肯定是最后一个人获得所有金币
        result.emplace_front(0);
    }
    if (pNum >= 3){  // 三个人的时候 1 号海盗可以直接获得全部金币
        result.emplace_front(0);
        result.reverse();
    }
    if (pNum >= 4){  // 四个人的时候也是特殊情况
        *result.begin() -= 2; // 1 号海盗只能拿 98 个金币了
        *(--result.end()) = 1;  // 3 号海盗分配 1 个金币
        result.emplace_back(1); // 4 号海盗分配 1 个金币
    }
    if (pNum >= 5){
        result.clear();
        result = distribution(pNum);  // 人数超过 5 之后使用递归得到分配方案
    }
    printResult(result);
    return 0;
}


