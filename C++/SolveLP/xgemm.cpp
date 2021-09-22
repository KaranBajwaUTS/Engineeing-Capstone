//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// xgemm.cpp
//
// Code generation for function 'xgemm'
//

// Include files
#include "xgemm.h"
#include "rt_nonfinite.h"
#include <cstring>
#include <string.h>

// Function Definitions
namespace coder {
namespace internal {
namespace blas {
void xgemm(int m, int n, int k, const double A[576], int lda,
           const double B[21904], int ib0, double C[11100])
{
  if ((m != 0) && (n != 0)) {
    int br;
    int cr;
    int i;
    int i1;
    int lastColC;
    br = ib0;
    lastColC = 148 * (n - 1);
    for (cr = 0; cr <= lastColC; cr += 148) {
      i = cr + 1;
      i1 = cr + m;
      if (i <= i1) {
        std::memset(&C[i + -1], 0, ((i1 - i) + 1) * sizeof(double));
      }
    }
    for (cr = 0; cr <= lastColC; cr += 148) {
      int ar;
      ar = -1;
      i = br + k;
      for (int ib{br}; ib < i; ib++) {
        int i2;
        i1 = cr + 1;
        i2 = cr + m;
        for (int ic{i1}; ic <= i2; ic++) {
          C[ic - 1] += B[ib - 1] * A[(ar + ic) - cr];
        }
        ar += lda;
      }
      br += 148;
    }
  }
}

void xgemm(int m, int n, int k, const double A[21904], int ia0,
           const double B[11100], double C[21904])
{
  if ((m != 0) && (n != 0)) {
    int br;
    int cr;
    int i;
    int i1;
    int lastColC;
    lastColC = 148 * (n - 1);
    for (cr = 0; cr <= lastColC; cr += 148) {
      i = cr + 1;
      i1 = cr + m;
      if (i <= i1) {
        std::memset(&C[i + -1], 0, ((i1 - i) + 1) * sizeof(double));
      }
    }
    br = -1;
    for (cr = 0; cr <= lastColC; cr += 148) {
      int ar;
      ar = ia0;
      i = cr + 1;
      i1 = cr + m;
      for (int ic{i}; ic <= i1; ic++) {
        double temp;
        temp = 0.0;
        for (int w{0}; w < k; w++) {
          temp += A[(w + ar) - 1] * B[(w + br) + 1];
        }
        C[ic - 1] += temp;
        ar += 148;
      }
      br += 148;
    }
  }
}

} // namespace blas
} // namespace internal
} // namespace coder

// End of code generation (xgemm.cpp)
