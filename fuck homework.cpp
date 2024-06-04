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

// ������֤���Ƿ�Ϊ18λ
bool isValidIdNumber(const string& idNumber) {
    return idNumber.length() == 18;
}

// ��鳵�ƺ��Ƿ�Ϸ�
bool isValidLicensePlate(const string& licensePlate) {
    if (licensePlate.length() != 5) return false;
    for (char ch : licensePlate) {
        if (!isdigit(ch) && !(isupper(ch) && ch != 'I' && ch != 'O')) {
            return false;
        }
    }
    return true;
}

// ���벢��֤������Ϣ
void inputRentalInfo() {
    RentalInfo info;
    cout << "�����붩����: ";
    cin >> info.orderId;
    
    while (true) {
        cout << "���������֤��(18λ): ";
        cin >> info.idNumber;
        if (isValidIdNumber(info.idNumber)) break;
        else cout << "���֤�ű���Ϊ18λ�����������롣" << endl;
    }
    
    while (true) {
        cout << "�����복�ƺ�(5λ���ֻ��д��ĸ): ";
        cin >> info.licensePlate;
        if (isValidLicensePlate(info.licensePlate)) break;
        else cout << "���ƺű���Ϊ5λ���ֻ��д��ĸ������'I'��'O'�������������롣" << endl;
    }
    
    info.fee = 0; // ��ʼ����Ϊ0
    rentalList.push_back(info);
}

// ��ʾ����������Ϣ
void displayRentalInfo() {
    cout << "������\t���֤��\t���ƺ�\t����" << endl;
    for (const auto& info : rentalList) {
        cout << info.orderId << "\t" << info.idNumber << "\t" << info.licensePlate << "\t" << info.fee << endl;
    }
}

// ��ѯ����������Ϣ
void queryRentalById() {
    string idNumber;
    cout << "���������֤��: ";
    cin >> idNumber;
    bool found = false;
    for (const auto& info : rentalList) {
        if (info.idNumber == idNumber) {
            cout << "������: " << info.orderId << ", ���֤��: " << info.idNumber << ", ���ƺ�: " << info.licensePlate << ", ����: " << info.fee << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "�޴���Ϣ" << endl;
    }
}

// ��ѯÿ���������޷���
void queryTotalFeeByLicensePlate() {
    string licensePlate;
    cout << "�����복�ƺ�: ";
    cin >> licensePlate;
    double totalFee = 0;
    for (const auto& info : rentalList) {
        if (info.licensePlate == licensePlate) {
            totalFee += info.fee;
        }
    }
    cout << "���ƺ�: " << licensePlate << ", �ܷ���: " << totalFee << endl;
}

// ���������Ϣ
void addRentalInfo() {
    inputRentalInfo();
    displayRentalInfo();
}

// �޸�������Ϣ
void modifyRentalInfo() {
    string idNumber;
    cout << "������Ҫ�޸ĵ�������Ϣ�����֤��: ";
    cin >> idNumber;
    bool found = false;
    for (auto& info : rentalList) {
        if (info.idNumber == idNumber) {
            cout << "�������µĶ�����: ";
            cin >> info.orderId;
            while (true) {
                cout << "�������µĳ��ƺ�(5λ���ֻ��д��ĸ): ";
                cin >> info.licensePlate;
                if (isValidLicensePlate(info.licensePlate)) break;
                else cout << "���ƺű���Ϊ5λ���ֻ��д��ĸ������'I'��'O'�������������롣" << endl;
            }
            cout << "�������µķ���: ";
            cin >> info.fee;
            found = true;
        }
    }
    if (!found) {
        cout << "�޴���Ϣ" << endl;
    }
    displayRentalInfo();
}

// ɾ��������Ϣ
void deleteRentalInfo() {
    string idNumber;
    cout << "������Ҫɾ����������Ϣ�����֤��: ";
    cin >> idNumber;
    auto it = remove_if(rentalList.begin(), rentalList.end(), [&idNumber](const RentalInfo& info) {
        return info.idNumber == idNumber;
    });
    if (it != rentalList.end()) {
        rentalList.erase(it, rentalList.end());
        cout << "ɾ���ɹ�" << endl;
    } else {
        cout << "�޴���Ϣ" << endl;
    }
    displayRentalInfo();
}

// ͳ�ƺ���
void statistics() {
    // ����ֻ��չʾһЩ�򵥵�ʾ��ͳ�ƺ���������Ը�����Ҫ������չ
    double totalAmount = 0;
    for (const auto& info : rentalList) {
        totalAmount += info.fee;
    }
    cout << "���¶����ܽ��: " << totalAmount << endl;

    if (!rentalList.empty()) {
        auto maxElement = max_element(rentalList.begin(), rentalList.end(), [](const RentalInfo& a, const RentalInfo& b) {
            return a.fee < b.fee;
        });
        cout << "���������ߵĳ��ƺ�: " << maxElement->licensePlate << endl;
    }
}

int main() {
    int choice;
    while (true) {
        cout << "1. ¼��������Ϣ\n";
        cout << "2. ��ʾ������Ϣ\n";
        cout << "3. ��ѯ����������Ϣ\n";
        cout << "4. ��ѯÿ���������޷���\n";
        cout << "5. ���������Ϣ\n";
        cout << "6. �޸�������Ϣ\n";
        cout << "7. ɾ��������Ϣ\n";
        cout << "8. ͳ����Ϣ\n";
        cout << "9. �˳�\n";
        cout << "��ѡ����: ";
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
                cout << "��Чѡ�������ѡ��" << endl;
        }
    }
    return 0;
}
