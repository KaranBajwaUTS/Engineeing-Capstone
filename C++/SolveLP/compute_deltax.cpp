//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// compute_deltax.cpp
//
// Code generation for function 'compute_deltax'
//

// Include files
#include "compute_deltax.h"
#include "SolveLP_internal_types.h"
#include "SolveLP_rtwutil.h"
#include "fullColLDL2_.h"
#include "partialColLDL3_.h"
#include "rt_nonfinite.h"
#include "solve.h"
#include "xgemm.h"
#include "xpotrf.h"
#include <cmath>
#include <cstring>
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
void compute_deltax(const double H[576], g_struct_T *solution,
                    h_struct_T *memspace, const i_struct_T *qrmanager,
                    j_struct_T *cholmanager, const b_struct_T *objective,
                    boolean_T alwaysPositiveDef)
{
  int mNull_tmp;
  int nVar_tmp;
  nVar_tmp = qrmanager->mrows - 1;
  mNull_tmp = qrmanager->mrows - qrmanager->ncols;
  if (mNull_tmp <= 0) {
    if (0 <= nVar_tmp) {
      std::memset(&solution->searchDir[0], 0, (nVar_tmp + 1) * sizeof(double));
    }
  } else {
    int idx;
    for (idx = 0; idx <= nVar_tmp; idx++) {
      solution->searchDir[idx] = -objective->grad[idx];
    }
    if (qrmanager->ncols <= 0) {
      switch (objective->objtype) {
      case 5:
        break;
      case 3: {
        double smax;
        int ix;
        int k;
        int nVars;
        int order;
        if (alwaysPositiveDef) {
          cholmanager->ndims = qrmanager->mrows;
          for (idx = 0; idx <= nVar_tmp; idx++) {
            order = qrmanager->mrows * idx;
            nVars = 148 * idx;
            for (k = 0; k <= nVar_tmp; k++) {
              cholmanager->FMat[nVars + k] = H[order + k];
            }
          }
          cholmanager->info =
              internal::lapack::xpotrf(qrmanager->mrows, cholmanager->FMat);
        } else {
          ix = qrmanager->mrows;
          cholmanager->ndims = qrmanager->mrows;
          for (idx = 0; idx < ix; idx++) {
            order = qrmanager->mrows * idx;
            nVars = 148 * idx;
            for (k = 0; k < ix; k++) {
              cholmanager->FMat[nVars + k] = H[order + k];
            }
          }
          if (qrmanager->mrows < 1) {
            nVars = -1;
          } else {
            nVars = 0;
            if (qrmanager->mrows > 1) {
              smax = std::abs(cholmanager->FMat[0]);
              for (k = 2; k <= ix; k++) {
                double s;
                s = std::abs(cholmanager->FMat[(k - 1) * 149]);
                if (s > smax) {
                  nVars = k - 1;
                  smax = s;
                }
              }
            }
          }
          cholmanager->regTol_ =
              std::fmax(std::abs(cholmanager->FMat[nVars + 148 * nVars]) *
                            2.2204460492503131E-16,
                        0.0);
          if (qrmanager->mrows > 128) {
            boolean_T exitg1;
            k = 0;
            exitg1 = false;
            while ((!exitg1) && (k < ix)) {
              nVars = 149 * k + 1;
              order = ix - k;
              if (k + 48 <= ix) {
                DynamicRegCholManager::partialColLDL3_(cholmanager, nVars,
                                                       order);
                k += 48;
              } else {
                DynamicRegCholManager::fullColLDL2_(cholmanager, nVars, order);
                exitg1 = true;
              }
            }
          } else {
            DynamicRegCholManager::fullColLDL2_(cholmanager, 1,
                                                qrmanager->mrows);
          }
          if (cholmanager->ConvexCheck) {
            idx = 0;
            int exitg2;
            do {
              exitg2 = 0;
              if (idx <= ix - 1) {
                if (cholmanager->FMat[idx + 148 * idx] <= 0.0) {
                  cholmanager->info = -idx - 1;
                  exitg2 = 1;
                } else {
                  idx++;
                }
              } else {
                cholmanager->ConvexCheck = false;
                exitg2 = 1;
              }
            } while (exitg2 == 0);
          }
        }
        if (cholmanager->info != 0) {
          solution->state = -6;
        } else if (alwaysPositiveDef) {
          CholManager::solve(cholmanager, solution->searchDir);
        } else {
          int i;
          order = cholmanager->ndims - 2;
          if (cholmanager->ndims != 0) {
            for (idx = 0; idx <= order + 1; idx++) {
              nVars = idx + idx * 148;
              i = order - idx;
              for (k = 0; k <= i; k++) {
                ix = (idx + k) + 1;
                solution->searchDir[ix] -= solution->searchDir[idx] *
                                           cholmanager->FMat[(nVars + k) + 1];
              }
            }
          }
          i = cholmanager->ndims;
          for (idx = 0; idx < i; idx++) {
            solution->searchDir[idx] /= cholmanager->FMat[idx + 148 * idx];
          }
          order = cholmanager->ndims;
          if (cholmanager->ndims != 0) {
            for (idx = order; idx >= 1; idx--) {
              nVars = (idx - 1) * 148;
              smax = solution->searchDir[idx - 1];
              i = idx + 1;
              for (k = order; k >= i; k--) {
                smax -= cholmanager->FMat[(nVars + k) - 1] *
                        solution->searchDir[k - 1];
              }
              solution->searchDir[idx - 1] = smax;
            }
          }
        }
      } break;
      default: {
        if (alwaysPositiveDef) {
          int ix;
          int k;
          int order;
          ix = objective->nvar - 1;
          cholmanager->ndims = objective->nvar;
          for (idx = 0; idx <= ix; idx++) {
            int nVars;
            order = objective->nvar * idx;
            nVars = 148 * idx;
            for (k = 0; k <= ix; k++) {
              cholmanager->FMat[nVars + k] = H[order + k];
            }
          }
          cholmanager->info =
              internal::lapack::xpotrf(objective->nvar, cholmanager->FMat);
          if (cholmanager->info != 0) {
            solution->state = -6;
          } else {
            double smax;
            int i;
            CholManager::solve(cholmanager, solution->searchDir);
            smax = 1.0 / objective->beta;
            order = objective->nvar + 1;
            i = qrmanager->mrows;
            for (k = order; k <= i; k++) {
              solution->searchDir[k - 1] *= smax;
            }
          }
        }
      } break;
      }
    } else {
      int nullStartIdx_tmp;
      nullStartIdx_tmp = 148 * qrmanager->ncols + 1;
      switch (objective->objtype) {
      case 5: {
        for (idx = 0; idx < mNull_tmp; idx++) {
          memspace->workspace_double[idx] =
              -qrmanager->Q[nVar_tmp + 148 * (qrmanager->ncols + idx)];
        }
        if (qrmanager->mrows != 0) {
          int i;
          int ix;
          if (0 <= nVar_tmp) {
            std::memset(&solution->searchDir[0], 0,
                        (nVar_tmp + 1) * sizeof(double));
          }
          ix = 0;
          i = nullStartIdx_tmp + 148 * (mNull_tmp - 1);
          for (idx = nullStartIdx_tmp; idx <= i; idx += 148) {
            int order;
            order = idx + nVar_tmp;
            for (int k{idx}; k <= order; k++) {
              int nVars;
              nVars = k - idx;
              solution->searchDir[nVars] +=
                  qrmanager->Q[k - 1] * memspace->workspace_double[ix];
            }
            ix++;
          }
        }
      } break;
      default: {
        double smax;
        int i;
        int ix;
        int k;
        int nVars;
        int order;
        switch (objective->objtype) {
        case 3:
          internal::blas::xgemm(qrmanager->mrows, mNull_tmp, qrmanager->mrows,
                                H, qrmanager->mrows, qrmanager->Q,
                                nullStartIdx_tmp, memspace->workspace_double);
          internal::blas::xgemm(mNull_tmp, mNull_tmp, qrmanager->mrows,
                                qrmanager->Q, nullStartIdx_tmp,
                                memspace->workspace_double, cholmanager->FMat);
          break;
        default:
          if (alwaysPositiveDef) {
            nVars = qrmanager->mrows;
            internal::blas::xgemm(objective->nvar, mNull_tmp, objective->nvar,
                                  H, objective->nvar, qrmanager->Q,
                                  nullStartIdx_tmp, memspace->workspace_double);
            for (order = 0; order < mNull_tmp; order++) {
              i = objective->nvar + 1;
              for (ix = i; ix <= nVars; ix++) {
                memspace->workspace_double[(ix + 148 * order) - 1] =
                    objective->beta *
                    qrmanager->Q[(ix + 148 * (order + qrmanager->ncols)) - 1];
              }
            }
            internal::blas::xgemm(mNull_tmp, mNull_tmp, qrmanager->mrows,
                                  qrmanager->Q, nullStartIdx_tmp,
                                  memspace->workspace_double,
                                  cholmanager->FMat);
          }
          break;
        }
        if (alwaysPositiveDef) {
          cholmanager->ndims = mNull_tmp;
          cholmanager->info =
              internal::lapack::xpotrf(mNull_tmp, cholmanager->FMat);
        } else {
          cholmanager->ndims = mNull_tmp;
          nVars = 0;
          if (mNull_tmp > 1) {
            smax = std::abs(cholmanager->FMat[0]);
            for (k = 2; k <= mNull_tmp; k++) {
              double s;
              s = std::abs(cholmanager->FMat[(k - 1) * 149]);
              if (s > smax) {
                nVars = k - 1;
                smax = s;
              }
            }
          }
          cholmanager->regTol_ =
              std::fmax(std::abs(cholmanager->FMat[nVars + 148 * nVars]) *
                            2.2204460492503131E-16,
                        0.0);
          if (mNull_tmp > 128) {
            boolean_T exitg1;
            k = 0;
            exitg1 = false;
            while ((!exitg1) && (k < mNull_tmp)) {
              nVars = 149 * k + 1;
              order = mNull_tmp - k;
              if (k + 48 <= mNull_tmp) {
                DynamicRegCholManager::partialColLDL3_(cholmanager, nVars,
                                                       order);
                k += 48;
              } else {
                DynamicRegCholManager::fullColLDL2_(cholmanager, nVars, order);
                exitg1 = true;
              }
            }
          } else {
            DynamicRegCholManager::fullColLDL2_(cholmanager, 1, mNull_tmp);
          }
          if (cholmanager->ConvexCheck) {
            idx = 0;
            int exitg2;
            do {
              exitg2 = 0;
              if (idx <= mNull_tmp - 1) {
                if (cholmanager->FMat[idx + 148 * idx] <= 0.0) {
                  cholmanager->info = -idx - 1;
                  exitg2 = 1;
                } else {
                  idx++;
                }
              } else {
                cholmanager->ConvexCheck = false;
                exitg2 = 1;
              }
            } while (exitg2 == 0);
          }
        }
        if (cholmanager->info != 0) {
          solution->state = -6;
        } else {
          if (qrmanager->mrows != 0) {
            if (0 <= mNull_tmp - 1) {
              std::memset(&memspace->workspace_double[0], 0,
                          mNull_tmp * sizeof(double));
            }
            i = nullStartIdx_tmp + 148 * (mNull_tmp - 1);
            for (idx = nullStartIdx_tmp; idx <= i; idx += 148) {
              smax = 0.0;
              order = idx + nVar_tmp;
              for (k = idx; k <= order; k++) {
                smax += qrmanager->Q[k - 1] * objective->grad[k - idx];
              }
              order = div_nde_s32_floor(idx - nullStartIdx_tmp, 148);
              memspace->workspace_double[order] += -smax;
            }
          }
          if (alwaysPositiveDef) {
            order = cholmanager->ndims;
            if (cholmanager->ndims != 0) {
              for (idx = 0; idx < order; idx++) {
                nVars = idx * 148;
                smax = memspace->workspace_double[idx];
                for (k = 0; k < idx; k++) {
                  smax -= cholmanager->FMat[nVars + k] *
                          memspace->workspace_double[k];
                }
                memspace->workspace_double[idx] =
                    smax / cholmanager->FMat[nVars + idx];
              }
            }
            order = cholmanager->ndims;
            if (cholmanager->ndims != 0) {
              for (idx = order; idx >= 1; idx--) {
                nVars = (idx + (idx - 1) * 148) - 1;
                memspace->workspace_double[idx - 1] /= cholmanager->FMat[nVars];
                for (k = 0; k <= idx - 2; k++) {
                  ix = (idx - k) - 2;
                  memspace->workspace_double[ix] -=
                      memspace->workspace_double[idx - 1] *
                      cholmanager->FMat[(nVars - k) - 1];
                }
              }
            }
          } else {
            order = cholmanager->ndims - 2;
            if (cholmanager->ndims != 0) {
              for (idx = 0; idx <= order + 1; idx++) {
                nVars = idx + idx * 148;
                i = order - idx;
                for (k = 0; k <= i; k++) {
                  ix = (idx + k) + 1;
                  memspace->workspace_double[ix] -=
                      memspace->workspace_double[idx] *
                      cholmanager->FMat[(nVars + k) + 1];
                }
              }
            }
            i = cholmanager->ndims;
            for (idx = 0; idx < i; idx++) {
              memspace->workspace_double[idx] /=
                  cholmanager->FMat[idx + 148 * idx];
            }
            order = cholmanager->ndims;
            if (cholmanager->ndims != 0) {
              for (idx = order; idx >= 1; idx--) {
                nVars = (idx - 1) * 148;
                smax = memspace->workspace_double[idx - 1];
                i = idx + 1;
                for (k = order; k >= i; k--) {
                  smax -= cholmanager->FMat[(nVars + k) - 1] *
                          memspace->workspace_double[k - 1];
                }
                memspace->workspace_double[idx - 1] = smax;
              }
            }
          }
          if (qrmanager->mrows != 0) {
            if (0 <= nVar_tmp) {
              std::memset(&solution->searchDir[0], 0,
                          (nVar_tmp + 1) * sizeof(double));
            }
            ix = 0;
            i = nullStartIdx_tmp + 148 * (mNull_tmp - 1);
            for (idx = nullStartIdx_tmp; idx <= i; idx += 148) {
              order = idx + nVar_tmp;
              for (k = idx; k <= order; k++) {
                nVars = k - idx;
                solution->searchDir[nVars] +=
                    qrmanager->Q[k - 1] * memspace->workspace_double[ix];
              }
              ix++;
            }
          }
        }
      } break;
      }
    }
  }
}

} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (compute_deltax.cpp)
