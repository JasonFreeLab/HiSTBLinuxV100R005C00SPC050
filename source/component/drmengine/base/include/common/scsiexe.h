#ifndef SCSIEXE_H_
#define SCSIEXE_H_

#include <scsi/sg.h>
#include <sys/ioctl.h>

#define SENSE_LEN   255
#define BLOCK_LEN   32
#define SCSI_TIMEOUT    20000

/***************************************************************************
 * name: init_io_hdr
 * parameter:
 * function: initialize the sg_io_hdr struct fields with the most common
 *           value
 * **************************************************************************/
struct sg_io_hdr * init_io_hdr(void);

void destroy_io_hdr(struct sg_io_hdr *);

void set_xfer_data(struct sg_io_hdr * p_hdr, void * data, unsigned int length);

void set_sense_data(struct sg_io_hdr * p_hdr, unsigned char * data,
        unsigned int length);

/***************************************************************************
 * name: execute_Inquiry
 * parameter:
 *      fd:         file descripter
 *      page_code:  cdb page code
 *      evpd:           cdb evpd
 *      p_hdr:      poiter to sg_io_hdr struct
 * function: make Inquiry cdb and execute it.
 * **************************************************************************/
int execute_Inquiry(int fd, int page_code, int evpd, struct sg_io_hdr * p_hdr);

#endif /*SCSIEXE_H_*/
