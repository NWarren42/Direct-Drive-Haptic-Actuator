/*
 * STP_CTL.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "STP_CTL".
 *
 * Model version              : 1.16
 * Simulink Coder version : 9.1 (R2019a) 23-Nov-2018
 * C source code generated on : Thu Feb  5 20:44:39 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "STP_CTL.h"
#include "STP_CTL_private.h"
#include "STP_CTL_dt.h"

/* Block signals (default storage) */
B_STP_CTL_T STP_CTL_B;

/* Block states (default storage) */
DW_STP_CTL_T STP_CTL_DW;

/* Real-time model */
RT_MODEL_STP_CTL_T STP_CTL_M_;
RT_MODEL_STP_CTL_T *const STP_CTL_M = &STP_CTL_M_;
real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Model output function */
void STP_CTL_output(void)
{
  /* local block i/o variables */
  real_T rtb_ManualSwitch;

  /* ManualSwitch: '<Root>/Manual Switch' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Constant4'
   */
  if (STP_CTL_P.ManualSwitch_CurrentSetting == 1) {
    rtb_ManualSwitch = STP_CTL_P.Constant_Value;
  } else {
    rtb_ManualSwitch = STP_CTL_P.Constant4_Value;
  }

  /* End of ManualSwitch: '<Root>/Manual Switch' */

  /* S-Function (hil_write_digital_block): '<S1>/HIL Write Digital' */

  /* S-Function Block: STP_CTL/CW8060 Outputs/HIL Write Digital (hil_write_digital_block) */
  {
    t_error result;
    STP_CTL_DW.HILWriteDigital_Buffer = (rtb_ManualSwitch != 0);
    result = hil_write_digital(STP_CTL_DW.HILInitialize_Card,
      &STP_CTL_P.HILWriteDigital_channels, 1, &STP_CTL_DW.HILWriteDigital_Buffer);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
    }
  }

  /* S-Function (hil_write_digital_block): '<S1>/HIL Write Digital1' incorporates:
   *  Constant: '<Root>/Constant1'
   */

  /* S-Function Block: STP_CTL/CW8060 Outputs/HIL Write Digital1 (hil_write_digital_block) */
  {
    t_error result;
    STP_CTL_DW.HILWriteDigital1_Buffer = (STP_CTL_P.Constant1_Value != 0);
    result = hil_write_digital(STP_CTL_DW.HILInitialize_Card,
      &STP_CTL_P.HILWriteDigital1_channels, 1,
      &STP_CTL_DW.HILWriteDigital1_Buffer);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
    }
  }

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  Constant: '<Root>/Constant2'
   *  Constant: '<Root>/Constant3'
   *  Constant: '<Root>/Constant5'
   */
  if ((STP_CTL_P.Constant2_Value != 0.0) && (!(STP_CTL_DW.active != 0.0))) {
    STP_CTL_DW.pulses_target = STP_CTL_P.Constant3_Value / 1.8;
    STP_CTL_DW.pulses_target = rt_roundd_snf(STP_CTL_DW.pulses_target);
    STP_CTL_DW.pulses_sent = 0.0;
    STP_CTL_DW.active = 1.0;
  }

  if (STP_CTL_DW.active != 0.0) {
    STP_CTL_B.PWM = STP_CTL_P.Constant5_Value;
    STP_CTL_DW.pulses_sent += STP_CTL_P.Constant5_Value * 0.001;
    if (STP_CTL_DW.pulses_sent >= STP_CTL_DW.pulses_target) {
      STP_CTL_B.PWM = 0.0;
      STP_CTL_DW.active = 0.0;
    }
  } else {
    STP_CTL_B.PWM = 0.0;
  }

  /* End of MATLAB Function: '<Root>/MATLAB Function' */

  /* S-Function (hil_write_pwm_block): '<S1>/HIL Write PWM' */

  /* S-Function Block: STP_CTL/CW8060 Outputs/HIL Write PWM (hil_write_pwm_block) */
  {
    t_error result;
    result = hil_write_pwm(STP_CTL_DW.HILInitialize_Card,
      &STP_CTL_P.HILWritePWM_channels, 1, &STP_CTL_B.PWM);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
    }
  }

  /* S-Function (hil_read_analog_block): '<Root>/HIL Read Analog' */

  /* S-Function Block: STP_CTL/HIL Read Analog (hil_read_analog_block) */
  {
    t_error result = hil_read_analog(STP_CTL_DW.HILInitialize1_Card,
      STP_CTL_P.HILReadAnalog_channels, 6, &STP_CTL_DW.HILReadAnalog_Buffer[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
    }

    STP_CTL_B.F1 = STP_CTL_DW.HILReadAnalog_Buffer[0];
    STP_CTL_B.T1 = STP_CTL_DW.HILReadAnalog_Buffer[1];
    STP_CTL_B.F2 = STP_CTL_DW.HILReadAnalog_Buffer[2];
    STP_CTL_B.T2 = STP_CTL_DW.HILReadAnalog_Buffer[3];
    STP_CTL_B.F3 = STP_CTL_DW.HILReadAnalog_Buffer[4];
    STP_CTL_B.T3 = STP_CTL_DW.HILReadAnalog_Buffer[5];
  }
}

/* Model update function */
void STP_CTL_update(void)
{
  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++STP_CTL_M->Timing.clockTick0)) {
    ++STP_CTL_M->Timing.clockTickH0;
  }

  STP_CTL_M->Timing.t[0] = STP_CTL_M->Timing.clockTick0 *
    STP_CTL_M->Timing.stepSize0 + STP_CTL_M->Timing.clockTickH0 *
    STP_CTL_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void STP_CTL_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: STP_CTL/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8", "0", &STP_CTL_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
      return;
    }

    is_switching = false;
    if ((STP_CTL_P.HILInitialize_CKPStart && !is_switching) ||
        (STP_CTL_P.HILInitialize_CKPEnter && is_switching)) {
      result = hil_set_clock_mode(STP_CTL_DW.HILInitialize_Card, (t_clock *)
        STP_CTL_P.HILInitialize_CKChannels, 2U, (t_clock_mode *)
        STP_CTL_P.HILInitialize_CKModes);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
        return;
      }
    }

    result = hil_watchdog_clear(STP_CTL_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
      return;
    }

    if ((STP_CTL_P.HILInitialize_AIPStart && !is_switching) ||
        (STP_CTL_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &STP_CTL_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (STP_CTL_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &STP_CTL_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = STP_CTL_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(STP_CTL_DW.HILInitialize_Card,
        STP_CTL_P.HILInitialize_AIChannels, 8U,
        &STP_CTL_DW.HILInitialize_AIMinimums[0],
        &STP_CTL_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
        return;
      }
    }

    if ((STP_CTL_P.HILInitialize_AOPStart && !is_switching) ||
        (STP_CTL_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &STP_CTL_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (STP_CTL_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &STP_CTL_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = STP_CTL_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges(STP_CTL_DW.HILInitialize_Card,
        STP_CTL_P.HILInitialize_AOChannels, 8U,
        &STP_CTL_DW.HILInitialize_AOMinimums[0],
        &STP_CTL_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
        return;
      }
    }

    if ((STP_CTL_P.HILInitialize_AOStart && !is_switching) ||
        (STP_CTL_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &STP_CTL_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = STP_CTL_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(STP_CTL_DW.HILInitialize_Card,
        STP_CTL_P.HILInitialize_AOChannels, 8U,
        &STP_CTL_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
        return;
      }
    }

    if (STP_CTL_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &STP_CTL_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = STP_CTL_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (STP_CTL_DW.HILInitialize_Card, STP_CTL_P.HILInitialize_AOChannels, 8U,
         &STP_CTL_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
        return;
      }
    }

    result = hil_set_digital_directions(STP_CTL_DW.HILInitialize_Card, NULL, 0U,
      STP_CTL_P.HILInitialize_DOChannels, 2U);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
      return;
    }

    if ((STP_CTL_P.HILInitialize_DOStart && !is_switching) ||
        (STP_CTL_P.HILInitialize_DOEnter && is_switching)) {
      STP_CTL_DW.HILInitialize_DOBits[0] = STP_CTL_P.HILInitialize_DOInitial;
      STP_CTL_DW.HILInitialize_DOBits[1] = STP_CTL_P.HILInitialize_DOInitial;
      result = hil_write_digital(STP_CTL_DW.HILInitialize_Card,
        STP_CTL_P.HILInitialize_DOChannels, 2U, (t_boolean *)
        &STP_CTL_DW.HILInitialize_DOBits[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
        return;
      }
    }

    if (STP_CTL_P.HILInitialize_DOReset) {
      STP_CTL_DW.HILInitialize_DOStates[0] = STP_CTL_P.HILInitialize_DOWatchdog;
      STP_CTL_DW.HILInitialize_DOStates[1] = STP_CTL_P.HILInitialize_DOWatchdog;
      result = hil_watchdog_set_digital_expiration_state
        (STP_CTL_DW.HILInitialize_Card, STP_CTL_P.HILInitialize_DOChannels, 2U,
         (const t_digital_state *) &STP_CTL_DW.HILInitialize_DOStates[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
        return;
      }
    }

    if ((STP_CTL_P.HILInitialize_EIPStart && !is_switching) ||
        (STP_CTL_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes = &STP_CTL_DW.HILInitialize_QuadratureModes
          [0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = STP_CTL_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode(STP_CTL_DW.HILInitialize_Card,
        STP_CTL_P.HILInitialize_EIChannels, 8U, (t_encoder_quadrature_mode *)
        &STP_CTL_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_FilterFrequency = &STP_CTL_DW.HILInitialize_FilterFrequency[0];
        for (i1=0; i1 < 8; i1++) {
          dw_FilterFrequency[i1] = STP_CTL_P.HILInitialize_EIFrequency;
        }
      }

      result = hil_set_encoder_filter_frequency(STP_CTL_DW.HILInitialize_Card,
        STP_CTL_P.HILInitialize_EIChannels, 8U,
        &STP_CTL_DW.HILInitialize_FilterFrequency[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
        return;
      }
    }

    if ((STP_CTL_P.HILInitialize_EIStart && !is_switching) ||
        (STP_CTL_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts = &STP_CTL_DW.HILInitialize_InitialEICounts
          [0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = STP_CTL_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(STP_CTL_DW.HILInitialize_Card,
        STP_CTL_P.HILInitialize_EIChannels, 8U,
        &STP_CTL_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
        return;
      }
    }

    if ((STP_CTL_P.HILInitialize_POPStart && !is_switching) ||
        (STP_CTL_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;
      result = hil_set_pwm_mode(STP_CTL_DW.HILInitialize_Card,
        &STP_CTL_P.HILInitialize_POChannels, 1U, (t_pwm_mode *)
        &STP_CTL_P.HILInitialize_POModes);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
        return;
      }

      if (STP_CTL_P.HILInitialize_POModes == PWM_DUTY_CYCLE_MODE ||
          STP_CTL_P.HILInitialize_POModes == PWM_ONE_SHOT_MODE ||
          STP_CTL_P.HILInitialize_POModes == PWM_TIME_MODE ||
          STP_CTL_P.HILInitialize_POModes == PWM_RAW_MODE) {
        STP_CTL_DW.HILInitialize_POSortedChans =
          STP_CTL_P.HILInitialize_POChannels;
        STP_CTL_DW.HILInitialize_POSortedFreqs =
          STP_CTL_P.HILInitialize_POFrequency;
        num_duty_cycle_modes++;
      } else {
        STP_CTL_DW.HILInitialize_POSortedChans =
          STP_CTL_P.HILInitialize_POChannels;
        STP_CTL_DW.HILInitialize_POSortedFreqs =
          STP_CTL_P.HILInitialize_POFrequency;
        num_frequency_modes++;
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(STP_CTL_DW.HILInitialize_Card,
          &STP_CTL_DW.HILInitialize_POSortedChans, num_duty_cycle_modes,
          &STP_CTL_DW.HILInitialize_POSortedFreqs);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(STP_CTL_DW.HILInitialize_Card,
          &STP_CTL_DW.HILInitialize_POSortedChans, num_frequency_modes,
          &STP_CTL_DW.HILInitialize_POSortedFreqs);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
          return;
        }
      }
    }

    if ((STP_CTL_P.HILInitialize_POStart && !is_switching) ||
        (STP_CTL_P.HILInitialize_POEnter && is_switching)) {
      result = hil_write_pwm(STP_CTL_DW.HILInitialize_Card,
        &STP_CTL_P.HILInitialize_POChannels, 1U,
        &STP_CTL_P.HILInitialize_POInitial);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize1' */

  /* S-Function Block: STP_CTL/HIL Initialize1 (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("ni_pci_6034e", "0", &STP_CTL_DW.HILInitialize1_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(STP_CTL_DW.HILInitialize1_Card,
      "terminal_board=e_series", 24);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(STP_CTL_DW.HILInitialize1_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
      return;
    }

    if ((STP_CTL_P.HILInitialize1_AIPStart && !is_switching) ||
        (STP_CTL_P.HILInitialize1_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &STP_CTL_DW.HILInitialize1_AIMinimums[0];
        for (i1=0; i1 < 16; i1++) {
          dw_AIMinimums[i1] = (STP_CTL_P.HILInitialize1_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &STP_CTL_DW.HILInitialize1_AIMaximums[0];
        for (i1=0; i1 < 16; i1++) {
          dw_AIMaximums[i1] = STP_CTL_P.HILInitialize1_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(STP_CTL_DW.HILInitialize1_Card,
        STP_CTL_P.HILInitialize1_AIChannels, 16U,
        &STP_CTL_DW.HILInitialize1_AIMinimums[0],
        &STP_CTL_DW.HILInitialize1_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
        return;
      }
    }
  }

  /* SystemInitialize for MATLAB Function: '<Root>/MATLAB Function' */
  STP_CTL_DW.pulses_target = 0.0;
  STP_CTL_DW.pulses_sent = 0.0;
  STP_CTL_DW.active = 0.0;
}

/* Model terminate function */
void STP_CTL_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: STP_CTL/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_digital_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(STP_CTL_DW.HILInitialize_Card);
    hil_monitor_stop_all(STP_CTL_DW.HILInitialize_Card);
    is_switching = false;
    if ((STP_CTL_P.HILInitialize_AOTerminate && !is_switching) ||
        (STP_CTL_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &STP_CTL_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = STP_CTL_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((STP_CTL_P.HILInitialize_DOTerminate && !is_switching) ||
        (STP_CTL_P.HILInitialize_DOExit && is_switching)) {
      STP_CTL_DW.HILInitialize_DOBits[0] = STP_CTL_P.HILInitialize_DOFinal;
      STP_CTL_DW.HILInitialize_DOBits[1] = STP_CTL_P.HILInitialize_DOFinal;
      num_final_digital_outputs = 2U;
    }

    if ((STP_CTL_P.HILInitialize_POTerminate && !is_switching) ||
        (STP_CTL_P.HILInitialize_POExit && is_switching)) {
      num_final_pwm_outputs = 1U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        || num_final_digital_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(STP_CTL_DW.HILInitialize_Card
                         , STP_CTL_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , &STP_CTL_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , STP_CTL_P.HILInitialize_DOChannels,
                         num_final_digital_outputs
                         , NULL, 0
                         , &STP_CTL_DW.HILInitialize_AOVoltages[0]
                         , &STP_CTL_P.HILInitialize_POFinal
                         , (t_boolean *) &STP_CTL_DW.HILInitialize_DOBits[0]
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(STP_CTL_DW.HILInitialize_Card,
            STP_CTL_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &STP_CTL_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(STP_CTL_DW.HILInitialize_Card,
            &STP_CTL_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &STP_CTL_P.HILInitialize_POFinal);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_digital_outputs > 0) {
          local_result = hil_write_digital(STP_CTL_DW.HILInitialize_Card,
            STP_CTL_P.HILInitialize_DOChannels, num_final_digital_outputs,
            (t_boolean *) &STP_CTL_DW.HILInitialize_DOBits[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(STP_CTL_DW.HILInitialize_Card);
    hil_monitor_delete_all(STP_CTL_DW.HILInitialize_Card);
    hil_close(STP_CTL_DW.HILInitialize_Card);
    STP_CTL_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize1' */

  /* S-Function Block: STP_CTL/HIL Initialize1 (hil_initialize_block) */
  {
    hil_task_stop_all(STP_CTL_DW.HILInitialize1_Card);
    hil_monitor_stop_all(STP_CTL_DW.HILInitialize1_Card);
    hil_task_delete_all(STP_CTL_DW.HILInitialize1_Card);
    hil_monitor_delete_all(STP_CTL_DW.HILInitialize1_Card);
    hil_close(STP_CTL_DW.HILInitialize1_Card);
    STP_CTL_DW.HILInitialize1_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  STP_CTL_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  STP_CTL_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  STP_CTL_initialize();
}

void MdlTerminate(void)
{
  STP_CTL_terminate();
}

/* Registration function */
RT_MODEL_STP_CTL_T *STP_CTL(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)STP_CTL_M, 0,
                sizeof(RT_MODEL_STP_CTL_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = STP_CTL_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    STP_CTL_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    STP_CTL_M->Timing.sampleTimes = (&STP_CTL_M->Timing.sampleTimesArray[0]);
    STP_CTL_M->Timing.offsetTimes = (&STP_CTL_M->Timing.offsetTimesArray[0]);

    /* task periods */
    STP_CTL_M->Timing.sampleTimes[0] = (0.001);

    /* task offsets */
    STP_CTL_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(STP_CTL_M, &STP_CTL_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = STP_CTL_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    STP_CTL_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(STP_CTL_M, -1);
  STP_CTL_M->Timing.stepSize0 = 0.001;

  /* External mode info */
  STP_CTL_M->Sizes.checksums[0] = (2320321783U);
  STP_CTL_M->Sizes.checksums[1] = (4095987136U);
  STP_CTL_M->Sizes.checksums[2] = (1894120713U);
  STP_CTL_M->Sizes.checksums[3] = (624134642U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[4];
    STP_CTL_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(STP_CTL_M->extModeInfo,
      &STP_CTL_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(STP_CTL_M->extModeInfo, STP_CTL_M->Sizes.checksums);
    rteiSetTPtr(STP_CTL_M->extModeInfo, rtmGetTPtr(STP_CTL_M));
  }

  STP_CTL_M->solverInfoPtr = (&STP_CTL_M->solverInfo);
  STP_CTL_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&STP_CTL_M->solverInfo, 0.001);
  rtsiSetSolverMode(&STP_CTL_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  STP_CTL_M->blockIO = ((void *) &STP_CTL_B);
  (void) memset(((void *) &STP_CTL_B), 0,
                sizeof(B_STP_CTL_T));

  /* parameters */
  STP_CTL_M->defaultParam = ((real_T *)&STP_CTL_P);

  /* states (dwork) */
  STP_CTL_M->dwork = ((void *) &STP_CTL_DW);
  (void) memset((void *)&STP_CTL_DW, 0,
                sizeof(DW_STP_CTL_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    STP_CTL_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  STP_CTL_M->Sizes.numContStates = (0);/* Number of continuous states */
  STP_CTL_M->Sizes.numY = (0);         /* Number of model outputs */
  STP_CTL_M->Sizes.numU = (0);         /* Number of model inputs */
  STP_CTL_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  STP_CTL_M->Sizes.numSampTimes = (1); /* Number of sample times */
  STP_CTL_M->Sizes.numBlocks = (19);   /* Number of blocks */
  STP_CTL_M->Sizes.numBlockIO = (7);   /* Number of block outputs */
  STP_CTL_M->Sizes.numBlockPrms = (168);/* Sum of parameter "widths" */
  return STP_CTL_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
