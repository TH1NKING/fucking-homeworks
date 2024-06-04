#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cctype>

using namespace std;

struct RentalInfo {
    string orderId;
    string idNumber;
    string licensePlate;
    double fee;
};

vector<RentalInfo> rentalList;

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
    // 这里只是展示一些简单的示例统计函数，你可以根据需要进行扩展
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

int main() {
    int choice;
    while (true) {
        cout << "1. 录入租赁信息\n";
        cout << "2. 显示租赁信息\n";
        cout << "3. 查询单条租赁信息\n";
        cout << "4. 查询每辆车的租赁费用\n";
        cout << "5. 添加租赁信息\n";
        cout << "6. 修改租赁信息\n";
        cout << "7. 删除租赁信息\n";
        cout << "8. 统计信息\n";
        cout << "9. 退出\n";
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
                queryRentalById();
                break;
            case 4:
                queryTotalFeeByLicensePlate();
                break;
            case 5:
                addRentalInfo();
                break;
            case 6:
                modifyRentalInfo();
                break;
            case 7:
                deleteRentalInfo();
                break;
            case 8:
                statistics();
                break;
            case 9:
                return 0;
            default:
                cout << "无效选项，请重新选择" << endl;
        }
    }
    return 0;
}
