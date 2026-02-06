/*
 * STP_CTL_dt.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "STP_CTL".
 *
 * Model version              : 1.22
 * Simulink Coder version : 9.1 (R2019a) 23-Nov-2018
 * C source code generated on : Thu Feb  5 21:22:36 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(t_boolean),
  sizeof(t_card)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "t_boolean",
  "t_card"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&STP_CTL_B.F1), 0, 0, 7 }
  ,

  { (char_T *)(&STP_CTL_DW.HILInitialize_AIMinimums[0]), 0, 0, 92 },

  { (char_T *)(&STP_CTL_DW.HILInitialize_Card), 15, 0, 2 },

  { (char_T *)(&STP_CTL_DW.HILWriteDigital_PWORK), 11, 0, 6 },

  { (char_T *)(&STP_CTL_DW.HILInitialize_DOStates[0]), 6, 0, 21 },

  { (char_T *)(&STP_CTL_DW.HILInitialize_POSortedChans), 7, 0, 1 },

  { (char_T *)(&STP_CTL_DW.HILInitialize_DOBits[0]), 8, 0, 2 },

  { (char_T *)(&STP_CTL_DW.HILWriteDigital1_Buffer), 14, 0, 1 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  8U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&STP_CTL_P.HILWriteDigital_channels), 7, 0, 9 },

  { (char_T *)(&STP_CTL_P.Constant6_Value), 0, 0, 32 },

  { (char_T *)(&STP_CTL_P.HILInitialize_CKChannels[0]), 6, 0, 9 },

  { (char_T *)(&STP_CTL_P.HILInitialize_AIChannels[0]), 7, 0, 45 },

  { (char_T *)(&STP_CTL_P.HILInitialize_Active), 8, 0, 74 },

  { (char_T *)(&STP_CTL_P.ManualSwitch_CurrentSetting), 3, 0, 2 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  6U,
  rtPTransitions
};

/* [EOF] STP_CTL_dt.h */
