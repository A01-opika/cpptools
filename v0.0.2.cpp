#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

vector<string> Storage;

void calculater() {
    cout << "===== calculater =====" << endl;
    string input;
    cout << "Enter expression with numbers and operators (+,-,*,/), NO SPACE ALLOWED:" << endl;
    cin >> input;

    // 先处理所有乘除法（优先级高）
    for(int i = 0; i < input.size(); i++) {
        if(input[i] == '*' || input[i] == '/') {
            // 查找左操作数
            int n1start = 0;
            for(int j = i-1; j >= 0; j--) {
                if(input[j] == '+' || input[j] == '-' || input[j] == '*' || input[j] == '/') {
                    n1start = j+1;
                    break;
                }
            }
            
            // 查找右操作数
            int n2end = input.size()-1;
            for(int j = i+1; j < input.size(); j++) {
                if(input[j] == '+' || input[j] == '-' || input[j] == '*' || input[j] == '/') {
                    n2end = j-1;
                    break;
                }
            }
            
            // 提取操作数
            string n1 = input.substr(n1start, i-n1start);
            string n2 = input.substr(i+1, n2end-i);
            
            try {
                int num1 = stoi(n1);
                int num2 = stoi(n2);
                int result = (input[i] == '*') ? num1 * num2 : num1 / num2;
                
                // 替换表达式部分
                input.replace(n1start, n2end-n1start+1, to_string(result));
                i = n1start; // 重置索引，重新检查
            } catch(...) {
                cout << "Error: Invalid number format!" << endl;
                return;
            }
        } else {
            i++;
        }
    }

    // 再处理加减法
    for(int i = 0; i < input.size(); ) {
        if(input[i] == '+' || input[i] == '-') {
            // 跳过表达式开头的正负号
            if(i == 0) {
                i++;
                continue;
            }
            
            // 查找左操作数
            int n1start = 0;
            for(int j = i-1; j >= 0; j--) {
                if(input[j] == '+' || input[j] == '-' || input[j] == '*' || input[j] == '/') {
                    n1start = j+1;
                    break;
                }
            }
            
            // 查找右操作数
            int n2end = input.size()-1;
            for(int j = i+1; j < input.size(); j++) {
                if(input[j] == '+' || input[j] == '-' || input[j] == '*' || input[j] == '/') {
                    n2end = j-1;
                    break;
                }
            }
            
            // 提取操作数
            string n1 = input.substr(n1start, i-n1start);
            string n2 = input.substr(i+1, n2end-i);
            
            try {
                int num1 = stoi(n1);
                int num2 = stoi(n2);
                int result = (input[i] == '+') ? num1 + num2 : num1 - num2;
                
                input.replace(n1start, n2end-n1start+1, to_string(result));
                i = n1start; // 重置索引
            } catch(...) {
                cout << "Error: Invalid number format!" << endl;
                return;
            }
        } else {
            i++;
        }
    }

    cout << " = " << input << endl;
}

void sorter(){
    cout << "===== sorter =====" << endl;
    cout << "Enter numbers to sort (separated by spaces):" << endl;
    string input;
    cin.ignore(); // 清除输入缓冲区
    getline(cin, input); // 允许输入带空格的内容
    
    // 选择排序方式
    cout << "Choose sort order:" << endl;
    cout << "1. Ascending (升序)" << endl;
    cout << "2. Descending (降序)" << endl;
    int order;
    cin >> order;
    
    // 解析输入的数字
    vector<int> numbers;
    string numStr;
    for(size_t i = 0; i < input.size(); ++i) {  // 替换范围for循环
        char c = input[i];
        if(isdigit(c) || c == '-') {
            numStr += c;
        } else if(!numStr.empty()) {
            numbers.push_back(atoi(numStr.c_str()));  // 使用atoi代替stoi
            numStr.clear();
        }
    }
    if(!numStr.empty()) {
        numbers.push_back(atoi(numStr.c_str()));
    }
    
    // 根据选择排序
    if(order == 1) {
        sort(numbers.begin(), numbers.end()); // 升序
    } else if(order == 2) {
        sort(numbers.begin(), numbers.end(), greater<int>()); // 降序
    } else {
        cout << "Invalid choice! Using ascending order by default." << endl;
        sort(numbers.begin(), numbers.end());
    }
    
    // 输出结果
    cout << "Sorted numbers: ";
    for(size_t i = 0; i < numbers.size(); ++i) {  // 替换换for循环
        cout << numbers[i] << " ";
    }
    cout << endl;
}

void storage_tools(){
    cout << "===== storage tools =====" << endl;
    if(Storage.size() == 0)
        Storage.push_back("invalid value for index[0]");
    cout << "Storage tools usage(warning: NO SPACES):" << endl;
    cout << "use < at the beginning of command to store a new value to the storage" << endl;
    cout << "use > at the beginning of command to retrieve a value from the storage" << endl;
    cout << "use # to clear all storage" << endl;
    cout << "use @ to print all storage" << endl;
    cout << "use ^ to print the size of the storage" << endl;
    cout << "use ! to exit storage tools" << endl;
    cout << "use ? to print this help again" << endl;
    cout << "use ~[index]-[value] to modify a value in the storage" << endl;
    cout << "use $s[filepath] to save storage to a txt file(use absolute path)" << endl;
    cout << "use $r[filepath] to load storage from a txt file(use absolute path)" << endl;
    string command;
    while(true){
        cout << "Enter command:" << endl;
        cin >> command;
        if(command[0] == '<'){
            string value;
            for(int i = 1; i < command.size(); i++){
                value += command[i];
            }
            Storage.push_back(value);
            cout << "Value " << value << " stored successfully in index [" << Storage.size()-1 << "]!" << endl;
        }
        else if(command[0] == '>'){
            string index_s;
            for(int i = 1; i < command.size(); i++){
                index_s += command[i];
            }
            int index = stoi(index_s);
            if(index < 1 || index >= Storage.size()){
                cout << "Error: Index out of range!" << endl;
            }
            else{
                cout << "Value at index [" << index << "] is: " << Storage[index] << endl;
            }
        }
        else if(command[0] == '#'){
            Storage.clear();
            cout << "Storage cleared successfully!" << endl;
        }
        else if(command[0] == '@'){
            int start = 1, end = Storage.size();
            if(command.size() != 1){
                int separator_pos = command.find('-', 1);
                if(separator_pos != string::npos && separator_pos > 1){
                    string start_s = command.substr(1, separator_pos-1);
                    string end_s = command.substr(separator_pos+1);
                    try {
                        start = stoi(start_s);
                        end = stoi(end_s);
                    } catch(...) {
                        cout << "Error: Invalid index format! try again and recorrect your input." << endl;
                        continue;
                    }
                }
            }
            for(int i = start; i < end; i++){
                cout << "Value at index [" << i << "] is: " << Storage[i] << endl;
            }
        }
        else if(command[0] == '^'){
            cout << "Storage size is: " << Storage.size() << endl;
        }
        else if(command[0] == '!'){
            cout << "Exiting storage tools..." << endl;
            break;
        }
        else if(command[0] == '?'){
            cout << "Storage tools usage(warning: NO SPACES):" << endl;
            cout << "use < at the beginning of command to store a new value to the storage" << endl;
            cout << "use > at the beginning of command to retrieve a value from the storage" << endl;
            cout << "use # to clear all storage" << endl;
            cout << "use @ to print all storage" << endl;
            cout << "use @[start]-[end] to print a range of storage" << endl;
            cout << "use ^ to print the size of the storage" << endl;
            cout << "use ! to exit storage tools" << endl;
            cout << "use ? to print this help again" << endl; 
            cout << "use ~[index]-[value] to modify a value in the storage" << endl;
            cout << "use $s[filepath] to save storage to a txt file(use absolute path)" << endl;
            cout << "use $r[filepath] to load storage from a txt file(use absolute path)" << endl;
        }
        else if(command[0] == '~'){
            size_t dash_pos = command.find('-', 1); // 从第1个字符开始查找'-'
            if(dash_pos != string::npos && dash_pos > 1){
                string index_s = command.substr(1, dash_pos-1);
                string value = command.substr(dash_pos+1);
                try {
                    int index = stoi(index_s);
                    if(index >= 1 && index < Storage.size()){
                        Storage[index] = value;
                        cout << "Value at index [" << index << "] modified to: " << value << endl;
                    } else {
                        cout << "Error: Index out of range!" << endl;
                    }
                } catch(...) {
                    cout << "Error: Invalid index format! try again and recorrect your input." << endl;
                }
            } else {
                cout << "Error: Invalid format! Use ~[index]-[value]" << endl;
            }
        }
        else if(command[0] == '$'){
            bool saveMode = false;
            string filepath;
            if(command[1] == 's') saveMode = true;
            for(int i = 2; i < command.size(); i++){
                filepath += command[i];
            }
            if(saveMode){
                fstream file;
                file.open(filepath, fstream::out);
                if(file.is_open()){
                    for(int i = 1; i < Storage.size(); i++){
                        file << Storage[i] << endl;
                    }
                    file.close();
                    cout << Storage.size() << " elements in storage saved to file " << filepath << " successfully!" << endl;
                } else {
                    cout << "Error: Failed to open file " << filepath << " for writing storage!" << endl;
                }
            } else {
                fstream file;
                file.open(filepath, fstream::in);
                if(file.is_open()){
                    Storage.clear();
                    string line;
                    while(getline(file, line)){
                        Storage.push_back(line);
                    }
                    file.close();
                    cout << Storage.size() << " elements in storage loaded from file " << filepath << " successfully!" << endl;
                } else {
                    cout << "Error: Failed to open file " << filepath << " for reading storage!" << endl;
                }
            }
        }
    }
}

int main(){
    string version = "v0.0.2";
    string infromation = "===== INFORMATION =====\nAuther: GlueStudio\nExplore at: https://gitcode.com/PowerGlue\nWhat's new:\n1. Fix bugs\n2. Add $ command in storage tools\n3. Let Storage index start from 1 instead of 0\nCheck update for this program at: https://gitcode.com/PowerGlue/Cpp_tools";
    cout << "Welcome to GlueStudio C++ tools!" << endl;
    cout << "The version of this toolbox is " << version << endl;
    while(true){
        string choice;
        cout << "===== choose function =====" << endl;
        cout << "1. calculater" << endl;
        cout << "2. sorter" << endl;
        cout << "3. storage tools" << endl;
        cout << "i. information" << endl;
        cout << "s. settings" << endl;
        cout << "e. exit" << endl;
        cin >> choice;
        if(choice == "1")
        {
            calculater();
        }
        else if(choice == "2"){
            sorter();
        }
        else if(choice == "3"){
            storage_tools();
        }
        else if(choice == "e"){
            return 0;
        }
        else if(choice == "i"){
            cout << infromation << endl;
        }
        else if(choice == "s"){
            cout << "settings unavailble now" << endl;
        }
        else{
            cout << "Invalid choice!" << endl;
        }
    }
}
