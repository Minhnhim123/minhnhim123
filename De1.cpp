#include <bits/stdc++.h>
using namespace std;

struct Tham {
    string tenHSX;
    int dienTich;
    double tien;
    string mauSac;
};

void sxTangDan(Tham ds[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = n - 1; j > i; j--) {
            if (ds[j].tien < ds[j-1].tien) {
                Tham temp = ds[j];
                ds[j] = ds[j-1];
                ds[j-1] = temp;
            }
        }
    }
}

// Greedy Algorithm
int A(Tham ds[], int n, double m, Tham kq[], double &tongTien, int &tongDienTich) {
    sxTangDan(ds, n);
    tongTien = 0;
    tongDienTich = 0;
    int sl = 0;
    int i = 0;
    while (i < n && ds[i].tien <= m) {
        kq[sl++] = ds[i];
        tongTien += ds[i].tien;
        tongDienTich += ds[i].dienTich;
        m -= ds[i].tien;
        i++;
    }
    return sl;
}

// quy hoach dong
int B(Tham ds[], int n, int s, Tham kq[], double &tongTien, int &soLuongXanh) {
    long** dp = new long*[n + 1];
    int** traceback = new int*[n + 1];
    for (int i = 0; i <= n; i++) {
        dp[i] = new long[s + 1]();
        traceback[i] = new int[s + 1]();
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= s; j++) {
            dp[i][j] = dp[i-1][j];
            if (ds[i-1].dienTich <= j) {
                long tam = ds[i-1].tien + dp[i-1][j - ds[i-1].dienTich];
                if (dp[i][j] < tam) {
                    dp[i][j] = tam;
                    traceback[i][j] = 1;
                }
            }
        }
    }

    int sl = 0;
    tongTien = 0;
    soLuongXanh = 0;
    int i = n;int j = s;
    while (i > 0 && j >= 0) {
        if (traceback[i][j] == 1) {
            kq[sl++] = ds[i-1];
            tongTien += ds[i-1].tien;
            if (ds[i-1].mauSac == "xanh") soLuongXanh++;
            j -= ds[i-1].dienTich;
        }
        i--;
    }

    return sl;
}

void inKetQua(Tham ketqua[], int soluongchon, double tongTien, int soLuongXanh = 0) {
    if (soluongchon == 0) cout << "Khong co phuong an thoa man" << endl;
		else {
        cout<< "So phuong an thoa man: " << soluongchon << endl;
        if (soLuongXanh > 0) {
            cout << "So luong tham mau xanh: " << soLuongXanh << endl;
        }
        cout << "Danh sach tham da mua:" << endl;
        for (int i = 0; i < soluongchon; i++) {
            cout << "-" << ketqua[i].tenHSX << ", Gia: " << ketqua[i].tien 
                 << ", Mau sac: " << ketqua[i].mauSac 
                 << ", Dien tich: " << ketqua[i].dienTich << endl;
    }
}
}
int main() {
    int n = 6;
    double m = 500000;
    Tham ds[n] = {
        {"Tham winmart", 15, 200000, "xanh"},
        {"Tham sunhouse", 20, 150000, "do"},
        {"Tham hoa phat", 30, 250000, "xanh"},
        {"Tham rang dong", 12, 100000, "vang"},
        {"Tham flower", 54, 300000, "xanh"},
        {"Tham everon", 6, 800000, "tim"}
    };
    Tham kq[n] = {};
    cout << "--------------Cau 1 (Tham lam)----------------" << endl;
    double tongTien1 = 0;
    int tongDienTich1 = 0;
    int sl1 = A(ds, n, m, kq, tongTien1, tongDienTich1);
    inKetQua(kq, sl1, tongTien1);
    cout << "Tong dien tich: " << tongDienTich1 << endl;
    cout << "\n--------------Cau 2 (Quy hoach dong)----------------" << endl;
    int s = 100;
    double tongTien2 = 0;
    int soLuongXanh = 0;
    int sl2 = B(ds, n, s, kq, tongTien2, soLuongXanh);
    inKetQua(kq, sl2, tongTien2, soLuongXanh);
}
