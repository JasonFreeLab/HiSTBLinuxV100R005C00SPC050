#include <hiflash.h>

#include "nand_sync.h"

/******************************************************************************/

struct nand_sync_timing *nand_get_sync_timing(struct nand_sync_timing *nand_sync_timing,
					   u8 *id, int id_len)
{
	struct nand_sync_timing *best = NULL;

	for (; nand_sync_timing->id_len; nand_sync_timing++) {
		/* allow match a serial device. */
		if (nand_sync_timing->id_len > id_len ||
		    memcmp(nand_sync_timing->id, id, nand_sync_timing->id_len))
			continue;

		if (!best || best->id_len < nand_sync_timing->id_len)
			best = nand_sync_timing;
	}

	return best;
}
/******************************************************************************/

static struct nand_sync *nand_sync[] = {
	&nand_sync_toggle_v10,
	&nand_sync_toggle_v20,
	&nand_sync_onfi_v23,
	&nand_sync_onfi_v30,
	NULL,
};
/******************************************************************************/

struct nand_sync *nand_get_sync(char nand_sync_type)
{
	int ix;

	for (ix = 0; nand_sync[ix]; ix++) {
		if (nand_sync[ix]->type == nand_sync_type)
			return nand_sync[ix];
	}

	return NULL;
}
/******************************************************************************/
