/**
 * @file dvc1124_afe.h
 * @brief Devechip DVC1124-1 21S Battery Analog Front-End Driver
 * @note I2C Slave Address 0x40 (Write) / 0x41 (Read), 100kHz, CRC8
 */

#ifndef __DVC1124_AFE_H__
#define __DVC1124_AFE_H__

#include <stdint.h>
#include <stdbool.h>

#define DVC1124_I2C_ADDR_WRITE       0x40
#define DVC1124_I2C_ADDR_READ        0x41
#define DVC1124_I2C_7BIT_ADDR        0x20

/* DVC1124 Internal Register Map */
#define DVC_REG_CELL1_V_HI           0x00
#define DVC_REG_CELL1_V_LO           0x01
/* ... Cells 1 to 24 span registers 0x00 - 0x2F (2 bytes per cell) ... */
#define DVC_REG_CURRENT_HI           0x30
#define DVC_REG_CURRENT_LO           0x31
#define DVC_REG_TEMP1_HI             0x34
#define DVC_REG_TEMP1_LO             0x35
#define DVC_REG_MOS_CTRL             0x40
#define DVC_REG_BAL_CTRL1            0x44  /* Balance cells 1-8 */
#define DVC_REG_BAL_CTRL2            0x45  /* Balance cells 9-16 */
#define DVC_REG_BAL_CTRL3            0x46  /* Balance cells 17-24 */
#define DVC_REG_SYS_STATUS           0x50

/* MOSFET Control Bits */
#define DVC_MOS_CHG_EN               (1 << 0)
#define DVC_MOS_DSG_EN               (1 << 1)
#define DVC_MOS_PCHG_EN              (1 << 2)
#define DVC_MOS_PDSG_EN              (1 << 3)

/* Driver Function Prototypes */
bool dvc1124_init(void);
bool dvc1124_read_cell_voltages(uint16_t *cell_mv, uint8_t cell_count);
bool dvc1124_read_pack_current(int32_t *current_ma);
bool dvc1124_read_temperatures(int16_t *temps_c, uint8_t count, int16_t *mos_temp);
bool dvc1124_set_balancing(uint32_t cell_mask);
bool dvc1124_set_fet_output(bool chg_on, bool dsg_on);
uint8_t dvc1124_calc_crc8(const uint8_t *data, uint16_t len);

#endif /* __DVC1124_AFE_H__ */
