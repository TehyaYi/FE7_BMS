/*!
LTC2666: 16-Channel SPI 16-/12-Bit +/-10V Vout SoftSpan DACs with 10ppm/C Max Reference

@verbatim

The LTC2666 is a family of 16-channel, 12/16-bit +/-10V digital-to-analog converters with integrated
precision references. They are guaranteed monotonic and have built-in rail-to-rail output buffers.
These SoftSpan DACs offer five output ranges up to +/-10V. The range of each channel is independently
programmable, or the part can be hardware-configured for operation in a fixed range.

The integrated 2.5V reference is buffered separately to each channel; an external reference can be used
for additional range options. The LTC2666 also includes toggle capability - alternating codes via the
software toggle command, or by providing a free-running clock to the TGP pin.

The SPI/Microwire-compatible 3-wire serial interface operates on logic levels as low as 1.71V, at clock
rates up to 50MHz.


 SPI DATA FORMAT (MSB First):

 24-Bit Load Sequence:

              Byte #1                       Byte #2                       Byte #3
              Command                   MSB                             LSB
 LTC2666-16 : C3 C2 C1 C0 A3 A2 A1 A0   D15 D14 D13 D12 D11 D10 D9 D8   D7 D6 D5 D4 D3 D2 D1 D0
 LTC2666-12 : C3 C2 C1 C0 A3 A2 A1 A0   D11 D10 D9  D8  D7  D6  D5 D4   D3 D2 D1 D0 X  X  X  X

 32-Bit Load Sequence:
              Byte #1                       Byte #2                       Byte #3                 Byte #4
              Command                   MSB                             LSB
 LTC2666-16 : X  X  X  X  X  X  X  X    C3 C2 C1 C0 A3 A2 A1 A0   D15 D14 D13 D12 D11 D10 D9 D8   D7 D6 D5 D4 D3 D2 D1 D0
 LTC2666-12 : X  X  X  X  X  X  X  X    C3 C2 C1 C0 A3 A2 A1 A0   D11 D10 D9  D8  D7  D6  D5 D4   D3 D2 D1 D0 X  X  X  X

 Cx   : DAC Command Code
 Ax   : DAC Address (0 to F, corresponding to DAC 0 to DAC 15)
 Dx   : DAC Data Bits
 X    : Don't care

@endverbatim
 
REVISION HISTORY
$Revision: 3232 $
$Date: 2015-03-05 13:19:03 -0800 (Thu, 05 Mar 2015) $

Copyright (c) 2013, Linear Technology Corp.(LTC)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of Linear Technology Corp.

The Linear Technology Linduino is not affiliated with the official Arduino team.
However, the Linduino is only possible because of the Arduino team's commitment 
to the open-source community.  Please, visit http://www.arduino.cc and 
http://store.arduino.cc , and consider a purchase that will help fund their 
ongoing work.
*/

/*! @file
    @ingroup LTC2666
    LTC2666 16-Channel SPI 16-/12-Bit +/-10V Vout SoftSpan DACs with 10ppm/C Max Reference
*/

#ifndef LTC2666_H
#define LTC2666_H

//! Define the SPI CS pin
#ifndef LTC2666_CS
#define LTC2666_CS QUIKEVAL_CS //! SPI Chip Select Pin
#endif

//! @name LTC2666 Command Codes
//! OR'd together with the DAC address to form the command byte
#define  LTC2666_CMD_WRITE_N              0x00  //!< Write to input register n
#define  LTC2666_CMD_UPDATE_N             0x10  //!< Update (power up) DAC register n
#define  LTC2666_CMD_WRITE_N_UPDATE_ALL   0x20  //!< Write to input register n, update (power-up) all
#define  LTC2666_CMD_WRITE_N_UPDATE_N     0x30  //!< Write to input register n, update (power-up) 
#define  LTC2666_CMD_POWER_DOWN_N         0x40  //!< Power down n
#define  LTC2666_CMD_POWER_DOWN_ALL       0x50  //!< Power down chip (all DAC's, MUX and reference)

#define  LTC2666_CMD_SPAN                 0x60  //!< Write span to dac n
#define  LTC2666_CMD_CONFIG               0x70  //!< Configure reference / toggle
#define  LTC2666_CMD_WRITE_ALL            0x80  //!< Write to all input registers
#define  LTC2666_CMD_UPDATE_ALL           0x90  //!< Update all DACs
#define  LTC2666_CMD_WRITE_ALL_UPDATE_ALL 0xA0  //!< Write to all input reg, update all DACs
#define  LTC2666_CMD_MUX                  0xB0  //!< Select MUX channel (controlled by 5 LSbs in data word)
#define  LTC2666_CMD_TOGGLE_SEL           0xC0  //!< Select which DACs can be toggled (via toggle pin or global toggle bit)
#define  LTC2666_CMD_GLOBAL_TOGGLE        0xD0  //!< Software toggle control via global toggle bit
#define  LTC2666_CMD_SPAN_ALL             0xE0  //!< Set span for all DACs
#define  LTC2666_CMD_NO_OPERATION         0xF0  //!< No operation
//! @}

//! @name LTC2666 Span Codes
//! @{
//! Descriptions are valid for a 2.5V reference.
//! These can also be interpreted as 0 to 2*Vref, 0 to 4*Vref, etc.
//! when an external reference other than 2.5V is used.
#define  LTC2666_SPAN_0_TO_5V             0x0000
#define  LTC2666_SPAN_0_TO_10V            0x0001
#define  LTC2666_SPAN_PLUS_MINUS_5V       0x0002
#define  LTC2666_SPAN_PLUS_MINUS_10V      0x0003
#define  LTC2666_SPAN_PLUS_MINUS_2V5      0x0004
//! @}

//! @name LTC2666 Minimums and Maximums for each Span
//! @{
//! Lookup tables for minimum and maximum outputs for a given span
const float LTC2666_MIN_OUTPUT[5] = {0.0, 0.0, -5.0, -10.0, -2.5};
const float LTC2666_MAX_OUTPUT[5] = {5.0, 10.0, 5.0, 10.0, 2.5};
//! @}

//! @name LTC2666 Configuration options
//! @{
//! Used in conjunction with LTC2666_CMD_CONFIG command
#define  LTC2666_REF_DISABLE              0x0001  //! Disable internal reference to save power when using an ext. ref.
#define  LTC2666_THERMAL_SHUTDOWN         0x0002  //! Disable thermal shutdown (NOT recommended)
//! @}

//! @name LTC2666 MUX enable
//! @{
//! Used in conjunction with LTC2666_CMD_MUX command
#define  LTC2666_MUX_DISABLE              0x0000  //! Disable MUX
#define  LTC2666_MUX_ENABLE               0x0010  //! Enable MUX, OR with MUX channel to be monitored
//! @}

//! @name LTC2666 Global Toggle
//! @{
//! Used in conjunction with LTC2666_CMD_GLOBAL_TOGGLE command, affects DACs whose
//! Toggle Select bits have been set to 1
#define  LTC2666_TOGGLE_REG_A              0x0000  //! Update DAC with register A
#define  LTC2666_TOGGLE_REG_B              0x0010  //! Update DAC with register B
//! @}

//! Write the 16-bit dac_code to the LTC2666
//! @return Zero if readback (SDO) data matches the value previously sent, One if mismatched (indicating data error somewhere)
int8_t LTC2666_write(uint8_t cs, uint8_t dac_command, uint8_t dac_address, uint16_t dac_code);

//! Calculate a LTC2666 DAC code given the desired output voltage and DAC address (0-3)
//! @return The 16 bit code to send to the DAC
uint16_t LTC2666_voltage_to_code(float dac_voltage, float min_output, float max_output);

//! Calculate the LTC2666 DAC output voltage given the DAC code, offset, and LSB
//! @return the output voltage
float LTC2666_code_to_voltage(uint16_t dac_code, float min_output, float max_output);

#endif  // LTC2666_H
