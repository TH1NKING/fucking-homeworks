#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <unordered_map>
#include <cctype>

using namespace std;

struct RentalInfo {
    string orderId;
    string idNumber;
    string licensePlate;
    double fee;
};

struct User {
    string username;
    string password;
    string idNumber;
    string key;
};

unordered_map<string, User> users; // 用户信息表
vector<RentalInfo> rentalList; // 租赁信息表

// 检查身份证号是否为18位
bool isValidIdNumber(const string& idNumber) {
    return idNumber.length() == 18;
}

// 检查车牌号是否合法
bool isValidLicensePlate(const string& licensePlate) {
    if (licensePlate.length() != 5) return false;
    for (char ch : licensePlate) {
        if (!isdigit(ch) && !(isupper(ch) && ch != 'I' && ch != 'O')) {
            return false;
        }
    }
    return true;
}

// 输入并验证租赁信息
void inputRentalInfo() {
    RentalInfo info;
    cout << "请输入订单号: ";
    cin >> info.orderId;
    
    while (true) {
        cout << "请输入身份证号(18位): ";
        cin >> info.idNumber;
        if (isValidIdNumber(info.idNumber)) break;
        else cout << "身份证号必须为18位，请重新输入。" << endl;
    }
    
    while (true) {
        cout << "请输入车牌号(5位数字或大写字母): ";
        cin >> info.licensePlate;
        if (isValidLicensePlate(info.licensePlate)) break;
        else cout << "车牌号必须为5位数字或大写字母（不含'I'和'O'），请重新输入。" << endl;
    }
    
    info.fee = 0; // 初始费用为0
    rentalList.push_back(info);
}

// 显示所有租赁信息
void displayRentalInfo() {
    cout << "订单号\t身份证号\t车牌号\t费用" << endl;
    for (const auto& info : rentalList) {
        cout << info.orderId << "\t" << info.idNumber << "\t" << info.licensePlate << "\t" << info.fee << endl;
    }
}

// 查询单条租赁信息
void queryRentalById() {
    string idNumber;
    cout << "请输入身份证号: ";
    cin >> idNumber;
    bool found = false;
    for (const auto& info : rentalList) {
        if (info.idNumber == idNumber) {
            cout << "订单号: " << info.orderId << ", 身份证号: " << info.idNumber << ", 车牌号: " << info.licensePlate << ", 费用: " << info.fee << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "无此信息" << endl;
    }
}

// 查询每辆车的租赁费用
void queryTotalFeeByLicensePlate() {
    string licensePlate;
    cout << "请输入车牌号: ";
    cin >> licensePlate;
    double totalFee = 0;
    for (const auto& info : rentalList) {
        if (info.licensePlate == licensePlate) {
            totalFee += info.fee;
        }
    }
    cout << "车牌号: " << licensePlate << ", 总费用: " << totalFee << endl;
}

// 添加租赁信息
void addRentalInfo() {
    inputRentalInfo();
    displayRentalInfo();
}

// 修改租赁信息
void modifyRentalInfo() {
    string idNumber;
    cout << "请输入要修改的租赁信息的身份证号: ";
    cin >> idNumber;
    bool found = false;
    for (auto& info : rentalList) {
        if (info.idNumber == idNumber) {
            cout << "请输入新的订单号: ";
            cin >> info.orderId;
            while (true) {
                cout << "请输入新的车牌号(5位数字或大写字母): ";
                cin >> info.licensePlate;
                if (isValidLicensePlate(info.licensePlate)) break;
                else cout << "车牌号必须为5位数字或大写字母（不含'I'和'O'），请重新输入。" << endl;
            }
            cout << "请输入新的费用: ";
            cin >> info.fee;
            found = true;
        }
    }
    if (!found) {
        cout << "无此信息" << endl;
    }
    displayRentalInfo();
}

// 删除租赁信息
void deleteRentalInfo() {
    string idNumber;
    cout << "请输入要删除的租赁信息的身份证号: ";
    cin >> idNumber;
    auto it = remove_if(rentalList.begin(), rentalList.end(), [&idNumber](const RentalInfo& info) {
        return info.idNumber == idNumber;
    });
    if (it != rentalList.end()) {
        rentalList.erase(it, rentalList.end());
        cout << "删除成功" << endl;
    } else {
        cout << "无此信息" << endl;
    }
    displayRentalInfo();
}

// 统计函数
void statistics() {
    double totalAmount = 0;
    for (const auto& info : rentalList) {
        totalAmount += info.fee;
    }
    cout << "当月订单总金额: " << totalAmount << endl;

    if (!rentalList.empty()) {
        auto maxElement = max_element(rentalList.begin(), rentalList.end(), [](const RentalInfo& a, const RentalInfo& b) {
            return a.fee < b.fee;
        });
        cout << "订单金额最高的车牌号: " << maxElement->licensePlate << endl;
    }
}

// 注册用户
void registerUser() {
    User user;
    cout << "请输入用户名: ";
    cin >> user.username;
    cout << "请输入密码: ";
    cin >> user.password;
    
    while (true) {
        cout << "请输入身份证号(18位): ";
        cin >> user.idNumber;
        if (isValidIdNumber(user.idNumber)) break;
        else cout << "身份证号必须为18位，请重新输入。" << endl;
    }
    
    while (true) {
        cout << "请输入不少于八位的密钥: ";
        cin >> user.key;
        if (user.key.length() >= 8) break;
        else cout << "密钥长度必须不少于八位，请重新输入。" << endl;
    }
    
    users[user.username] = user;
    cout << "注册成功！" << endl;
}

// 用户登录
bool loginUser(User& loggedInUser) {
    string username, password;
    cout << "请输入用户名: ";
    cin >> username;
    cout << "请输入密码: ";
    cin >> password;
    
    if (users.find(username) != users.end() && users[username].password == password) {
        loggedInUser = users[username];
        return true;
    }
    
    cout << "用户名或密码错误！" << endl;
    return false;
}

// 重置密码
void resetPassword() {
    string username, idNumber, key;
    cout << "请输入用户名: ";
    cin >> username;
    if (users.find(username) == users.end()) {
        cout << "用户名不存在！" << endl;
        return;
    }
    
    cout << "请输入身份证号: ";
    cin >> idNumber;
    cout << "请输入密钥: ";
    cin >> key;
    
    if (users[username].idNumber == idNumber && users[username].key == key) {
        cout << "请输入新密码: ";
        cin >> users[username].password;
        cout << "密码重置成功！" << endl;
    } else {
        cout << "身份证号或密钥错误！" << endl;
    }
}

// 管理员登录
bool loginAdmin() {
    string adminUsername = "112233";
    string adminPassword = "112233";
    string username, password;
    
    cout << "请输入管理员账号: ";
    cin >> username;
    cout << "请输入管理员密码: ";
    cin >> password;
    
    if (username == adminUsername && password == adminPassword) {
        return true;
    }
    
    cout << "管理员账号或密码错误！" << endl;
    return false;
}

void userMenu() {
    User loggedInUser;
    while (true) {
        int choice;
        cout << "1. 用户登录\n";
        cout << "2. 用户注册\n";
        cout << "3. 重置密码\n";
        cout << "4. 返回主菜单\n";
        cout << "请选择功能: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                if (loginUser(loggedInUser)) {
                    while (true) {
                        cout << "1. 查询单条租赁信息\n";
                        cout << "2. 查询每辆车的租赁费用\n";
                        cout << "3. 返回\n";
                        cout << "请选择功能: ";
                        cin >> choice;
                        
                        if (choice == 1) {
                            queryRentalById();
                        } else if (choice == 2) {
                            queryTotalFeeByLicensePlate();
                        } else if (choice == 3) {
                            break;
                        } else {
                            cout << "无效选项，请重新选择" << endl;
                        }
                    }
                }
                break;
            case 2:
                registerUser();
                break;
            case 3:
                resetPassword();
                break;
            case 4:
                return;
            default:
                cout << "无效选项，请重新选择" << endl;
        }
    }
}

void adminMenu() {
    if (loginAdmin()) {
        while (true) {
            int choice;
            cout << "1. 录入租赁信息\n";
            cout << "2. 显示租赁信息\n";
            cout << "3. 添加租赁信息\n";
            cout << "4. 修改租赁信息\n";
            cout << "5. 删除租赁信息\n";
            cout << "6. 统计信息\n";
            cout << "7. 返回主菜单\n";
            cout << "请选择功能: ";
            cin >> choice;
            
            switch (choice) {
                case 1:
                    inputRentalInfo();
                    break;
                case 2:
                    displayRentalInfo();
                    break;
                case 3:
                    addRentalInfo();
                    break;
                case 4:
                    modifyRentalInfo();
                    break;
                case 5:
                    deleteRentalInfo();
                    break;
                case 6:
                    statistics();
                    break;
                case 7:
                    return;
                default:
                    cout << "无效选项，请重新选择" << endl;
            }
        }
    }
}

int main() {
    while (true) {
        int choice;
        cout << "1. 用户端\n";
        cout << "2. 管理端\n";
        cout << "3. 退出\n";
        cout << "请选择功能: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                userMenu();
                break;
            case 2:
                adminMenu();
                break;
            case 3:
                return 0;
            default:
                cout << "无效选项，请重新选择" << endl;
        }
    }
    return 0;
}
