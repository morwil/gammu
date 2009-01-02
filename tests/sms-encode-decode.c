#include <gammu.h>
#include "sms-printing.h"

int main(int argc UNUSED, char** argv UNUSED) {
	GSM_MultiSMSMessage		sms;
    GSM_Error               error;
	GSM_MultiPartSMSInfo	SMSInfo;
    unsigned char           Buffer[800];

	GSM_ClearMultiPartSMSInfo(&SMSInfo);
	SMSInfo.EntriesNum		= 1;

    EncodeUnicode(Buffer,
            ".........1.........2.........3.........4.........5.........6.........7.........8.........9........0"
            ".........1.........2.........3.........4.........5.........6.........7.........8.........9........0"
            ".........1.........2.........3.........4.........5.........6.........7.........8.........9........0"
            , 300);
    SMSInfo.Entries[0].Buffer  		= Buffer;
    SMSInfo.Entries[0].ID			= SMS_ConcatenatedTextLong;
    SMSInfo.UnicodeCoding   		= false;
    error = GSM_EncodeMultiPartSMS(NULL, &SMSInfo,&sms);

    /* Just set some values to sender so that we don't print mess */
    EncodeUnicode(sms.SMS[0].Number, "321", GSM_MAX_NUMBER_LENGTH);
    EncodeUnicode(sms.SMS[1].Number, "321", GSM_MAX_NUMBER_LENGTH);

    if (error != ERR_NONE) {
        printf("GSM_EncodeMultiPartSMS failed!\n");
        return 1;
    }

	/* Display message */
	DisplayTestSMS(sms);

    return 0;
}
