/**
 * @file throttle_control.h
 * @brief Control of the throttle system.
 *
 */


#ifndef _OSCC_KIA_SOUL_THROTTLE_CONTROL_H_
#define _OSCC_KIA_SOUL_THROTTLE_CONTROL_H_


#include <stdint.h>


/*
 * @brief Number of bits to shift to go from a 10-bit value to a 12-bit value.
 *
 */
#define BIT_SHIFT_10BIT_TO_12BIT (2)

/*
 * @brief Number of steps per volt corresponding to 4096 steps across 5 volts.
 *
 */
#define STEPS_PER_VOLT (819.2)

/*
 * @brief Scalar value for the low spoof signal taken from a calibration curve.
 *
 */
#define SPOOF_LOW_SIGNAL_CALIBRATION_CURVE_SCALE (0.00002)

/*
 * @brief Offset value for the low spoof signal taken from a calibration curve.
 *
 */
#define SPOOF_LOW_SIGNAL_CALIBRATION_CURVE_OFFSET (0.40)

/*
 * @brief Scalar value for the high spoof signal taken from a calibration curve.
 *
 */
#define SPOOF_HIGH_SIGNAL_CALIBRATION_CURVE_SCALE (0.00005)

/*
 * @brief Offset value for the high spoof signal taken from a calibration curve.
 *
 */
#define SPOOF_HIGH_SIGNAL_CALIBRATION_CURVE_OFFSET (0.80)

/*
 * @brief Minimum allowed value for the low spoof signal value.
 *
 */
#define SPOOF_LOW_SIGNAL_RANGE_MIN (328)

/*
 * @brief Maximum allowed value for the low spoof signal value.
 *
 */
#define SPOOF_LOW_SIGNAL_RANGE_MAX (1638)

/*
 * @brief Minimum allowed value for the high spoof signal value.
 *
 */
#define SPOOF_HIGH_SIGNAL_RANGE_MIN (656)

/*
 * @brief Maximum allowed value for the high spoof signal value.
 *
 */
#define SPOOF_HIGH_SIGNAL_RANGE_MAX (3358)

/*
 * @brief Value of the accelerator position that indicates operator override.
 *
 */

#define ACCELERATOR_OVERRIDE_THRESHOLD ( 750.0 )

/*
 * @brief Amount of time between sensor checks. [milliseconds]
 *
 */
#define SENSOR_VALIDITY_CHECK_INTERVAL_IN_MSEC ( 250 )

/*
 * @brief Number of consecutive faults that can occur when reading the
 *        sensors before control is disabled.
 *
 */
#define SENSOR_VALIDITY_CHECK_FAULT_COUNT ( 4 )

/*
 * @brief Alpha term for the exponential filter used to smooth the sensor input.
 *
 */
#define ACCELERATOR_SENSOR_EXPONENTIAL_FILTER_ALPHA ( 0.25 )


/**
 * @brief Accelerator position values.
 *
 * Contains high and low accelerator values.
 *
 */
typedef struct
{
    uint16_t low; /* Low value of accelerator position. */

    uint16_t high; /* High value of accelerator position. */
} accelerator_position_s;


/**
 * @brief Current throttle control state.
 *
 * Current state of the throttle module control system.
 *
 */
typedef struct
{
    bool enabled; /* Flag indicating whether control is currently enabled. */

    bool operator_override; /* Flag indicating whether accelerator was manually
                               pressed by operator. */

    bool invalid_sensor_value; /* Flag indicating a value read from one of the
                                  sensors is invalid. */

    uint16_t commanded_accelerator_position; /* Position of accelerator commanded
                                                by the controller. */
} kia_soul_throttle_control_state_s;


// ****************************************************************************
// Function:    check_for_operator_override
//
// Purpose:     Checks to see if the vehicle's operator has manually pressed
//              the accelerator and disables control if they have.
//
// Returns:     void
//
// Parameters:  void
//
// ****************************************************************************
void check_for_operator_override( void );


// ****************************************************************************
// Function:    check_for_sensor_faults
//
// Purpose:     Checks to see if valid values are being read from the sensors.
//
// Returns:     void
//
// Parameters:  void
//
// ****************************************************************************
void check_for_sensor_faults( void );


// ****************************************************************************
// Function:    read_accelerator_position_sensor
//
// Purpose:     Reads current value from the accelerator position sensor.
//
// Returns:     void
//
// Parameters:  [out] value - pointer to \ref accelerator_position_s that will receive
//                            the sensor values.
//
// ****************************************************************************
void read_accelerator_position_sensor(
    accelerator_position_s * const value );


// ****************************************************************************
// Function:    update_throttle
//
// Purpose:     Writes throttle spoof values to DAC.
//
// Returns:     void
//
// Parameters:  void
//
// ****************************************************************************
void update_throttle( void );


// ****************************************************************************
// Function:    enable_control
//
// Purpose:     Enable control of the throttle system.
//
// Returns:     void
//
// Parameters:  void
//
// ****************************************************************************
void enable_control( void );


// ****************************************************************************
// Function:    disable_control
//
// Purpose:     Disable control of the throttle system.
//
// Returns:     void
//
// Parameters:  void
//
// ****************************************************************************
void disable_control( void );


#endif /* _OSCC_KIA_SOUL_THROTTLE_CONTROL_H_ */
