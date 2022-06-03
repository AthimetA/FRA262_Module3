/*
 * Kalman.c
 *
 *  Created on: Jun 2, 2022
 *      Author: mobil
 */
#include "main.h"
#include "Kalman.h"
#include "arm_math.h"

<<<<<<< HEAD
void KalmanMatrixInit(KalmanFilterVar *KalmanVar)
{
	  arm_mat_init_f32(&(KalmanVar ->MatA), 3, 3, KalmanVar ->MatA_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatB), 3, 1, KalmanVar ->MatB_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatC), 1, 3, KalmanVar ->MatC_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatD), 1, 1, KalmanVar ->MatD_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatQ), 3, 3, KalmanVar ->MatQ_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatR), 1, 1, KalmanVar ->MatR_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatG), 3, 3, KalmanVar ->MatG_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatState), 3, 1, KalmanVar ->MatState_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatStateLast), 3, 1, KalmanVar ->MatStateLast_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatPredict), 3, 3, KalmanVar ->MatPredict_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatPredictLast), 3, 3, KalmanVar ->MatPredictLast_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatY), 1, 1, KalmanVar ->MatY_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatZ), 1, 1, KalmanVar ->MatZ_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatS), 1, 1, KalmanVar ->MatS_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatK), 3, 1, KalmanVar ->MatK_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatI), 3, 3, KalmanVar ->MatI_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatAt), 3, 3, KalmanVar ->MatAt_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatGt), 3, 3, KalmanVar ->MatGt_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatCt), 3, 1, KalmanVar ->MatCt_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatGQGt), 3, 3, KalmanVar ->MatGQGt_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatSinv), 1, 1, KalmanVar ->MatSinv_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatCPk), 1, 3, KalmanVar ->MatCPk_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatAPk), 3, 3, KalmanVar ->MatAPk_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatAPkAt), 3, 3, KalmanVar ->MatAPkAt_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatCXk), 1, 1, KalmanVar ->MatCXk_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatCPkCt), 1, 1, KalmanVar ->MatCPkCt_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatPkCt), 3, 1, KalmanVar ->MatPkCt_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatKYk), 3, 1,KalmanVar ->MatKYk_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatKC), 3, 3, KalmanVar ->MatKC_Data);
	  arm_mat_init_f32(&(KalmanVar ->MatI_KC), 3, 3, KalmanVar ->MatI_KC_Data);
	  // Get Transpose
	  arm_mat_trans_f32(&(KalmanVar ->MatA), &(KalmanVar ->MatAt));
	  arm_mat_trans_f32(&(KalmanVar ->MatG), &(KalmanVar ->MatGt));
	  arm_mat_trans_f32(&(KalmanVar ->MatC), &(KalmanVar ->MatCt));
	  // Get Buffer
	  arm_mat_mult_f32(&(KalmanVar ->MatG), &(KalmanVar ->MatQ), &(KalmanVar ->MatGQGt));
	  arm_mat_mult_f32(&(KalmanVar ->MatGQGt), &(KalmanVar ->MatGt), &(KalmanVar ->MatGQGt));
}

void KalmanFilterFunction(KalmanFilterVar *KalmanVar,float32_t PositionDeg)
{
	// 1.Prediction
	// Predicted State Estimate
	KalmanVar ->Kalmanstatus = arm_mat_mult_f32(&(KalmanVar ->MatA), &(KalmanVar ->MatStateLast), &(KalmanVar ->MatState)); // A*Xk-1 ,No B*u
	// Predicted error covariance
	KalmanVar ->Kalmanstatus = arm_mat_mult_f32(&(KalmanVar ->MatA), &(KalmanVar ->MatPredictLast), &(KalmanVar ->MatAPk)); // A*Pk-1
	KalmanVar ->Kalmanstatus = arm_mat_mult_f32(&(KalmanVar ->MatAPk), &(KalmanVar ->MatAt), &(KalmanVar ->MatAPkAt)); // A*Pk-1*At
	KalmanVar ->Kalmanstatus = arm_mat_add_f32(&(KalmanVar ->MatAPkAt), &(KalmanVar ->MatGQGt), &(KalmanVar ->MatPredict)); // A*Pk-1*At + GQGt
	// 2.Correction
	// Innovation residual
	KalmanVar -> MatZ_Data[0] = PositionDeg; // Sensor Input
	KalmanVar ->Kalmanstatus = arm_mat_mult_f32(&(KalmanVar ->MatC), &(KalmanVar ->MatState), &(KalmanVar ->MatCXk)); // C*Xk
	KalmanVar ->Kalmanstatus = arm_mat_sub_f32(&(KalmanVar ->MatZ), &(KalmanVar ->MatCXk), &(KalmanVar ->MatY)); // Zk - C*Xk
	// Innovation covariance
	KalmanVar ->Kalmanstatus = arm_mat_mult_f32(&(KalmanVar ->MatC), &(KalmanVar ->MatPredict), &(KalmanVar ->MatCPk)); // C*Pk
	KalmanVar ->Kalmanstatus = arm_mat_mult_f32(&(KalmanVar ->MatCPk), &(KalmanVar ->MatCt), &(KalmanVar ->MatCPkCt)); // C*Pk*Ct
	KalmanVar ->Kalmanstatus = arm_mat_add_f32(&(KalmanVar ->MatCPkCt), &(KalmanVar ->MatR), &(KalmanVar ->MatS)); // C*Pk*Ct + R
	KalmanVar ->Kalmanstatus = arm_mat_inverse_f32(&(KalmanVar ->MatS), &(KalmanVar ->MatSinv)); // S inverse
	// Optimal Kalman gain
	KalmanVar ->Kalmanstatus = arm_mat_mult_f32(&(KalmanVar ->MatPredict), &(KalmanVar ->MatCt), &(KalmanVar ->MatPkCt)); // Pk*Ct
	KalmanVar ->Kalmanstatus = arm_mat_mult_f32(&(KalmanVar ->MatPkCt), &(KalmanVar ->MatSinv), &(KalmanVar ->MatK)); // Pk*Ct*Sinv
	// Corrected state estimate
	KalmanVar ->Kalmanstatus = arm_mat_mult_f32(&(KalmanVar ->MatK), &(KalmanVar ->MatY), &(KalmanVar ->MatKYk)); // K*Yk
	KalmanVar ->Kalmanstatus = arm_mat_add_f32(&(KalmanVar ->MatKYk), &(KalmanVar ->MatState), &(KalmanVar ->MatStateLast)); // Xk+K*Yk
	// Corrected estimate covariance
	KalmanVar ->Kalmanstatus = arm_mat_mult_f32(&(KalmanVar ->MatK), &(KalmanVar ->MatC), &(KalmanVar ->MatKC)); //K*C
	KalmanVar ->Kalmanstatus = arm_mat_sub_f32(&(KalmanVar ->MatI), &(KalmanVar ->MatKC), &(KalmanVar ->MatI_KC)); // I-K*C
	KalmanVar ->Kalmanstatus = arm_mat_mult_f32(&(KalmanVar ->MatI_KC), &(KalmanVar ->MatPredict), &(KalmanVar ->MatPredictLast)); // (I-K*C)*Pk
}
=======
>>>>>>> parent of 06c0c4d (Update แยกไฟล์ Function)
