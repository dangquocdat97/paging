// osmo-bts-> include -> osmo-bts -> gsm_data_shared.h
#define HARDCODED_BSIC	0x3f	/* NCC = 7 / BCC = 7   NCC:0-7, BCC: 0-7*/



struct gsmtap_hdr {
	uint8_t version;	/*!< version, set to 0x01 currently */
	uint8_t hdr_len;	/*!< length in number of 32bit words */
	uint8_t type;		/*!< see GSMTAP_TYPE_* */
	uint8_t timeslot;	/*!< timeslot (0..7 on Um) */

	uint16_t arfcn;		/*!< ARFCN (frequency) */
	int8_t signal_dbm;	/*!< signal level in dBm */
	int8_t snr_db;		/*!< signal/noise ratio in dB */

	uint32_t frame_number;	/*!< GSM Frame Number (FN) */

	uint8_t sub_type;	/*!< Type of burst/channel, see above */
	uint8_t antenna_nr;	/*!< Antenna Number */
	uint8_t sub_slot;	/*!< sub-slot within timeslot */
	uint8_t res;		/*!< reserved for future use (RFU) */

} __attribute__((packed));

// generate si message
// osmo-bsc -> src -> system_information. 
// control channel description gsm48_control_channel_descr

//libosmocore -> include -> osmocom ->gsm -> protocol -> gsm_08_58.h
#define RSL_BS_PA_MFRMS

/* Initialize those parts that don't require osmo-bsc specific dependencies.
 * This part is shared among the thin programs in osmo-bsc/src/utils/.
 * osmo-bsc requires further initialization that pulls in more dependencies (see
 * bsc_bts_alloc_register()). */
struct gsm_bts *gsm_bts_alloc(struct gsm_network *net, uint8_t bts_num)