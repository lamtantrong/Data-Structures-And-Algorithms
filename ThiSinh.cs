using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ThiSinhDuThi
{
    class ThiSinh
    {
        public string SBD { get; set; }
        public string HoTen { get; set; }
        public int NamSinh { get; set; }
        public double DiemToan { get; set; }
        public double DiemVan { get; set; }
        public double DiemNN { get; set; }

        public ThiSinh(string sbd, string hoten, int namsinh, double diemtoan, double diemvan, double diemnn)
        {
            SBD = sbd;
            HoTen = hoten;
            NamSinh = namsinh;
            DiemToan = diemtoan;
            DiemVan = diemvan;
            DiemNN = diemnn;
        }

        public ThiSinh()
        {
            SBD = "";
            HoTen = "";
            NamSinh = 0;
            DiemToan = 0;
            DiemVan = 0;
            DiemNN = 0;
        }

        public ThiSinh(ThiSinh ts)
        {
            SBD = ts.SBD;
            HoTen = ts.HoTen;
            NamSinh = ts.NamSinh;
            DiemToan = ts.DiemToan;
            DiemVan = ts.DiemVan;
            DiemNN = ts.DiemNN;
        }
        public double TongDiem
        {
            get { return DiemToan + DiemVan + DiemNN * 2; }
        }

        public string KetQua
        {
            get { return TongDiem >= 25 ? "Đậu" : "Rớt"; }
        }

        public void XuatThiSinh()
        {
            Console.WriteLine("{0,-10}{1,-20}{2,-10}{3,-10}{4,-10}{5,-15}{6,-10}{7,-10}", SBD, HoTen, NamSinh, DiemToan, DiemVan, DiemNN, TongDiem, KetQua);
        }
    }
}
