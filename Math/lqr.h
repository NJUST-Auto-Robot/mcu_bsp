/*
 * @Author: skybase
 * @Date: 2024-12-20 19:40:36
 * @LastEditors: skybase
 * @LastEditTime: 2025-03-08 00:36:31
 * @Description:  ?(???)?? 
 * @FilePath: \luntui_feika\code\lqr.h
 */
#ifndef LQR_H
#define LQR_H

#define Matrix_type float
#define _x_dim 6
#define _u_dim 2

typedef enum
{
    FIXED = 0,
    POLYNOMIAL_FIT,

} LQR_K_UPDATE_MODE;

typedef struct
{

    int x_dim;  //����x�����ά��
    int u_dim;  //u�����ά��

    Matrix_type* mat_X;
    Matrix_type* mat_U;
    Matrix_type* mat_K;

}LQR_struct;

void LQR_Init(LQR_struct *_instance, int x_dim, int u_dim);
Matrix_type *LQR_Calculate(LQR_struct *_instance, Matrix_type *x_val, Matrix_type *x_set_val);

#endif