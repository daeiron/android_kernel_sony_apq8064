/*
 * Copyright(c) 2012, Analogix Semiconductor. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef __SP_TX_DRV_H
#define __SP_TX_DRV_H

/*#define D(fmt, arg...) printk("<1>```%s:%d: " fmt, __func__, __LINE__, ##arg)*/

#define MAX_BUF_CNT 6
#define DVI_MODE 0x00
#define HDMI_MODE 0x01
#define VIDEO_STABLE_TH 3
#define AUDIO_STABLE_TH 1
#define SCDT_EXPIRE_TH 10
#define SP_TX_HDCP_FAIL_THRESHOLD         10

extern unchar bEDID_extblock[128];
extern unchar bEDID_firstblock[128];

enum SP_TX_System_State {
	SP_TX_INITIAL = 1,
	SP_TX_WAIT_SLIMPORT_PLUGIN,
	SP_TX_PARSE_EDID,
	SP_TX_CONFIG_HDMI_INPUT,
	SP_TX_LINK_TRAINING,
	SP_TX_CONFIG_SLIMPORT_OUTPUT,
	SP_TX_HDCP_AUTHENTICATION,
	SP_TX_PLAY_BACK
};

enum HDMI_RX_System_State {
	HDMI_CLOCK_DET = 1,
	HDMI_SYNC_DET,
	HDMI_VIDEO_CONFIG,
	HDMI_AUDIO_CONFIG,
	HDMI_PLAYBACK
};

enum HDMI_color_depth {
	Hdmi_legacy,
	Hdmi_24bit,
	Hdmi_30bit,
	Hdmi_36bit
};
enum SP_TX_POWER_BLOCK {
	SP_TX_PWR_REG,
	SP_TX_PWR_HDCP,
	SP_TX_PWR_AUDIO,
	SP_TX_PWR_VIDEO,
	SP_TX_PWR_LINK,
	SP_TX_PWR_TOTAL
};

enum SP_TX_SEND_MSG {
	MSG_OCM_EN,
	MSG_INPUT_HDMI,
	MSG_INPUT_DVI,
	MSG_LINK_TRAINING,
	MSG_CLEAR_IRQ,
};

enum PACKETS_TYPE {
	AVI_PACKETS,
	SPD_PACKETS,
	MPEG_PACKETS,
	VSI_PACKETS
};

struct Packet_AVI {
	unchar AVI_data[13];
};

struct Packet_SPD {
	unchar SPD_data[13];
};

struct Packet_MPEG {
	unchar MPEG_data[13];
};

struct AudiInfoframe {
	unchar type;
	unchar version;
	unchar length;
	unchar pb_byte[11];
};

enum INTStatus {
	COMMON_INT_1 = 0,
	COMMON_INT_2 = 1,
	COMMON_INT_3 = 2,
	COMMON_INT_4 = 3,
	SP_INT_STATUS = 6
};

enum SP_LINK_BW {
	BW_54G = 0x14,
	BW_27G = 0x0A,
	BW_162G = 0x06,
	BW_NULL = 0x00
};

void sp_tx_variable_init(void);
void sp_tx_initialization(void);
void sp_tx_show_infomation(void);
void sp_tx_power_down(enum SP_TX_POWER_BLOCK sp_tx_pd_block);
void sp_tx_power_on(enum SP_TX_POWER_BLOCK sp_tx_pd_block);
void sp_tx_avi_setup(void);
void sp_tx_clean_hdcp(void);
unchar sp_tx_chip_located(void);
void sp_tx_vbus_poweron(void);
void sp_tx_vbus_powerdown(void);
void sp_tx_rst_aux(void);
void sp_tx_config_packets(enum PACKETS_TYPE bType);
unchar sp_tx_hw_link_training(void);
unchar sp_tx_lt_pre_config(void);
void sp_tx_video_mute(unchar enable);
void sp_tx_set_colorspace(void);
void sp_tx_set_3d_packets(void);
void sp_tx_int_irq_handler(void);
void sp_tx_send_message(enum SP_TX_SEND_MSG message);
void sp_tx_hdcp_process(void);
void sp_tx_set_system_state(enum SP_TX_System_State ss);
unchar sp_tx_get_cable_type(void);
unchar sp_tx_get_dp_connection(void);
unchar sp_tx_get_hdmi_connection(void);
unchar sp_tx_get_vga_connection(void);
void sp_tx_edid_read(void);
uint sp_tx_link_err_check(void);
void sp_tx_eye_diagram_test(void);

/* ***************************************************************** */
/* Functions protoype for HDMI Input */
/* ***************************************************************** */

void sp_tx_config_hdmi_input(void);
void hdmi_rx_set_hpd(unchar Enable);
void hdmi_rx_tmds_en(void);
void hdmi_rx_initialize(void);
void hdmi_rx_int_irq_handler(void);
void hdmi_rx_set_termination(unchar Enable);

#endif