/*
 * STP_CTL.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "STP_CTL".
 *
 * Model version              : 1.1
 * Simulink Coder version : 9.1 (R2019a) 23-Nov-2018
 * C source code generated on : Wed Nov 19 18:23:30 2025
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
static void rate_monotonic_scheduler(void);
time_T rt_SimUpdateDiscreteEvents(
  int_T rtmNumSampTimes, void *rtmTimingData, int_T *rtmSampleHitPtr, int_T
  *rtmPerTaskSampleHits )
{
  rtmSampleHitPtr[1] = rtmStepTask(STP_CTL_M, 1);
  UNUSED_PARAMETER(rtmNumSampTimes);
  UNUSED_PARAMETER(rtmTimingData);
  UNUSED_PARAMETER(rtmPerTaskSampleHits);
  return(-1);
}

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (STP_CTL_M->Timing.TaskCounters.TID[1])++;
  if ((STP_CTL_M->Timing.TaskCounters.TID[1]) > 4) {/* Sample time: [0.01s, 0.0s] */
    STP_CTL_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/* Model output function for TID0 */
void STP_CTL_output0(void)             /* Sample time: [0.002s, 0.0s] */
{
  {                                    /* Sample time: [0.002s, 0.0s] */
    rate_monotonic_scheduler();
  }
}

/* Model update function for TID0 */
void STP_CTL_update0(void)             /* Sample time: [0.002s, 0.0s] */
{
  /* Update absolute time */
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

/* Model output function for TID1 */
void STP_CTL_output1(void)             /* Sample time: [0.01s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_SmoothSignalGenerator;

  /* S-Function (hil_read_analog_block): '<Root>/HIL Read Analog' */

  /* S-Function Block: STP_CTL/HIL Read Analog (hil_read_analog_block) */
  {
    t_error result = hil_read_analog(STP_CTL_DW.HILInitialize_Card,
      &STP_CTL_P.HILReadAnalog_channels, 1, &STP_CTL_DW.HILReadAnalog_Buffer);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
    }

    STP_CTL_B.HILReadAnalog = STP_CTL_DW.HILReadAnalog_Buffer;
  }

  /* S-Function (smooth_signal_generator_block): '<Root>/Smooth Signal Generator' */
  /* S-Function Block: STP_CTL/Smooth Signal Generator (smooth_signal_generator_block) */
  {
    real_T w = TWO_PI * STP_CTL_P.SmoothSignalGenerator_Frequency;
    boolean_T params_changed = (STP_CTL_P.SmoothSignalGenerator_Amplitude !=
      STP_CTL_DW.SmoothSignalGenerator_RWORK.Amp || w !=
      STP_CTL_DW.SmoothSignalGenerator_RWORK.W);

    /*
       Discrete-time:

       y_sin = sin(w*(t + dt)) = sin(w*t)*cos(w*dt) + cos(w*t)*sin(w*dt)
       y_cos = cos(w*(t + dt)) = cos(w*t)*cos(w*dt) - sin(w*t)*sin(w*dt)

       Since dt is fixed and known (the sampling period), we can compute the
       output at the next time step, t + dt, from the previous time step, t,
       simply by applying the formulae above where sin(w*dt) and cos(w*dt) are constant.

       Now, suppose the amplitude or frequency is changed. Then when the current
       value of the output is less than the new amplitude, we need to solve the
       equation:
       1. A1 * y_sin = A2 * sin(x)
       whence:
       x  = asin(A1*y_sin/A2)
       We can then compute a new value of sin(x) and cos(x).
     */
    real_T y_sin = STP_CTL_DW.SmoothSignalGenerator_RWORK.Sin_w_t;
    real_T y_cos = STP_CTL_DW.SmoothSignalGenerator_RWORK.Cos_w_t;

    /* Produce the output(s) */
    rtb_SmoothSignalGenerator = STP_CTL_DW.SmoothSignalGenerator_RWORK.Amp *
      y_sin;

    /* Compute the new sin and cos values */
    STP_CTL_DW.SmoothSignalGenerator_RWORK.Sin_w_t = y_sin *
      STP_CTL_DW.SmoothSignalGenerator_RWORK.Cos_w_dt + y_cos *
      STP_CTL_DW.SmoothSignalGenerator_RWORK.Sin_w_dt;
    STP_CTL_DW.SmoothSignalGenerator_RWORK.Cos_w_t = y_cos *
      STP_CTL_DW.SmoothSignalGenerator_RWORK.Cos_w_dt - y_sin *
      STP_CTL_DW.SmoothSignalGenerator_RWORK.Sin_w_dt;

    /*
       If the amplitude or frequency parameter changes, then adjust the
       sine wave parameters such that the sine wave output is continuous.
     */
    if (params_changed) {
      real_T x;

      /*
         Only adjust the amplitude once the current amplitude crosses zero. Otherwise
         we get strange behaviour when continuously modifying the input amplitude and
         frequency using input signals.
       */
      if (y_sin == 0 || STP_CTL_DW.SmoothSignalGenerator_RWORK.Sin_w_t == 0 ||
          (y_sin < 0) != (STP_CTL_DW.SmoothSignalGenerator_RWORK.Sin_w_t < 0)) {
        if (fabs(STP_CTL_DW.SmoothSignalGenerator_RWORK.Amp *
                 STP_CTL_DW.SmoothSignalGenerator_RWORK.Sin_w_t) <
            STP_CTL_P.SmoothSignalGenerator_Amplitude) {
          x = asin(STP_CTL_DW.SmoothSignalGenerator_RWORK.Amp *
                   STP_CTL_DW.SmoothSignalGenerator_RWORK.Sin_w_t /
                   STP_CTL_P.SmoothSignalGenerator_Amplitude);
          STP_CTL_DW.SmoothSignalGenerator_RWORK.Sin_w_dt = sin(w * 0.01);
          STP_CTL_DW.SmoothSignalGenerator_RWORK.Cos_w_dt = cos(w * 0.01);
          STP_CTL_DW.SmoothSignalGenerator_RWORK.Sin_w_t = sin(x);

          /*
             There are always two solutions for the phase. Choose the solution
             that matches the slope as well as the amplitude.
           */
          if ((cos(x) < 0) != (STP_CTL_DW.SmoothSignalGenerator_RWORK.Cos_w_t <
                               0)) {
            STP_CTL_DW.SmoothSignalGenerator_RWORK.Cos_w_t = -cos(x);
          } else {
            STP_CTL_DW.SmoothSignalGenerator_RWORK.Cos_w_t = cos(x);
          }
        } else {
          /* really low amplitudes where sawtooth wave goes further in one time step after crossing zero than the new amplitude */
          x = w * 0.01;
          STP_CTL_DW.SmoothSignalGenerator_RWORK.Sin_w_t = 0;

          /* Make sure cosine output is also continuous */
          if (STP_CTL_DW.SmoothSignalGenerator_RWORK.Cos_w_t < 0) {
            STP_CTL_DW.SmoothSignalGenerator_RWORK.Cos_w_t = -1;
          } else {
            STP_CTL_DW.SmoothSignalGenerator_RWORK.Cos_w_t = +1;
          }

          STP_CTL_DW.SmoothSignalGenerator_RWORK.Sin_w_dt = sin(x);
          STP_CTL_DW.SmoothSignalGenerator_RWORK.Cos_w_dt = cos(x);
        }

        STP_CTL_DW.SmoothSignalGenerator_RWORK.Amp =
          STP_CTL_P.SmoothSignalGenerator_Amplitude;
        STP_CTL_DW.SmoothSignalGenerator_RWORK.W = w;
      }
    }
  }

  /* S-Function (hil_write_analog_block): '<Root>/HIL Write Analog' */

  /* S-Function Block: STP_CTL/HIL Write Analog (hil_write_analog_block) */
  {
    t_error result;
    result = hil_write_analog(STP_CTL_DW.HILInitialize_Card,
      &STP_CTL_P.HILWriteAnalog_channels, 1, &rtb_SmoothSignalGenerator);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
    }
  }
}

/* Model update function for TID1 */
void STP_CTL_update1(void)             /* Sample time: [0.01s, 0.0s] */
{
  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++STP_CTL_M->Timing.clockTick1)) {
    ++STP_CTL_M->Timing.clockTickH1;
  }

  STP_CTL_M->Timing.t[1] = STP_CTL_M->Timing.clockTick1 *
    STP_CTL_M->Timing.stepSize1 + STP_CTL_M->Timing.clockTickH1 *
    STP_CTL_M->Timing.stepSize1 * 4294967296.0;
}

/* Model output wrapper function for compatibility with a static main program */
void STP_CTL_output(int_T tid)
{
  switch (tid) {
   case 0 :
    STP_CTL_output0();
    break;

   case 1 :
    STP_CTL_output1();
    break;

   default :
    break;
  }
}

/* Model update wrapper function for compatibility with a static main program */
void STP_CTL_update(int_T tid)
{
  switch (tid) {
   case 0 :
    STP_CTL_update0();
    break;

   case 1 :
    STP_CTL_update1();
    break;

   default :
    break;
  }
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
  }

  /* Start for S-Function (smooth_signal_generator_block): '<Root>/Smooth Signal Generator' */

  /* S-Function Block: STP_CTL/Smooth Signal Generator (smooth_signal_generator_block) */
  {
    real_T T = 1.0 / STP_CTL_P.SmoothSignalGenerator_Frequency;
    STP_CTL_DW.SmoothSignalGenerator_RWORK.Amp =
      STP_CTL_P.SmoothSignalGenerator_Amplitude;
    STP_CTL_DW.SmoothSignalGenerator_RWORK.W = TWO_PI *
      STP_CTL_P.SmoothSignalGenerator_Frequency;
    STP_CTL_DW.SmoothSignalGenerator_RWORK.Sin_w_dt = sin
      (STP_CTL_DW.SmoothSignalGenerator_RWORK.W * 0.01);
    STP_CTL_DW.SmoothSignalGenerator_RWORK.Cos_w_dt = cos
      (STP_CTL_DW.SmoothSignalGenerator_RWORK.W * 0.01);
    STP_CTL_DW.SmoothSignalGenerator_RWORK.Sin_w_t = sin
      (STP_CTL_P.SmoothSignalGenerator_InitialPh);
    STP_CTL_DW.SmoothSignalGenerator_RWORK.Cos_w_t = cos
      (STP_CTL_P.SmoothSignalGenerator_InitialPh);
  }
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

    if (num_final_analog_outputs > 0) {
      result = hil_write_analog(STP_CTL_DW.HILInitialize_Card,
        STP_CTL_P.HILInitialize_AOChannels, num_final_analog_outputs,
        &STP_CTL_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(STP_CTL_M, _rt_error_message);
      }
    }

    hil_task_delete_all(STP_CTL_DW.HILInitialize_Card);
    hil_monitor_delete_all(STP_CTL_DW.HILInitialize_Card);
    hil_close(STP_CTL_DW.HILInitialize_Card);
    STP_CTL_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  STP_CTL_output(tid);
}

void MdlUpdate(int_T tid)
{
  STP_CTL_update(tid);
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
    mdlTsMap[1] = 1;
    STP_CTL_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    STP_CTL_M->Timing.sampleTimes = (&STP_CTL_M->Timing.sampleTimesArray[0]);
    STP_CTL_M->Timing.offsetTimes = (&STP_CTL_M->Timing.offsetTimesArray[0]);

    /* task periods */
    STP_CTL_M->Timing.sampleTimes[0] = (0.002);
    STP_CTL_M->Timing.sampleTimes[1] = (0.01);

    /* task offsets */
    STP_CTL_M->Timing.offsetTimes[0] = (0.0);
    STP_CTL_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(STP_CTL_M, &STP_CTL_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = STP_CTL_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits = STP_CTL_M->Timing.perTaskSampleHitsArray;
    STP_CTL_M->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    STP_CTL_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(STP_CTL_M, -1);
  STP_CTL_M->Timing.stepSize0 = 0.002;
  STP_CTL_M->Timing.stepSize1 = 0.01;

  /* External mode info */
  STP_CTL_M->Sizes.checksums[0] = (1050869013U);
  STP_CTL_M->Sizes.checksums[1] = (3845686984U);
  STP_CTL_M->Sizes.checksums[2] = (3795075303U);
  STP_CTL_M->Sizes.checksums[3] = (4193305289U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    STP_CTL_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(STP_CTL_M->extModeInfo,
      &STP_CTL_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(STP_CTL_M->extModeInfo, STP_CTL_M->Sizes.checksums);
    rteiSetTPtr(STP_CTL_M->extModeInfo, rtmGetTPtr(STP_CTL_M));
  }

  STP_CTL_M->solverInfoPtr = (&STP_CTL_M->solverInfo);
  STP_CTL_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&STP_CTL_M->solverInfo, 0.002);
  rtsiSetSolverMode(&STP_CTL_M->solverInfo, SOLVER_MODE_MULTITASKING);

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
    dtInfo.numDataTypes = 15;
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
  STP_CTL_M->Sizes.numSampTimes = (2); /* Number of sample times */
  STP_CTL_M->Sizes.numBlocks = (5);    /* Number of blocks */
  STP_CTL_M->Sizes.numBlockIO = (1);   /* Number of block outputs */
  STP_CTL_M->Sizes.numBlockPrms = (89);/* Sum of parameter "widths" */
  return STP_CTL_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
