using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
using System.Threading.Tasks;
using Sinh_Viên;

namespace ThiSinhDuThi
{

    internal class Program
    {

        static void Main(string[] args)
        {

            Console.OutputEncoding = Encoding.UTF8;
            Console.InputEncoding = Encoding.Unicode;
            DanhSachThiSinh ds = new DanhSachThiSinh();
            ds.NhapTuFileXML("DSThiSinh.xml");
            //ds.NhapTuBanPhim();
            ds.XuatDanhSach();
            Console.ReadKey();
            Console.Clear();
            Console.WriteLine("Sắp xếp Thí sinh theo tổng điểm giảm dần");
            Console.WriteLine("------------------------------------------");

            ds.SapXepTheoTongDiemGiamDan();
            ds.XuatDanhSach();

            Console.WriteLine("Sắp xếp Thí sinh tăng dần theo họ tên");
            Console.WriteLine("------------------------------------------");
            ds.SapXepTheoHoTenTangDan();
            ds.XuatDanhSach();

            List<ThiSinh> dsDau = ds.LayDanhSachThiSinhDau();
            Console.WriteLine("Danh sách Thí sinh đậu");
            Console.WriteLine("------------------------------------------");

            foreach (ThiSinh dau in dsDau)
                dau.XuatThiSinh();
            List<ThiSinh> dsTheoNamSinh = ds.LayDanhSachThiSinh1995VaDiemToanTren9();
            Console.WriteLine("Danh sách sinh viên có năm sinh trên 1995 hoặc có điểm toán trên 9");
            foreach (ThiSinh dsts in dsTheoNamSinh)
                dsts.XuatThiSinh();


            Console.ReadLine();
        }
    }
}