#include <bits/stdc++.h>
using namespace std;

struct HocPhan {
    string maLopHocPhan;
    string tenHocPhan;
    int soTC;
    double hocPhi; 
};

void sxTangDan(HocPhan ds[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = n - 1; j > i; j--) {
            if (ds[j].hocPhi * ds[j].soTC < ds[j-1].hocPhi * ds[j-1].soTC) {
                HocPhan temp = ds[j];
                ds[j] = ds[j-1];
                ds[j-1] = temp;
            }
        }
    }
}

// Greedy 
int C(HocPhan ds[], int n, double p, HocPhan kq[], double &tongHocPhi) {
    sxTangDan(ds, n);
    tongHocPhi = 0;
    int sl = 0;
    int i = 0;
    while (i < n && (ds[i].hocPhi * ds[i].soTC) <= p) {
        kq[sl++] = ds[i];
        tongHocPhi += ds[i].hocPhi * ds[i].soTC;
        p -= ds[i].hocPhi * ds[i].soTC;
        i++;
    }
    return sl;
}

// quy hoach dong
int D(HocPhan ds[], int n, double m, HocPhan kq[], double &tongHocPhi) {
    int M = (int)m;
    long** t = new long*[n + 1]; 
    for (int i = 0; i <= n; i++) {
        t[i] = new long[M + 1]();
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= M; j++) {
            t[i][j] = t[i-1][j];
            int cost = (int)(ds[i-1].hocPhi * ds[i-1].soTC);
            if (cost <= j) {
                long tam = ds[i-1].soTC + t[i-1][j - cost];
                if (t[i][j] < tam) t[i][j] = tam;
            }
        }
    }

    int sl = 0;
    tongHocPhi = 0;
    int i = n;int j = M;
    while (i > 0 && j >= 0) {
        int cost = (int)(ds[i-1].hocPhi * ds[i-1].soTC);
        if (t[i][j] != t[i-1][j]) {
            kq[sl++] = ds[i-1];
            tongHocPhi += ds[i-1].hocPhi * ds[i-1].soTC;
            j -= cost;
        }
        i--;
    }
    return sl;
}

void inKetQua(HocPhan ketqua[], int soluongchon, double tongHocPhi) {
    if (soluongchon == 0) cout << "Khong co phuong an thoa man" << endl;
    else {
        cout << "So luong hoc phan can dang ky : " << soluongchon << endl;
        cout << "Tong hoc phi : " << tongHocPhi << endl;
        cout << "Danh sach cac mon dang ky :" << endl;
        for (int i = 0; i < soluongchon; i++) {
            cout << "-" << ketqua[i].maLopHocPhan << ", Ten hoc phan : " << ketqua[i].tenHocPhan 
                 << ", So tin chi : " << ketqua[i].soTC 
                 << ", Hoc phi 1 tin : " << ketqua[i].hocPhi << endl;
        }
    }
}

int main() {
    int n = 6;
    double p = 1500000;
    HocPhan ds[n] = {
        {"20243IT6044001", "Ung dung thuat toan", 3, 450000},
        {"20243IT6018002", "Co so du lieu", 4, 400000},
        {"20243IT6025003", "Tri tue nhan tao", 3, 500000},
        {"20243IT6030004", "Mang may tinh", 4, 200000},
        {"20243IT6010005", "Kien truc may tinh", 3, 200000},
        {"20243IT6050006", "Phan tich dac ta", 1, 500000}
    };
    HocPhan kq[n] = {};
    cout << "--------------Cau 1 (Tham lam)----------------" << endl;
    double tongHocPhi1 = 0;
    int sl1 = C(ds, n, p, kq, tongHocPhi1);
    inKetQua(kq, sl1, tongHocPhi1);

    cout << "\n--------------Cau 2 (Quy hoach dong)----------------" << endl;
    double m = 2000000;
    double tongHocPhi2 = 0;
    int sl2 = D(ds, n, m, kq, tongHocPhi2);
    inKetQua(kq, sl2, tongHocPhi2);

}
