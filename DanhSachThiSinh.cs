using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Xml;
using ThiSinhDuThi;

namespace Sinh_Viên
{
    class DanhSachThiSinh
    {
        List<ThiSinh> dsThiSinh;

        public DanhSachThiSinh()
        {
            dsThiSinh = new List<ThiSinh>();
        }
        public void NhapTuBanPhim()
        {
            Console.Write("Nhap so luong thi sinh: ");
            int n = int.Parse(Console.ReadLine());

            for (int i = 0; i < n; i++)
            {
                Console.WriteLine("Nhap thong tin thi sinh thu {0}", i + 1);

                Console.Write("SBD: ");
                string sbd = Console.ReadLine();

                Console.Write("Ho ten: ");
                string hoten = Console.ReadLine();

                Console.Write("Nam sinh: ");
                int namsinh = int.Parse(Console.ReadLine());

                Console.Write("Diem toan: ");
                double diemtoan = double.Parse(Console.ReadLine());

                Console.Write("Diem van: ");
                double diemvan = double.Parse(Console.ReadLine());

                Console.Write("Diem ngoai ngu: ");
                double diemnn = double.Parse(Console.ReadLine());

                ThiSinh ts = new ThiSinh(sbd, hoten, namsinh, diemtoan, diemvan, diemnn);
                dsThiSinh.Add(ts);
            }
        }


        public void NhapTuFileXML(string tenFile)
        {
            XmlDocument doc = new XmlDocument();
            doc.Load(tenFile);
            XmlNodeList nodeList = doc.SelectNodes("/DSSV/ThiSinh");

            foreach (XmlNode node in nodeList)
            {
                ThiSinh ts = new ThiSinh();
                ts.SBD = node["SBD"].InnerText;
                ts.HoTen = node["HT"].InnerText;
                ts.NamSinh = int.Parse(node["NamSinh"].InnerText);
                ts.DiemToan = double.Parse(node["Toan"].InnerText);
                ts.DiemVan = double.Parse(node["Van"].InnerText);
                ts.DiemNN = double.Parse(node["NN"].InnerText);

                dsThiSinh.Add(ts);
            }
        }
        public void XuatDanhSach()
        {
            Console.WriteLine("Danh sach thi sinh:");
            Console.WriteLine("{0,-10}{1,-20}{2,-10}{3,-10}{4,-10}{5,-15}{6,-10}{7,-10} ", "|SBD", "|Họ tên", "|Năm sinh", "|Diểm toán", "|Diểm văn", "|Diểm ngoại ngữ", "|Tổng diểm", "|Kết quả|");

            foreach (ThiSinh ts in dsThiSinh)
            {
                Console.WriteLine("{0,-10}{1,-20}{2,-10}{3,-10}{4,-10}{5,-15} {6,-10} {7,-10}", ts.SBD, ts.HoTen, ts.NamSinh, ts.DiemToan, ts.DiemVan, ts.DiemNN, ts.TongDiem,ts.KetQua);
            }
        }
        public void SapXepTheoTongDiemGiamDan()
        {
            dsThiSinh.Sort((ts1, ts2) => ts2.TongDiem.CompareTo(ts1.TongDiem));
        }

        public void SapXepTheoHoTenTangDan()
        {
            dsThiSinh.Sort((ts1, ts2) =>
            {
                int cmp = ts1.HoTen.CompareTo(ts2.HoTen);
                if (cmp == 0)
                {
                    cmp = ts2.DiemToan.CompareTo(ts1.DiemToan);
                }
                return cmp;
            });
        }
        public List<ThiSinh> LayDanhSachThiSinhDau()
        {

            return dsThiSinh.Where(ts => ts.KetQua == "Đậu").ToList();
        }

        public List<ThiSinh> LayDanhSachThiSinh1995VaDiemToanTren9()
        {
            return dsThiSinh.Where(ts => ts.NamSinh > 1995 || ts.DiemToan >= 9).ToList();
        }
    }
}
