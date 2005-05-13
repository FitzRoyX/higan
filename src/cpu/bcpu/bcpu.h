class bCPU;

class bDMA {
public:
bCPU *cpu;
struct {
//$420b
  bool   active;
//$420c
  bool   hdma_active;
//$43x0
  bool   direction;
  bool   hdma_indirect;
  int8   incmode;
  bool   fixedxfer;
  uint8  xfermode;
//$43x1
  uint8  destaddr;
//$43x2-$43x4
  uint32 srcaddr;
//$43x5-$43x6
  uint16 xfersize;
//$43x7
  uint8  hdma_indirect_bank;

//hdma-specific
  bool   hdma_first_line;
  bool   hdma_repeat;
  uint16 hdma_line_counter;
  uint32 hdma_address, hdma_iaddress;
  bool   hdma_completed;
}channel[8];
bool hdma_triggered;

  void   hdma_write(uint8 i, uint8 l, uint8 x);
  void   hdma_run();
  void   hdma_initialize();
  void   run();
  void   reset();
  uint16 dma_cputommio(uint8 i, uint8 index);
  uint16 dma_mmiotocpu(uint8 i, uint8 index);
  void   dma_xfer_type0(uint8 i);
  void   dma_xfer_type1(uint8 i);
  void   dma_xfer_type2(uint8 i);
  void   dma_xfer_type3(uint8 i);
  void   dma_xfer_type4(uint8 i);
  void   dma_xfer_type5(uint8 i);

  bDMA(bCPU *_cpu);
};

class bCPUMMIO : public MMIO {
public:
bCPU *cpu;
  uint8 read (uint32 addr);
  void  write(uint32 addr, uint8 value);
  bCPUMMIO(bCPU *_cpu);
};

class bCPU : public CPU {
public:
enum { CPUSTATE_RUN = 0, CPUSTATE_DMA, CPUSTATE_WAI, CPUSTATE_STP };
uint8 cpustate;

bDMA *dma;
  enum {
    OPMODE_ADDR = 1, OPMODE_LONG = 2,
    OPMODE_DBR  = 3, OPMODE_PBR  = 4,
    OPMODE_DP   = 5, OPMODE_SP   = 6
  };
CPUReg24 aa, rd;
uint8    dp, sp;

struct {
  bool   nmi_triggered;
  bool   nmi_pin;
  bool   r4210_read;

  bool   irq_triggered;
  bool   irq_pin;

//$2181-$2183
  uint32 wram_addr;

//$4016
  uint8  joypad1_strobe_value;
  uint8  joypad1_read_pos;

//$4200
  bool   nmi_enabled;
  bool   hirq_enabled, virq_enabled;
  bool   auto_joypad_poll;

//$4201
  uint8  pio;

//$4202-$4203
  uint8  mul_a, mul_b;

//$4204-$4206
  uint16 div_a;
  uint8  div_b;

//$4207-$420a
  uint16 hirq_pos, virq_pos;

//$4214-$4216
  uint16 r4214;
  uint16 r4216;
}status;

  uint8 pio_status();
  void  irq(uint16 addr);
  void  run();
  void  scanline();
  void  frame();
  void  power();
  void  reset();

//mmio commands
  void  mmio_reset();
  uint8 mmio_r2180();
  uint8 mmio_r21c2();
  uint8 mmio_r21c3();
  uint8 mmio_r4016();
  uint8 mmio_r4210();
  uint8 mmio_r4211();
  uint8 mmio_r4212();
  uint8 mmio_r4213();
  uint8 mmio_r4214();
  uint8 mmio_r4215();
  uint8 mmio_r4216();
  uint8 mmio_r4217();
  uint8 mmio_r4218();
  uint8 mmio_r4219();
  void  mmio_w2180(uint8 value);
  void  mmio_w2181(uint8 value);
  void  mmio_w2182(uint8 value);
  void  mmio_w2183(uint8 value);
  void  mmio_w4016(uint8 value);
  void  mmio_w4200(uint8 value);
  void  mmio_w4201(uint8 value);
  void  mmio_w4202(uint8 value);
  void  mmio_w4203(uint8 value);
  void  mmio_w4204(uint8 value);
  void  mmio_w4205(uint8 value);
  void  mmio_w4206(uint8 value);
  void  mmio_w4207(uint8 value);
  void  mmio_w4208(uint8 value);
  void  mmio_w4209(uint8 value);
  void  mmio_w420a(uint8 value);
  void  mmio_w420b(uint8 value);
  void  mmio_w420c(uint8 value);
  void  mmio_w420d(uint8 value);
  void  mmio_w43x0(uint8 value, uint8 i);
  void  mmio_w43x1(uint8 value, uint8 i);
  void  mmio_w43x2(uint8 value, uint8 i);
  void  mmio_w43x3(uint8 value, uint8 i);
  void  mmio_w43x4(uint8 value, uint8 i);
  void  mmio_w43x5(uint8 value, uint8 i);
  void  mmio_w43x6(uint8 value, uint8 i);
  void  mmio_w43x7(uint8 value, uint8 i);

  void  exec_opcode();

  uint8 op_read ();
  uint8 op_read (uint8 mode, uint32 addr);
  void  op_write(uint8 mode, uint32 addr, uint8 value);
  uint8 stack_read ();
  void  stack_write(uint8 value);

//cpu extra-cycle conditions
  void cpu_c2();
  void cpu_c4(uint16 a, uint16 b);
  void cpu_c6(uint16 a);
  void cpu_io();

//op_adc
  void flags_adc_b();
  void flags_adc_w();
  void op_adc_constb();
  void op_adc_constw();
  void op_adc_const();
  void op_adc_addrb();
  void op_adc_addrw();
  void op_adc_addr();
  void op_adc_addrxb();
  void op_adc_addrxw();
  void op_adc_addrx();
  void op_adc_dpb();
  void op_adc_dpw();
  void op_adc_dp();
  void op_adc_idpb();
  void op_adc_idpw();
  void op_adc_idp();
  void op_adc_ildpb();
  void op_adc_ildpw();
  void op_adc_ildp();
  void op_adc_longb();
  void op_adc_longw();
  void op_adc_long();
  void op_adc_longxb();
  void op_adc_longxw();
  void op_adc_longx();
  void op_adc_addryb();
  void op_adc_addryw();
  void op_adc_addry();
  void op_adc_dpxb();
  void op_adc_dpxw();
  void op_adc_dpx();
  void op_adc_idpxb();
  void op_adc_idpxw();
  void op_adc_idpx();
  void op_adc_idpyb();
  void op_adc_idpyw();
  void op_adc_idpy();
  void op_adc_ildpyb();
  void op_adc_ildpyw();
  void op_adc_ildpy();
  void op_adc_srb();
  void op_adc_srw();
  void op_adc_sr();
  void op_adc_isryb();
  void op_adc_isryw();
  void op_adc_isry();
//op_and
  void flags_and_b();
  void flags_and_w();
  void op_and_constb();
  void op_and_constw();
  void op_and_const();
  void op_and_addrb();
  void op_and_addrw();
  void op_and_addr();
  void op_and_addrxb();
  void op_and_addrxw();
  void op_and_addrx();
  void op_and_dpb();
  void op_and_dpw();
  void op_and_dp();
  void op_and_idpb();
  void op_and_idpw();
  void op_and_idp();
  void op_and_ildpb();
  void op_and_ildpw();
  void op_and_ildp();
  void op_and_longb();
  void op_and_longw();
  void op_and_long();
  void op_and_longxb();
  void op_and_longxw();
  void op_and_longx();
  void op_and_addryb();
  void op_and_addryw();
  void op_and_addry();
  void op_and_dpxb();
  void op_and_dpxw();
  void op_and_dpx();
  void op_and_idpxb();
  void op_and_idpxw();
  void op_and_idpx();
  void op_and_idpyb();
  void op_and_idpyw();
  void op_and_idpy();
  void op_and_ildpyb();
  void op_and_ildpyw();
  void op_and_ildpy();
  void op_and_srb();
  void op_and_srw();
  void op_and_sr();
  void op_and_isryb();
  void op_and_isryw();
  void op_and_isry();
//op_cmp
  void flags_cmp_b();
  void flags_cmp_w();
  void op_cmp_constb();
  void op_cmp_constw();
  void op_cmp_const();
  void op_cmp_addrb();
  void op_cmp_addrw();
  void op_cmp_addr();
  void op_cmp_addrxb();
  void op_cmp_addrxw();
  void op_cmp_addrx();
  void op_cmp_dpb();
  void op_cmp_dpw();
  void op_cmp_dp();
  void op_cmp_idpb();
  void op_cmp_idpw();
  void op_cmp_idp();
  void op_cmp_ildpb();
  void op_cmp_ildpw();
  void op_cmp_ildp();
  void op_cmp_longb();
  void op_cmp_longw();
  void op_cmp_long();
  void op_cmp_longxb();
  void op_cmp_longxw();
  void op_cmp_longx();
  void op_cmp_addryb();
  void op_cmp_addryw();
  void op_cmp_addry();
  void op_cmp_dpxb();
  void op_cmp_dpxw();
  void op_cmp_dpx();
  void op_cmp_idpxb();
  void op_cmp_idpxw();
  void op_cmp_idpx();
  void op_cmp_idpyb();
  void op_cmp_idpyw();
  void op_cmp_idpy();
  void op_cmp_ildpyb();
  void op_cmp_ildpyw();
  void op_cmp_ildpy();
  void op_cmp_srb();
  void op_cmp_srw();
  void op_cmp_sr();
  void op_cmp_isryb();
  void op_cmp_isryw();
  void op_cmp_isry();
//op_eor
  void flags_eor_b();
  void flags_eor_w();
  void op_eor_constb();
  void op_eor_constw();
  void op_eor_const();
  void op_eor_addrb();
  void op_eor_addrw();
  void op_eor_addr();
  void op_eor_addrxb();
  void op_eor_addrxw();
  void op_eor_addrx();
  void op_eor_dpb();
  void op_eor_dpw();
  void op_eor_dp();
  void op_eor_idpb();
  void op_eor_idpw();
  void op_eor_idp();
  void op_eor_ildpb();
  void op_eor_ildpw();
  void op_eor_ildp();
  void op_eor_longb();
  void op_eor_longw();
  void op_eor_long();
  void op_eor_longxb();
  void op_eor_longxw();
  void op_eor_longx();
  void op_eor_addryb();
  void op_eor_addryw();
  void op_eor_addry();
  void op_eor_dpxb();
  void op_eor_dpxw();
  void op_eor_dpx();
  void op_eor_idpxb();
  void op_eor_idpxw();
  void op_eor_idpx();
  void op_eor_idpyb();
  void op_eor_idpyw();
  void op_eor_idpy();
  void op_eor_ildpyb();
  void op_eor_ildpyw();
  void op_eor_ildpy();
  void op_eor_srb();
  void op_eor_srw();
  void op_eor_sr();
  void op_eor_isryb();
  void op_eor_isryw();
  void op_eor_isry();
//op_incdec
  void op_incb();
  void op_incw();
  void op_inc();
  void op_inc_addrb();
  void op_inc_addrw();
  void op_inc_addr();
  void op_inc_addrxb();
  void op_inc_addrxw();
  void op_inc_addrx();
  void op_inc_dpb();
  void op_inc_dpw();
  void op_inc_dp();
  void op_inc_dpxb();
  void op_inc_dpxw();
  void op_inc_dpx();
  void op_inxb();
  void op_inxw();
  void op_inx();
  void op_inyb();
  void op_inyw();
  void op_iny();
  void op_decb();
  void op_decw();
  void op_dec();
  void op_dec_addrb();
  void op_dec_addrw();
  void op_dec_addr();
  void op_dec_addrxb();
  void op_dec_addrxw();
  void op_dec_addrx();
  void op_dec_dpb();
  void op_dec_dpw();
  void op_dec_dp();
  void op_dec_dpxb();
  void op_dec_dpxw();
  void op_dec_dpx();
  void op_dexb();
  void op_dexw();
  void op_dex();
  void op_deyb();
  void op_deyw();
  void op_dey();
//op_lda
  void flags_lda_b();
  void flags_lda_w();
  void op_lda_constb();
  void op_lda_constw();
  void op_lda_const();
  void op_lda_addrb();
  void op_lda_addrw();
  void op_lda_addr();
  void op_lda_addrxb();
  void op_lda_addrxw();
  void op_lda_addrx();
  void op_lda_dpb();
  void op_lda_dpw();
  void op_lda_dp();
  void op_lda_idpb();
  void op_lda_idpw();
  void op_lda_idp();
  void op_lda_ildpb();
  void op_lda_ildpw();
  void op_lda_ildp();
  void op_lda_longb();
  void op_lda_longw();
  void op_lda_long();
  void op_lda_longxb();
  void op_lda_longxw();
  void op_lda_longx();
  void op_lda_addryb();
  void op_lda_addryw();
  void op_lda_addry();
  void op_lda_dpxb();
  void op_lda_dpxw();
  void op_lda_dpx();
  void op_lda_idpxb();
  void op_lda_idpxw();
  void op_lda_idpx();
  void op_lda_idpyb();
  void op_lda_idpyw();
  void op_lda_idpy();
  void op_lda_ildpyb();
  void op_lda_ildpyw();
  void op_lda_ildpy();
  void op_lda_srb();
  void op_lda_srw();
  void op_lda_sr();
  void op_lda_isryb();
  void op_lda_isryw();
  void op_lda_isry();
//op_misc
  void flags_bit_b();
  void flags_bit_w();
  void op_bit_constb();
  void op_bit_constw();
  void op_bit_const();
  void op_bit_addrb();
  void op_bit_addrw();
  void op_bit_addr();
  void op_bit_addrxb();
  void op_bit_addrxw();
  void op_bit_addrx();
  void op_bit_dpb();
  void op_bit_dpw();
  void op_bit_dp();
  void op_bit_dpxb();
  void op_bit_dpxw();
  void op_bit_dpx();
  void flags_cpx_b();
  void flags_cpx_w();
  void op_cpx_constb();
  void op_cpx_constw();
  void op_cpx_const();
  void op_cpx_addrb();
  void op_cpx_addrw();
  void op_cpx_addr();
  void op_cpx_dpb();
  void op_cpx_dpw();
  void op_cpx_dp();
  void flags_cpy_b();
  void flags_cpy_w();
  void op_cpy_constb();
  void op_cpy_constw();
  void op_cpy_const();
  void op_cpy_addrb();
  void op_cpy_addrw();
  void op_cpy_addr();
  void op_cpy_dpb();
  void op_cpy_dpw();
  void op_cpy_dp();
  void flags_ldx_b();
  void flags_ldx_w();
  void op_ldx_constb();
  void op_ldx_constw();
  void op_ldx_const();
  void op_ldx_addrb();
  void op_ldx_addrw();
  void op_ldx_addr();
  void op_ldx_addryb();
  void op_ldx_addryw();
  void op_ldx_addry();
  void op_ldx_dpb();
  void op_ldx_dpw();
  void op_ldx_dp();
  void op_ldx_dpyb();
  void op_ldx_dpyw();
  void op_ldx_dpy();
  void flags_ldy_b();
  void flags_ldy_w();
  void op_ldy_constb();
  void op_ldy_constw();
  void op_ldy_const();
  void op_ldy_addrb();
  void op_ldy_addrw();
  void op_ldy_addr();
  void op_ldy_addrxb();
  void op_ldy_addrxw();
  void op_ldy_addrx();
  void op_ldy_dpb();
  void op_ldy_dpw();
  void op_ldy_dp();
  void op_ldy_dpxb();
  void op_ldy_dpxw();
  void op_ldy_dpx();
  void op_stx_addrb();
  void op_stx_addrw();
  void op_stx_addr();
  void op_stx_dpb();
  void op_stx_dpw();
  void op_stx_dp();
  void op_stx_dpyb();
  void op_stx_dpyw();
  void op_stx_dpy();
  void op_sty_addrb();
  void op_sty_addrw();
  void op_sty_addr();
  void op_sty_dpb();
  void op_sty_dpw();
  void op_sty_dp();
  void op_sty_dpxb();
  void op_sty_dpxw();
  void op_sty_dpx();
  void op_stz_addrb();
  void op_stz_addrw();
  void op_stz_addr();
  void op_stz_addrxb();
  void op_stz_addrxw();
  void op_stz_addrx();
  void op_stz_dpb();
  void op_stz_dpw();
  void op_stz_dp();
  void op_stz_dpxb();
  void op_stz_dpxw();
  void op_stz_dpx();
  void op_xba();
  void op_trb_addrb();
  void op_trb_addrw();
  void op_trb_addr();
  void op_trb_dpb();
  void op_trb_dpw();
  void op_trb_dp();
  void op_tsb_addrb();
  void op_tsb_addrw();
  void op_tsb_addr();
  void op_tsb_dpb();
  void op_tsb_dpw();
  void op_tsb_dp();
  void op_mvn();
  void op_mvp();
  void op_brk();
  void op_cop();
  void op_stp();
  void op_wai();
  void op_xce();
  void op_nop();
  void op_wdm();
  void op_clc();
  void op_cld();
  void op_cli();
  void op_clv();
  void op_sec();
  void op_sed();
  void op_sei();
  void op_rep();
  void op_sep();
  void op_taxb();
  void op_taxw();
  void op_tax();
  void op_tayb();
  void op_tayw();
  void op_tay();
  void op_tcd();
  void op_tcs();
  void op_tdc();
  void op_tsc();
  void op_tsxb();
  void op_tsxw();
  void op_tsx();
  void op_txab();
  void op_txaw();
  void op_txa();
  void op_txsb();
  void op_txsw();
  void op_txs();
  void op_txyb();
  void op_txyw();
  void op_txy();
  void op_tyab();
  void op_tyaw();
  void op_tya();
  void op_tyxb();
  void op_tyxw();
  void op_tyx();
//op_ora
  void flags_ora_b();
  void flags_ora_w();
  void op_ora_constb();
  void op_ora_constw();
  void op_ora_const();
  void op_ora_addrb();
  void op_ora_addrw();
  void op_ora_addr();
  void op_ora_addrxb();
  void op_ora_addrxw();
  void op_ora_addrx();
  void op_ora_dpb();
  void op_ora_dpw();
  void op_ora_dp();
  void op_ora_idpb();
  void op_ora_idpw();
  void op_ora_idp();
  void op_ora_ildpb();
  void op_ora_ildpw();
  void op_ora_ildp();
  void op_ora_longb();
  void op_ora_longw();
  void op_ora_long();
  void op_ora_longxb();
  void op_ora_longxw();
  void op_ora_longx();
  void op_ora_addryb();
  void op_ora_addryw();
  void op_ora_addry();
  void op_ora_dpxb();
  void op_ora_dpxw();
  void op_ora_dpx();
  void op_ora_idpxb();
  void op_ora_idpxw();
  void op_ora_idpx();
  void op_ora_idpyb();
  void op_ora_idpyw();
  void op_ora_idpy();
  void op_ora_ildpyb();
  void op_ora_ildpyw();
  void op_ora_ildpy();
  void op_ora_srb();
  void op_ora_srw();
  void op_ora_sr();
  void op_ora_isryb();
  void op_ora_isryw();
  void op_ora_isry();
//op_pc
  void op_jmp_addr();
  void op_jmp_long();
  void op_jmp_iaddr();
  void op_jmp_iaddrx();
  void op_jmp_iladdr();
  void op_jsr_addr();
  void op_jsr_long();
  void op_jsr_iaddrx();
  void op_rtie();
  void op_rtin();
  void op_rti();
  void op_rts();
  void op_rtl();
  void op_bra();
  void op_brl();
  void op_bcc();
  void op_bcs();
  void op_bne();
  void op_beq();
  void op_bpl();
  void op_bmi();
  void op_bvc();
  void op_bvs();
//op_sbc
  void flags_sbc_b();
  void flags_sbc_w();
  void op_sbc_constb();
  void op_sbc_constw();
  void op_sbc_const();
  void op_sbc_addrb();
  void op_sbc_addrw();
  void op_sbc_addr();
  void op_sbc_addrxb();
  void op_sbc_addrxw();
  void op_sbc_addrx();
  void op_sbc_dpb();
  void op_sbc_dpw();
  void op_sbc_dp();
  void op_sbc_idpb();
  void op_sbc_idpw();
  void op_sbc_idp();
  void op_sbc_ildpb();
  void op_sbc_ildpw();
  void op_sbc_ildp();
  void op_sbc_longb();
  void op_sbc_longw();
  void op_sbc_long();
  void op_sbc_longxb();
  void op_sbc_longxw();
  void op_sbc_longx();
  void op_sbc_addryb();
  void op_sbc_addryw();
  void op_sbc_addry();
  void op_sbc_dpxb();
  void op_sbc_dpxw();
  void op_sbc_dpx();
  void op_sbc_idpxb();
  void op_sbc_idpxw();
  void op_sbc_idpx();
  void op_sbc_idpyb();
  void op_sbc_idpyw();
  void op_sbc_idpy();
  void op_sbc_ildpyb();
  void op_sbc_ildpyw();
  void op_sbc_ildpy();
  void op_sbc_srb();
  void op_sbc_srw();
  void op_sbc_sr();
  void op_sbc_isryb();
  void op_sbc_isryw();
  void op_sbc_isry();
//op_shift
  void op_aslb();
  void op_aslw();
  void op_asl();
  void op_asl_addrb();
  void op_asl_addrw();
  void op_asl_addr();
  void op_asl_addrxb();
  void op_asl_addrxw();
  void op_asl_addrx();
  void op_asl_dpb();
  void op_asl_dpw();
  void op_asl_dp();
  void op_asl_dpxb();
  void op_asl_dpxw();
  void op_asl_dpx();
  void op_lsrb();
  void op_lsrw();
  void op_lsr();
  void op_lsr_addrb();
  void op_lsr_addrw();
  void op_lsr_addr();
  void op_lsr_addrxb();
  void op_lsr_addrxw();
  void op_lsr_addrx();
  void op_lsr_dpb();
  void op_lsr_dpw();
  void op_lsr_dp();
  void op_lsr_dpxb();
  void op_lsr_dpxw();
  void op_lsr_dpx();
  void op_rolb();
  void op_rolw();
  void op_rol();
  void op_rol_addrb();
  void op_rol_addrw();
  void op_rol_addr();
  void op_rol_addrxb();
  void op_rol_addrxw();
  void op_rol_addrx();
  void op_rol_dpb();
  void op_rol_dpw();
  void op_rol_dp();
  void op_rol_dpxb();
  void op_rol_dpxw();
  void op_rol_dpx();
  void op_rorb();
  void op_rorw();
  void op_ror();
  void op_ror_addrb();
  void op_ror_addrw();
  void op_ror_addr();
  void op_ror_addrxb();
  void op_ror_addrxw();
  void op_ror_addrx();
  void op_ror_dpb();
  void op_ror_dpw();
  void op_ror_dp();
  void op_ror_dpxb();
  void op_ror_dpxw();
  void op_ror_dpx();
//op_sta
  void op_sta_addrb();
  void op_sta_addrw();
  void op_sta_addr();
  void op_sta_addrxb();
  void op_sta_addrxw();
  void op_sta_addrx();
  void op_sta_dpb();
  void op_sta_dpw();
  void op_sta_dp();
  void op_sta_idpb();
  void op_sta_idpw();
  void op_sta_idp();
  void op_sta_ildpb();
  void op_sta_ildpw();
  void op_sta_ildp();
  void op_sta_longb();
  void op_sta_longw();
  void op_sta_long();
  void op_sta_longxb();
  void op_sta_longxw();
  void op_sta_longx();
  void op_sta_addryb();
  void op_sta_addryw();
  void op_sta_addry();
  void op_sta_dpxb();
  void op_sta_dpxw();
  void op_sta_dpx();
  void op_sta_idpxb();
  void op_sta_idpxw();
  void op_sta_idpx();
  void op_sta_idpyb();
  void op_sta_idpyw();
  void op_sta_idpy();
  void op_sta_ildpyb();
  void op_sta_ildpyw();
  void op_sta_ildpy();
  void op_sta_srb();
  void op_sta_srw();
  void op_sta_sr();
  void op_sta_isryb();
  void op_sta_isryw();
  void op_sta_isry();
//op_stack
  void op_phab();
  void op_phaw();
  void op_pha();
  void op_phb();
  void op_phd();
  void op_phk();
  void op_php();
  void op_phxb();
  void op_phxw();
  void op_phx();
  void op_phyb();
  void op_phyw();
  void op_phy();
  void op_plab();
  void op_plaw();
  void op_pla();
  void op_plb();
  void op_pld();
  void op_plp();
  void op_plxb();
  void op_plxw();
  void op_plx();
  void op_plyb();
  void op_plyw();
  void op_ply();
  void op_pea();
  void op_pei();
  void op_per();

  bCPU();
  ~bCPU();
};
