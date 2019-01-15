//==================================================================================================
//| �ļ����� | Bsp_DataType.h
//|--------- |--------------------------------------------------------------------------------------
//| �ļ����� | Bspģ������Ӧ����������
//|--------- |--------------------------------------------------------------------------------------
//| ��Ȩ���� | 
//|----------|--------------------------------------------------------------------------------------
//|  �汾    |  ʱ��       |  ����     | ����
//|--------- |-------------|-----------|------------------------------------------------------------
//|  V1.0    | 2019.01.12  |  wjb      | ��ΪTI C2000��DSP ���������� C2000��û��8λ����
//==================================================================================================
#ifndef  __BSP_DATATYPE_H__
#define  __BSP_DATATYPE_H__


#ifdef __cplusplus
extern  "C" {                                  /* See Note #1.                                         */
#endif

#include  <stdint.h>

typedef uint8_t         BOOL;
typedef uint8_t         INT8U;
typedef int8_t          INT8S;
typedef uint16_t        INT16U;                   
typedef int16_t         INT16S;                  
typedef uint32_t        INT32U;                   
typedef int32_t         INT32S; 
typedef uint64_t        INT64U;                   
typedef int64_t         INT64S;  
typedef float           FP32;                     
typedef double          FP64; 


#ifndef FALSE
#define FALSE   0
#endif

#ifndef TRUE
#define TRUE    1
#endif

//��׼�궨��
#ifndef NULL
#define NULL   (void *)0
#endif


#ifdef __cplusplus
}                                              /* End of 'extern'al C lang linkage.                    */
#endif


#ifndef __STATIC_INLINE
#define __STATIC_INLINE static inline
#endif

#ifndef __weak
#define __weak      weak
#endif

#endif                                                          /* End of module include.                               */

