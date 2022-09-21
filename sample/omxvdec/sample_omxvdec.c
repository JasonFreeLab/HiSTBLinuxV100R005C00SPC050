#include "omxvdec_test.h"


int main(int argc, char **argv)
{
    OMXVDEC_TEST_ATTR test_attr;
    test_attr.auto_exit = OMX_FALSE;

    return omxvdec_test(argc, argv, &test_attr);
}
