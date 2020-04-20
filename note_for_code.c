//osmo-bts -> src -> common -> bts.c
int bts_ccch_copy_msg(struct gsm_bts *bts, uint8_t *out_buf, struct gsm_time *gt,
		      int is_ag_res)

// check ham sau trong file osmo-bts -> src -> common ->paging.c
int paging_gen_msg(struct paging_state *ps, uint8_t *out_buf, struct gsm_time *gt,
		   int *is_empty)
// can xem ham paging link den dau - co the la osmo-bts -> src -> ->common->scheduler.c

paging_gen_msg() => bts_ccch_copy_msg() => l1sap_ph_rts_ind() => l1sap_up()
//--------------------------------------------------------------
rc = l1sap_ph_rts_ind(trx, l1sap, &l1sap->u.data);  // l1sap_up


else if (L1SAP_IS_CHAN_AGCH_PCH(chan_nr)) {
		p = msgb_put(msg, GSM_MACBLOCK_LEN);
		rc = bts_ccch_copy_msg(trx->bts, p, &g_time,    //l1sap_ph_rts_ind
				       (L1SAP_FN2CCCHBLOCK(fn) <
					num_agch(trx, "PH-RTS-IND")));
		if (rc <= 0)
			memcpy(p, fill_frame, GSM_MACBLOCK_LEN);
	}

if (!is_ag_res)
		rc = paging_gen_msg(btsb->paging_state, out_buf, gt, &is_empty);  // bts_ccch_copy_msg
//---------------------------------------------------------------

int bts_ccch_copy_msg(struct gsm_bts *bts, uint8_t *out_buf, struct gsm_time *gt,
		      int is_ag_res)
rc = bts_ccch_copy_msg(trx->bts, p, &g_time,
				       (L1SAP_FN2CCCHBLOCK(fn) <
					num_agch(trx, "PH-RTS-IND")));

#define L1SAP_FN2CCCHBLOCK(fn) ((fn % 51) / 5 - 1)
//--------------------------------------------------------------


uint8_t num_agch(struct gsm_bts_trx *trx, const char * arg)
{
	struct gsm_bts *b = trx->bts;
	struct gsm48_system_information_type_3 *si3;
	if (GSM_BTS_HAS_SI(b, SYSINFO_TYPE_3)) {
		si3 = GSM_BTS_SI(b, SYSINFO_TYPE_3);
		return si3->control_channel_desc.bs_ag_blks_res;
	}
	LOGP(DL1P, LOGL_ERROR, "%s: Unable to determine actual BS_AG_BLKS_RES "
	     "value as SI3 is not available yet\n", arg);
	return INVALID_BS_AG_BLKS_RES;
}

//-----------------------------------------------------------------
/* generate paging message for given gsm time */
int paging_gen_msg(struct paging_state *ps, uint8_t *out_buf, struct gsm_time *gt,
		   int *is_empty)
rc = paging_gen_msg(btsb->paging_state, out_buf, gt, &is_empty);


// file sau define function de gui du lieu tu bts osmo-bts->src->osmo-bts-trx->scheduler.trx.c
// Tx khong co NB, ma chi co FB va SB, cung k co CCCH ma chi co TCH ?

 // MAC/RLC block trong gsm luon luon gom 23 byte

// Mot so function can luu y khi lam lien quan den paging
/* get paging block index over multiple 51 multiframes */
static int get_pag_subch_nr(struct paging_state *ps, struct gsm_time *gt);

/*! Test whether a linked list is empty.
 *  \param[in] head the llist to test.
 *  \returns 1 if the list is empty, 0 otherwise.
 */
static inline int llist_empty(const struct llist_head *head)
{
	return head->next == head;
}

//------------------------------------
//osmo-bts ->src -> osmo-bts-trx -> scheduler_trx.c
// file tren define cac ham gui/nhan cac kenh, tu fcch, sch, data...