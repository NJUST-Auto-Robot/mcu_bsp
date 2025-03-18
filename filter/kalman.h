#ifndef __KALMAN_H_
#define __KALMAN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// *����ʹ�õ�һ�׿������˲�
typedef struct
{
    float estimate;          // ����ֵ
    float estimate_error;    // �������
    float measurement_error; // �������
    float process_noise;     // ��������
} KalmanFilter_t;

void KalmanFilter_Init(KalmanFilter_t *kf, float initial_estimate, float initial_estimate_error, float measurement_error, float process_noise);
float KalmanFilter_Update(KalmanFilter_t *kf, float measurement);

// *��չ�������˲�(δ��֤)
typedef struct
{
    int state_dim; // ״̬����ά��
    int obs_dim;   // �۲����ά��
    float *x;      // ״̬����ֵ���� [state_dim]
    float *P;      // �������Э������� [state_dim * state_dim]
    float *Q;      // ��������Э������� [state_dim * state_dim]
    float *R;      // �۲�����Э������� [obs_dim * obs_dim]
    float *F;      // ״̬ת�ƾ��� [state_dim * state_dim]
    float *H;      // �۲���� [obs_dim * state_dim]
} KalmanFilter_Pro_t;

void KalmanFilter_Pro_Update(KalmanFilter_Pro_t *kf, float *z);
KalmanFilter_Pro_t *KalmanFilter_Pro_Init(int state_dim, int obs_dim);

#endif
