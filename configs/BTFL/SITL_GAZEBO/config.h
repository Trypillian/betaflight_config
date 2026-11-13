/*
 * This file is part of Betaflight.
 *
 * Betaflight is free software. You can redistribute this software
 * and/or modify this software under the terms of the GNU General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later
 * version.
 *
 * Betaflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define FC_TARGET_MCU       SITL

#define BOARD_NAME          SITL_GAZEBO
#define MANUFACTURER_ID     BTFL

// Gazebo Harmonic (BetaflightPlugin) bridge:
//   - quaternion pre-multiplied by Rz(π/2)
//   - gyro Z kept positive (FRD frame from sensor)
//   - GPS position mirrored around spawn origin
//   - barometric pressure derived from altitude (plugin doesn't supply pressure)
#define ENABLE_GAZEBO_BRIDGE    1

// The sim models (iris, quad10) carry the standard QuadX directions, M0/M3 cw
// and M1/M2 ccw, so yaw is not reversed. This was 1 for as long as the bridge
// handed Betaflight an inverted yaw rate: the two cancelled, the flight
// controller stayed self-consistent, and only the pilot's stick was backwards.
// The bridge now delivers yaw correctly (see sitl_gyro.h), so this must be 0 --
// setting one without the other makes heading hold diverge.
#define YAW_MOTORS_REVERSED     0

// Flight plan / GPX waypoint integration with the Gazebo world
#define USE_FLIGHT_PLAN

// FPV trainer: carry the stock OSD in this SITL build so the real Betaflight
// OSD can be streamed to the simulator's FPV viewer over MSP DisplayPort,
// exactly as a digital VTX would carry it.
//
// Two defines, because they do different jobs. common_pre.h skips its whole
// OSD section for SITL builds, so USE_OSD has to be asserted here, from a
// header that is included before it; once it is, common_pre.h's own
// "#if defined(USE_OSD)" block cascades USE_CMS, USE_MSP_DISPLAYPORT,
// USE_OSD_OVER_MSP_DISPLAYPORT and the SD/HD canvases for free. target.h is
// included later still and would strip OSD and CMS straight back out, so
// SITL_ENABLE_OSD is the flag that tells it not to. Stock SITL defines
// neither and is untouched.
#define SITL_ENABLE_OSD         1
#define USE_OSD

// Stock hook in io/serial.c: this port gets FUNCTION_VTX_MSP|FUNCTION_MSP,
// which config.c then picks as the DisplayPort serial. UART2 is tcp://127.0.0.1:5762,
// leaving 5761 for MSP/CLI -- cliMode is global and latches, which blocks arming,
// so the OSD feed must not share that port.
#define MSP_DISPLAYPORT_UART    SERIAL_PORT_UART2

// Attitude comes straight from the simulator's quaternion, not from the Mahony
// estimator, because the gyro this bridge hands Betaflight is in a LEFT-handed
// triad and no estimator can integrate that correctly.
//
// Measured against Gazebo truth (scratchpad gyroaxes): BF receives
// (+p, +q, -r) where truth body rates are (p, q, r) -- exactly one axis
// inverted, which is a reflection rather than a rotation. It arises because
// the bridge converts FLU->FRD ({x,-y,-z}, proper) and sitl_gyro.h's
// sitlGyroBodyFromSim then applies (+,-,+) of its own, which is improper; the
// y negations cancel and the z one does not. Neither of the bridge's frame
// modes can compose to something right-handed, because the improper half is
// on Betaflight's side.
//
// Integration in a reflected triad is exact for rotation about ONE axis and
// wrong for any combination, which is precisely the observed symptom: single
// axis angle steps tracked to 0.3 deg, while a sustained roll+yaw -- an orbit
// -- left the estimate frozen at roll 7.8 deg while the craft truly swung to
// -25 deg, a 34 deg error. ANGLE mode then holds a horizon that is not there
// and the aircraft departs; ACRO never consults the estimate, which is why it
// flies normally.
//
// target.h's switch for this is SITL_ATTITUDE_DIRECT (it undefines
// USE_IMU_CALC); sitl.c then feeds imuSetAttitudeQuat() the FDM quaternion,
// which it converts with a documented, proper rotation. config.h is included
// before target.h, so defining it here reaches that #if. The rate loops keep
// using the gyro as before -- they are self-consistent with the mixer, which
// is why the aircraft was always stable despite the bad horizon.
//
// Stock SITL does not define this and is unaffected.
#define SITL_ATTITUDE_DIRECT
