#define ATTR_ADDR 0x3c0
#define MISC_ADDR 0x3c2
#define VGAENABLE_ADDR 0x3c3
#define SEQU_ADDR 0x3c4
#define GRAC_ADDR 0x3ce
#define CRTC_ADDR 0x3d4
#define STATUS_ADDR 0x3da
#define CHIPSTECH_ADDR 0x3d6

void UnProtectCRTC(void);
unsigned char RegisterIn(int, char);
void RegisterOut(int, char, unsigned char);

void OutPortb(int, unsigned char);
void OutPortw(int, int);
unsigned char InPortb(int);
unsigned int InPortw(int);

/*
 * UnProtectCRTC()
 * Unprotects the CRTC registers so they can be modified.
 */
void UnProtectCRTC(void) {
    int v;
    OutPortb(CRTC_ADDR, 0x11);           // Index = 11h
    v = InPortb(CRTC_ADDR + 1);          // Read from 3d5h
    v = v & 0x7F;                        // Set bit 7 to 0
    OutPortb(CRTC_ADDR, 0x11);           // Index = 11h again
    OutPortw(CRTC_ADDR, 0x11 | (v << 8)); // Write to unprotect
}

/*
 * RegisterIn()
 * Returns the value contained in the specified register.
 */
unsigned char RegisterIn(int Controlador, char index) {
    unsigned char valor;

    switch (Controlador) {
        case MISC_ADDR:
            valor = InPortb(0x3cc);
            break;

        case ATTR_ADDR:
            InPortb(STATUS_ADDR);         // Reset flip-flop
            OutPortb(ATTR_ADDR, index);
            valor = InPortb(ATTR_ADDR + 1);
            break;

        case SEQU_ADDR:
        case GRAC_ADDR:
        case CRTC_ADDR:
        case CHIPSTECH_ADDR:
            OutPortb(Controlador, index); // Set index
            valor = InPortb(Controlador + 1);
            break;

        case VGAENABLE_ADDR:
        default:
            valor = InPortb(Controlador); // Default case
            break;
    }

    OutPortb(ATTR_ADDR, 0x20); // Allow screen writes
    return valor;              // Return the value
}

/*
 * RegisterOut()
 * Writes the value to the specified register.
 */
void RegisterOut(int Controlador, char index, unsigned char valor) {
    switch (Controlador) {
        case ATTR_ADDR:
            InPortb(STATUS_ADDR);  // Reset flip-flop
            OutPortb(ATTR_ADDR, index);
            OutPortb(ATTR_ADDR, valor);  // Write value
            break;

        case SEQU_ADDR:
            if (index == 1) {
                OutPortw(SEQU_ADDR, 0x0100);            // Reset sequencer
                OutPortw(SEQU_ADDR, (valor << 8) | 1);  // Write value
                OutPortw(SEQU_ADDR, 0x0300);            // Restore sequencer
                break;
            }
        case GRAC_ADDR:
        case CRTC_ADDR:
        case CHIPSTECH_ADDR:
            OutPortw(Controlador, (index | (valor << 8)));
            break;

        case MISC_ADDR:
        case VGAENABLE_ADDR:
        default:
            OutPortb(Controlador, valor);  // Write to port
            break;
    }

    OutPortb(ATTR_ADDR, 0x20);  // Allow screen writes
}

/*
 * Input and Output functions using Watcom C #pragma aux for port I/O
 */

#pragma aux InPortb =   \
    "in al, dx"         \
    parm [dx]           \
    value [al];
unsigned char InPortb(int port);


#pragma aux InPortw =   \
    "in ax, dx"         \
    parm [dx]           \
    value [ax];
unsigned int InPortw(int port);


#pragma aux OutPortb =  \
    "out dx, al"        \
    parm [dx] [al];
void OutPortb(int port, unsigned char dato);


#pragma aux OutPortw =  \
    "out dx, ax"        \
    parm [dx] [ax];
void OutPortw(int port, int dato);

