// D:\Core\Documents\GitHub\Macropad-V2\Macropad V2 Code\HID Descriptor Basic.h


char ReportDescriptor[48] = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x07,                    // USAGE (Keypad)
    0xa1, 0x01,                    // COLLECTION (Application)
    0xa1, 0x00,                    //   COLLECTION (Physical)
    0x05, 0x09,                    //     USAGE_PAGE (Button)
    0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
    0x29, 0x1e,                    //     USAGE_MAXIMUM (Button 30)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
    0x95, 0x1e,                    //     REPORT_COUNT (30)
    0x75, 0x01,                    //     REPORT_SIZE (1)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x75, 0x02,                    //     REPORT_SIZE (2)
    0x81, 0x03,                    //     INPUT (Cnst,Var,Abs)
    0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
    0x09, 0x38,                    //     USAGE (Wheel)
    0x16, 0x00, 0x80,              //     LOGICAL_MINIMUM (-32768)
    0x26, 0xff, 0x7f,              //     LOGICAL_MAXIMUM (32767)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x75, 0x10,                    //     REPORT_SIZE (16)
    0x81, 0x06,                    //     INPUT (Data,Var,Rel)
    0xc0,                          //   END_COLLECTION
    0xc0                           // END_COLLECTION
};

