//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// maxConstraintViolation.cpp
//
// Code generation for function 'maxConstraintViolation'
//

// Include files
#include "maxConstraintViolation.h"
#include "SolveLP_internal_types.h"
#include "SolveLP_rtwutil.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
namespace WorkingSet {
double b_maxConstraintViolation(c_struct_T *obj, const double x[75])
{
  double v;
  int iac;
  int idxLB;
  int mFixed;
  int mLB;
  int mUB;
  mLB = obj->sizes[3];
  mUB = obj->sizes[4];
  mFixed = obj->sizes[0];
  switch (obj->probType) {
  case 2: {
    double c;
    int ia;
    v = 0.0;
    for (idxLB = 0; idxLB < 48; idxLB++) {
      obj->maxConstrWorkspace[idxLB] = obj->bineq[idxLB];
      obj->maxConstrWorkspace[idxLB] = -obj->maxConstrWorkspace[idxLB];
    }
    for (iac = 0; iac <= 3525; iac += 75) {
      c = 0.0;
      idxLB = iac + 24;
      for (ia = iac + 1; ia <= idxLB; ia++) {
        c += obj->Aineq[ia - 1] * x[(ia - iac) - 1];
      }
      idxLB = div_nde_s32_floor(iac, 75);
      obj->maxConstrWorkspace[idxLB] += c;
    }
    for (iac = 0; iac < 48; iac++) {
      obj->maxConstrWorkspace[iac] -= x[iac + 24];
      v = std::fmax(v, obj->maxConstrWorkspace[iac]);
    }
    obj->maxConstrWorkspace[0] = obj->beq;
    obj->maxConstrWorkspace[0] = -obj->maxConstrWorkspace[0];
    c = 0.0;
    for (ia = 0; ia < 24; ia++) {
      c += obj->Aeq[ia] * x[ia];
    }
    obj->maxConstrWorkspace[0] += c;
    obj->maxConstrWorkspace[0] = (obj->maxConstrWorkspace[0] - x[72]) + x[73];
    v = std::fmax(v, std::abs(obj->maxConstrWorkspace[0]));
  } break;
  default: {
    double c;
    int ia;
    v = 0.0;
    for (idxLB = 0; idxLB < 48; idxLB++) {
      obj->maxConstrWorkspace[idxLB] = obj->bineq[idxLB];
      obj->maxConstrWorkspace[idxLB] = -obj->maxConstrWorkspace[idxLB];
    }
    for (iac = 0; iac <= 3525; iac += 75) {
      c = 0.0;
      idxLB = iac + obj->nVar;
      for (ia = iac + 1; ia <= idxLB; ia++) {
        c += obj->Aineq[ia - 1] * x[(ia - iac) - 1];
      }
      idxLB = div_nde_s32_floor(iac, 75);
      obj->maxConstrWorkspace[idxLB] += c;
    }
    for (iac = 0; iac < 48; iac++) {
      v = std::fmax(v, obj->maxConstrWorkspace[iac]);
    }
    obj->maxConstrWorkspace[0] = obj->beq;
    obj->maxConstrWorkspace[0] = -obj->maxConstrWorkspace[0];
    c = 0.0;
    idxLB = obj->nVar;
    for (ia = 1; ia <= idxLB; ia++) {
      c += obj->Aeq[ia - 1] * x[ia - 1];
    }
    obj->maxConstrWorkspace[0] += c;
    v = std::fmax(v, std::abs(obj->maxConstrWorkspace[0]));
  } break;
  }
  if (obj->sizes[3] > 0) {
    for (iac = 0; iac < mLB; iac++) {
      idxLB = obj->indexLB[iac] - 1;
      v = std::fmax(v, -x[idxLB] - obj->lb[idxLB]);
    }
  }
  if (obj->sizes[4] > 0) {
    for (iac = 0; iac < mUB; iac++) {
      idxLB = obj->indexUB[iac] - 1;
      v = std::fmax(v, x[idxLB] - obj->ub[idxLB]);
    }
  }
  if (obj->sizes[0] > 0) {
    for (iac = 0; iac < mFixed; iac++) {
      v = std::fmax(v, std::abs(x[obj->indexFixed[iac] - 1] -
                                obj->ub[obj->indexFixed[iac] - 1]));
    }
  }
  return v;
}

double maxConstraintViolation(c_struct_T *obj, const double x[11100])
{
  double v;
  int iac;
  int idxLB;
  int mFixed;
  int mLB;
  int mUB;
  mLB = obj->sizes[3];
  mUB = obj->sizes[4];
  mFixed = obj->sizes[0];
  switch (obj->probType) {
  case 2: {
    double c;
    int ia;
    v = 0.0;
    for (idxLB = 0; idxLB < 48; idxLB++) {
      obj->maxConstrWorkspace[idxLB] = obj->bineq[idxLB];
      obj->maxConstrWorkspace[idxLB] = -obj->maxConstrWorkspace[idxLB];
    }
    for (iac = 0; iac <= 3525; iac += 75) {
      c = 0.0;
      idxLB = iac + 24;
      for (ia = iac + 1; ia <= idxLB; ia++) {
        c += obj->Aineq[ia - 1] * x[(ia - iac) + 147];
      }
      idxLB = div_nde_s32_floor(iac, 75);
      obj->maxConstrWorkspace[idxLB] += c;
    }
    for (iac = 0; iac < 48; iac++) {
      obj->maxConstrWorkspace[iac] -= x[iac + 172];
      v = std::fmax(v, obj->maxConstrWorkspace[iac]);
    }
    obj->maxConstrWorkspace[0] = obj->beq;
    obj->maxConstrWorkspace[0] = -obj->maxConstrWorkspace[0];
    c = 0.0;
    for (ia = 0; ia < 24; ia++) {
      c += obj->Aeq[ia] * x[ia + 148];
    }
    obj->maxConstrWorkspace[0] += c;
    obj->maxConstrWorkspace[0] = (obj->maxConstrWorkspace[0] - x[220]) + x[221];
    v = std::fmax(v, std::abs(obj->maxConstrWorkspace[0]));
  } break;
  default: {
    double c;
    int ia;
    v = 0.0;
    for (idxLB = 0; idxLB < 48; idxLB++) {
      obj->maxConstrWorkspace[idxLB] = obj->bineq[idxLB];
      obj->maxConstrWorkspace[idxLB] = -obj->maxConstrWorkspace[idxLB];
    }
    for (iac = 0; iac <= 3525; iac += 75) {
      c = 0.0;
      idxLB = iac + obj->nVar;
      for (ia = iac + 1; ia <= idxLB; ia++) {
        c += obj->Aineq[ia - 1] * x[(ia - iac) + 147];
      }
      idxLB = div_nde_s32_floor(iac, 75);
      obj->maxConstrWorkspace[idxLB] += c;
    }
    for (iac = 0; iac < 48; iac++) {
      v = std::fmax(v, obj->maxConstrWorkspace[iac]);
    }
    obj->maxConstrWorkspace[0] = obj->beq;
    obj->maxConstrWorkspace[0] = -obj->maxConstrWorkspace[0];
    c = 0.0;
    idxLB = obj->nVar;
    for (ia = 1; ia <= idxLB; ia++) {
      c += obj->Aeq[ia - 1] * x[ia + 147];
    }
    obj->maxConstrWorkspace[0] += c;
    v = std::fmax(v, std::abs(obj->maxConstrWorkspace[0]));
  } break;
  }
  if (obj->sizes[3] > 0) {
    for (iac = 0; iac < mLB; iac++) {
      idxLB = obj->indexLB[iac];
      v = std::fmax(v, -x[idxLB + 147] - obj->lb[idxLB - 1]);
    }
  }
  if (obj->sizes[4] > 0) {
    for (iac = 0; iac < mUB; iac++) {
      idxLB = obj->indexUB[iac];
      v = std::fmax(v, x[idxLB + 147] - obj->ub[idxLB - 1]);
    }
  }
  if (obj->sizes[0] > 0) {
    for (iac = 0; iac < mFixed; iac++) {
      v = std::fmax(v, std::abs(x[obj->indexFixed[iac] + 147] -
                                obj->ub[obj->indexFixed[iac] - 1]));
    }
  }
  return v;
}

} // namespace WorkingSet
} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (maxConstraintViolation.cpp)
