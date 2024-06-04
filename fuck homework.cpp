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

unordered_map<string, User> users; // �û���Ϣ��
vector<RentalInfo> rentalList; // ������Ϣ��

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

// ע���û�
void registerUser() {
    User user;
    cout << "�������û���: ";
    cin >> user.username;
    cout << "����������: ";
    cin >> user.password;
    
    while (true) {
        cout << "���������֤��(18λ): ";
        cin >> user.idNumber;
        if (isValidIdNumber(user.idNumber)) break;
        else cout << "���֤�ű���Ϊ18λ�����������롣" << endl;
    }
    
    while (true) {
        cout << "�����벻���ڰ�λ����Կ: ";
        cin >> user.key;
        if (user.key.length() >= 8) break;
        else cout << "��Կ���ȱ��벻���ڰ�λ�����������롣" << endl;
    }
    
    users[user.username] = user;
    cout << "ע��ɹ���" << endl;
}

// �û���¼
bool loginUser(User& loggedInUser) {
    string username, password;
    cout << "�������û���: ";
    cin >> username;
    cout << "����������: ";
    cin >> password;
    
    if (users.find(username) != users.end() && users[username].password == password) {
        loggedInUser = users[username];
        return true;
    }
    
    cout << "�û������������" << endl;
    return false;
}

// ��������
void resetPassword() {
    string username, idNumber, key;
    cout << "�������û���: ";
    cin >> username;
    if (users.find(username) == users.end()) {
        cout << "�û��������ڣ�" << endl;
        return;
    }
    
    cout << "���������֤��: ";
    cin >> idNumber;
    cout << "��������Կ: ";
    cin >> key;
    
    if (users[username].idNumber == idNumber && users[username].key == key) {
        cout << "������������: ";
        cin >> users[username].password;
        cout << "�������óɹ���" << endl;
    } else {
        cout << "���֤�Ż���Կ����" << endl;
    }
}

// ����Ա��¼
bool loginAdmin() {
    string adminUsername = "112233";
    string adminPassword = "112233";
    string username, password;
    
    cout << "���������Ա�˺�: ";
    cin >> username;
    cout << "���������Ա����: ";
    cin >> password;
    
    if (username == adminUsername && password == adminPassword) {
        return true;
    }
    
    cout << "����Ա�˺Ż��������" << endl;
    return false;
}

void userMenu() {
    User loggedInUser;
    while (true) {
        int choice;
        cout << "1. �û���¼\n";
        cout << "2. �û�ע��\n";
        cout << "3. ��������\n";
        cout << "4. �������˵�\n";
        cout << "��ѡ����: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                if (loginUser(loggedInUser)) {
                    while (true) {
                        cout << "1. ��ѯ����������Ϣ\n";
                        cout << "2. ��ѯÿ���������޷���\n";
                        cout << "3. ����\n";
                        cout << "��ѡ����: ";
                        cin >> choice;
                        
                        if (choice == 1) {
                            queryRentalById();
                        } else if (choice == 2) {
                            queryTotalFeeByLicensePlate();
                        } else if (choice == 3) {
                            break;
                        } else {
                            cout << "��Чѡ�������ѡ��" << endl;
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
                cout << "��Чѡ�������ѡ��" << endl;
        }
    }
}

void adminMenu() {
    if (loginAdmin()) {
        while (true) {
            int choice;
            cout << "1. ¼��������Ϣ\n";
            cout << "2. ��ʾ������Ϣ\n";
            cout << "3. ���������Ϣ\n";
            cout << "4. �޸�������Ϣ\n";
            cout << "5. ɾ��������Ϣ\n";
            cout << "6. ͳ����Ϣ\n";
            cout << "7. �������˵�\n";
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
                    cout << "��Чѡ�������ѡ��" << endl;
            }
        }
    }
}

int main() {
    while (true) {
        int choice;
        cout << "1. �û���\n";
        cout << "2. �����\n";
        cout << "3. �˳�\n";
        cout << "��ѡ����: ";
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
                cout << "��Чѡ�������ѡ��" << endl;
        }
    }
    return 0;
}
