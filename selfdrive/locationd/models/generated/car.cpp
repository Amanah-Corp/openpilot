#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.10.1                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_4329134677672719662) {
   out_4329134677672719662[0] = delta_x[0] + nom_x[0];
   out_4329134677672719662[1] = delta_x[1] + nom_x[1];
   out_4329134677672719662[2] = delta_x[2] + nom_x[2];
   out_4329134677672719662[3] = delta_x[3] + nom_x[3];
   out_4329134677672719662[4] = delta_x[4] + nom_x[4];
   out_4329134677672719662[5] = delta_x[5] + nom_x[5];
   out_4329134677672719662[6] = delta_x[6] + nom_x[6];
   out_4329134677672719662[7] = delta_x[7] + nom_x[7];
   out_4329134677672719662[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8663601870348907847) {
   out_8663601870348907847[0] = -nom_x[0] + true_x[0];
   out_8663601870348907847[1] = -nom_x[1] + true_x[1];
   out_8663601870348907847[2] = -nom_x[2] + true_x[2];
   out_8663601870348907847[3] = -nom_x[3] + true_x[3];
   out_8663601870348907847[4] = -nom_x[4] + true_x[4];
   out_8663601870348907847[5] = -nom_x[5] + true_x[5];
   out_8663601870348907847[6] = -nom_x[6] + true_x[6];
   out_8663601870348907847[7] = -nom_x[7] + true_x[7];
   out_8663601870348907847[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_666742920972236807) {
   out_666742920972236807[0] = 1.0;
   out_666742920972236807[1] = 0;
   out_666742920972236807[2] = 0;
   out_666742920972236807[3] = 0;
   out_666742920972236807[4] = 0;
   out_666742920972236807[5] = 0;
   out_666742920972236807[6] = 0;
   out_666742920972236807[7] = 0;
   out_666742920972236807[8] = 0;
   out_666742920972236807[9] = 0;
   out_666742920972236807[10] = 1.0;
   out_666742920972236807[11] = 0;
   out_666742920972236807[12] = 0;
   out_666742920972236807[13] = 0;
   out_666742920972236807[14] = 0;
   out_666742920972236807[15] = 0;
   out_666742920972236807[16] = 0;
   out_666742920972236807[17] = 0;
   out_666742920972236807[18] = 0;
   out_666742920972236807[19] = 0;
   out_666742920972236807[20] = 1.0;
   out_666742920972236807[21] = 0;
   out_666742920972236807[22] = 0;
   out_666742920972236807[23] = 0;
   out_666742920972236807[24] = 0;
   out_666742920972236807[25] = 0;
   out_666742920972236807[26] = 0;
   out_666742920972236807[27] = 0;
   out_666742920972236807[28] = 0;
   out_666742920972236807[29] = 0;
   out_666742920972236807[30] = 1.0;
   out_666742920972236807[31] = 0;
   out_666742920972236807[32] = 0;
   out_666742920972236807[33] = 0;
   out_666742920972236807[34] = 0;
   out_666742920972236807[35] = 0;
   out_666742920972236807[36] = 0;
   out_666742920972236807[37] = 0;
   out_666742920972236807[38] = 0;
   out_666742920972236807[39] = 0;
   out_666742920972236807[40] = 1.0;
   out_666742920972236807[41] = 0;
   out_666742920972236807[42] = 0;
   out_666742920972236807[43] = 0;
   out_666742920972236807[44] = 0;
   out_666742920972236807[45] = 0;
   out_666742920972236807[46] = 0;
   out_666742920972236807[47] = 0;
   out_666742920972236807[48] = 0;
   out_666742920972236807[49] = 0;
   out_666742920972236807[50] = 1.0;
   out_666742920972236807[51] = 0;
   out_666742920972236807[52] = 0;
   out_666742920972236807[53] = 0;
   out_666742920972236807[54] = 0;
   out_666742920972236807[55] = 0;
   out_666742920972236807[56] = 0;
   out_666742920972236807[57] = 0;
   out_666742920972236807[58] = 0;
   out_666742920972236807[59] = 0;
   out_666742920972236807[60] = 1.0;
   out_666742920972236807[61] = 0;
   out_666742920972236807[62] = 0;
   out_666742920972236807[63] = 0;
   out_666742920972236807[64] = 0;
   out_666742920972236807[65] = 0;
   out_666742920972236807[66] = 0;
   out_666742920972236807[67] = 0;
   out_666742920972236807[68] = 0;
   out_666742920972236807[69] = 0;
   out_666742920972236807[70] = 1.0;
   out_666742920972236807[71] = 0;
   out_666742920972236807[72] = 0;
   out_666742920972236807[73] = 0;
   out_666742920972236807[74] = 0;
   out_666742920972236807[75] = 0;
   out_666742920972236807[76] = 0;
   out_666742920972236807[77] = 0;
   out_666742920972236807[78] = 0;
   out_666742920972236807[79] = 0;
   out_666742920972236807[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_9041872531305286328) {
   out_9041872531305286328[0] = state[0];
   out_9041872531305286328[1] = state[1];
   out_9041872531305286328[2] = state[2];
   out_9041872531305286328[3] = state[3];
   out_9041872531305286328[4] = state[4];
   out_9041872531305286328[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_9041872531305286328[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_9041872531305286328[7] = state[7];
   out_9041872531305286328[8] = state[8];
}
void F_fun(double *state, double dt, double *out_62538366870240575) {
   out_62538366870240575[0] = 1;
   out_62538366870240575[1] = 0;
   out_62538366870240575[2] = 0;
   out_62538366870240575[3] = 0;
   out_62538366870240575[4] = 0;
   out_62538366870240575[5] = 0;
   out_62538366870240575[6] = 0;
   out_62538366870240575[7] = 0;
   out_62538366870240575[8] = 0;
   out_62538366870240575[9] = 0;
   out_62538366870240575[10] = 1;
   out_62538366870240575[11] = 0;
   out_62538366870240575[12] = 0;
   out_62538366870240575[13] = 0;
   out_62538366870240575[14] = 0;
   out_62538366870240575[15] = 0;
   out_62538366870240575[16] = 0;
   out_62538366870240575[17] = 0;
   out_62538366870240575[18] = 0;
   out_62538366870240575[19] = 0;
   out_62538366870240575[20] = 1;
   out_62538366870240575[21] = 0;
   out_62538366870240575[22] = 0;
   out_62538366870240575[23] = 0;
   out_62538366870240575[24] = 0;
   out_62538366870240575[25] = 0;
   out_62538366870240575[26] = 0;
   out_62538366870240575[27] = 0;
   out_62538366870240575[28] = 0;
   out_62538366870240575[29] = 0;
   out_62538366870240575[30] = 1;
   out_62538366870240575[31] = 0;
   out_62538366870240575[32] = 0;
   out_62538366870240575[33] = 0;
   out_62538366870240575[34] = 0;
   out_62538366870240575[35] = 0;
   out_62538366870240575[36] = 0;
   out_62538366870240575[37] = 0;
   out_62538366870240575[38] = 0;
   out_62538366870240575[39] = 0;
   out_62538366870240575[40] = 1;
   out_62538366870240575[41] = 0;
   out_62538366870240575[42] = 0;
   out_62538366870240575[43] = 0;
   out_62538366870240575[44] = 0;
   out_62538366870240575[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_62538366870240575[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_62538366870240575[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_62538366870240575[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_62538366870240575[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_62538366870240575[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_62538366870240575[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_62538366870240575[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_62538366870240575[53] = -9.8000000000000007*dt;
   out_62538366870240575[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_62538366870240575[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_62538366870240575[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_62538366870240575[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_62538366870240575[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_62538366870240575[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_62538366870240575[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_62538366870240575[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_62538366870240575[62] = 0;
   out_62538366870240575[63] = 0;
   out_62538366870240575[64] = 0;
   out_62538366870240575[65] = 0;
   out_62538366870240575[66] = 0;
   out_62538366870240575[67] = 0;
   out_62538366870240575[68] = 0;
   out_62538366870240575[69] = 0;
   out_62538366870240575[70] = 1;
   out_62538366870240575[71] = 0;
   out_62538366870240575[72] = 0;
   out_62538366870240575[73] = 0;
   out_62538366870240575[74] = 0;
   out_62538366870240575[75] = 0;
   out_62538366870240575[76] = 0;
   out_62538366870240575[77] = 0;
   out_62538366870240575[78] = 0;
   out_62538366870240575[79] = 0;
   out_62538366870240575[80] = 1;
}
void h_25(double *state, double *unused, double *out_6359509751087296679) {
   out_6359509751087296679[0] = state[6];
}
void H_25(double *state, double *unused, double *out_7842149085654755664) {
   out_7842149085654755664[0] = 0;
   out_7842149085654755664[1] = 0;
   out_7842149085654755664[2] = 0;
   out_7842149085654755664[3] = 0;
   out_7842149085654755664[4] = 0;
   out_7842149085654755664[5] = 0;
   out_7842149085654755664[6] = 1;
   out_7842149085654755664[7] = 0;
   out_7842149085654755664[8] = 0;
}
void h_24(double *state, double *unused, double *out_2086835435358409646) {
   out_2086835435358409646[0] = state[4];
   out_2086835435358409646[1] = state[5];
}
void H_24(double *state, double *unused, double *out_5669499486649256098) {
   out_5669499486649256098[0] = 0;
   out_5669499486649256098[1] = 0;
   out_5669499486649256098[2] = 0;
   out_5669499486649256098[3] = 0;
   out_5669499486649256098[4] = 1;
   out_5669499486649256098[5] = 0;
   out_5669499486649256098[6] = 0;
   out_5669499486649256098[7] = 0;
   out_5669499486649256098[8] = 0;
   out_5669499486649256098[9] = 0;
   out_5669499486649256098[10] = 0;
   out_5669499486649256098[11] = 0;
   out_5669499486649256098[12] = 0;
   out_5669499486649256098[13] = 0;
   out_5669499486649256098[14] = 1;
   out_5669499486649256098[15] = 0;
   out_5669499486649256098[16] = 0;
   out_5669499486649256098[17] = 0;
}
void h_30(double *state, double *unused, double *out_2280367725631245205) {
   out_2280367725631245205[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3687904646563179197) {
   out_3687904646563179197[0] = 0;
   out_3687904646563179197[1] = 0;
   out_3687904646563179197[2] = 0;
   out_3687904646563179197[3] = 0;
   out_3687904646563179197[4] = 1;
   out_3687904646563179197[5] = 0;
   out_3687904646563179197[6] = 0;
   out_3687904646563179197[7] = 0;
   out_3687904646563179197[8] = 0;
}
void h_26(double *state, double *unused, double *out_5829116421031607295) {
   out_5829116421031607295[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4100645766780699440) {
   out_4100645766780699440[0] = 0;
   out_4100645766780699440[1] = 0;
   out_4100645766780699440[2] = 0;
   out_4100645766780699440[3] = 0;
   out_4100645766780699440[4] = 0;
   out_4100645766780699440[5] = 0;
   out_4100645766780699440[6] = 0;
   out_4100645766780699440[7] = 1;
   out_4100645766780699440[8] = 0;
}
void h_27(double *state, double *unused, double *out_7085561054961409292) {
   out_7085561054961409292[0] = state[3];
}
void H_27(double *state, double *unused, double *out_5862667958363604108) {
   out_5862667958363604108[0] = 0;
   out_5862667958363604108[1] = 0;
   out_5862667958363604108[2] = 0;
   out_5862667958363604108[3] = 1;
   out_5862667958363604108[4] = 0;
   out_5862667958363604108[5] = 0;
   out_5862667958363604108[6] = 0;
   out_5862667958363604108[7] = 0;
   out_5862667958363604108[8] = 0;
}
void h_29(double *state, double *unused, double *out_3448111526707386942) {
   out_3448111526707386942[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7576030685233155141) {
   out_7576030685233155141[0] = 0;
   out_7576030685233155141[1] = 1;
   out_7576030685233155141[2] = 0;
   out_7576030685233155141[3] = 0;
   out_7576030685233155141[4] = 0;
   out_7576030685233155141[5] = 0;
   out_7576030685233155141[6] = 0;
   out_7576030685233155141[7] = 0;
   out_7576030685233155141[8] = 0;
}
void h_28(double *state, double *unused, double *out_1632275864907283034) {
   out_1632275864907283034[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5788314371406865901) {
   out_5788314371406865901[0] = 1;
   out_5788314371406865901[1] = 0;
   out_5788314371406865901[2] = 0;
   out_5788314371406865901[3] = 0;
   out_5788314371406865901[4] = 0;
   out_5788314371406865901[5] = 0;
   out_5788314371406865901[6] = 0;
   out_5788314371406865901[7] = 0;
   out_5788314371406865901[8] = 0;
}
void h_31(double *state, double *unused, double *out_7810141143716179846) {
   out_7810141143716179846[0] = state[8];
}
void H_31(double *state, double *unused, double *out_7872795047531716092) {
   out_7872795047531716092[0] = 0;
   out_7872795047531716092[1] = 0;
   out_7872795047531716092[2] = 0;
   out_7872795047531716092[3] = 0;
   out_7872795047531716092[4] = 0;
   out_7872795047531716092[5] = 0;
   out_7872795047531716092[6] = 0;
   out_7872795047531716092[7] = 0;
   out_7872795047531716092[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_4329134677672719662) {
  err_fun(nom_x, delta_x, out_4329134677672719662);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8663601870348907847) {
  inv_err_fun(nom_x, true_x, out_8663601870348907847);
}
void car_H_mod_fun(double *state, double *out_666742920972236807) {
  H_mod_fun(state, out_666742920972236807);
}
void car_f_fun(double *state, double dt, double *out_9041872531305286328) {
  f_fun(state,  dt, out_9041872531305286328);
}
void car_F_fun(double *state, double dt, double *out_62538366870240575) {
  F_fun(state,  dt, out_62538366870240575);
}
void car_h_25(double *state, double *unused, double *out_6359509751087296679) {
  h_25(state, unused, out_6359509751087296679);
}
void car_H_25(double *state, double *unused, double *out_7842149085654755664) {
  H_25(state, unused, out_7842149085654755664);
}
void car_h_24(double *state, double *unused, double *out_2086835435358409646) {
  h_24(state, unused, out_2086835435358409646);
}
void car_H_24(double *state, double *unused, double *out_5669499486649256098) {
  H_24(state, unused, out_5669499486649256098);
}
void car_h_30(double *state, double *unused, double *out_2280367725631245205) {
  h_30(state, unused, out_2280367725631245205);
}
void car_H_30(double *state, double *unused, double *out_3687904646563179197) {
  H_30(state, unused, out_3687904646563179197);
}
void car_h_26(double *state, double *unused, double *out_5829116421031607295) {
  h_26(state, unused, out_5829116421031607295);
}
void car_H_26(double *state, double *unused, double *out_4100645766780699440) {
  H_26(state, unused, out_4100645766780699440);
}
void car_h_27(double *state, double *unused, double *out_7085561054961409292) {
  h_27(state, unused, out_7085561054961409292);
}
void car_H_27(double *state, double *unused, double *out_5862667958363604108) {
  H_27(state, unused, out_5862667958363604108);
}
void car_h_29(double *state, double *unused, double *out_3448111526707386942) {
  h_29(state, unused, out_3448111526707386942);
}
void car_H_29(double *state, double *unused, double *out_7576030685233155141) {
  H_29(state, unused, out_7576030685233155141);
}
void car_h_28(double *state, double *unused, double *out_1632275864907283034) {
  h_28(state, unused, out_1632275864907283034);
}
void car_H_28(double *state, double *unused, double *out_5788314371406865901) {
  H_28(state, unused, out_5788314371406865901);
}
void car_h_31(double *state, double *unused, double *out_7810141143716179846) {
  h_31(state, unused, out_7810141143716179846);
}
void car_H_31(double *state, double *unused, double *out_7872795047531716092) {
  H_31(state, unused, out_7872795047531716092);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_init(car);
