
// BufferReader.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "BitReader.h"
#include "BitWriter.h"

using namespace std;

#pragma pack(push, 1)

struct test {

  uint8_t t1;
  uint16_t t2;
  uint32_t t3;

  struct {
    uint32_t tt1 : 1;
    uint32_t tt5 : 4;
    uint32_t tt2 : 7;
    uint32_t tt3 : 9;
    uint32_t tt4 : 11;
  };
};

#pragma pack(pop, 1)

int main() {

  test TT = {1, 2, 3, {1, 2, 2, 144, 345}};
  void *k = &TT;

  unsigned char t[100] = {0};
  unsigned char *tp = t;
  BitWriter *bw = new BitWriter(tp, 100);
  bw->write_8_bit(1);
  bw->write_16_bit(2);
  bw->write_32_bit(3);
  bw->write_n_bit(1, 1);
  bw->write_n_bit(2, 4);
  bw->write_n_bit(2, 7);
  bw->write_n_bit(144, 9);
  bw->write_n_bit(345, 11);
  size_t kz = bw->size();
  bw->write_n_bit(6, 3);
  bw->write_n_bit(12, 7);
  kz = bw->size();

  BitReader *br = new BitReader(tp);
  cout << br->read_8_bit() << endl;
  cout << br->read_16_bit() << endl;
  cout << br->read_32_bit() << endl;

  cout << br->read_n_bit(1) << endl;
  cout << br->read_n_bit(4) << endl;
  cout << br->read_n_bit(7) << endl;
  cout << br->read_n_bit(9) << endl;
  cout << br->read_n_bit(11) << endl;
  cout << br->read_n_bit(3) << endl;
  cout << br->read_n_bit(7) << endl;

  for (int i = 0; i < 10; ++i) {
    bw->write_n_bit(4, 3);
  }

  for (int i = 0; i < 10; ++i) {
    cout << br->read_n_bit(3) << endl;
  }

  std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧:
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5.
//   转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
