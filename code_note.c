#include "scheduler_trx.c"

const ubit_t _sched_fcch_burst[148]; // 3TB+142 Fixed Bits+3TB
const ubit_t _sched_sch_train[64];   // 3TB+39 Encrypted Bits + 64 Bit Sychronization +3TB+39 Encrypted Bits

/*! \brief FCCH Burst (TS 05.02 Chapter 5.2.4) */
const ubit_t _sched_fcch_burst[GSM_BURST_LEN] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

/*! \brief SCH training sequence (TS 05.02 Chapter 5.2.5) */
const ubit_t _sched_sch_train[64] = {
	1,0,1,1,1,0,0,1,0,1,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,
	0,0,1,0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,1,1,0,1,1,0,0,0,0,1,1,0,1,1,
};




/* obtain a to-be-transmitted SCH (synchronization channel) burst */
ubit_t *tx_sch_fn(struct l1sched_trx *l1t, uint8_t tn, uint32_t fn,
	enum trx_chan_type chan, uint8_t bid, uint16_t *nbits)
{
	static ubit_t bits[GSM_BURST_LEN], burst[78];
	uint8_t sb_info[4];
	struct	gsm_time t;
	uint8_t t3p, bsic;

	LOGL1S(DL1P, LOGL_DEBUG, l1t, tn, chan, fn, "Transmitting SCH\n");

	/* BURST BYPASS */

	/* create SB info from GSM time and BSIC */
	gsm_fn2gsmtime(&t, fn);
	t3p = t.t3 / 10;
	bsic = l1t->trx->bts->bsic;
	sb_info[0] =
		((bsic &  0x3f) << 2) |
		((t.t1 & 0x600) >> 9);
	sb_info[1] =
		((t.t1 & 0x1fe) >> 1);
	sb_info[2] =
		((t.t1 & 0x001) << 7) |
		((t.t2 &  0x1f) << 2) |
		((t3p  &   0x6) >> 1);
	sb_info[3] =
		 (t3p  &   0x1);

	/* encode bursts */
	gsm0503_sch_encode(burst, sb_info);

	/* compose burst */
	memset(bits, 0, 3);
	memcpy(bits + 3, burst, 39);
	memcpy(bits + 42, _sched_sch_train, 64);
	memcpy(bits + 106, burst + 39, 39);
	memset(bits + 145, 0, 3);

	if (nbits)
		*nbits = GSM_BURST_LEN;

	return bits;
}

/* obtain a to-be-transmitted FCCH (frequency correction channel) burst */
ubit_t *tx_fcch_fn(struct l1sched_trx *l1t, uint8_t tn, uint32_t fn,
	enum trx_chan_type chan, uint8_t bid, uint16_t *nbits)
{
	LOGL1S(DL1P, LOGL_DEBUG, l1t, tn, chan, fn, "Transmitting FCCH\n");

	if (nbits)
		*nbits = GSM_BURST_LEN;

	/* BURST BYPASS */

	return (ubit_t *) _sched_fcch_burst;
}

/*! Parse GSM Frame Number into struct \ref gsm_time
 *  \param[out] time Caller-provided memory for \ref gsm_time
 *  \param[in] fn GSM Frame Number */
void gsm_fn2gsmtime(struct gsm_time *time, uint32_t fn)
{
	time->fn = fn;
	time->t1 = time->fn / (26*51);
	time->t2 = time->fn % 26;
	time->t3 = time->fn % 51;
	time->tc = (time->fn / 51) % 8;
}

// carrier frequency offset
// sampling clock frequency offset
